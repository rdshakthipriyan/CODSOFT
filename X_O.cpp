#include <iostream>
using namespace std;
// Function to display the Tic-Tac-Toe board
void displayBoard(char board[3][3]) {
    cout << "-------------\n";
    for (int i = 0; i < 3; i++) {
        cout << "| ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

bool checkWin(char board[3][3], char player) {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||  // Check row
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) { // Check column
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // Diagonal
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) { // Opposite diagonal
        return true;
    }
    return false;
}

// Function to check if the game is a draw
bool checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') { // If there's any empty space
                return false;
            }
        }
    }
    return true; // No empty space, it's a draw
}

// Function to handle player input and update the board
bool playerMove(char board[3][3], char player) {
    int row, col;
    cout << "Player " << player << ", enter your move (row and column) [0-2]: ";
    cin >> row >> col;
    
    // Ensure valid input
    if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
        cout << "Invalid move! The cell is either out of bounds or already taken. Try again.\n";
        return false;
    }
    
    board[row][col] = player;
    return true;
}

// Function to play a single game of Tic-Tac-Toe
void playGame() {
    // Initialize the board as a 3x3 grid filled with spaces
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char currentPlayer = 'X';
    bool gameWon = false;
    bool gameDraw = false;

    while (!gameWon && !gameDraw) {
        displayBoard(board);
        bool validMove = false;
        
        // Prompt the current player for a valid move
        while (!validMove) {
            validMove = playerMove(board, currentPlayer);
        }

        // Check if the current player has won
        if (checkWin(board, currentPlayer)) {
            gameWon = true;
            displayBoard(board);
            cout << "Player " << currentPlayer << " wins!\n";
            break;
        }

        // Check for a draw
        if (checkDraw(board)) {
            gameDraw = true;
            displayBoard(board);
            cout << "The game is a draw.\n";
            break;
        }

        // Switch players
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

// Main function to control the flow of the game
int main() {
    char playAgain;
    
    do {
        playGame();
        
        // Ask if the players want to play again
        cout << "Do you want to play again? (y/n): ";
        cin >> playAgain;
        
    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "Thanks for playing!\n";
    return 0;
}
