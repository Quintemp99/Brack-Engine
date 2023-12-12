//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AISYSTEM_HPP
#define BRACK_ENGINE_AISYSTEM_HPP


#include "ISystem.hpp"

class AISystem : public ISystem {
public:
    AISystem();

    ~AISystem() override;

    Vector2 getNextLocation(const Vector2& target, const Vector2& source);

    const std::string getName() const override;

    void cleanUp() override;

    void update(milliseconds deltaTime) override;

    void clearCache() override;
};


#endif //BRACK_ENGINE_AISYSTEM_HPP
