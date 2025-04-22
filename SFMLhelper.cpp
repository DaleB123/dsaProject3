#include "SFMLhelper.h"
#include <iostream>

SFMLhelper::SFMLhelper()
{
    window.create(sf::VideoMode(800, 600), "Imdbb", sf::Style::Close);
    font.loadFromFile("../fonts/times.ttf");

    sf::Image img;
    img.loadFromFile("../images/movieclip.png");
    window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());

    buttons.resize(3);
    texts.resize(3);

    addText("Input: [Dataset]", sf::Vector2f(150, 50), 30);
    addText("Sort by:", sf::Vector2f(600, 50), 20);


    state = 1;

    auto start = [](SFMLhelper *helper)
    {
        helper->setState(2);
        string text;
        if (helper->getSort() == 0) text = "Actors";
        else text = "Movies";
        helper->addText(text, sf::Vector2f(675, 50), 20);
    };
    auto sortMovie = [](SFMLhelper *helper)
    {
        helper->setSort(1);
    };
    auto sortActor = [](SFMLhelper *helper)
    {
        helper->setSort(0);
    };
    addButton("Start", sf::Vector2f(325,250), 50, start);
    addButton("Movies", sf::Vector2f(650,80),25, sortMovie);
    addButton("Actors", sf::Vector2f(650, 50), 25, sortActor);

    state = 2;

    addText("Heap Sort:", sf::Vector2f(400,150), 25);
    addText("Time Taken:", sf::Vector2f(400,175), 20);
    addText("Merge Sort:", sf::Vector2f(400,300), 25);
    addText("Time Taken:", sf::Vector2f(400,325), 20);

    state = 1;
}

SFMLhelper::~SFMLhelper()
{
    window.close();
}

void SFMLhelper::addText(string str, sf::Vector2f pos, int size)
{
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::Black);
    text.setPosition(pos);
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);

    texts[state].push_back(text);

}

void SFMLhelper::addButton(string str, sf::Vector2f pos, int size, function<void(SFMLhelper *helper)> onClick)
{
    sf::Text text;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::Black);

    sf::RectangleShape border;
    border.setFillColor(sf::Color(255,0,0,40));
    border.setSize(sf::Vector2f(text.getGlobalBounds().width*1.2, text.getGlobalBounds().height*1.2));

    text.setPosition(border.getPosition().x + border.getSize().x/2.f, border.getPosition().y);
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/3);

    sf::RenderTexture renderTexture;
    renderTexture.create(text.getGlobalBounds().width*1.2, text.getGlobalBounds().height*1.2);

    renderTexture.display();
    renderTexture.draw(border);
    renderTexture.draw(text);
    Button button(renderTexture.getTexture(), onClick, pos);
    buttons[state].push_back(button);
}

void SFMLhelper::update()
{
    window.clear(sf::Color::White);
    for (auto b : buttons[0])
    {
        sf::Sprite sprite;
        sprite.setTexture(b.texture);
        sprite.setPosition(b.pos);
        window.draw(sprite);
    }
    for (auto b : buttons[state])
    {
        sf::Sprite sprite;
        sprite.setTexture(b.texture);
        sprite.setPosition(b.pos);
        window.draw(sprite);
    }

    for (auto t : texts[0])
    {
        window.draw(t);
    }
    for (auto t : texts[state])
    {
        window.draw(t);
    }
    window.display();
}

void SFMLhelper::buttonPressed()
{
    auto mp = sf::Mouse::getPosition(window);
    auto tp = window.mapPixelToCoords(mp);
    for (auto button : buttons[state])
    {
        sf::Sprite sprite;
        sprite.setTexture(button.texture);
        sprite.setPosition(button.pos);
        if (sprite.getGlobalBounds().contains(mp.x, mp.y))
        {
            button.onClick(this);
            break;
        }
    }
}

    void SFMLhelper::setState(int state)
{
    this->state = state;
}

void SFMLhelper::setSort(int sort)
{
    if (this->sort != sort)
    {
        sf::Vector2f temp = buttons[state][1].pos;
        buttons[state][1].pos = buttons[state][2].pos;
        buttons[state][2].pos = temp;
        this->sort = sort;
    }
}

int SFMLhelper::getSort()
{
    return sort;
}

