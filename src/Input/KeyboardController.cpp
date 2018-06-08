#include "KeyboardController.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

KeyboardController::KeyboardController(sf::RenderWindow& window)
    : m_pWindow (&window)
{
    m_keyMap.emplace(Controller::Input::Forward, sf::Keyboard::Key::W);
    m_keyMap.emplace(Controller::Input::Back, sf::Keyboard::Key::S);
    m_keyMap.emplace(Controller::Input::Left, sf::Keyboard::Key::A);
    m_keyMap.emplace(Controller::Input::Right, sf::Keyboard::Key::D);
    m_keyMap.emplace(Controller::Input::Jump, sf::Keyboard::Key::Space);
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

bool KeyboardController::firePressed() const
{
    return isPressed(Controller::Input::Fire);
}

void KeyboardController::toggleLookLock()
{
    m_isLookLocked = !m_isLookLocked;
    if (m_isLookLocked) {
        m_isLookLocked = false;
        m_pWindow->setMouseCursorGrabbed(true);
        m_pWindow->setMouseCursorVisible(false);
    }
    else {
        m_isLookLocked = true;
        m_pWindow->setMouseCursorGrabbed(false);
        m_pWindow->setMouseCursorVisible(true);
    }
}

glm::vec3 KeyboardController::getLookChange() const
{
    if (m_isLookLocked) {
        return { 0, 0, 0 };
    }

    static sf::Vector2i center = { 1280 / 2, 720 / 2 };
    static auto lastPosition = sf::Mouse::getPosition(*m_pWindow);

    auto pos = sf::Mouse::getPosition(*m_pWindow);
    auto change = pos - lastPosition;

    if (m_isMouseCentreLocked)
    {
        sf::Mouse::setPosition(center, *m_pWindow);
        lastPosition = center;
    } else {
        lastPosition = pos;
    }

    return
    {
        // Convert to float for that smooth movement
        change.y/10.f, change.x/10.f, 0
    };
}

bool KeyboardController::isPressed(Controller::Input input) const
{
    return sf::Keyboard::isKeyPressed(m_keyMap.at(input));
}
