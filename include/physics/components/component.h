#pragma once

#include "bodies/body.h"

class Component {
public:
    virtual ~Component() = default;
    virtual void Update(float dt) = 0;

    virtual void set_body(Body* body) = 0;
};
