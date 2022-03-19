//
// Created by Deepak Ramalingam on 2/4/22.
//

#ifndef OPENGLCUBE_COMPONENTS_H
#define OPENGLCUBE_COMPONENTS_H

#include <iostream>

namespace DeepsEngine::Component {
        struct Id {
            u_int32_t id;
        };

        struct Tag {
            std::string name;
        };

        struct Position {
            float x;
            float y;
            float z;
        };

        struct Rotation {
            float x;
            float y;
            float z;
        };

        struct Scale {
            float x;
            float y;
            float z;
        };

        struct Transform {
            Position position;
            Rotation rotation;
            Scale scale;
        };
    }

#endif  // OPENGLCUBE_COMPONENTS_H
