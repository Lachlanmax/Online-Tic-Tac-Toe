#include "game.h"

TicTacToe::TicTacToe() {
    resetBoard();
}

void TicTacToe::resetBoard() {
    for (int i = 0; i < 9; i++) {
        board[i] = EMPTY;
    }
    gameState = WAITING;
    isXTurn = true;
}

bool TicTacToe::isValidMove(int position) const {
    return position >= 0 && position < 9 && board[position] == EMPTY;
}

bool TicTacToe::makeMove(int position, bool isX) {
    if (!isValidMove(position)) {
        return false;
    }
    
    board[position] = isX ? PLAYER_X : PLAYER_O;
    isXTurn = !isXTurn;
    gameState = checkWinner();
    
    if (gameState == WAITING && isBoardFull()) {
        gameState = DRAW;
    }
    
    return true;
}

GameState TicTacToe::checkWinner() {
    // Winning combinations
    int winPatterns[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // columns
        {0, 4, 8}, {2, 4, 6}              // diagonals
    };
    
    for (int i = 0; i < 8; i++) {
        int a = winPatterns[i][0];
        int b = winPatterns[i][1];
        int c = winPatterns[i][2];
        
        if (board[a] != EMPTY && board[a] == board[b] && board[b] == board[c]) {
            return (board[a] == PLAYER_X) ? X_WON : O_WON;
        }
    }
    
    return WAITING;
}

bool TicTacToe::isBoardFull() const {
    for (int i = 0; i < 9; i++) {
        if (board[i] == EMPTY) {
            return false;
        }
    }
    return true;
}

CellState TicTacToe::getCell(int position) const {
    if (position < 0 || position >= 9) return EMPTY;
    return board[position];
}

bool TicTacToe::getIsXTurn() const {
    return isXTurn;
}

GameState TicTacToe::getGameState() const {
    return gameState;
}

void TicTacToe::printBoard() const {
    std::cout << "\n";
    for (int i = 0; i < 9; i++) {
        if (i > 0 && i % 3 == 0) {
            std::cout << "\n-----------\n";
        }
        if (i > 0 && i % 3 != 0) {
            std::cout << "|";
        }
        
        if (board[i] == EMPTY) {
            std::cout << " " << i << " ";
        } else if (board[i] == PLAYER_X) {
            std::cout << " X ";
        } else {
            std::cout << " O ";
        }
    }
    std::cout << "\n\n";
}

void TicTacToe::serializeBoard(char* buffer, int bufferSize) {
    if (bufferSize < 11) return;
    
    for (int i = 0; i < 9; i++) {
        buffer[i] = static_cast<char>(board[i]);
    }
    buffer[9] = static_cast<char>(gameState);
    buffer[10] = isXTurn ? 1 : 0;
}

void TicTacToe::deserializeBoard(const char* buffer, int bufferSize) {
    if (bufferSize < 11) return;
    
    for (int i = 0; i < 9; i++) {
        board[i] = static_cast<CellState>(buffer[i]);
    }
    gameState = static_cast<GameState>(buffer[9]);
    isXTurn = buffer[10] == 1;
}
