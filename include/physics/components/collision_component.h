#pragma once

#include "component.h"
#include "bodies/body.h"


class CollisionComponent : public Component {
public:
    CollisionComponent() = default;
    ~CollisionComponent();

    void Update(float dt) override;

    void set_body(Body* body) override { body_ = body; }

private:
    Body* body_;
};
