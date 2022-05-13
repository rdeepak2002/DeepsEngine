//
// Created by Deepak Ramalingam on 2/4/22.
//

#ifndef OPENGLCUBE_COMPONENTS_H
#define OPENGLCUBE_COMPONENTS_H

#include <iostream>
#include <filesystem>
#include "Logger.h"
#include "Application.h"

#define SOL_ALL_SAFETIES_ON 1
#include "sol/state.hpp"
#include <yaml-cpp/yaml.h>
#include <glm/gtx/string_cast.hpp>

using std::filesystem::exists;

namespace DeepsEngine::Component {
        struct Component {
            virtual void Serialize(YAML::Emitter &out) {

            }

            void glmVec3ToYaml(YAML::Emitter &out, glm::vec3 vec) {
                out << YAML::BeginMap;
                out << YAML::Key << "x" << YAML::Value << std::to_string(vec.x);
                out << YAML::Key << "y" << YAML::Value << std::to_string(vec.y);
                out << YAML::Key << "z" << YAML::Value << std::to_string(vec.z);
                out << YAML::EndMap;
            }

            glm::vec3 yamlToGlmVec3(YAML::Node yaml) {
                return {yaml["x"].as<float>(), yaml["y"].as<float>(), yaml["z"].as<float>()};
            }
        };

        struct Id : public Component {
            Id() = default;
            Id(uint32_t id) {
                this->id = id;
            }
            Id(YAML::Node yamlData) {
                this->id = yamlData["id"].as<uint32_t>();
            }
            uint32_t id;
        };

        struct Tag : public Component {
            Tag() = default;
            Tag(std::string tag) {
                this->tag = tag;
            }
            Tag(YAML::Node yamlData) {
                this->tag = yamlData["tag"].as<std::string>();
            }
            std::string tag;
            virtual void Serialize(YAML::Emitter &out) override {
                out << YAML::Key << "Tag";
                out << YAML::BeginMap;
                out << YAML::Key << "tag" << YAML::Value << tag;
                out << YAML::EndMap;
            }
        };

        struct Transform : public Component {
            Transform() = default;
            Transform(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
                this->position = position;
                this->rotation = rotation;
                this->scale = scale;
            }
            Transform(YAML::Node yamlData) {
                this->position = yamlToGlmVec3(yamlData["position"]);
                this->rotation = yamlToGlmVec3(yamlData["rotation"]);
                this->scale = yamlToGlmVec3(yamlData["scale"]);
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
            glm::vec3 up() {
                return glm::vec3(0.0f, 1.0f,  0.0f);
            }
            glm::vec3 position;
            glm::vec3 rotation;
            glm::vec3 scale;
            virtual void Serialize(YAML::Emitter &out) override {
                out << YAML::Key << "Transform";
                out << YAML::BeginMap;

                out << YAML::Key << "position" << YAML::Value;
                glmVec3ToYaml(out, position);

                out << YAML::Key << "rotation" << YAML::Value;
                glmVec3ToYaml(out, rotation);

                out << YAML::Key << "scale" << YAML::Value;
                glmVec3ToYaml(out, scale);

                out << YAML::EndMap;
            }
        };

        struct MeshFilter : public Component {
            MeshFilter() = default;
            MeshFilter(std::string mesh) {
                this->mesh = mesh;
            }
            MeshFilter(YAML::Node yamlData) {
                this->mesh = yamlData["mesh"].as<std::string>();
            }
            std::string mesh;
            virtual void Serialize(YAML::Emitter &out) override {
                out << YAML::Key << "MeshFilter";
                out << YAML::BeginMap;

                out << YAML::Key << "mesh" << YAML::Value << mesh;

                out << YAML::EndMap;
            }
        };

        struct Camera : public Component {
            Camera() = default;
            Camera(float fov, float zNear, float zFar) {
                this->fov = fov;
                this->zNear = zNear;
                this->zFar = zFar;
            }
            Camera(YAML::Node yamlData) {
                this->fov = yamlData["fov"].as<float>();
                this->zNear = yamlData["zNear"].as<float>();
                this->zFar = yamlData["zFar"].as<float>();
            }
            float fov;
            float zNear;
            float zFar;
            virtual void Serialize(YAML::Emitter &out) override {
                out << YAML::Key << "Camera";
                out << YAML::BeginMap;

                out << YAML::Key << "fov" << YAML::Value << std::to_string(fov);
                out << YAML::Key << "zNear" << YAML::Value << std::to_string(zNear);
                out << YAML::Key << "zFar" << YAML::Value << std::to_string(zFar);

                out << YAML::EndMap;
            }
        };

        struct LuaScript : public Component {
            LuaScript() = default;
            LuaScript(std::string scriptPath) {
                this->scriptPath = scriptPath;
                shouldInit = true;
                shouldUpdate = true;
            }
            LuaScript(YAML::Node yamlData) {
                this->scriptPath = yamlData["scriptPath"].as<std::string>();
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
            virtual void Serialize(YAML::Emitter &out) override {
                out << YAML::Key << "LuaScript";
                out << YAML::BeginMap;

                out << YAML::Key << "scriptPath" << YAML::Value << scriptPath;

                out << YAML::EndMap;
            }
        };

