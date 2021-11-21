//
// Created by Deepak Ramalingam on 11/21/21.
//

#include "Renderer.h"

int main() {
    Renderer *renderer = new Renderer(true, false);

    renderer->init();

    while (!renderer->shuttingDown()) {
        renderer->render();
    }

    renderer->shutDown();

    return 0;
}