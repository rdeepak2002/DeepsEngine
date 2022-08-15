//
// Created by Deepak Ramalingam on 8/5/22.
//

#ifndef DEEPSENGINE_CUBEMESH_H
#define DEEPSENGINE_CUBEMESH_H

#include "PrimitiveMesh.h"

namespace DeepsEngine {
    class CubeMesh : public PrimitiveMesh {
    public:
        CubeMesh();
        void Finalize();
    };
}

#endif //DEEPSENGINE_CUBEMESH_H
