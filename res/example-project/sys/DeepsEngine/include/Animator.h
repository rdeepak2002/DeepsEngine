//
// Created by Deepak Ramalingam on 5/15/22.
//

#ifndef DEEPSENGINE_ANIMATOR_H
#define DEEPSENGINE_ANIMATOR_H

#pragma once

#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <Animation.h>
#include <Bone.h>
#include <entt/entt.hpp>

class Animator
{
public:
    Animator(Animation* animation, std::string entityGuid)
    {
        this->entityGuid = entityGuid;
        m_CurrentTime = 0.0;
        m_CurrentAnimation = animation;

        m_FinalBoneMatrices.reserve(100);

        for (int i = 0; i < 100; i++)
            m_FinalBoneMatrices.push_back(glm::mat4(1.0f));
    }

    void UpdateAnimation(float dt);

    void PlayAnimation(Animation* pAnimation)
    {
        m_CurrentAnimation = pAnimation;
        m_CurrentTime = 0.0f;
    }

    void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);

    std::vector<glm::mat4> GetFinalBoneMatrices()
    {
        return m_FinalBoneMatrices;
    }

private:
    std::vector<glm::mat4> m_FinalBoneMatrices;
    Animation* m_CurrentAnimation;
    float m_CurrentTime;
    float m_DeltaTime;
    std::unordered_set<std::string> bonesList;
    std::string entityGuid;
};

#endif //DEEPSENGINE_ANIMATOR_H
