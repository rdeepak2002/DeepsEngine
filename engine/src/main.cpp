//
// Created by Deepak Ramalingam on 11/21/21.
//

#include "Renderer.h"

int main() {
    bool showWindow = true;
    // TODO: set this to false for engine
    bool saveOutputRender = false;

    Renderer *renderer = new Renderer(showWindow, saveOutputRender, "../editornative/example_projects/blank_project");

    renderer->init();

    std::string newEntityGuid = renderer->addEntity("cube");
//    Component* cubeTransform = new Component(newEntityGuid, "transform", "vec3(0,0,0)");
//    renderer->addComponent(cubeTransform);

    while (!renderer->shuttingDown()) {
        renderer->render();
    }

    renderer->shutDown();

    return 0;
}