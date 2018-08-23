#include "KeyboardController.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

KeyboardController::KeyboardController(sf::RenderWindow& window)
    : m_pWindow (&window)
    , m_winowCentre (window.getSize().x / 2, window.getSize().y / 2)
{
    m_keyMap.emplace(Controller::Input::Forward, sf::Keyboard::Key::W);
    m_keyMap.emplace(Controller::Input::Back, sf::Keyboard::Key::S);
    m_keyMap.emplace(Controller::Input::Left, sf::Keyboard::Key::A);
    m_keyMap.emplace(Controller::Input::Right, sf::Keyboard::Key::D);
    m_keyMap.emplace(Controller::Input::Jump, sf::Keyboard::Key::Space);
    m_keyMap.emplace(Controller::Input::Down, sf::Keyboard::Key::LShift);

    m_pWindow->setMouseCursorGrabbed(true);
    m_pWindow->setMouseCursorVisible(false);
}

bool KeyboardController::forwardPressed() const
{
    return isPressed(Controller::Input::Forward);
}

bool KeyboardController::backPressed() const
{
    return isPressed(Controller::Input::Back);
}

bool KeyboardController::leftPressed() const
{
    return isPressed(Controller::Input::Left);
}

bool KeyboardController::rightPressed() const
{
    return isPressed(Controller::Input::Right);
}

bool KeyboardController::jumpPressed() const
{
    return isPressed(Controller::Input::Jump);
}

bool KeyboardController::downPressed() const
{
    return isPressed(Controller::Input::Down);
}

bool KeyboardController::firePressed() const
{
    return isPressed(Controller::Input::Fire);
}

// Left Mouse Button
bool KeyboardController::mouse1Down() const
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

// Right Mouse Button
bool KeyboardController::mouse2Down() const
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
}

// Scroll Wheel
bool KeyboardController::mouse3Down() const
{
	return sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle);
}

bool KeyboardController::scrollForward() const
{
	//return sf::Mouse::isButtonPressed(sf::Mouse::VerticalWheel);
	return false;
}

bool KeyboardController::scrollBackward() const
{
	//return sf::Mouse::isButtonPressed(sf::Mouse::VerticalWheel);
	return false;
}


void KeyboardController::tryToggleLookLock()
{
   // if (!m_pWindow->hasFocus()) return;

    static bool isKeyBackUp = true;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && isKeyBackUp) {
        isKeyBackUp = false;
        if (m_isLookLocked) {
            m_isLookLocked = false;
            m_pWindow->setMouseCursorGrabbed(true);
            m_pWindow->setMouseCursorVisible(false);
            sf::Mouse::setPosition(m_winowCentre, *m_pWindow);
        }
        else {
            m_isLookLocked = true;
            m_pWindow->setMouseCursorGrabbed(false);
            m_pWindow->setMouseCursorVisible(true);
        }
    }
    if (!isKeyBackUp) {
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
            isKeyBackUp = true;
        }
    }
}

glm::vec3 KeyboardController::getLookChange() const
{
    if (m_isLookLocked || sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        return { 0, 0, 0 };
    }

    static auto lastPosition = sf::Mouse::getPosition(*m_pWindow);

    auto pos = sf::Mouse::getPosition(*m_pWindow);
    auto change = pos - lastPosition;

    if (!m_isMouseCentreLocked)
    {
        sf::Mouse::setPosition(m_winowCentre, *m_pWindow);
        lastPosition = m_winowCentre;
    } else {
        lastPosition = pos;
    }

    return
    {
        // Convert to float for that smooth movement
        change.y/10.f, change.x/10.f, 0
    };
}

sf::Vector2i KeyboardController::getMousePositionRelativeToWindow() const
{
	return sf::Mouse::getPosition(*m_pWindow);
}

bool KeyboardController::isPressed(Controller::Input input) const
{
    //if (!m_pWindow->hasFocus()) return false;
    return sf::Keyboard::isKeyPressed(m_keyMap.at(input));
}
