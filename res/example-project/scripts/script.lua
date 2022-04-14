function onCreate(entity)
    print("On create function")
    entity:GetTransform().position.x = 2.0
end

function onUpdate(entity, dt)
    print("On update function")
    print(dt)
end