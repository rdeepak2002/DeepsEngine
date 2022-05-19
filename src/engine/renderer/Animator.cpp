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

        std::string boneEntityGuid = entityGuid + "-node-" + nodeName;

        if (bonesList.find(nodeName) == bonesList.end()) {
            // bone is not in set
            bonesList.insert(nodeName);

            if (Application::getInstance().scene.entityExists(boneEntityGuid)) {
                // use existing bone entity
                DeepsEngine::Entity boneEntity = Application::getInstance().scene.findEntityByGuid(boneEntityGuid);

                boneEntity.GetComponent<DeepsEngine::Component::Transform>().position = translation;
                boneEntity.GetComponent<DeepsEngine::Component::Transform>().rotation = glm::vec3(glm::radians(glm::eulerAngles(rotation).x), glm::radians(glm::eulerAngles(rotation).y), glm::radians(glm::eulerAngles(rotation).z));
                boneEntity.GetComponent<DeepsEngine::Component::Transform>().scale = scale;

                DeepsEngine::Entity thisEntity = Application::getInstance().scene.findEntityByGuid(entityGuid);
                thisEntity.GetComponent<DeepsEngine::Component::HierarchyComponent>().addChild(boneEntity);
            } else {
                // remove existing bone entity
                DeepsEngine::Entity boneEntity = Application::getInstance().scene.CreateEntity(nodeName, boneEntityGuid);

                boneEntity.GetComponent<DeepsEngine::Component::Transform>().position = translation;
                boneEntity.GetComponent<DeepsEngine::Component::Transform>().rotation = glm::vec3(glm::radians(glm::eulerAngles(rotation).x), glm::radians(glm::eulerAngles(rotation).y), glm::radians(glm::eulerAngles(rotation).z));
                boneEntity.GetComponent<DeepsEngine::Component::Transform>().scale = scale;

                DeepsEngine::Entity thisEntity = Application::getInstance().scene.findEntityByGuid(entityGuid);
                thisEntity.GetComponent<DeepsEngine::Component::HierarchyComponent>().addChild(boneEntity);
            }
        } else {
            auto boneEntity = Application::getInstance().scene.findEntityByGuid(boneEntityGuid);

            boneEntity.GetComponent<DeepsEngine::Component::Transform>().position = translation;
            boneEntity.GetComponent<DeepsEngine::Component::Transform>().rotation = glm::vec3(glm::radians(glm::eulerAngles(rotation).x), glm::radians(glm::eulerAngles(rotation).y), glm::radians(glm::eulerAngles(rotation).z));
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
