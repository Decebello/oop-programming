#include <iostream>
#include <clocale>
#include "Field.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    GameField session;

    cout << "=== Новая партия: Четыре в ряд ===\n";

    while (!session.isGameFinished()) {
        session.render();

        cout << "Сейчас ход игрока: " 
             << (session.getActivePlayer() == RED_PLAYER ? "КРАСНЫЙ" : "ЖЕЛТЫЙ") 
             << "\nВыберите колонку для сброса фишки (1-7): ";

        int userChoice;
        cin >> userChoice;

        if (!session.dropToken(userChoice)) {
            cout << "Невозможно сделать ход в эту колонку! Попробуйте еще раз.\n";
        }
    }

    session.render();

    return 0;
}