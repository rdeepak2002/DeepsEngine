function onCreate(self)
    Logger.Debug("On create function")
    self:GetTransform().position.x = 2.0
end

function onUpdate(self, dt)
    Logger.Debug("Update function")
    Logger.Debug(tostring(dt))
end