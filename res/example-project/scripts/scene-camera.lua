function init(entity)
    -- define speed of camera movement and rotation
    self.translationSpeed = 2.0
    self.rotationSpeed = 1.0
end

function update(entity, dt)
    -- change pitch of camera
    if(Input.GetButtonDown(Key.Down))
    then
        local pitch = entity:GetTransform().rotation.x - self.rotationSpeed * dt

        if (pitch > 89.0)
        then
            pitch = 89.0
        end

        if (pitch < -89.0)
        then
            pitch = -89.0
        end

        entity:GetTransform().rotation.x = pitch
    end

    if(Input.GetButtonDown(Key.Up))
    then
        local pitch = entity:GetTransform().rotation.x + self.rotationSpeed * dt

        if (pitch > 89.0)
        then
            pitch = 89.0
        end

        if (pitch < -89.0)
        then
            pitch = -89.0
        end

        entity:GetTransform().rotation.x = pitch
    end

    -- change yaw of camera
    if(Input.GetButtonDown(Key.Left))
    then
        local yaw = entity:GetTransform().rotation.y - self.rotationSpeed * dt
        entity:GetTransform().rotation.y = yaw
    end

    if(Input.GetButtonDown(Key.Right))
    then
        local yaw = entity:GetTransform().rotation.y + self.rotationSpeed * dt
        entity:GetTransform().rotation.y = yaw
    end

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
        dPosition.y = -1.0
    end

    -- move camera up
    if(Input.GetButtonDown(Key.Space))
    then
        dPosition.y = 1.0
    end

    -- TODO: normalize dPosition vector

    dPosition = dPosition * self.translationSpeed * dt

    -- update position of entity
    newPosition = entityPosition + dPosition
    entity:GetTransform().position = newPosition
end

