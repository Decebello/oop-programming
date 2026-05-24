#pragma once

const int COLS = 7;
const int ROWS = 6;

enum CellState {
    EMPTY_SLOT,
    RED_PLAYER,
    YELLOW_PLAYER
};

class GameField {
private:
    CellState grid[COLS][ROWS];
    
    CellState activePlayer;
    
    CellState gameWinner;

    void evaluateBoard();

public:
    GameField();

    void resetGame();

    bool dropToken(int columnNumber);

    bool isGameFinished() const;

    CellState getActivePlayer() const;

    CellState checkSlot(int colIndex, int rowIndex) const;

    void render() const;
};