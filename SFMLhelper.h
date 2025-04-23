
#ifndef SFMLHELPER_H
#define SFMLHELPER_H
#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>
#include <chrono>
#include <string>

using namespace std;

class SFMLhelper
{
    struct Button
    {
        sf::Texture texture;
        function<void(SFMLhelper*)> onClick;
        sf::Vector2f pos;

        Button(sf::Texture texture, function<void(SFMLhelper*)> onClick, sf::Vector2f pos)
        {
            this->texture = texture;
            this->onClick = onClick;
            this->pos = pos;
        }
    };
    sf::Font font;
    vector<vector<Button>> buttons = vector<vector<Button>>();
    vector<vector<sf::Text>> texts = vector<vector<sf::Text>>();
    int state = 0;
    int sort = 0;

public:
    sf::RenderWindow window;
    SFMLhelper();
    ~SFMLhelper();

    void addText(string str, sf::Vector2f pos, int size);
    void addButton(string str, sf::Vector2f pos, int size, function<void(SFMLhelper *helper)> onClick);
    void buttonPressed();
    void update();
    void setState(int state);
    void setSort(int sort);
    int getSort();

    void compareAlgorithms();
};

#endif