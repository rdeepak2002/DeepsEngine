//
// Created by Deepak Ramalingam on 2/4/22.
//

#ifndef OPENGLCUBE_COMPONENTS_H
#define OPENGLCUBE_COMPONENTS_H

#include <iostream>

namespace DeepsEngine::Component {
        struct Component {

        };

        struct Id : public Component {
            Id() = default;
            Id(uint32_t id) {
                this->id = id;
            }
            uint32_t id;
        };

        struct Tag : public Component {
            Tag() = default;
            Tag(std::string tag) {
                this->tag = tag;
            }
            std::string tag;
        };

        struct Position : public Component {
            Position() = default;
            Position(float x, float y, float z) {
                this->x = x;
                this->y = y;
                this->z = z;
            }
            float x;
            float y;
            float z;
        };

        struct Rotation : public Component {
            Rotation() = default;
            Rotation(float x, float y, float z) {
                this->x = x;
                this->y = y;
                this->z = z;
            }
            float x;
            float y;
            float z;
        };

        struct Scale : public Component {
            Scale() = default;
            Scale(float x, float y, float z) {
                this->x = x;
                this->y = y;
                this->z = z;
            }
            float x;
            float y;
            float z;
        };

        struct Transform : public Component {
            Transform() = default;
            Transform(Position position, Rotation rotation, Scale scale) {
                this->position = position;
                this->rotation = rotation;
                this->scale = scale;
            }
            Position position;
            Rotation rotation;
            Scale scale;
        };

        struct MeshFilter : public Component {
            MeshFilter() = default;
            MeshFilter(std::string mesh) {
                this->mesh = mesh;
            }
            std::string mesh;
        };

        struct Camera : public Component {
            Camera() = default;
            Camera(float fov, float zNear, float zFar) {
                this->fov = fov;
                this->zNear = zNear;
                this->zFar = zFar;
            }
            float fov;
            float zNear;
            float zFar;
        };
    }

#endif  // OPENGLCUBE_COMPONENTS_H