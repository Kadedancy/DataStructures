#define DO_UNIT_TESTING 0
#include <iostream>
#if DO_UNIT_TESTING
#include <gtest/gtest.h>
#else
#include <graph.h>
#include <textcircle.h>
#endif


int main()
{
#if DO_UNIT_TESTING
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
#else

    std::ifstream file("sampletxt.txt");
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file." << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Visualization");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) 
    {
        std::cerr << "Error loading font." << std::endl;
        return 1;
    }

    Graph<int, float> graph;

    std::string line;
    while (std::getline(file, line)) 
    {
        std::cout << "Read line: " << line << std::endl;
        std::stringstream ss(line);
        char type;
        ss >> type;
        if (type == 'n') 
        {
            int nodeId;
            std::string displayText;
            int red, green, blue;
            float x, y;

            ss.ignore(1);
            ss >> nodeId;
            ss.ignore(1); 
            std::getline(ss, displayText, ':');
            ss >> red;
            ss.ignore(1);
            ss >> green;
            ss.ignore(1);
            ss >> blue;
            ss.ignore(1); 
            ss >> x;
            ss.ignore(1); 
            ss >> y;

            std::cout << "Parsed node: " << nodeId << ", " << displayText << ", " << red << ", " << green << ", " << blue << ", " << x << ", " << y << std::endl; // Debug output

            graph.addNode(nodeId);

            ssuds::TextCircle circle(sf::Vector2f(x, y), displayText, font);
            circle.setCircleColor(sf::Color(red, green, blue));

            window.draw(circle);
        }
        else if (type == 'e') 
        {
            int nodeId1;
            int nodeId2;
            float distance;

            ss.ignore(1); 
            ss >> nodeId1;
            ss.ignore(1); 
            ss >> nodeId2;
            ss.ignore(1); 
            ss >> distance;

            std::cout << "Parsed edge: " << nodeId1 << ", " << nodeId2 << ", " << distance << std::endl; 

        }
    }

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.display();
    }
#endif
}
