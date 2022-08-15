//
// Created by Deepak Ramalingam on 8/6/22.
//

#ifndef DEEPSENGINE_SPHEREMESH_H
#define DEEPSENGINE_SPHEREMESH_H

#include "PrimitiveMesh.h"

namespace DeepsEngine {
    class SphereMesh : public PrimitiveMesh {
    public:
        SphereMesh();
        void Finalize();
    };
}

#endif //DEEPSENGINE_SPHEREMESH_H
