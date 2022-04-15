function onCreate(self)
    self:GetTransform().rotation.y = 0.0
end

function onUpdate(self, dt)
    self:GetTransform().rotation.y = self:GetTransform().rotation.y + 1.0 * dt
end