function init(entity)
    Logger.Debug("On init in lua")
    self.speed = 1.0
end

function update(entity, dt)
    if(Input.GetButtonDown(Key.W))
    then
        entity:GetTransform().position.z = entity:GetTransform().position.z - self.speed * dt
    end

    if(Input.GetButtonDown(Key.S))
    then
        entity:GetTransform().position.z = entity:GetTransform().position.z + self.speed * dt
    end
end

