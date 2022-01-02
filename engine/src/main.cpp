//
// Created by Deepak Ramalingam on 11/21/21.
//

#include <document.h>
#include "Renderer.h"

int main() {
    bool showWindow = true;
    // TODO: set this to false for engine
    bool saveOutputRender = false;

    Renderer *renderer = new Renderer(showWindow, saveOutputRender, "../editornative/example_projects/blank_project");

    renderer->init();

    std::string newEntityGuid = renderer->addEntity("cube");
//    renderer->updateComponent(0, "{\"transform\": {\"position\": {\"x\": 0.5}, \"rotation\": {\"x\": 0.5}}}");

    while (!renderer->shuttingDown()) {
        renderer->render();
    }

    renderer->shutDown();

    return 0;
}