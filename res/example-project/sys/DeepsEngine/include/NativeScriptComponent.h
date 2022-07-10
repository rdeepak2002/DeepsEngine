//
// Created by Deepak Ramalingam on 6/11/22.
//

#ifndef DEEPSENGINE_NATIVESCRIPTCOMPONENT_H
#define DEEPSENGINE_NATIVESCRIPTCOMPONENT_H

extern "C" {
class NativeScriptComponent {
public:
    NativeScriptComponent() = default;

    virtual ~NativeScriptComponent() = default;


    virtual void init() {

    }

    virtual void update(double dt) {

    }
};

// the types of the class factories
typedef NativeScriptComponent* create_t();
typedef void destroy_t(NativeScriptComponent*);
}

#endif //DEEPSENGINE_NATIVESCRIPTCOMPONENT_H
