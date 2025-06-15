#pragma once

#include "component.h"
#include "bodies/body.h"


class GravityComponent : public Component {
public:
    GravityComponent() = default;
    ~GravityComponent() = default;

    void Update(float dt) override;

    void set_body(Body* body) override { body_ = body; }

private:
    Body* body_;
};
