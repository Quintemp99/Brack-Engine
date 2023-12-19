//
// Created by jesse on 02/11/2023.
//

#include <Components/ObjectInfoComponent.hpp>
#include <Components/PersistenceTag.hpp>
#include "BrackEngine.hpp"
#include "Systems/RenderingSystem.hpp"
#include "Logger.hpp"
#include "ConfigSingleton.hpp"
#include "Systems/InputSystem.hpp"
#include "FPSSingleton.hpp"
#include "Systems/AudioSystem.hpp"
#include "Systems/BehaviourScriptSystem.hpp"
#include "Systems/ClickSystem.hpp"
#include "Systems/AudioSystem.hpp"
#include "Systems/PhysicsSystem.hpp"
#include "Systems/ReplaySystem.hpp"
#include "Systems/AnimationSystem.hpp"
#include "Systems/ParticleSystem.hpp"
#include "Systems/AISystem.hpp"


BrackEngine::BrackEngine(Config &&config) : deltaTimeMultiplier(ConfigSingleton::getInstance().deltaTimeMultiplier) {
    ConfigSingleton::getInstance().setConfig(config);
    SystemManager::getInstance().AddSystem(std::make_shared<InputSystem>());
    SystemManager::getInstance().AddSystem(std::make_shared<ClickSystem>());
    SystemManager::getInstance().AddSystem(std::make_shared<AudioSystem>());
    SystemManager::getInstance().AddSystem(std::make_shared<BehaviourScriptSystem>());
    SystemManager::getInstance().AddSystem(std::make_shared<AISystem>());
    SystemManager::getInstance().AddSystem(std::make_shared<PhysicsSystem>());
    SystemManager::getInstance().AddSystem(std::make_shared<AnimationSystem>());
    SystemManager::getInstance().AddSystem(std::make_shared<RenderingSystem>());
    SystemManager::getInstance().AddSystem(std::make_shared<ParticleSystem>());

    lastTime = std::chrono::high_resolution_clock::now();
    SystemManager::getInstance().AddSystem(std::make_shared<ReplaySystem>(lastTime));

    if (ConfigSingleton::GetInstance().IsShowFPSTrue())
        CreateFPS();
}

void BrackEngine::Run() {
    Logger::Debug("Updating systems");
    while (ConfigSingleton::getInstance().isRunning()) {
        FPSSingleton::GetInstance().Start();
        auto deltaTime = GetDeltaTime();
        SystemManager::getInstance().UpdateSystems(deltaTime * deltaTimeMultiplier);
        FPSSingleton::GetInstance().End();
        if (ConfigSingleton::GetInstance().IsShowFPSTrue())
            UpdateFPS(deltaTime);

        SceneManager::getInstance().setActiveScene();
    }

    SystemManager::getInstance().CleanUp();
}

milliseconds BrackEngine::GetDeltaTime() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(
            currentTime - lastTime);
    lastTime = currentTime;

    float deltaTimeInSeconds = deltaTime.count();
    milliseconds deltaTimeInMilliSeconds = deltaTimeInSeconds * 1000.0f;
    return deltaTimeInMilliSeconds;
}


void BrackEngine::CreateFPS() {
    auto entityId = EntityManager::getInstance().createEntity();
    auto objectInfoComponent = ObjectInfoComponent();
    auto textComponent = TextComponent();

    objectInfoComponent.name = "FPS";
    objectInfoComponent.tag = "FPS";
    objectInfoComponent.entityId = entityId;

    textComponent.text = "0";
    textComponent.fontSize = 32;
    textComponent.color = std::make_unique<Color>(255, 0, 0, 255);
    textComponent.entityId = entityId;
    textComponent.sortingLayer = 0;
    textComponent.orderInLayer = 0;

    ComponentStore::GetInstance().addComponent<TransformComponent>(entityId);
    ComponentStore::GetInstance().addComponent<ObjectInfoComponent>(objectInfoComponent);
    ComponentStore::GetInstance().addComponent<TextComponent>(textComponent);
    ComponentStore::GetInstance().addComponent<PersistenceTag>(entityId);

    EntityManager::getInstance().addEntityWithName(entityId, objectInfoComponent.name);
    EntityManager::getInstance().addEntityWithTag(entityId, objectInfoComponent.tag);
    EntityManager::getInstance().setEntityActive(entityId, true);
}

void BrackEngine::UpdateFPS(float deltaTime) {
    totalTime += deltaTime;
    if (totalTime < 1 / 12.0f)
        return;

    totalTime = 0;

    if (!EntityManager::getInstance().entityExistsByTag("FPS")) {
        CreateFPS();
        return;
    }

    entity fpsId = EntityManager::getInstance().getEntityByTag("FPS");
    auto &textComponent = ComponentStore::GetInstance().tryGetComponent<TextComponent>(
            fpsId);

    textComponent.text = std::to_string(FPSSingleton::GetInstance().GetFPS());;
}

void BrackEngine::save(const std::string &filePath, const std::string &content) const {
    std::ofstream file(filePath, std::ios::binary);

    // Check if the file can be opened for writing
    if (!file.is_open()) {
        std::cerr << "Unable to open file for writing: " << filePath << std::endl;
        return;
    }

    // Write the size of the string first
    size_t size = content.size();
    if (!file.write(reinterpret_cast<const char *>(&size), sizeof(size_t))) {
        std::cerr << "Error writing size to file: " << filePath << std::endl;
        file.close(); // Close the file before returning
        return;
    }

    // Write the content of the string
    if (!file.write(content.c_str(), size)) {
        std::cerr << "Error writing content to file: " << filePath << std::endl;
    }

    file.close();
}

std::string BrackEngine::load(const std::string &filePath) const {
    std::ifstream file(filePath, std::ios::binary);

    // Check if the file can be opened for reading
    if (!file.is_open()) {
        std::cerr << "Unable to open file for reading: " << filePath << std::endl;
        return "";
    }

    // Read the size of the string first
    size_t size;
    if (!file.read(reinterpret_cast<char *>(&size), sizeof(size_t))) {
        std::cerr << "Error reading size from file: " << filePath << std::endl;
        return "";
    }

    // Read the content of the string
    std::string content(size, '\0');
    if (!file.read(&content[0], size)) {
        std::cerr << "Error reading content from file: " << filePath << std::endl;
    }

    file.close();
    return content;
}