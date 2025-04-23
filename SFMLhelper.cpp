#include "SFMLhelper.h"
#include "heapSort.h"
#include "mergeSort.h"
#include <fstream>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/MovieActorWikidata.h"

using namespace bridges;

SFMLhelper::SFMLhelper()
{
    window.create(sf::VideoMode(800, 600), "Imdbb", sf::Style::Close);
    font.loadFromFile("../../fonts/times.ttf");

    sf::Image img;
    img.loadFromFile("../../images/movieclip.png");
    window.setIcon(img.getSize().x, img.getSize().y, img.getPixelsPtr());

    buttons.resize(3);
    texts.resize(3);

    addText("Input: Wikidata Actors and Movies", sf::Vector2f(215, 50), 25);
    addText("Sort by:", sf::Vector2f(600, 50), 20);


    state = 1;

    auto start = [](SFMLhelper *helper)
    {
        helper->setState(2);
        string text;
        if (helper->getSort() == 0) text = "Actors";
        else text = "Movies";
        helper->addText(text, sf::Vector2f(675, 50), 20);
        helper->compareAlgorithms();
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
    addText("Start", sf::Vector2f(375,260), 40);
    addButton("Movies", sf::Vector2f(650,80),25, sortMovie);
    addText("Movies", sf::Vector2f(675,80), 20);
    addButton("Actors", sf::Vector2f(650, 50), 25, sortActor);
    addText("Actors", sf::Vector2f(675,50), 20);

    state = 2;

    addText("Heap Sort:", sf::Vector2f(400,150), 25);
    addText("Merge Sort:", sf::Vector2f(400,300), 25);

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

    text.setPosition(border.getPosition().x + border.getSize().x/2.f, border.getPosition().y+border.getSize().y/2.f);
    text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/3);

    sf::RenderTexture renderTexture;
    renderTexture.create(text.getGlobalBounds().width*1.2, text.getGlobalBounds().height*1.2);

    renderTexture.display();
    renderTexture.draw(border);
    renderTexture.draw(text);
    buttons[state].push_back(Button(renderTexture.getTexture(), onClick, pos));
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
        sf::Vector2f temp2 = texts[state][1].getPosition();
        buttons[state][1].pos = buttons[state][2].pos;
        buttons[state][2].pos = temp;
        texts[state][1].setPosition(texts[state][2].getPosition());
        texts[state][2].setPosition(temp2);
        this->sort = sort;
    }
}

int SFMLhelper::getSort()
{
    return sort;
}

void SFMLhelper::compareAlgorithms()
{
    heapSort hs;
    mergeSort ms;
    Bridges bridges(1, "dayrianfigueroa", "1543558140810");
    DataSource ds (&bridges);
    vector<bridges::MovieActorWikidata> data = ds.getWikidataActorMovie(2000,2001);
    vector<string> heap;
    vector<string> merge;
    if (sort == 0)
    {
        for (auto point : data)
        {
            heap.push_back(point.getActorName());
            merge.push_back(point.getActorName());
        }
    } else
    {
        for (auto point : data)
        {
            heap.push_back(point.getMovieName());
            merge.push_back(point.getMovieName());
        }
    }



    chrono::system_clock::time_point heapStart = chrono::system_clock::now();
    hs.sort(heap);
    chrono::system_clock::time_point heapEnd = chrono::system_clock::now();
    int heapTime = chrono::duration_cast<chrono::milliseconds>(heapEnd - heapStart).count();
    addText("Time Taken: " + to_string(heapTime) + " ms", sf::Vector2f(400,175), 20);

    chrono::system_clock::time_point mergeStart = chrono::system_clock::now();
    ms.mergesort(merge);
    chrono::system_clock::time_point mergeEnd = chrono::system_clock::now();
    int mergeTime = chrono::duration_cast<chrono::milliseconds>(mergeEnd - mergeStart).count();
    addText("Time Taken: " + to_string(mergeTime) + " ms", sf::Vector2f(400,325), 20);

    int difference;
    string faster;
    if (mergeTime > heapTime) { difference = mergeTime - heapTime; faster = "Heap Sort"; }
    else { difference = heapTime - mergeTime; faster = "Merge Sort"; }

    addText("Difference: " + to_string(difference) + " ms", sf::Vector2f(100,400), 20);
    addText("Faster Algorithm: " + faster, sf::Vector2f(150,425), 20);


    ofstream file;

    file.open("../../output/out1.txt");
    for (auto n : heap)
    {
        file << n << endl;
    }
    file.close();

    file.open("../../output/out2.txt");
    for (auto n : merge)
    {
        file << n << endl;
    }
    file.close();

}