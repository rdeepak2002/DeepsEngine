//
// Created by Deepak Ramalingam on 5/18/22.
//

#include "Animator.h"
#include "Application.h"
#include "Entity.h"
#include "Component.h"
#include <glm/gtx/matrix_decompose.hpp>

void Animator::CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform)
{
    std::string nodeName = node->name;
    glm::mat4 nodeTransform = node->transformation;

//    Logger::Warn("Node name: ");
//    Logger::Warn(nodeName);

    Bone* Bone = m_CurrentAnimation->FindBone(nodeName);

    if (Bone)
    {
        Bone->Update(m_CurrentTime);
        nodeTransform = Bone->GetLocalTransform();

        glm::mat4 globalTransformation = parentTransform * nodeTransform;

        glm::vec3 scale;
        glm::quat rotation;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(globalTransformation, scale, rotation, translation, skew, perspective);

        if (bonesList.find(nodeName) == bonesList.end()) {
            // bone is not in set
            bonesList.insert(nodeName);

            // TODO: only do Create Entity if you cannot find entity
            DeepsEngine::Entity boneEntity = Application::getInstance().scene.CreateEntity(nodeName);
            // TODO: set guid to parent id with node name appended

            boneEntity.GetComponent<DeepsEngine::Component::Transform>().position = translation;
            boneEntity.GetComponent<DeepsEngine::Component::Transform>().rotation = glm::eulerAngles(rotation);
            boneEntity.GetComponent<DeepsEngine::Component::Transform>().scale = scale;

            boneEntityMap.insert(std::make_pair(nodeName, boneEntity.entity));

            DeepsEngine::Entity thisEntity = Application::getInstance().scene.findEntityByGuid(entityGuid);
            thisEntity.GetComponent<DeepsEngine::Component::HierarchyComponent>().addChild(boneEntity);

            // TODO: remove this hardcoded part where we attach the box entity to the head
            DeepsEngine::Entity boxEntity = Application::getInstance().scene.findEntityByGuid("d8f6b582-f8d0-4c25-a1a4-7ddcf79ca0eq");
            std::string headBone = "mixamorig::Head";
            std::string leftHandBone = "mixamorig:LeftHandMiddle2_$AssimpFbx$_Rotation";
            std::string rightHandBone = "mixamorig:RightHandMiddle2_$AssimpFbx$_Rotation";

            if (nodeName == rightHandBone) {
                boneEntity.GetComponent<DeepsEngine::Component::HierarchyComponent>().addChild(boxEntity);
            }
        } else {
            entt::entity boneEntityHandle = boneEntityMap[nodeName];
            auto boneEntity = DeepsEngine::Entity(boneEntityHandle);

            boneEntity.GetComponent<DeepsEngine::Component::Transform>().position = translation;
            boneEntity.GetComponent<DeepsEngine::Component::Transform>().rotation = glm::eulerAngles(rotation);
            boneEntity.GetComponent<DeepsEngine::Component::Transform>().scale = scale;
        }
    }

    glm::mat4 globalTransformation = parentTransform * nodeTransform;

    auto boneInfoMap = m_CurrentAnimation->GetBoneIDMap();
    if (boneInfoMap.find(nodeName) != boneInfoMap.end())
    {
        int index = boneInfoMap[nodeName].id;
        glm::mat4 offset = boneInfoMap[nodeName].offset;
        m_FinalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);
}
