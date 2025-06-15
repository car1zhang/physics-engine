#pragma once

#include "bodies/body.h"

class Component {
public:
    virtual void Update(float dt) = 0;

    virtual void set_body(Body* body) = 0;
};
