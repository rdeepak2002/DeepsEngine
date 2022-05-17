//
// Created by Deepak Ramalingam on 5/15/22.
//

#ifndef DEEPSENGINE_ANIMDATA_H
#define DEEPSENGINE_ANIMDATA_H

#pragma once

#include<glm/glm.hpp>

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;

    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;

};
#pragma once

#endif //DEEPSENGINE_ANIMDATA_H
