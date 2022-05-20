function init(entity)

end

function update(entity, dt)
    if(Input.GetButtonDown(Key.P))
    then
        entity:GetMeshFilter():setMeshPath("src/models/link_fbx/Dancing.fbx")
    end
end