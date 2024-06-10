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
    string mode = "-b";
    ofstream out("output");
    sf::Image img;
    img.loadFromFile("testImg.png");
    cout << img.getSize().x << endl;
    int sizeX = img.getSize().x;
    int sizeY = img.getSize().y;
    int pixel_size = 3;
    if (mode == "-a") {
        int q = 0;
        for (int x = 0; x < sizeX; x += pixel_size) {
            q++;
            for (int y = 0; y < sizeY; y += pixel_size) {
                sf::Color c = img.getPixel(x, y);
                out << "draw color " << int(c.r) << " " << int(c.g) << " " << int(c.b) << endl;
                out << "draw rect " << x << " " << sizeY - y << " " << pixel_size << " " << pixel_size << " 0 0" << endl;
            }
            if (q % 8 == 0) out << "drawflush display1" << endl;
        }
        out << "drawflush display1" << endl;
    } else if (mode == "-c") {
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
        }
    } else if (mode == "-b") {
        vector<line> lines = {};
        int counter = 0;
        //line min = line();
        //min.x1 = -1;
        sf::Image newImage = img;
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

            sf::Texture texture;
            texture.loadFromFile("testImg.png");
            sf::Sprite sprite;
            sprite.setTexture(texture);

            window.draw(sprite);
            
            int r = rand() % 255;
            int g = rand() % 255;
            int b = rand() % 255;

            int x1 = rand() % Width;
            int y1 = rand() % Height;
            int x2 = rand() % Width;
            int y2 = rand() % Height;

            if (x2 > y2) {
                y2 = y1;
            } else {
                x2 = x1;
            }

            sf::Vertex line[] =
            {
                sf::Vertex(sf::Vector2f(x1, y1), sf::Color(r, g, b)),
                sf::Vertex(sf::Vector2f(x2, y2), sf::Color(r, g, b))
            };
            //line.color = sf::Color(250, 150, 100);
            window.draw(line, 2, sf::Lines);
            
            ll sum = 0;
            for (int x = 0; x < sizeX; x++) {
                for (int y = 0; y < sizeY; y++) {
                    sf::Color c = newImage.getPixel(x, y);
                    if (x >= x1 && x <= x2 && y >= y1 && y <= y2) {
                        sum += abs(c.r - r) + abs(c.g - g) + abs(c.b - b);
                        //cout << "yeeee" << endl;
                    }
                }
            }
            cout << sum << endl;
            if (sum == 0) {
                out << "draw color " << r << " " << g << " " << b << endl;
                out << "draw line " << x1 << " " << y1 << " " << x2 << " " << y2 << " 0 0" << endl;
                out << "drawflush display1" << endl;
            }

            /*int x1 = rand() % Width;
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

            window.draw(convex);*/




            texture.update(img);
            sprite.setTexture(texture);

            //window.draw(sprite);

            window.display();
        }
    }
    return 0;
}