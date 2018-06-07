#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Controller.h"

class KeyboardController : public Controller
{
    public:
        KeyboardController();

        bool forwardPressed() const;
        bool backPressed() const;
        bool leftPressed() const;
        bool rightPressed() const;
        bool jumpPressed() const;
        bool firePressed() const;

        glm::vec3 getLookChange(const sf::RenderWindow& window) const;

    private:
        bool isPressed(Controller::Input input) const;

        std::unordered_map<Controller::Input, sf::Keyboard::Key> m_keyMap;

        bool m_mouseLocked = true;
};
