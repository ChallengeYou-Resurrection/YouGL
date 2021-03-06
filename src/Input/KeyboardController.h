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

		bool mouse1Down() const;
		bool mouse2Down() const;
		bool mouse3Down() const;

		bool scrollForward() const;
		bool scrollBackward() const;

        void tryToggleLookLock();

        glm::vec3 getLookChange() const;

		virtual sf::Vector2i getMousePositionRelativeToWindow() const;

    private:
        bool isPressed(Controller::Input input) const;

        std::unordered_map<Controller::Input, sf::Keyboard::Key> m_keyMap;
        sf::RenderWindow* m_pWindow;
        sf::Vector2i m_winowCentre;

        bool m_isMouseCentreLocked = false;
        bool m_isLookLocked = false;
};
