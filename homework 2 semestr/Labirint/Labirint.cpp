#include "Labirint.h"
#include <iostream>
#include <fstream>
#include <queue>

//классификация пикселей
bool Labirint::isWall(const Pixel& p) const {
    return (p.red < 50 && p.green < 50 && p.blue < 50);
}

bool Labirint::isEntrance(const Pixel& p) const {
    return (p.green > 150 && p.red < 100 && p.blue < 100);
}

bool Labirint::isExit(const Pixel& p) const {
    return (p.red > 150 && p.green < 100 && p.blue < 100);
}

//загрузка BMP файла
bool Labirint::loadBMP(const string& filename) {
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        cerr << "Не удалось открыть файл: " << filename << endl;
        return false;
    }

    unsigned char sig[2];
    fin.read(reinterpret_cast<char*>(sig), 2);
    if (sig[0] != 'B' || sig[1] != 'M') {
        cerr << "Файл не является BMP" << endl;
        return false;
    }

    rawHeader.resize(54);
    rawHeader[0] = sig[0];
    rawHeader[1] = sig[1];
    fin.read(reinterpret_cast<char*>(rawHeader.data() + 2), 52);

    unsigned int dataOffset = *reinterpret_cast<unsigned int*>(&rawHeader[10]);
    width  = *reinterpret_cast<int*>(&rawHeader[18]);
    int rawHeight = *reinterpret_cast<int*>(&rawHeader[22]);
    unsigned short bpp = *reinterpret_cast<unsigned short*>(&rawHeader[28]);

    if (bpp != 24) {
        cerr << "Поддерживаются только 24-битные BMP" << endl;
        return false;
    }

    bool bottomUp = (rawHeight > 0);
    height = bottomUp ? rawHeight : -rawHeight;

    int rowStride = ((width * 3 + 3) / 4) * 4; 

    fin.seekg(dataOffset, ios::beg);

    image.assign(height, vector<Pixel>(width));
    maze.assign(height, vector<int>(width, 0));

    for (int fileRow = 0; fileRow < height; fileRow++) {
        int y = bottomUp ? (height - 1 - fileRow) : fileRow;
        vector<unsigned char> buf(rowStride);
        fin.read(reinterpret_cast<char*>(buf.data()), rowStride);

        for (int x = 0; x < width; x++) {
            Pixel px;
            px.blue  = buf[x * 3 + 0];
            px.green = buf[x * 3 + 1];
            px.red   = buf[x * 3 + 2];
            image[y][x] = px;

            if (isWall(px)) {
                maze[y][x] = 1;
            } else if (isEntrance(px)) {
                maze[y][x] = 0;
                entrance = { x, y };
            } else if (isExit(px)) {
                maze[y][x] = 0;
                exitPoint = { x, y };
            } else {
                maze[y][x] = 0;
            }
        }
    }

    if (entrance.col < 0 || exitPoint.col < 0) {
        cerr << "Не найдена точка входа или выхода" << endl;
        return false;
    }

    return true;
}

//алгоритм Ли

bool Labirint::waveExpand(vector<vector<int>>& dist) const {
    dist.assign(height, vector<int>(width, -1));
    queue<Point> q;

    dist[entrance.row][entrance.col] = 0;
    q.push(entrance);

    const int dc[] = { 0,  0, 1, -1 };
    const int dr[] = { 1, -1, 0,  0 };

    while (!q.empty()) {
        Point cur = q.front();
        q.pop();

        if (cur.col == exitPoint.col && cur.row == exitPoint.row)
            return true;

        for (int d = 0; d < 4; d++) {
            int nc = cur.col + dc[d];
            int nr = cur.row + dr[d];
            if (nc >= 0 && nc < width && nr >= 0 && nr < height
                    && dist[nr][nc] == -1 && maze[nr][nc] == 0) {
                dist[nr][nc] = dist[cur.row][cur.col] + 1;
                q.push({ nc, nr });
            }
        }
    }

    return false;
}

//обратный проход и покраска пути
void Labirint::traceback(vector<vector<int>>& dist) {
    const int dc[] = { 0,  0, 1, -1 };
    const int dr[] = { 1, -1, 0,  0 };

    int c = exitPoint.col;
    int r = exitPoint.row;

    while (!(c == entrance.col && r == entrance.row)) {
        if (!(c == exitPoint.col && r == exitPoint.row)) {
            image[r][c] = { 255, 0, 0 }; 
        }

        int step = dist[r][c];
        for (int d = 0; d < 4; d++) {
            int pc = c + dc[d];
            int pr = r + dr[d];
            if (pc >= 0 && pc < width && pr >= 0 && pr < height
                    && dist[pr][pc] == step - 1) {
                c = pc;
                r = pr;
                break;
            }
        }
    }
}

bool Labirint::solve() {
    vector<vector<int>> dist;
    if (!waveExpand(dist)) {
        cerr << "Путь не найден" << endl;
        return false;
    }
    traceback(dist);
    return true;
}

//запись BMP файла
bool Labirint::saveBMP(const string& filename) const {
    ofstream fout(filename, ios::binary);
    if (!fout.is_open()) {
        cerr << "Не удалось создать файл: " << filename << endl;
        return false;
    }

    fout.write(reinterpret_cast<const char*>(rawHeader.data()), rawHeader.size());

    unsigned int dataOffset = *reinterpret_cast<const unsigned int*>(&rawHeader[10]);
    if (dataOffset > 54) {
        vector<unsigned char> gap(dataOffset - 54, 0);
        fout.write(reinterpret_cast<const char*>(gap.data()), gap.size());
    }

    int rowStride = ((width * 3 + 3) / 4) * 4;
    vector<unsigned char> padding(rowStride - width * 3, 0);

    for (int fileRow = 0; fileRow < height; fileRow++) {
        int y = height - 1 - fileRow; 
        for (int x = 0; x < width; x++) {
            const Pixel& px = image[y][x];
            fout.put(px.blue);
            fout.put(px.green);
            fout.put(px.red);
        }
        if (!padding.empty())
            fout.write(reinterpret_cast<const char*>(padding.data()), padding.size());
    }

    return true;
}
