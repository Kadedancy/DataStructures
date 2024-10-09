#include <textcircle.h>

namespace ssuds
{
    TextCircle::TextCircle()
    {

    }

    TextCircle::TextCircle(const sf::Vector2f& position, const std::string& text, const sf::Font& font)
    {
        m_text.setFont(font);
        m_text.setString(text);
        m_text.setCharacterSize(20);
        m_text.setFillColor(sf::Color::Black);

        sf::FloatRect textBounds = m_text.getLocalBounds();
        float textWidth = textBounds.width / 2.f;

        m_text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
        m_text.setPosition(position.x, position.y);

        m_circle.setOrigin(textWidth, textWidth);
        m_circle.setPosition(position);
        m_circle.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255));
        m_circle.setRadius(textWidth);


    }

    bool TextCircle::inside(const sf::Vector2f& point) const
    {
        sf::Vector2f circleCenter = m_circle.getPosition();
        float radius = m_circle.getRadius();
        float distance = std::sqrt((point.x - circleCenter.x) * (point.x - circleCenter.x) +
            (point.y - circleCenter.y) * (point.y - circleCenter.y));
        return distance <= radius;
    }

    void TextCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_circle, states);
        target.draw(m_text, states);
    }

    void TextCircle::setPosition(const sf::Vector2f& position)
    {
        m_circle.setPosition(position);
        m_text.setPosition(position);
    }

    bool TextCircle::notMoving()
    {
        return true;
    }

    void TextCircle::setCircleColor(const sf::Color& color)
    {
        m_circle.setFillColor(color);
    }
}

