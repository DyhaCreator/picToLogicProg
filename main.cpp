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
    /*int x1 = 0;
    int y1 = 0;
    int x2 = 0;
    int y2 = 0;
    int x3 = 0;
    int y3 = 0;*/
    int x = 0;
    int y = 0;
    int r = 0;
    sf::Color c;
    tr() {}
    /*tr(int x1, int y1, int x2, int y2, int x3, int y3, sf::Color c) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
        this->x3 = x3;
        this->y3 = y3;
        this->c = c;
    }*/
    tr(int x, int y, int r, sf::Color c) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->c = c;
    }
};

sf::Event ev;
sf::RenderWindow window = sf::RenderWindow(sf::VideoMode(Width * 2, Height), "PicToLogic");

int main() {
    string mode = "-r";
    ofstream out("output");
    //out << "draw color 0 0 0 255 0 0\ndraw rect 0 0 100 100 0 0\ndrawflush display1" << endl;
    sf::Image img;
    img.loadFromFile("test3.png");
    window.setFramerateLimit(1000);

    if (mode == "-b") {
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

            out << "draw color 0 0 0 255 0 0\ndraw rect 0 0 100 100 0 0\ndrawflush display1" << endl;

            window.display();
        }
    }

    if (mode == "-a") {
        int step = 0;
        
        sf::Image after;
        after.create(img.getSize().x, img.getSize().y);

        while(window.isOpen()){
            while(window.pollEvent(ev)){
                switch(ev.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                }
            }
            window.clear(sf::Color(150, 150, 150));

            window.clear(sf::Color(150, 150, 150));
            sf::Texture texture;
            texture.loadFromImage(img);
            sf::Sprite sprite;
            sprite.setTexture(texture);

            window.draw(sprite);

            texture.loadFromImage(after);
            sprite.setTexture(texture);
            sprite.setPosition(Width, 0);

            window.draw(sprite);

            int sx = rand() % Width;
            int sy = rand() % Height;

            int radius = 10;
            sf::CircleShape point(radius);
            point.setFillColor(sf::Color(100, 250, 50));
            point.setPosition(sx - radius, sy - radius);

            window.draw(point);

            window.display();
        }
    }

    if (mode == "-r") {
        int tileSizeX = 200;
        int tileSizeY = 200;
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

        int maxTrianglesInTile = INF;

        ll lastErr = sumImg;

        int cr = 30;
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
                sf::CircleShape point(trImage[i].r);
                point.setFillColor(trImage[i].c);
                point.setPosition(trImage[i].x - trImage[i].r, trImage[i].y - trImage[i].r);
                window.draw(point);
                /*sf::ConvexShape convex;
                convex.setPointCount(3);
                convex.setFillColor(trImage[i].c);
                convex.setPoint(0, sf::Vector2f(trImage[i].x1, trImage[i].y1));
                convex.setPoint(1, sf::Vector2f(trImage[i].x2, trImage[i].y2));
                convex.setPoint(2, sf::Vector2f(trImage[i].x3, trImage[i].y3));

                window.draw(convex);*/
            }

            /*sf::Texture texture;
            texture.loadFromFile("testImg.png");
            sf::Sprite sprite;
            sprite.setTexture(texture);

            window.draw(sprite);*/

            int r = rand() % 255;
            int g = rand() % 255;
            int b = rand() % 255;

            /*int x1 = min(rand() % (tileSizeX + tileSizeX / 10) + tileCoordX * tileSizeX, (int)img.getSize().x);
            int y1 = min(rand() % (tileSizeY + tileSizeY / 10) + tileCoordY * tileSizeY, (int)img.getSize().y);
            int x2 = min(rand() % (tileSizeX + tileSizeX / 10) + tileCoordX * tileSizeX, (int)img.getSize().x);
            int y2 = min(rand() % (tileSizeY + tileSizeY / 10) + tileCoordY * tileSizeY, (int)img.getSize().y);
            int x3 = min(rand() % (tileSizeX + tileSizeX / 10) + tileCoordX * tileSizeX, (int)img.getSize().x);
            int y3 = min(rand() % (tileSizeY + tileSizeY / 10) + tileCoordY * tileSizeY, (int)img.getSize().y);*/

            int cx = rand() % tileSizeX;
            int cy = rand() % tileSizeY;
            //cr = rand() % 30;

            /*sf::ConvexShape convex;
            convex.setPointCount(3);
            convex.setFillColor(sf::Color(r, g, b));
            convex.setPoint(0, sf::Vector2f(x1, y1));
            convex.setPoint(1, sf::Vector2f(x2, y2));
            convex.setPoint(2, sf::Vector2f(x3, y3));

            window.draw(convex);*/

            sf::CircleShape convex(cr);
            convex.setFillColor(sf::Color(r, g, b));
            convex.setPosition(cx - cr, cy - cr);

            window.draw(convex);

            convex.setPosition(cx - cr, Height - cy - cr);

            sf::RenderTexture render;
            render.create(Width, Height);
            render.clear();

            for (int i = 0; i < trImage.size(); i++) {
                sf::CircleShape point(trImage[i].r);
                point.setFillColor(trImage[i].c);
                point.setPosition(trImage[i].x - trImage[i].r, Height - trImage[i].y - trImage[i].r);
                render.draw(point);

                /*sf::ConvexShape convex;
                convex.setPointCount(3);
                convex.setFillColor(trImage[i].c);
                convex.setPoint(0, sf::Vector2f(trImage[i].x1, Height - trImage[i].y1));
                convex.setPoint(1, sf::Vector2f(trImage[i].x2, Height - trImage[i].y2));
                convex.setPoint(2, sf::Vector2f(trImage[i].x3, Height - trImage[i].y3));

                render.draw(convex);*/
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
                bestTriangle = tr(cx, cy, cr, sf::Color(r, g, b));
                bestErr = err;
            }
            texture.loadFromImage(err);
            sprite.setTexture(texture);
            window.draw(sprite);

            window.display();
            gen++;
            //cout << gen << endl;
            if (gen >= 500) {
                cout << best << endl;
                best = INF;
                trImage.push_back(bestTriangle);
                //img = bestErr;
                gen = 0;
                out << "draw color " << int(bestTriangle.c.r) << " " << int(bestTriangle.c.g) << " " << int(bestTriangle.c.b) << " 255 0 0" << endl;
                out << "draw poly " << bestTriangle.x << " " << Height - bestTriangle.y << " 1000 " << bestTriangle.r << " 0 0" << endl;
                if (gens % 25 == 0) out << "drawflush display1" << endl;
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
                cout << cr << endl;
                if (gens % (220 / cr) == 0) cr--;
                if (cr == 0) break;
            }
        }
        out << "drawflush display1" << endl;
        out << "stop" << endl;
    }
    return 0;
}