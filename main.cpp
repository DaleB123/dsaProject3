#include <iostream>
#include <SFML/Graphics.hpp>
#include "SFMLhelper.h"

using namespace std;

int main()
{
    SFMLhelper h;

/*
    visual.draw(h.addText("Input: [Dataset]", sf::Vector2f(50, 30), 30));
    visual.draw(h.addText("Sort by:", sf::Vector2f(600, 30), 20));
    visual.draw(h.addText("Heap Sort", sf::Vector2f(325, 150), 25));
    visual.draw(h.addText("Merge Sort", sf::Vector2f(325, 300), 25));
    visual.draw(h.addText("Difference:", sf::Vector2f(50, 400), 25));
    visual.draw(h.addText("Output:", sf::Vector2f(50, 525), 25));
*/


    while (h.window.isOpen())
    {
        h.update();
        sf::Event event;
        while (h.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                h.window.close();
            } else if (event.type == sf::Event::MouseButtonReleased)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    h.buttonPressed();
                }
            }
        }
    }
    return 0;
}
