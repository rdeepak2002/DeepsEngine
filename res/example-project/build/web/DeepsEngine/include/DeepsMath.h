//
// Created by Deepak Ramalingam on 5/5/22.
//

#ifndef DEEPSENGINE_DEEPSMATH_H
#define DEEPSENGINE_DEEPSMATH_H

#include "glm/fwd.hpp"
#include "glm/geometric.hpp"

class DeepsMath {
public:
    static glm::vec3 normalizeVec3(glm::vec3 vec);
    static float degreesToRadians(float degrees);
private:
    DeepsMath() = default;
public:
    DeepsMath(DeepsMath const&) = delete;
    void operator=(DeepsMath const&) = delete;
};


#endif //DEEPSENGINE_DEEPSMATH_H
