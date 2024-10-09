#define DO_UNIT_TESTING 0
#include <iostream>
#if DO_UNIT_TESTING
#include <gtest/gtest.h>
#else
#include <SFML/Graphics.hpp>
#include <worddrawer.h>
#endif


int main()
{
#if DO_UNIT_TESTING
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else
    sf::RenderWindow window(sf::VideoMode(800, 600), "Window");
    sf::Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        return EXIT_FAILURE;
    }
    ssuds::WordDrawer wordDrawer("american-words.80");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else {
                wordDrawer.handleInput(event, window);
            }
        }

        wordDrawer.update(window);

        window.clear(sf::Color::White);

        window.draw(wordDrawer);

        window.display();
    }
    return EXIT_SUCCESS;
#endif
}
