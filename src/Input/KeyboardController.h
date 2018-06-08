#pragma once

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Controller.h"

class KeyboardController : public Controller
{
    public:
        KeyboardController(sf::RenderWindow& window);

        bool forwardPressed() const;
        bool backPressed() const;
        bool leftPressed() const;
        bool rightPressed() const;
        bool jumpPressed() const;
        bool downPressed() const;
        bool firePressed() const;

        void tryToggleLookLock();

        glm::vec3 getLookChange() const;

    private:
        bool isPressed(Controller::Input input) const;

        std::unordered_map<Controller::Input, sf::Keyboard::Key> m_keyMap;
        sf::RenderWindow* m_pWindow;

        bool m_isMouseCentreLocked = true;
        bool m_isLookLocked = false;
};
