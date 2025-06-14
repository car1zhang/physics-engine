#pragma once

#include "component.h"
#include "bodies/body.h"


class GravityComponent : public Component {
public:
    GravityComponent(Body* body);
    ~GravityComponent();

    void Update(float dt);

private:
    Body* body_;
};
