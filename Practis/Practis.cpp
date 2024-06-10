#include <iostream> // ϳ��������� �������� ��� ������ � �������� �� ��������� ��������
using namespace std; // ������������ �������� ���� std

// ����������� ������ �����
char board[3][3] = { {'1', '2', '3'},
                     {'4', '5', '6'},
                     {'7', '8', '9'} };
char current_marker; // ����� ��� ��������� ������� ��������� ������
int current_player; // ����� ��� ��������� ������ ��������� ������

// ������� ��� ��������� ������ �����
void drawBoard() {
    cout << "-------------\n"; // ������ ���� �����
    for (int i = 0; i < 3; i++) { // ����������� �� ������ �����
        cout << "| "; // ˳�� ���� �����
        for (int j = 0; j < 3; j++) { // ����������� �� �������� �����
            cout << board[i][j] << " | "; // ��������� �������� ������ � ����� ��� ������
        }
        cout << "\n-------------\n"; // ����� ���� �����
    }
}

// ������� ��� ��������� ������� �� �����
bool placeMarker(int slot) {
    int row = (slot - 1) / 3; // ���������� ����� �� ����� ��������� �����
    int col = (slot - 1) % 3; // ���������� ������� �� ����� ��������� �����

    // ��������, �� ������ �� �������
    if (board[row][col] != 'X' && board[row][col] != '0') {
        board[row][col] = current_marker; // ��������� ������� �� �����
        return true; // ������ ��������� �������
    }
    else {
        return false; // ������ �������, ��������� �� ��������
    }
}

// ������� ��� ���������� ���������
int winner() {
    // �������� ����� �� �������� ���������
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return current_player; // �������� ������� ������
        }
    }
    // �������� �������� �� �������� ���������
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            return current_player; // �������� ������� ������
        }
    }
    // �������� ��������� �� �������� ���������
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return current_player; // �������� ������� ������
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return current_player; // �������� ������� ������
    }

    return 0; // ���� ���������
}

// ������� ��� ���� ��������� ������ �� ���� �������
void swapPlayerAndMarker() {
    current_marker = (current_marker == 'X') ? '0' : 'X'; // ���� �������
    current_player = (current_player == 1) ? 2 : 1; // ���� ������ ������
}

// ������� ������� ���
void game() {
    char marker_p1; // ����� ��� ������� ������� ������
    while (true) { // ���� ��� ������������ ����������� ������ �������
        cout << "Player 1, choose your marker (X or 0): "; // ����� �������
        cin >> marker_p1; // ���������� �������

        if (marker_p1 == 'X' || marker_p1 == '0') { // �������� ����������� �������
            break; // ����� � ����� ��� ����������� ������
        }
        else {
            cout << "Invalid marker! Choose either X or 0.\n"; // ����������� ��� ������������ ������
        }
    }

    current_player = 1; // ������������ ������� ������
    current_marker = marker_p1; // ������������ ������� ������� ������

    drawBoard(); // ��������� ��������� �����

    int player_won = 0; // ����� ��� ��������� ���������� ���

    for (int i = 0; i < 9; i++) { // ���� ��� ���������� ����
        cout << "It's player " << current_player << "'s turn. Enter your slot: "; // ����������� ��� ��� ������
        int slot; // ����� ��� ��������� ��������� �����
        cin >> slot; // ���������� ��������� �����

        if (slot < 1 || slot > 9) { // �������� ����������� �����
            cout << "That slot is invalid! Try another slot!\n"; // ����������� ��� ������������ ����
            i--; // ��������� ��������� ��� ���������� ����
            continue; // ������� ��������
        }

        if (!placeMarker(slot)) { // ��������, �� ���� ��������
            cout << "That slot is occupied! Try another slot!\n"; // ����������� ��� �������� ����
            i--; // ��������� ��������� ��� ���������� ����
            continue; // ������� ��������
        }

        drawBoard(); // ��������� �������� �����

        player_won = winner(); // �������� �������� ���������

        if (player_won == 1) { // �������� ������� ������
            cout << "Player 1 wins! Congratulations!\n"; // ����������� ��� ��������
            break; // ����� � �����
        }
        if (player_won == 2) { // �������� ������� ������
            cout << "Player 2 wins! Congratulations!\n"; // ����������� ��� ��������
            break; // ����� � �����
        }

        swapPlayerAndMarker(); // ���� ������ � �������
    }

    if (player_won == 0) { // ͳ���
        cout << "It's a tie!\n"; // ����������� ��� ����
    }
}

int main() {
    game(); // ������ ������� ���
    return 0; // ���������� ��������
}
