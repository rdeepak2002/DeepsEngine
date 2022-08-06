//
// Created by Deepak Ramalingam on 8/5/22.
//

#ifndef DEEPSENGINE_PRIMITIVEMESH_H
#define DEEPSENGINE_PRIMITIVEMESH_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "OpenGLRenderer.h"

namespace DeepsEngine {
    class PrimitiveMesh {
    public:
        std::vector<glm::vec3> Positions;
        std::vector<glm::vec2> UV;
        std::vector<glm::vec3> Normals;
        unsigned int VAO = 0;
        unsigned int VBO = 0;
    public:
        PrimitiveMesh();
    };
}

#endif //DEEPSENGINE_PRIMITIVEMESH_H
