//
// Created by jesse on 06/11/2023.
//

#include <EngineManagers/SceneManager.hpp>
#include "ConfigSingleton.hpp"
#include "includes/EntityManager.hpp"

ConfigSingleton ConfigSingleton::instance;

ConfigSingleton &ConfigSingleton::getInstance() {
    return instance;
}

bool ConfigSingleton::isRunning() const {
    return isRunning_;
}

void ConfigSingleton::toggleIsRunning() {
    isRunning_ = !isRunning_;
}

void ConfigSingleton::setDeltaTimeMultiplier(float deltaTimeMultiplier) {
    ConfigSingleton::instance.deltaTimeMultiplier = deltaTimeMultiplier;
}

void ConfigSingleton::setIsRunning(bool isRunning) {
    ConfigSingleton::isRunning_ = isRunning;
}

std::string ConfigSingleton::getWindowTitle() const {
    return windowTitle;
}

Vector2 ConfigSingleton::getWindowSize() const {
    return windowSize;
}

bool ConfigSingleton::isFullscreen() const {
    return fullscreen;
}

int ConfigSingleton::getParticleLimit() const {
    return particleLimit;
}

std::string ConfigSingleton::getBaseAssetPath() const {
    return BaseAssetPath;
}

int ConfigSingleton::getAmountOfSoundEffectsChannels() const {
    return amountOfSoundEffectsChannels;
}

void ConfigSingleton::setConfig(Config config) {
    isRunning_ = config.isRunning;
    windowTitle = config.windowTitle;
    windowSize = config.windowSize;
    fullscreen = config.fullscreen;
    BaseAssetPath = config.BaseAssetPath;
    showFPS_ = config.showFPS;
    amountOfSoundEffectsChannels = config.amountOfSoundEffectsChannels;
    fpsLimit = config.fpsLimit;
    particleLimit = config.particleLimit;
    deltaTimeMultiplier = config.deltaTimeMultiplier;
}

bool ConfigSingleton::IsShowFPSTrue() const {
    return showFPS;
}

void ConfigSingleton::toggleShowFps() {
    showFPS = !showFPS;
    if (EntityManager::getInstance().entityExistsByTag("FPS")) {
        SceneManager::getInstance().getGameObjectByName("FPS").value()->setActive(showFPS);
    }
}

void ConfigSingleton::SetWindowSize(Vector2 size) const {
    size = size;
}

uint32_t ConfigSingleton::getFPSLimit() const {
    return fpsLimit;
}

void ConfigSingleton::setFPSLimit(uint32_t fpsLimit) {
    ConfigSingleton::fpsLimit = fpsLimit;
}
