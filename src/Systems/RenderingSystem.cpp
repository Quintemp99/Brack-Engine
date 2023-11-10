//
// Created by jesse on 31/10/2023.
//

#include "RenderingSystem.hpp"
#include "../includes/ComponentStore.hpp"
#include "../Logger.hpp"

RenderingSystem::RenderingSystem() : sdl2Wrapper(new RenderWrapper()) {
}

RenderingSystem::~RenderingSystem() {

}

void RenderingSystem::Update(float deltaTime) {
    //Render camera
    try {
        auto cameraId = ComponentStore::GetInstance().getEntitiesWithComponent<CameraComponent>()[0];
        auto cameraComponent = ComponentStore::GetInstance().getComponent<CameraComponent>(cameraId);
        auto textComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<TextComponent>();
        sdl2Wrapper->RenderCamera(cameraComponent);
        for (int entityId: textComponentIds) {
            auto textComponent = ComponentStore::GetInstance().getComponent<TextComponent>(entityId);
            auto transformComponent = ComponentStore::GetInstance().getComponent<TransformComponent>(entityId);
            sdl2Wrapper->RenderText(textComponent, transformComponent);
        }
#if CURRENT_LOG_LEVEL >= LOG_LEVEL_DEBUG
        auto boxCollisionComponentIds = ComponentStore::GetInstance().getEntitiesWithComponent<BoxCollisionComponent>();
        for (int entityId: boxCollisionComponentIds) {
            auto boxCollisionComponent = ComponentStore::GetInstance().getComponent<BoxCollisionComponent>(entityId);
            auto transformComponent = ComponentStore::GetInstance().getComponent<TransformComponent>(entityId);
            sdl2Wrapper->RenderBoxCollisionComponents(boxCollisionComponent,transformComponent);
        }
#endif
        sdl2Wrapper->RenderFrame();
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void RenderingSystem::CleanUp() {
    sdl2Wrapper->Cleanup();
}

const std::string RenderingSystem::GetName() const {
    return "RenderingSystem";
}
