//
// Created by Deepak Ramalingam on 2/4/22.
//

#ifndef OPENGLCUBE_COMPONENTS_H
#define OPENGLCUBE_COMPONENTS_H

#include <iostream>
#include <filesystem>
#include "src/engine/util/Logger.h"

#define SOL_ALL_SAFETIES_ON 1
#include "src/engine/include/sol2/include/sol/state.hpp"

using std::filesystem::exists;

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

        struct Transform : public Component {
            Transform() = default;
            Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
                this->position = position;
                this->rotation = rotation;
                this->scale = scale;
            }
            glm::vec3 front() {
                float yaw = glm::degrees(rotation.y);
                float pitch = glm::degrees(rotation.x);
                float roll = glm::degrees(rotation.z);

                glm::vec3 front;
                front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
                front.y = sin(glm::radians(pitch));
                front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

                return glm::normalize(front);
            }
            glm::vec3 right() {
                glm::vec3 up = glm::vec3(0.0f, 1.0f,  0.0f);
                return glm::normalize(glm::cross(front(), up));
            }
            glm::vec3 position;
            glm::vec3 rotation;
            glm::vec3 scale;
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

        struct LuaScript : public Component {
            LuaScript() = default;
            LuaScript(std::string scriptPath) {
                if (std::filesystem::exists(scriptPath)) {
                    this->scriptPath = scriptPath;
                } else {
                    Logger::Error("Unable to find script " + scriptPath);
                }
                shouldInit = true;
                shouldUpdate = true;
            }
            ~LuaScript() {
                self.abandon();
                hooks.init.abandon();
                hooks.update.abandon();
            }
            std::string scriptPath;
            sol::table self;
            struct {
                sol::function init;
                sol::function update;
            } hooks;
            bool shouldInit;
            bool shouldUpdate;
        };
    }

#endif  // OPENGLCUBE_COMPONENTS_H
