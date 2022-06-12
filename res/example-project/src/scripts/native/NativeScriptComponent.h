//
// Created by Deepak Ramalingam on 6/11/22.
//

#ifndef DEEPSENGINE_NATIVESCRIPTCOMPONENT_H
#define DEEPSENGINE_NATIVESCRIPTCOMPONENT_H

#define CREATE_FUNC_(name) create_ ## name
#define CREATE_FUNC(name) CREATE_FUNC_(name)

#define DESTROY_FUNC_(name) destroy_ ## name
#define DESTROY_FUNC(name) DESTROY_FUNC_(name)

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
