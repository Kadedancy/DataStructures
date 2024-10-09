#define DO_UNIT_TEST 0
#if DO_UNIT_TEST
#include <gtest/gtest.h>
#else
#include <SFML/Graphics.hpp>
#include <visual_graph.h>
#endif

#if !DO_UNIT_TEST
// some helper functions used in main

#endif

int main()
{
#if DO_UNIT_TEST
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Graph Creator");

    sf::Font status_font, circle_font;
    if (!status_font.loadFromFile("../../../media/fonts/Courier_Prime/CourierPrime-Regular.ttf") ||
        !circle_font.loadFromFile("../../../media/fonts/Open_Sans/static/OpenSans-Regular.ttf"))
    {
        std::cout << "Error loading fonts\n";
        return EXIT_FAILURE;
    }

    misc::VisualGraph Graph(circle_font, "../../../media/output.txt");

    int startNode = -1;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f clickPosition(event.mouseButton.x, event.mouseButton.y);

                for (auto& node : Graph.mCircleData)
                {
                    if (node.second.point_inside(clickPosition))
                    {
                        startNode = node.first;

                        node.second.set_highlight(sf::TextCircleHighlightMode::WHITE);

                        break;
                    }
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A)
            {
                GC.BFTraversal(startNode);

                std::cout << "Breadth-First Traversal from Node " << startNode << ":\n";
                for (const auto& pair : Graph.traversal) 
                {
                    std::cout << "Node: " << pair.first << ", Parent: " << pair.second << '\n';
                }
                std::cout << std::endl; 
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
            {
                GC.DFTraversal(startNode);

                std::cout << "Depth-First Traversal from Node " << startNode << ":\n";
                for (const auto& pair : Graph.traversal) 
                {
                    std::cout << "Node: " << pair.first << ", Parent: " << pair.second << '\n';
                }
                std::cout << std::endl;
            }
        }

        window.clear(sf::Color::Black);

        Graph.draw(window);

        window.display();
    }

    return EXIT_SUCCESS;
#endif
}