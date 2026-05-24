#include <iostream>
#include "Field.h"

using namespace std;

GameField::GameField() {
    resetGame();
}

void GameField::resetGame() {
    activePlayer = RED_PLAYER;
    gameWinner = EMPTY_SLOT;
    
    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            grid[i][j] = EMPTY_SLOT;
        }
    }
}

CellState GameField::getActivePlayer() const {
    return activePlayer;
}

CellState GameField::checkSlot(int colIndex, int rowIndex) const {
    if (colIndex >= 0 && colIndex < COLS && rowIndex >= 0 && rowIndex < ROWS) {
        return grid[colIndex][rowIndex];
    }
    return EMPTY_SLOT;
}

bool GameField::dropToken(int columnNumber) {
    if (gameWinner != EMPTY_SLOT || columnNumber < 1 || columnNumber > COLS) {
        return false;
    }

    int targetCol = columnNumber - 1;

    for (int j = 0; j < ROWS; ++j) {
        if (grid[targetCol][j] == EMPTY_SLOT) {
            grid[targetCol][j] = activePlayer;
            
            evaluateBoard(); 
            
            activePlayer = (activePlayer == RED_PLAYER) ? YELLOW_PLAYER : RED_PLAYER;
            return true;
        }
    }

    return false; 
}

void GameField::evaluateBoard() {
    const int DIRECTIONS = 4;
    const int shiftX[] = { 1, 0, 1, 1 };
    const int shiftY[] = { 0, 1, 1, -1 };
    const int TARGET_STREAK = 4;

    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            CellState startToken = grid[i][j];
            if (startToken == EMPTY_SLOT) continue;

            for (int d = 0; d < DIRECTIONS; ++d) {
                int sequenceLength = 1;
                int currentX = i + shiftX[d];
                int currentY = j + shiftY[d];

                while (currentX >= 0 && currentX < COLS && 
                       currentY >= 0 && currentY < ROWS && 
                       grid[currentX][currentY] == startToken) {
                    
                    sequenceLength++;
                    if (sequenceLength == TARGET_STREAK) {
                        gameWinner = startToken;
                        return;
                    }
                    currentX += shiftX[d];
                    currentY += shiftY[d];
                }
            }
        }
    }
}

bool GameField::isGameFinished() const {
    if (gameWinner != EMPTY_SLOT) return true;

    for (int i = 0; i < COLS; ++i) {
        for (int j = 0; j < ROWS; ++j) {
            if (grid[i][j] == EMPTY_SLOT) return false;
        }
    }
    return true;
}

void GameField::render() const {
    cout << "\n";
    for (int j = ROWS - 1; j >= 0; --j) {
        cout << "| ";
        for (int i = 0; i < COLS; ++i) {
            if (grid[i][j] == RED_PLAYER) cout << "R ";
            else if (grid[i][j] == YELLOW_PLAYER) cout << "Y ";
            else cout << ". ";
        }
        cout << "|\n";
    }
    cout << "-----------------------\n";
    cout << "  1 2 3 4 5 6 7\n\n";

    if (isGameFinished()) {
        if (gameWinner == RED_PLAYER) cout << "Матч завершен! Победили КРАСНЫЕ!\n";
        else if (gameWinner == YELLOW_PLAYER) cout << "Матч завершен! Победили ЖЕЛТЫЕ!\n";
        else cout << "Матч завершен! Ничья, свободных мест нет.\n";
    }
}