//
// Created by Stef van Stipdonk on 29/10/2023.
//

#ifndef BRACK_ENGINE_ICOMPONENT_HPP
#define BRACK_ENGINE_ICOMPONENT_HPP

#include <cstdint>

struct IComponent {
    virtual ~IComponent() = default;

    // Als we nog achter andere overeenkomende dingen komen bij ieder component kunnen we die hier toevoegens
    uint32_t entityID;
    bool isActive = true;
};

#endif //BRACK_ENGINE_ICOMPONENT_HPP
