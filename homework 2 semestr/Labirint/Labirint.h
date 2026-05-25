#pragma once
#include <vector>
#include <string>

using namespace std;

struct Point {
    int col, row;
};

struct Pixel {
    unsigned char blue, green, red;
};

class Labirint {
private:
    int width  { 0 };
    int height { 0 };

    vector<unsigned char> rawHeader;

    //таблица пикселей исходного изображения
    vector<vector<Pixel>> image;

    vector<vector<int>> maze;

    Point entrance { -1, -1 };  
    Point exitPoint { -1, -1 }; 

    //вспомогательные классификаторы пикселей
    bool isWall   (const Pixel& p) const;
    bool isEntrance(const Pixel& p) const;
    bool isExit   (const Pixel& p) const;

    //волновой алгоритм Ли
    bool waveExpand(vector<vector<int>>& dist) const;

    //обратный проход по карте расстояний и покраска найденного пути
    void traceback(vector<vector<int>>& dist);

public:
    bool loadBMP(const string& filename);

    // запускает алгоритм Ли и рисует путь на image
    bool solve();

    //записывает изменённое изображение в BMP
    bool saveBMP(const string& filename) const;
};
