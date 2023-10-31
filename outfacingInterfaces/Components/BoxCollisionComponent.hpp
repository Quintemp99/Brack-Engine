//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
#define BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP

#include "CollisionComponent.hpp"

class BoxCollisionComponent : public CollisionComponent {
public:
    BoxCollisionComponent() = default;

    ~BoxCollisionComponent() override = default;

    Vector2 size;
};

#endif //BRACK_ENGINE_BOXCOLLISIONCOMPONENT_HPP
