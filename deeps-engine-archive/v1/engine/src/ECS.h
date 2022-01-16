//
// Created by Deepak Ramalingam on 12/29/21.
//

#ifndef CORE_ECS_H
#define CORE_ECS_H

#include <iostream>
#include <glm.hpp>

// A simple type alias
using Entity = std::uint32_t;

// Used to define the size of arrays later on
const Entity MAX_ENTITIES = 255;

// A simple type alias
using ComponentType = std::uint8_t;

// Used to define the size of arrays later on
const ComponentType MAX_COMPONENTS = 32;

// A simple type alias
using Signature = std::bitset<MAX_COMPONENTS>;

struct Vec3 {
    double x;
    double y;
    double z;
};

struct Gravity {
    Vec3 force;
};

struct RigidBody {
    Vec3 velocity;
    Vec3 acceleration;
};

struct Transform {
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;
};

#endif //CORE_ECS_H
