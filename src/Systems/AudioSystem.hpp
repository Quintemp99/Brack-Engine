//
// Created by jesse on 31/10/2023.
//

#ifndef BRACK_ENGINE_AUDIOSYSTEM_HPP
#define BRACK_ENGINE_AUDIOSYSTEM_HPP


#include <cstdint>
#include <memory>
#include "ISystem.hpp"
#include "../Wrappers/AudioWrapper.hpp"

class AudioSystem : public ISystem {
public:
    AudioSystem();

    ~AudioSystem() override;

    const std::string GetName() const override;
    void CleanUp() override;

    void Update(float deltaTime) override;

    void PlaySound(AudioComponent& audioComponent);

    void PauseSound(AudioComponent& audioComponent);

    void StopSound(AudioComponent& audioComponent);

private:
    std::unique_ptr<AudioWrapper> audioWrapper;
};


#endif //BRACK_ENGINE_AUDIOSYSTEM_HPP
