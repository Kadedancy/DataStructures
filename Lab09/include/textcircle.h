#pragma once
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <graph.h>

namespace ssuds
{
    class TextCircle : public sf::Drawable
    {
    public:
        TextCircle();

        TextCircle(const sf::Vector2f& position, const std::string& text, const sf::Font& font);

        bool inside(const sf::Vector2f& point) const;

        void setPosition(const sf::Vector2f& position);

        bool notMoving();
        
        void setCircleColor(const sf::Color& color);

    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        sf::CircleShape m_circle;
        sf::Text m_text;

    };
}
