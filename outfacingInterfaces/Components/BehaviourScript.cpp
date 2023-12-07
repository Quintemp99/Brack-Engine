//
// Created by Olaf van den Berg on 7-12-2023.
//
#include <Components/BehaviourScript.hpp>
#include "../../src/GameObjectConverter.hpp"

std::optional<GameObject> BehaviourScript::getGameObjectByName(const std::string &name) {
    return GameObjectConverter::getGameObjectByName(name);
}

std::vector<GameObject> BehaviourScript::getGameObjectsByName(const std::string &name) {
    return GameObjectConverter::getGameObjectsByName(name);
}

std::optional<GameObject> BehaviourScript::getGameObjectByTag(const std::string &tag) {
    return GameObjectConverter::getGameObjectByTag(tag);
}

std::vector<GameObject> BehaviourScript::getGameObjectsByTag(const std::string &tag) {
    return GameObjectConverter::getGameObjectsByTag(tag);
}


std::vector<GameObject> BehaviourScript::getChildren() {
    return GameObjectConverter::getChildren(entityID);
}

std::optional<GameObject> BehaviourScript::getParent() {
    return GameObjectConverter::getParent(entityID);
}


