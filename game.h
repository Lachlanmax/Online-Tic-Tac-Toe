#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstring>
#include <vector>

// Board states
enum CellState {
    EMPTY = 0,
    PLAYER_X = 1,
    PLAYER_O = 2
};

enum GameState {
    WAITING = 0,
    PLAYING = 1,
    X_WON = 2,
    O_WON = 3,
    DRAW = 4
};

class TicTacToe {
private:
    CellState board[9];
    GameState gameState;
    bool isXTurn;

public:
    TicTacToe();
    
    // Game logic
    bool makeMove(int position, bool isX);
    bool isValidMove(int position) const;
    GameState checkWinner();
    bool isBoardFull() const;
    void resetBoard();
    
    // Getters
    CellState getCell(int position) const;
    bool getIsXTurn() const;
    GameState getGameState() const;
    
    // Display
    void printBoard() const;
    
    // Serialization
    void serializeBoard(char* buffer, int bufferSize);
    void deserializeBoard(const char* buffer, int bufferSize);
};

#endif
