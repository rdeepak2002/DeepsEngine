function init(entity)
    Logger.Debug("On init in lua")
    self.translationSpeed = 2.0
    self.rotationSpeed = 1.0
end

function update(entity, dt)
    -- camera rotation
    if(Input.GetButtonDown(Key.Down))
    then
        entity:GetTransform().rotation.x = entity:GetTransform().rotation.x - self.rotationSpeed * dt
    end

    if(Input.GetButtonDown(Key.Up))
    then
        entity:GetTransform().rotation.x = entity:GetTransform().rotation.x + self.rotationSpeed * dt
    end

    if(Input.GetButtonDown(Key.Left))
    then
        entity:GetTransform().rotation.y = entity:GetTransform().rotation.y - self.rotationSpeed * dt
    end

    if(Input.GetButtonDown(Key.Right))
    then
        entity:GetTransform().rotation.y = entity:GetTransform().rotation.y + self.rotationSpeed * dt
    end

    if(Input.GetButtonDown(Key.S))
    then
        entity:GetTransform().position.z = entity:GetTransform().position.z + self.translationSpeed * dt
    end

    if(Input.GetButtonDown(Key.W))
    then
        entity:GetTransform().position.z = entity:GetTransform().position.z - self.translationSpeed * dt
    end

    if(Input.GetButtonDown(Key.A))
    then
        entity:GetTransform().position.x = entity:GetTransform().position.x - self.translationSpeed * dt
    end

    if(Input.GetButtonDown(Key.D))
    then
        entity:GetTransform().position.x = entity:GetTransform().position.x + self.translationSpeed * dt
    end
end

