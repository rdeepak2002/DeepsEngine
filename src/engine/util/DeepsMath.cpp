//
// Created by Deepak Ramalingam on 5/5/22.
//

#include "DeepsMath.h"
#include <iostream>

glm::vec3 DeepsMath::normalizeVec3(glm::vec3 vec) {
    if (glm::length(vec) == 0) {
        return {};
    }
    return glm::normalize(vec);
}
