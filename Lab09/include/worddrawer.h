#pragma once
#include<iostream>
#include <fstream>
#include <queue.h>
#include <stack.h>
#include <SFML/Graphics.hpp>
#include <textcircle.h>
#include <array_list.h>

namespace ssuds
{
    class WordDrawer : public sf::Drawable
    {
    private:
        sf::Font font;
        std::ifstream wordFile;
        ArrayList<TextCircle> arrayOfCircles;
        ssuds::queue<std::string> wordQueue;
        sf::Text statusText;
        bool wordMoving;
        bool wordPlaced;


    public:
        WordDrawer(const std::string& filename);
        ~WordDrawer();

        void handleInput(sf::Event& event, sf::RenderWindow& window);
        void update(sf::RenderWindow& window);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        void loadWords();


    };
}