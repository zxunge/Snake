// SPDX-License-Identifier: MIT

#include <SFML/Window/Keyboard.hpp>

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include <functional>
#include <vector>

class KeyHandler
{
private:
    sf::Clock                           m_pressClock;
    bool                                m_isKeyPressed       = false;
    bool                                m_longPressTriggered = false;
    std::vector<sf::Keyboard::Scancode> m_targetKeys;
    float                               m_longPressDuration;

    std::function<void()> m_onPress;
    std::function<void()> m_onLongPress;
    std::function<void()> m_onLongRelease;
    std::function<void()> m_onShortRelease;

public:
    KeyHandler(std::vector<sf::Keyboard::Scancode> keys, float duration = 0.5f) :
        m_targetKeys(keys),
        m_longPressDuration(duration)
    {
    }

    void setHandlers(std::function<void()> onPress        = nullptr,
                     std::function<void()> onLongPress    = nullptr,
                     std::function<void()> onLongRelease  = nullptr,
                     std::function<void()> onShortRelease = nullptr)
    {
        m_onPress        = onPress;
        m_onLongPress    = onLongPress;
        m_onLongRelease  = onLongRelease;
        m_onShortRelease = onShortRelease;
    }

    void update()
    {
        for (auto targetKey : m_targetKeys)
        {
            if (sf::Keyboard::isKeyPressed(targetKey))
            {
                if (!m_isKeyPressed)
                {
                    m_isKeyPressed       = true;
                    m_longPressTriggered = false;
                    m_pressClock.restart();
                    if (m_onPress)
                        m_onPress();
                }
                else if (m_pressClock.getElapsedTime().asSeconds() >= m_longPressDuration)
                {
                    m_longPressTriggered = true;
                    if (m_onLongPress)
                        m_onLongPress();
                }
                return;
            }
        }
        if (m_isKeyPressed)
        {
            bool wasLongPress    = m_longPressTriggered;
            m_isKeyPressed       = false;
            m_longPressTriggered = false;

            if (wasLongPress)
            {
                if (m_onLongRelease)
                    m_onLongRelease();
            }
            else
            {
                if (m_onShortRelease)
                    m_onShortRelease();
            }
        }
    }
};
