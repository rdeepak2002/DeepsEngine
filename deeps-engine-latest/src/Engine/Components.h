//
// Created by Deepak Ramalingam on 2/4/22.
//

#ifndef OPENGLCUBE_COMPONENTS_H
#define OPENGLCUBE_COMPONENTS_H

namespace Components {
  struct position {
    float x;
    float y;
    float z;
  };

  struct rotation {
    float x;
    float y;
    float z;
  };

  struct scale {
    float x;
    float y;
    float z;
  };

  struct transform {
    position position;
    rotation rotation;
    scale scale;
  };
}

#endif  // OPENGLCUBE_COMPONENTS_H
