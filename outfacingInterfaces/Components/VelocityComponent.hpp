//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_VELOCITYCOMPONENT_HPP
#define BRACK_ENGINE_VELOCITYCOMPONENT_HPP

#include "TransformComponent.hpp"

class VelocityComponent : public TransformComponent {
public:
    VelocityComponent() = default;

    ~VelocityComponent() = default;

    Vector2 velocity;
};

#endif //BRACK_ENGINE_VELOCITYCOMPONENT_HPP
