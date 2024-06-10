#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#define ll long long
#define INF 1000000007
using namespace std;

const int Width = 200;
const int Height = 200;

struct tr{
    int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int x3 = 0;
    int y3 = 0;
    sf::Color c;
    tr() {}
    tr(int x1, int y1, int x2, int y2, int x3, int y3, sf::Color c) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
        this->c = c;
    }
};

sf::Event ev;
sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(Width * 2, Height), "PicToLogic");

int main() {
    ofstream out("output");
    //out << "draw color 0 0 0 255 0 0\ndraw rect 0 0 100 100 0 0\ndrawflush display1" << endl;
    sf::Image img;
    img.loadFromFile("test5.png");
    window.setFramerateLimit(1000);

    if (mode == '-r') {
        int tileSizeX = 100;
        int tileSizeY = 100;
        ll sumImg = 0;
        for (int x = 0; x < img.getSize().x; x++) {
            for (int y = 0; y < img.getSize().y; y++) {
                sf::Color c = img.getPixel(x, y);
                sumImg += c.r + c.g + c.b;
            }
        }
        cout << sumImg << endl;
        int gen = 0;
        int gens = 0;
        int best = INF;
        tr bestTriangle = tr();
        vector<tr> trImage = {};
        sf::Image bestErr;

        int tileCoordX = 0;
        int tileCoordY = 0;

        int maxTrianglesInTile = 100;

        ll lastErr = sumImg;
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
            texture.loadFromImage(img);
            sf::Sprite sprite;
            sprite.setTexture(texture);

            window.draw(sprite);

            for (int i = 0; i < trImage.size(); i++) {
                sf::ConvexShape convex;
                convex.setPointCount(3);
                convex.setFillColor(trImage[i].c);
                convex.setPoint(0, sf::Vector2f(trImage[i].x1, trImage[i].y1));
                convex.setPoint(1, sf::Vector2f(trImage[i].x2, trImage[i].y2));
                convex.setPoint(2, sf::Vector2f(trImage[i].x3, trImage[i].y3));

                window.draw(convex);
            }

            /*sf::Texture texture;
            texture.loadFromFile("testImg.png");
            sf::Sprite sprite;
            sprite.setTexture(texture);

            window.draw(sprite);*/

            int r = rand() % 255;
            int g = rand() % 255;
            int b = rand() % 255;

            int x1 = min(rand() % (tileSizeX + tileSizeX / 10) + tileCoordX * tileSizeX, (int)img.getSize().x);
            int y1 = min(rand() % (tileSizeY + tileSizeY / 10) + tileCoordY * tileSizeY, (int)img.getSize().y);
            int x2 = min(rand() % (tileSizeX + tileSizeX / 10) + tileCoordX * tileSizeX, (int)img.getSize().x);
            int y2 = min(rand() % (tileSizeY + tileSizeY / 10) + tileCoordY * tileSizeY, (int)img.getSize().y);
            int x3 = min(rand() % (tileSizeX + tileSizeX / 10) + tileCoordX * tileSizeX, (int)img.getSize().x);
            int y3 = min(rand() % (tileSizeY + tileSizeY / 10) + tileCoordY * tileSizeY, (int)img.getSize().y);

            sf::ConvexShape convex;
            convex.setPointCount(3);
            convex.setFillColor(sf::Color(r, g, b));
            convex.setPoint(0, sf::Vector2f(x1, y1));
            convex.setPoint(1, sf::Vector2f(x2, y2));
            convex.setPoint(2, sf::Vector2f(x3, y3));

            window.draw(convex);

            convex.setPoint(0, sf::Vector2f(x1, Height - y1));
            convex.setPoint(1, sf::Vector2f(x2, Height - y2));
            convex.setPoint(2, sf::Vector2f(x3, Height - y3));

            sf::RenderTexture render;
            render.create(Width, Height);
            render.clear();

            for (int i = 0; i < trImage.size(); i++) {
                sf::ConvexShape convex;
                convex.setPointCount(3);
                convex.setFillColor(trImage[i].c);
                convex.setPoint(0, sf::Vector2f(trImage[i].x1, Height - trImage[i].y1));
                convex.setPoint(1, sf::Vector2f(trImage[i].x2, Height - trImage[i].y2));
                convex.setPoint(2, sf::Vector2f(trImage[i].x3, Height - trImage[i].y3));

                render.draw(convex);
            }

            render.draw(convex);
            sprite.setTexture(render.getTexture());
            sprite.setPosition(Width, 0);
            window.draw(sprite);

            sf::Image triangle;
            triangle = render.getTexture().copyToImage();

            sf::Image err;
            err.create(Width, Height);
            ll sumErr = lastErr;
            for (int x = tileCoordX * tileSizeX; x < (tileCoordX + 1) * tileSizeX; x++) {
                for (int y = tileCoordY * tileSizeY; y < (tileCoordY + 1) * tileSizeY; y++) {
                    sf::Color c1 = img.getPixel(x, y);
                    sf::Color c2 = triangle.getPixel(x, y);
                    err.setPixel(x, y, sf::Color(abs(c1.r - c2.r), abs(c1.g - c2.g), abs(c1.b - c2.b)));
                    sumErr -= c1.r + c1.g + c1.b;
                    sumErr += abs(c1.r - c2.r) + abs(c1.g - c2.g) + abs(c1.b - c2.b);
                }
            }
            //cout << sumErr << endl;
            if (best > sumErr) {
                best = sumErr;
                bestTriangle = tr(x1, y1, x2, y2, x3, y3, sf::Color(r, g, b));
                bestErr = err;
            }
            texture.loadFromImage(err);
            sprite.setTexture(texture);
            window.draw(sprite);

            window.display();
            gen++;
            //cout << gen << endl;
            if (gen >= 5000) {
                cout << best << endl;
                best = INF;
                trImage.push_back(bestTriangle);
                //img = bestErr;
                gen = 0;
                out << "draw color " << int(bestTriangle.c.r) << " " << int(bestTriangle.c.g) << " " << int(bestTriangle.c.b) << " 255 0 0" << endl;
                out << "draw triangle " << bestTriangle.x1 << " " << Height - bestTriangle.y1 << " " << 
                bestTriangle.x2 << " " << Height - bestTriangle.y2 << " " <<
                bestTriangle.x3 << " " << Height - bestTriangle.y3 << endl;
                if (gens % 10 == 0) out << "drawflush display1" << endl;
                gens++;
                //cout << tileCoordX << " " << tileCoordY << endl;
                //cout << tileSizeX << " " << tileSizeY << endl;
                if (gens > maxTrianglesInTile) {
                    tileCoordX++;
                    if (tileCoordX >= img.getSize().x / tileSizeX) {
                        tileCoordX = 0;
                        tileCoordY++;
                    }
                    if (tileCoordY >= img.getSize().y / tileSizeY) break;
                    gens = 0;
                }
            }
        }
        out << "drawflush display1" << endl;
        out << "stop" << endl;
    }
    return 0;
}