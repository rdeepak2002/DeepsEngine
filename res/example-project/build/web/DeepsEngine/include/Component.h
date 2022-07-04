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
#include "Entity.h"
#include "NativeScript.h"

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

        Id(std::string id) {
            this->id = id;
        }

        Id(YAML::Node yamlData) {
            this->id = yamlData["id"].as<std::string>();
        }

        std::string id;
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

    struct HierarchyComponent : public Component {
        HierarchyComponent(Entity &thisEntity) {
            this->entityGuid = thisEntity.GetComponent<DeepsEngine::Component::Id>().id;
            parentGuid = "root";
        }

        HierarchyComponent(Entity &thisEntity, Entity &parent) {
            this->entityGuid = thisEntity.GetComponent<DeepsEngine::Component::Id>().id;
            parent.GetComponent<HierarchyComponent>().addChild(thisEntity);
        }

        HierarchyComponent(YAML::Node yamlData, std::string entityGuid) {
            this->entityGuid = entityGuid;
            this->parentGuid = yamlData["parentGuid"].as<std::string>();
            this->childrenGuids = yamlData["childrenGuids"].as<std::vector<std::string>>();
        }

        virtual void Serialize(YAML::Emitter &out) override {
            out << YAML::Key << "Hierarchy";
            out << YAML::BeginMap;

            out << YAML::Key << "parentGuid" << YAML::Value << parentGuid;
            out << YAML::Key << "childrenGuids" << YAML::Value << childrenGuids;

            out << YAML::EndMap;
        }

        void addChild(Entity &childEntity) {
            childEntity.GetComponent<DeepsEngine::Component::HierarchyComponent>().parentGuid = entityGuid;
            if (!std::count(childrenGuids.begin(), childrenGuids.end(), childEntity.GetComponent<DeepsEngine::Component::Id>().id)) {
                childrenGuids.push_back(childEntity.GetComponent<DeepsEngine::Component::Id>().id);
            }
        }

        std::string entityGuid;
        std::string parentGuid;
        std::vector<std::string> childrenGuids;
    };

    struct Transform : public Component {
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

        glm::mat4 getModelMatrix(Entity &entity) {
            glm::mat4 parentModelMatrix = glm::mat4(1.0f);

            if (entity.HasComponent<HierarchyComponent>() && entity.GetComponent<HierarchyComponent>().parentGuid != "root") {
                Entity parentEntity = Application::getInstance().scene.findEntityByGuid(entity.GetComponent<HierarchyComponent>().parentGuid);

                if (parentEntity && parentEntity.HasComponent<Transform>()) {
                    parentModelMatrix = parentEntity.GetComponent<Transform>().getModelMatrix(parentEntity);
                }
            }

            if (overrideModelMatrix) {
                return parentModelMatrix * modelMatrixOverride;
            }

            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            model = glm::translate(model, glm::vec3(position.x, position.y, position.z));
            model = glm::rotate(model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(scale.x, scale.y, scale.z));

            return parentModelMatrix * model;
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
            glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
            return glm::normalize(glm::cross(front(), up));
        }

        glm::vec3 up() {
            return glm::vec3(0.0f, 1.0f, 0.0f);
        }

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        std::string entityGuid;

        bool overrideModelMatrix = false;
        glm::mat4 modelMatrixOverride = glm::mat4(1.0f);

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

        void changeScript(std::string newScriptPath) {
            self.abandon();
            hooks.init.abandon();
            hooks.update.abandon();
            shouldInit = true;
            shouldUpdate = true;

            scriptPath = newScriptPath;
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

    struct Material : public Component {
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
            std::string specularTextureAbsPath = Application::getInstance().getProjectPath().append(
                    specularTexturePath);
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

    struct Light : public Component {
        Light() = default;

        Light(std::string type) {
            if (type != "directional" && type != "point" && type != "spotlight") {
                Logger::Error("Invalid light type: " + type);
                exit(1);
            }

            cutOff = 0.0f;
            outerCutOff = 0.0f;

            ambient = glm::vec3(0, 0, 0);
            diffuse = glm::vec3(0, 0, 0);
            specular = glm::vec3(0, 0, 0);

            constant = 0.0f;
            linear = 0.0f;
            quadratic = 0.0f;

            setLightType(type);
        }

        Light(YAML::Node yamlData) {
            this->setLightType(yamlData["type"].as<std::string>());

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

        float cutOff;
        float outerCutOff;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        float constant;
        float linear;
        float quadratic;

        unsigned int VBO, VAO;

        virtual void Serialize(YAML::Emitter &out) override {
            out << YAML::Key << "Light";
            out << YAML::BeginMap;

            out << YAML::Key << "type" << YAML::Value << type;

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

        void setLightType(std::string newLightType) {
            this->type = newLightType;

            float cubeVertices[] = {
                    // positions          // normals           // texture coords
                    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                    0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                    0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                    -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

                    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                    0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                    0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

                    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                    0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                    0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
                    0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
                    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                    0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                    -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                    -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

                    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                    0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                    0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
            };

            // configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);
            glGenBuffers(1, &VBO);

            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

            // update the lamp's position attribute's stride to reflect the updated buffer data
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
            glEnableVertexAttribArray(0);
        }

        void draw() {
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    };

    struct MeshFilter : public Component {
        MeshFilter(std::string mesh, std::string entityGuid) {
            this->entityGuid = entityGuid;
            loadMissingTextures();
            this->meshPath = "";
            this->setMeshType(mesh);
            this->flipTextures = false;
        }

        MeshFilter(std::string mesh, std::string meshPath, std::string entityGuid) {
            this->entityGuid = entityGuid;
            loadMissingTextures();
            this->meshPath = meshPath;
            this->setMeshType(mesh);
            this->flipTextures = false;
        }

        MeshFilter(YAML::Node yamlData, std::string entityGuid) {
            this->entityGuid = entityGuid;
            loadMissingTextures();

            if (!yamlData["meshPath"]) {
                Logger::Warn("Providing blank mesh path for mesh component");
                this->meshPath = "";
            } else {
                this->meshPath = yamlData["meshPath"].as<std::string>();
            }

            if (yamlData["flipTextures"]) {
                this->flipTextures = yamlData["flipTextures"].as<bool>();
            } else {
                this->flipTextures = false;
            }

            this->setMeshType(yamlData["mesh"].as<std::string>());
        }

        bool flipTextures;
        std::string entityGuid;
        std::string mesh;
        std::string meshPath;
        Animator* animator;
        AnimatedModel *animatedModel;
        Model *model;
        unsigned int VBO, VAO;
        unsigned int missingTextureDiffuse, missingTextureSpecular;

        void loadMissingTextures() {
            std::string missingTextureDiffuseFilePath = Application::getInstance().getProjectPath().append("src").append("textures").append("missing_texture.png");
            std::string missingTextureSpecularFilePath = Application::getInstance().getProjectPath().append("src").append("textures").append("missing_texture_specular.png");
            missingTextureDiffuse = Application::getInstance().renderer->loadTexture(missingTextureDiffuseFilePath.c_str());
            missingTextureSpecular = Application::getInstance().renderer->loadTexture(missingTextureSpecularFilePath.c_str());
        }

        virtual void Serialize(YAML::Emitter &out) override {
            out << YAML::Key << "MeshFilter";
            out << YAML::BeginMap;

            out << YAML::Key << "mesh" << YAML::Value << mesh;
            out << YAML::Key << "meshPath" << YAML::Value << meshPath;
            out << YAML::Key << "flipTextures" << YAML::Value << flipTextures;

            out << YAML::EndMap;
        }

        void setMeshType(std::string meshType) {
            this->mesh = meshType;

            if (mesh == "cube") {
                float cubeVertices[] = {
                        // positions          // normals           // texture coords
                        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
                        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
                        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
                        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

                        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
                        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,

                        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
                        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,

                        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
                        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
                        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

                        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
                        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
                        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
                };

                glGenVertexArrays(1, &VAO);
                glGenBuffers(1, &VBO);

                glBindBuffer(GL_ARRAY_BUFFER, VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

                glBindVertexArray(VAO);
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
                glEnableVertexAttribArray(0);
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
                glEnableVertexAttribArray(2);
            } else if (mesh == "static-model") {
                if (!meshPath.empty()) {
                    stbi_set_flip_vertically_on_load(flipTextures);
                    model = new Model(Application::getInstance().getProjectPath().append(meshPath));
                    stbi_set_flip_vertically_on_load(false);
                }
            } else if (mesh == "animated-model") {
                if (!meshPath.empty()) {
                    stbi_set_flip_vertically_on_load(flipTextures);
                    animatedModel = new AnimatedModel(Application::getInstance().getProjectPath().append(meshPath));
                    stbi_set_flip_vertically_on_load(false);
                    Animation* defaultAnimation = new Animation(Application::getInstance().getProjectPath().append(meshPath), animatedModel);
                    animator = new Animator(defaultAnimation, entityGuid);
                }
            } else {
                Logger::Error("Unknown mesh type: " + mesh);
                exit(1);
            }
        }

        void setMeshPath(std::string newMeshPath) {
            Logger::Warn("Setting new mesh path: " + newMeshPath);
            meshPath = newMeshPath;
            setMeshType(mesh);
        }

        void draw(Entity &entity, Shader *shader) {
            // get diffuse and specular map from entity material
            unsigned int diffuseMap = missingTextureDiffuse;
            unsigned int specularMap = missingTextureSpecular;
            float materialShininess = 32.0f;

            if (entity.HasComponent<DeepsEngine::Component::Material>()) {
                diffuseMap = entity.GetComponent<DeepsEngine::Component::Material>().diffuse;
                specularMap = entity.GetComponent<DeepsEngine::Component::Material>().specular;
                materialShininess = entity.GetComponent<DeepsEngine::Component::Material>().shininess;
            }

            // bind diffuse map
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, diffuseMap);

            // bind specular map
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, specularMap);

            // bind texture maps
            shader->setInt("material.diffuse", 0);
            shader->setInt("material.specular", 1);
            shader->setFloat("material.shininess", materialShininess);

            // draw the mesh
            if (mesh == "cube") {
                glBindVertexArray(VAO);
                glDrawArrays(GL_TRIANGLES, 0, 36);
            } else if (mesh == "static-model") {
                if (!model) {
                    Logger::Error("Static mesh not initialized");
                    exit(1);
                }

                model->Draw(*shader);
            } else if (mesh == "animated-model") {
                if (!animatedModel) {
                    Logger::Error("Animated mesh not initialized");
                    exit(1);
                }

                animator->UpdateAnimation(std::chrono::duration_cast<std::chrono::milliseconds>(timestep).count() * 0.001);

                auto transforms = animator->GetFinalBoneMatrices();
                for (int i = 0; i < transforms.size(); ++i)
                    shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

                animatedModel->Draw(*shader);
            } else {
                Logger::Error("Unknown mesh type: " + mesh);
                exit(1);
            }
        }
    };

    struct SceneCameraComponent : Component {
        SceneCameraComponent() {
            sceneCamera = true;
        }

        SceneCameraComponent(YAML::Node yamlData) {
            this->sceneCamera = yamlData["sceneCamera"].as<bool>();
        }

        bool sceneCamera;
    };

    struct NativeScriptComponent : Component {
        NativeScriptComponent() {
            shouldInit = true;
            shouldUpdate = true;
        }

        NativeScriptComponent(std::string className, std::string filePath) {
            this->className = className;
            this->filePath = filePath;
            shouldInit = true;
            shouldUpdate = true;
        }

        NativeScriptComponent(YAML::Node yamlData) {
            this->className = yamlData["className"].as<std::string>();
            this->filePath = yamlData["filePath"].as<std::string>();
            shouldInit = true;
            shouldUpdate = true;
        }

        ~NativeScriptComponent() {

        }

        std::shared_ptr<NativeScript> nativeScript;
        std::string className;
        std::string filePath;
        bool shouldInit;
        bool shouldUpdate;

        void changeScript(std::string relativeFilePath) {
            shouldInit = true;
            shouldUpdate = true;

            string::size_type slashLoc = relativeFilePath.find_last_of('/');
            string::size_type extensionLoc = relativeFilePath.find_last_of('.');

            if (slashLoc == string::npos) {
                slashLoc = relativeFilePath.find_last_of('\\');
            }

            if (slashLoc == string::npos) {
                slashLoc = 0;
            }

            this->filePath = relativeFilePath;
            this->className = relativeFilePath.substr(slashLoc + 1, extensionLoc - slashLoc - 1);
        }

        virtual void Serialize(YAML::Emitter &out) override {
            out << YAML::Key << "NativeScriptComponent";
            out << YAML::BeginMap;

            out << YAML::Key << "className" << YAML::Value << className;
            out << YAML::Key << "filePath" << YAML::Value << className;

            out << YAML::EndMap;
        }
    };
}

#endif  // OPENGLCUBE_COMPONENTS_H
