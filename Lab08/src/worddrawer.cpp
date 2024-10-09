#include "WordDrawer.h"


namespace ssuds
{
    WordDrawer::WordDrawer(const std::string& filename)
    {
        if (!font.loadFromFile("arial.ttf"))
        {
            throw std::runtime_error("Failed to load font");
        }
        
        wordMoving = false;

        statusText.setFont(font);
        statusText.setCharacterSize(24);
        statusText.setFillColor(sf::Color::Black);
        statusText.setPosition(10, 10);
        statusText.setString("Left Click To Generate Circle");

        wordFile.open(filename, std::ios::binary);
        if (!wordFile.is_open())
        {
            throw std::runtime_error("Failed to open word file");
        }

        loadWords();
    }

    WordDrawer::~WordDrawer()
    {
        wordFile.close();
    }

    void WordDrawer::handleInput(sf::Event& event, sf::RenderWindow& window)
    {
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            wordMoving = true;
            if (wordMoving)
            {
                statusText.setString("Left Click To Place Circle , Right Click To Delete Last Circle");
            }

            if (arrayOfCircles.size() != 0)
            {
                if (!wordQueue.empty())
                {
                    std::string word = wordQueue.head();
                    wordQueue.dequeue();
                    arrayOfCircles.append(TextCircle(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)), word, font));
                }
                else
                {
                    loadWords();
                }
            }
            else
            {
                if (!wordQueue.empty())
                {
                    std::string word = wordQueue.head();
                    wordQueue.dequeue();
                    arrayOfCircles.append(TextCircle(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y)), word, font));
                }
            }
            wordMoving = false;
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
        {
            if (arrayOfCircles.size() != 0)
            {
                arrayOfCircles.remove(arrayOfCircles.size() - 1);
            }
        }
    }

    void WordDrawer::update(sf::RenderWindow& window)
    {
        if (arrayOfCircles.size() != 0)
        {
            sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

            TextCircle& lastCircle = arrayOfCircles[arrayOfCircles.size() - 1];

            if (lastCircle.notMoving())
            {
                lastCircle.setPosition(mousePosition);
            }
        }
    }

    void WordDrawer::loadWords()
    {
        std::ifstream countFile("american-words.80");
        unsigned int totalLines = 0;
        std::string line;

        while (std::getline(countFile, line)) 
        {
            ++totalLines;
        }

        countFile.close();

        wordFile.clear();
        wordFile.seekg(0, std::ios::beg);

        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int i = 0; i < 10; ++i)
        {
            int randomPosition = std::rand() % totalLines;

            wordFile.clear();
            wordFile.seekg(0, std::ios::beg);

            for (int j = 0; j < randomPosition; j++) 
            {
                std::getline(wordFile, line);
            }

            std::getline(wordFile, line);
            wordQueue.enqueue(line);
        }
    }
    void WordDrawer::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        for (unsigned int i = 0; i < arrayOfCircles.size(); ++i)
        {
            target.draw(arrayOfCircles[i], states);
        }
        target.draw(statusText, states);
    }
}