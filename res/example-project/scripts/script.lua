local totalTime = 0.0

function onCreate(self)
    Logger.Debug("On Create")
    -- TODO: fix issue where on create is randomly called which causes rotation stutter
    -- self:GetTransform().rotation.y = 0.0
end

function onUpdate(self, dt)
    totalTime = totalTime + dt
    Logger.Debug("Total time in script:")
    Logger.Debug(tostring(totalTime))
    self:GetTransform().rotation.y = self:GetTransform().rotation.y + 1.0 * dt
end