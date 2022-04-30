function init(entity)
    Logger.Debug("On init in lua")
    self.totalTime = 0.0
    entity:GetTransform().rotation.y = 1.0
end

function update(entity, dt)
     Logger.Debug("On update in lua")
     self.totalTime = self.totalTime + dt
     Logger.Debug(tostring(self.totalTime))
     entity:GetTransform().rotation.y = entity:GetTransform().rotation.y + 1.0 * dt
end

function destroy(entity)
    Logger.Debug("On destroy in lua")
end
