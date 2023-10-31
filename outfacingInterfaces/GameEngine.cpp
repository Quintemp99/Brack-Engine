//
// Created by jesse on 31/10/2023.
//

#include "GameEngine.hpp"
#include "../src/Wrappers/SDL2Wrapper.hpp"

GameEngine::GameEngine() : sdl2Wrapper(nullptr){
    sdl2Wrapper = new SDL2Wrapper();
}

GameEngine::~GameEngine() {
    Cleanup();
    delete sdl2Wrapper;
}

bool GameEngine::Initialize() {
    return sdl2Wrapper->Initialize();
}

void GameEngine::Run() {
    sdl2Wrapper->Run();
}

void GameEngine::Cleanup() {
    sdl2Wrapper->Cleanup();
}
