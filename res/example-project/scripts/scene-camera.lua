function init(entity)
    -- define speed of camera movement and rotation
    self.translationSpeed = 2.0
    self.rotationSpeed = 1.0
    self.maxPitch = DeepsMath.degreesToRadians(89.0)
    self.minPitch = DeepsMath.degreesToRadians(-89.0)
end

function update(entity, dt)
    updateRotation(entity, dt)
    updateTranslation(entity, dt)
end

function updateRotation(entity, dt)
    -- change pitch of camera
    local dRotation = vec3.new(0.0, 0.0, 0.0)

    if(Input.GetButtonDown(Key.Down))
    then
        dRotation = dRotation - vec3.new(1.0,0.0,0.0)
    end

    if(Input.GetButtonDown(Key.Up))
    then
        dRotation = dRotation - vec3.new(-1.0,0.0,0.0)
    end

    -- change yaw of camera
    if(Input.GetButtonDown(Key.Left))
    then
        dRotation = dRotation - vec3.new(0.0,1.0,0.0)
    end

    if(Input.GetButtonDown(Key.Right))
    then
        dRotation = dRotation - vec3.new(0.0,-1.0,0.0)
    end

    -- normalize dRotation vector before multiplying by speed and change in time
    dRotation = DeepsMath.normalizeVec3(dRotation) * self.rotationSpeed * dt
    newRotation = entity:GetTransform().rotation + dRotation

    -- keep pitch within boundaries to prevent weird camera behavior
    if (newRotation.x > self.maxPitch)
    then
        newRotation.x = self.maxPitch
    end

    if (newRotation.x < self.minPitch)
    then
        newRotation.x = self.minPitch
    end

    -- update rotation of entity
    entity:GetTransform().rotation = newRotation
end

function updateTranslation(entity, dt)
    -- variables for translation
    local entityTransform = entity:GetTransform()
    local entityPosition = vec3.new(entity:GetTransform().position.x, entity:GetTransform().position.y, entity:GetTransform().position.z)
    local entityFront = entityTransform:front()
    local entityRight = entityTransform:right()
    local dPosition = vec3.new(0.0, 0.0, 0.0)

    -- move camera back
    if(Input.GetButtonDown(Key.S))
    then
        dPosition = dPosition - entityFront
    end

    -- move camera forward
    if(Input.GetButtonDown(Key.W))
    then
        dPosition = dPosition + entityFront
    end

    -- move camera left
    if(Input.GetButtonDown(Key.A))
    then
        dPosition = dPosition - entityRight
    end

    -- move camera right
    if(Input.GetButtonDown(Key.D))
    then
        dPosition = dPosition + entityRight
    end

    -- reset dPosition y to 0 to simulate minecraft movement
    dPosition.y = 0.0   -- dont change y position to make controls like minecraft

    -- move camera down
    if(Input.GetButtonDown(Key.LeftShift))
    then
        dPosition.y = dPosition.y - 1.0
    end

    -- move camera up
    if(Input.GetButtonDown(Key.Space))
    then
        dPosition.y = dPosition.y + 1.0
    end

    -- normalize dPosition vector before multiplying by speed and change in time
    dPosition = DeepsMath.normalizeVec3(dPosition) * self.translationSpeed * dt

    -- update position of entity
    newPosition = entityPosition + dPosition
    entity:GetTransform().position = newPosition
end