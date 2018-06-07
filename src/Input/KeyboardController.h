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

<<<<<<< HEAD
        bool m_isMouseCentreLocked = true;
=======
        bool m_mouseLocked = false;
>>>>>>> 17ec87d4d15f307c9c50f27cb0905561cff333b4
};