        struct Material: public Component {
            std::string diffuseTexturePath;
            std::string specularTexturePath;
            float shininess;
            unsigned int diffuse; // index of diffuse texture for OpenGL
            unsigned int specular; // index of specular texture for OpenGL

            Material(const std::string &diffuseTexturePath, const std::string &specularTexturePath, float shininess)
                    : diffuseTexturePath(diffuseTexturePath), specularTexturePath(specularTexturePath),
                      shininess(shininess) {
                loadTextures();
            }

            Material(YAML::Node yamlData) {
                this->diffuseTexturePath = yamlData["diffuseTexturePath"].as<std::string>();
                this->specularTexturePath = yamlData["specularTexturePath"].as<std::string>();
                this->shininess = yamlData["shininess"].as<float>();
                loadTextures();
            }

            void loadTextures() {
                std::string diffuseTextureAbsPath = Application::getInstance().getProjectPath().append(diffuseTexturePath);
                std::string specularTextureAbsPath = Application::getInstance().getProjectPath().append(specularTexturePath);
                diffuse = Application::getInstance().renderer->loadTexture(diffuseTextureAbsPath.c_str());
                specular = Application::getInstance().renderer->loadTexture(specularTextureAbsPath.c_str());
            }

            virtual void Serialize(YAML::Emitter &out) override {
                out << YAML::Key << "Material";
                out << YAML::BeginMap;

                out << YAML::Key << "diffuseTexturePath" << YAML::Value << diffuseTexturePath;
                out << YAML::Key << "specularTexturePath" << YAML::Value << specularTexturePath;
                out << YAML::Key << "shininess" << YAML::Value << std::to_string(shininess);

                out << YAML::EndMap;
            }
        };

        struct Light: public Component {
            Light() = default;

            Light(std::string type) {
                if (type != "directional" && type != "point" && type != "spotlight") {
                    Logger::Error("Invalid light type: " + type);
                    exit(1);
                }

                direction = glm::vec3(0,0,0);
                cutOff = 0.0f;
                outerCutOff = 0.0f;

                ambient = glm::vec3(0,0,0);
                diffuse = glm::vec3(0,0,0);
                specular = glm::vec3(0,0,0);

                constant = 0.0f;
                linear = 0.0f;
                quadratic = 0.0f;

                this->type = std::move(type);
            }

            Light(const std::string &type, const glm::vec3 &direction, float cutOff, float outerCutOff,
                           const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular,
                           float constant, float linear, float quadratic) : type(type), direction(direction),
                                                                            cutOff(cutOff), outerCutOff(outerCutOff),
                                                                            ambient(ambient), diffuse(diffuse),
                                                                            specular(specular), constant(constant),
                                                                            linear(linear), quadratic(quadratic) {}

            Light(YAML::Node yamlData) {
                this->type = yamlData["type"].as<std::string>();

                this->direction = yamlToGlmVec3(yamlData["direction"]);
                this->cutOff = yamlData["cutOff"].as<float>();
                this->outerCutOff = yamlData["outerCutOff"].as<float>();

                this->ambient = yamlToGlmVec3(yamlData["ambient"]);
                this->diffuse = yamlToGlmVec3(yamlData["diffuse"]);
                this->specular = yamlToGlmVec3(yamlData["specular"]);

                this->constant = yamlData["constant"].as<float>();
                this->linear = yamlData["linear"].as<float>();
                this->quadratic = yamlData["quadratic"].as<float>();
            }

            std::string type;

            glm::vec3 direction;
            float cutOff;
            float outerCutOff;

            glm::vec3 ambient;
            glm::vec3 diffuse;
            glm::vec3 specular;

            float constant;
            float linear;
            float quadratic;

            virtual void Serialize(YAML::Emitter &out) override {
                out << YAML::Key << "Light";
                out << YAML::BeginMap;

                out << YAML::Key << "type" << YAML::Value << type;

                out << YAML::Key << "direction" << YAML::Value;
                glmVec3ToYaml(out, direction);
                out << YAML::Key << "cutOff" << YAML::Value << std::to_string(cutOff);
                out << YAML::Key << "outerCutOff" << YAML::Value << std::to_string(outerCutOff);

                out << YAML::Key << "ambient" << YAML::Value;
                glmVec3ToYaml(out, ambient);
                out << YAML::Key << "diffuse" << YAML::Value;
                glmVec3ToYaml(out, diffuse);
                out << YAML::Key << "specular" << YAML::Value;
                glmVec3ToYaml(out, specular);

                out << YAML::Key << "constant" << YAML::Value << std::to_string(constant);
                out << YAML::Key << "linear" << YAML::Value << std::to_string(linear);
                out << YAML::Key << "quadratic" << YAML::Value << std::to_string(quadratic);

                out << YAML::EndMap;
            }
        };
    }

#endif  // OPENGLCUBE_COMPONENTS_H
