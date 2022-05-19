//
// Created by Deepak Ramalingam on 5/18/22.
//

#include "Animator.h"
#include "Application.h"
#include "Entity.h"
#include "Component.h"

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

        if (bonesList.find(nodeName) == bonesList.end()) {
            // bone is not in set
            bonesList.insert(nodeName);

            // TODO: pass down parent entity
            DeepsEngine::Entity linkEntity = Application::getInstance().scene.findEntityByGuid("52e57bab-334a-46ac-a26a-69362743323a");

            DeepsEngine::Entity boneEntity = Application::getInstance().scene.CreateEntity(nodeName);
            boneEntity.GetComponent<DeepsEngine::Component::Transform>().isBone = true;
            boneEntity.GetComponent<DeepsEngine::Component::Transform>().overrideModelMatrix = parentTransform * nodeTransform;

            boneEntityMap.insert(std::make_pair(nodeName, boneEntity.entity));

            linkEntity.GetComponent<DeepsEngine::Component::HierarchyComponent>().addChild(boneEntity);

            // TODO: remove this hardcoded part
            DeepsEngine::Entity boxEntity = Application::getInstance().scene.findEntityByGuid("d8f6b582-f8d0-4c25-a1a4-7ddcf79ca0eq");

            if (nodeName == "mixamorig:Head") {
                Logger::Error("Attaching box here");
                Logger::Warn(glm::to_string(Bone->GetLocalTransform()));
                boneEntity.GetComponent<DeepsEngine::Component::HierarchyComponent>().addChild(boxEntity);
            }
        } else {
            entt::entity boneEntityHandle = boneEntityMap[nodeName];
            auto boneEntity = DeepsEngine::Entity(boneEntityHandle);
            boneEntity.GetComponent<DeepsEngine::Component::Transform>().overrideModelMatrix = parentTransform * nodeTransform;
        }

//        if (boneMap.count(nodeName) <= 0) {
//            DeepsEngine::Entity boxEntity = Application::getInstance().scene.findEntityByGuid("d8f6b582-f8d0-4c25-a1a4-7ddcf79ca0e0");
//            DeepsEngine::Entity linkEntity = Application::getInstance().scene.findEntityByGuid("52e57bab-334a-46ac-a26a-69362743323a");
//
//            boneMap.insert(std::make_pair(nodeName, Bone));
//            DeepsEngine::Entity boneEntity = Application::getInstance().scene.CreateEntity(nodeName);
//            Bone->entity = &(boneEntity);
//            Bone->entity->GetComponent<DeepsEngine::Component::Transform>().isBone = true;
//            Bone->entity->GetComponent<DeepsEngine::Component::Transform>().overrideModelMatrix = nodeTransform;
//
//            linkEntity.GetComponent<DeepsEngine::Component::HierarchyComponent>().addChild(*(Bone->entity));
//
//            if (nodeName == "mixamorig:RightHand_$AssimpFbx$_Rotation") {
//                Logger::Error("Attaching box here");
//                Logger::Warn(glm::to_string(Bone->GetLocalTransform()));
//                Bone->entity->GetComponent<DeepsEngine::Component::HierarchyComponent>().addChild(boxEntity);
//            }
//        }
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
