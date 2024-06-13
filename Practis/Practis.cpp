#include <iostream> // Including the library for input and output streams
#include <fstream> // Including the library for file streams
#include <string> // Including the string library for using to_string
#include <nlohmann/json.hpp> // Including the JSON library

using namespace std;
using json = nlohmann::json; // Using the nlohmann JSON namespace

// Initializing the game board
char board[3][3] = { {'1', '2', '3'},
                     {'4', '5', '6'},
                     {'7', '8', '9'} };
char current_marker; // Variable to store the marker of the current player
int current_player; // Variable to store the number of the current player

void drawBoard() {
    cout << "-------------\n"; // Top border of the board
    for (int i = 0; i < 3; i++) { // Iterating through the rows of the board
        cout << "| "; // Left border of the row
        for (int j = 0; j < 3; j++) { // Iterating through the columns of the board
            cout << board[i][j] << " | "; // Printing the cell value and the right border of the cell
        }
        cout << "\n-------------\n"; // Bottom border of the row
    }
}

// Function to place the marker on the board
bool placeMarker(int slot) {
    int row = (slot - 1) / 3; // Calculating the row based on the entered slot
    int col = (slot - 1) % 3; // Calculating the column based on the entered slot

    // Checking if the cell is not occupied
    if (board[row][col] != 'X' && board[row][col] != '0') {
        board[row][col] = current_marker; // Placing the marker on the board
        return true; // Successfully placed the marker
    }
    else {
        return false; // Cell is occupied
    }
}

// Function to determine the winner
int winner() {
    // Checking rows for a winning combination
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return current_player; // Current player wins
        }
    }
    // Checking columns for a winning combination
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return current_player; // Current player wins
        }
    }
    // Checking diagonals for a winning combination
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return current_player; // Current player wins
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return current_player; // Current player wins
    }

    return 0; // No winner
}

// Function to swap the current player and their marker
void swapPlayerAndMarker() {
    current_marker = (current_marker == 'X') ? '0' : 'X'; // Switching the marker
    current_player = (current_player == 1) ? 2 : 1; // Switching the player number
}

// Function to save the game result to a CSV file
void saveGameResult(int player_won) {
    ofstream file("game_results.csv", ios::app); // Opening the CSV file in append mode
    if (file.is_open()) {
        file << "Player " << (player_won ? to_string(player_won) : "None") << ","
            << (player_won ? "Win" : "Tie") << endl;
        file.close(); // Closing the file
    }
    else {
        cout << "Unable to open file for writing results.\n";
    }
}

// Function to save the game state to a JSON file
void saveGameState() {
    json game_state; // Creating a JSON object
    game_state["current_player"] = current_player;
    game_state["current_marker"] = current_marker;

    // Saving the board state
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            game_state["board"][i][j] = board[i][j];
        }
    }

    ofstream file("game_state.json"); // Opening the JSON file for writing
    if (file.is_open()) {
        file << game_state.dump(4); // Dumping the JSON object to the file with 4-space indentation
        file.close(); // Closing the file
    }
    else {
        cout << "Unable to open file for writing game state.\n";
    }
}

// Function to run the game
void game() {
    char marker_p1; // Variable to store the marker of the first player
    do {
        cout << "Player 1, choose your marker (X or 0): "; // Prompting the first player to choose their marker
        cin >> marker_p1; // Reading the marker
    } while (marker_p1 != 'X' && marker_p1 != '0'); // Ensuring the marker is either 'X' or '0'

    current_player = 1; // Setting the first player
    current_marker = marker_p1; // Setting the marker of the first player

    drawBoard(); // Displaying the initial board
    int player_won = 0; // Variable to store the game result (0 means no winner yet)

    for (int i = 0; i < 9 && player_won == 0; i++) { // Loop for making moves, max 9 moves
        int slot; // Variable to store the chosen slot
        cout << "Player " << current_player << "'s turn. Enter your slot: "; // Prompting the current player to enter a slot
        cin >> slot; // Reading the chosen slot

        // Checking if the slot is valid and not occupied
        if (slot < 1 || slot > 9 || !placeMarker(slot)) {
            cout << "Invalid slot! Try again.\n"; // Invalid slot message
            i--; // Decrease i to repeat the iteration for the same player
            continue; // Skip the rest of the loop and continue with the next iteration
        }

        drawBoard(); // Displaying the updated board
        saveGameState(); // Saving the game state after each move
        player_won = winner(); // Checking for a winner

        if (player_won == 0) swapPlayerAndMarker(); // If no winner, switch player and marker
    }

    // Displaying the result of the game
    cout << (player_won ? "Player " + to_string(player_won) + " wins! Congratulations!\n" : "It's a tie!\n");

    saveGameResult(player_won); // Saving the game result to a CSV file
}

int main() {
    game(); // Calling the game function
    return 0; // Ending the program
}
