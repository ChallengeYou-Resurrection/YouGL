#include "KeyboardController.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

KeyboardController::KeyboardController()
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

glm::vec3 KeyboardController::getLookChange(const sf::RenderWindow& window) const
{
    static sf::Vector2i center = { 1280 / 2, 720 / 2 };
    static auto lastPosition = sf::Mouse::getPosition(window);

    auto pos = sf::Mouse::getPosition(window);
    auto change = pos - lastPosition;

    //sf::Mouse::setPosition(center, window);
    lastPosition = pos;
    return
    {
        change.y/10, change.x/10, 0
    };
}

bool KeyboardController::isPressed(Controller::Input input) const
{
    return sf::Keyboard::isKeyPressed(m_keyMap.at(input));
}
