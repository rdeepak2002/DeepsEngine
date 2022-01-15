//
// Created by Deepak Ramalingam on 1/15/22.
//

#ifndef OPENGLCUBE_OPENGLRENDERER_H
#define OPENGLCUBE_OPENGLRENDERER_H
// TODO: QT SPECIFIC, replace w/ #include <glad.h> (and also initialize glad in initializeStandalone function)
///
#include "node_modules/@nodegui/qode/dist/1.0.6/lib/QtGui.framework/Versions/5/Headers/QOpenGLFunctions"
///

#include <glfw3.h>
#include <iostream>

namespace OpenGLRenderer {
  void initialize();
  void clear();
  void update();
}

#endif  // OPENGLCUBE_OPENGLRENDERER_H
