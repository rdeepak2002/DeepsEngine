//
// Created by Deepak Ramalingam on 5/5/22.
//

#include "DeepsMath.h"
#include "glm/trigonometric.hpp"

glm::vec3 DeepsMath::normalizeVec3(glm::vec3 vec) {
    if (glm::length(vec) == 0) {
        return {};
    }
    return glm::normalize(vec);
}

float DeepsMath::degreesToRadians(float degrees) {
    return glm::radians(degrees);
}
