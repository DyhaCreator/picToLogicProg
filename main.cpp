#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#define ll long long
using namespace std;

const int Width = 500;
const int Height = 500;

struct line{
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int yw = 0;
    line() {}
};

sf::Event ev;
sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(Width * 2, Height), "PicToLogic");

int main() {
    window.setFramerateLimit(5);
    while(window.isOpen()){
        while(window.pollEvent(ev)){
            switch(ev.type){
            case sf::Event::Closed:
                window.close();
                break;
            }
        }
        window.clear(sf::Color(150, 150, 150));
        sf::Image img;
        img.loadFromFile("testImg.png");
        sf::Texture texture;
        texture.loadFromImage(img);
        sf::Sprite sprite;
        sprite.setTexture(texture);

        window.draw(sprite);

        /*sf::Texture texture;
        texture.loadFromFile("testImg.png");
        sf::Sprite sprite;
        sprite.setTexture(texture);

        window.draw(sprite);*/

        int r = rand() % 255;
        int g = rand() % 255;
        int b = rand() % 255;

        int x1 = rand() % Width;
        int y1 = rand() % Height;
        int x2 = rand() % Width;
        int y2 = rand() % Height;
        int x3 = rand() % Width;
        int y3 = rand() % Height;

        sf::ConvexShape convex;
        convex.setPointCount(3);
        convex.setFillColor(sf::Color(r, g, b));
        convex.setPoint(0, sf::Vector2f(x1, y1));
        convex.setPoint(1, sf::Vector2f(x2, y2));
        convex.setPoint(2, sf::Vector2f(x3, y3));

        window.draw(convex);
        window.display();
    }
    return 0;
}