#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
using namespace std;

class Config {
public:
    struct players {
        string one;
        string two = "Computer";
    };

    players player;
    static const int N = 3;
    char board[N][N];
    bool endGame = false;
    char activeSign;
    char activePlayer = 'p';
    char HUMAN = 'x';
    char COMPUTER = 'o';
    int nrw = 1, nrk = 1;
    int bx = 18, by = 20;
    int pozx, pozy;
};

static int counterAB = 0;
static int counterMM = 0;
static Config G_DATA;

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x; // X -> współrzędna bufora ekranu w poziomie, y -> nr kolumny w tabeli
    c.Y = y; // Y -> współrzędna bufora ekranu w pionie, x -> nr kolumny w tabeli
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void initBoard() {
    for (int i = 0; i < G_DATA.N; i++) {
        for (int j = 0; j < G_DATA.N; j++) {
            G_DATA.board[i][j] = ' ';
        }
    }
}

void drawBoard() {
    for (int i = 0; i < G_DATA.N; i++) {
        gotoxy(G_DATA.bx, G_DATA.by + i);
        for (int j = 0; j < G_DATA.N; j++) {
            cout << "|";
            cout << G_DATA.board[i][j];
        }
        cout << "|";
        cout << endl;
    }
}

bool checkWin(char board[][G_DATA.N]) {
    for (int i = 0; i < 3; i++)
    {
        if ((G_DATA.board[i][0] == G_DATA.board[i][1]) && (G_DATA.board[i][1] == G_DATA.board[i][2]) && (G_DATA.board[i][0] != ' ')) {
            return true;
        }
        if ((G_DATA.board[0][i] == G_DATA.board[1][i]) && (G_DATA.board[1][i] == G_DATA.board[2][i]) && (G_DATA.board[0][i] != ' ')) {
            return true;
        }
    }
    if ((G_DATA.board[0][0] == G_DATA.board[1][1]) && (G_DATA.board[1][1] == G_DATA.board[2][2]) && (G_DATA.board[0][0] != ' ')) {
        return true;
    }if ((G_DATA.board[2][0] == G_DATA.board[1][1]) && (G_DATA.board[1][1] == G_DATA.board[0][2]) && (G_DATA.board[2][0] != ' ')) {
        return true;
    }
    return false;
}

bool checkTie() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (G_DATA.board[i][j] == ' ') {
                return false;
            }
        }
    }
}

// Minimax AB
int minimaxAB(char board[][G_DATA.N], int depth, int alpha, int beta, bool isAI)
{
    int score = 0, bestScore = 0;
    counterAB++; //Stats

    if (checkWin(board))
    {
        return ((isAI) ? (-10 + depth) : (10 - depth));
    }
    else
    {
        if (depth < 9)
        {
            bestScore = (isAI) ? -9999 : 9999;
            for (int i = 0; i < G_DATA.N; i++)
            {
                for (int j = 0; j < G_DATA.N; j++)
                {
                    if (board[i][j] == ' ')
                    {
                        board[i][j] = (isAI) ? G_DATA.COMPUTER : G_DATA.HUMAN;
                        score = minimaxAB(board, depth + 1, alpha, beta, !isAI);
                        board[i][j] = ' ';
                        bestScore = (isAI) ? max(bestScore, score) : min(bestScore, score);
                        (isAI) ? alpha = max(alpha, score) : beta = min(beta, score);

                        if (beta <= alpha) goto pruneLabel;

                    }
                }
            }

        pruneLabel:
            return bestScore;

        }
        else return 0;
    }
}

int minimax(char board[][G_DATA.N], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    counterMM++; //Stats

    if (checkWin(board) == true)
    {
        if (isAI == true)
            return -1;
        if (isAI == false)
            return +1;
    }
    else
    {
        if (depth < 9)
        {
            if (isAI == true)
            {
                bestScore = -999;
                for (int i = 0; i < G_DATA.N; i++)
                {
                    for (int j = 0; j < G_DATA.N; j++)
                    {
                        if (board[i][j] == ' ')
                        {
                            board[i][j] = G_DATA.COMPUTER;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = ' ';
                            if (score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
                for (int i = 0; i < G_DATA.N; i++)
                {
                    for (int j = 0; j < G_DATA.N; j++)
                    {
                        if (board[i][j] == ' ')
                        {
                            board[i][j] = G_DATA.HUMAN;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = ' ';
                            if (score < bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
}

bool checkIfEmpty(int x, int y, char s) {
    if (G_DATA.board[y][x] == ' ') {
        cout << s;
        G_DATA.board[y][x] = s;
        return true;
    }
    else return false;
}

void calcPosition()
{
    int klawisz = 0;
    int pozx = G_DATA.bx + 2 * G_DATA.nrw;
    pozx++;
    int pozy = G_DATA.by + G_DATA.nrk;
    bool acceptedEntry = false;

    gotoxy(pozx, pozy);
    while (!acceptedEntry) {
        while (klawisz != 32)
        {
            klawisz = _getch();
            if (klawisz == 77 && (pozx + 2) <= G_DATA.bx + 5) { pozx += 2; G_DATA.nrk++; }      // RIGHT
            else if (klawisz == 75 && (pozx - 2) >= G_DATA.bx) { pozx -= 2; G_DATA.nrk--; }     // LEFT
            else if (klawisz == 80 && (pozy + 1) <= G_DATA.by + 2) { pozy += 1; G_DATA.nrw++; } // DOWN
            else if (klawisz == 72 && (pozy - 1) >= G_DATA.by) { pozy -= 1; G_DATA.nrw--; }     // TOP
            gotoxy(pozx, pozy);
        }

        if (checkIfEmpty(G_DATA.nrk, G_DATA.nrw, G_DATA.activeSign)) {
            acceptedEntry = true;
        } else { 
            klawisz = 0;
            gotoxy(0, G_DATA.by + 3);
            cout << "Field is not empty! Pick another one." << endl;
            gotoxy(pozx, pozy);
        }
    }

}

void ClearScreen() {
    for (int i = 0; i < 20; i++) cout << "                                                                                                 \n";
}

int bestMove(char board[][G_DATA.N], int moveIndex)
{
    int x = -1, y = -1, empty = 0;
    int score = 0, bestScore = -9999;
    gotoxy(0, G_DATA.by + 5);
    ClearScreen();
    gotoxy(0, G_DATA.by + 5);
    for (int i = 0; i < G_DATA.N; i++)
    {
        for (int j = 0; j < G_DATA.N; j++)
        {
            if (board[i][j] == ' ')
            {
                empty++;
                board[i][j] = G_DATA.COMPUTER;
                score = minimaxAB(board, moveIndex + 1, -9999, 9999, false);
                cout << "For Row: " << i+1 << ", Column: " << j+1 << ", using the Minimax AB alpha beta + algorithm: " << counterAB << " operations." << endl;
                minimax(board, moveIndex + 1, false);
                cout << "For Row: " << i+1 << ", Column: " << j+1 << ", using the Regular MiniMax algorithm: " << counterMM << " operations." << endl;
                counterAB = counterMM = 0;
                board[i][j] = ' ';
                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }

    if (empty != 9) return x * 3 + y;
    else return 4;

}

void gameLogic() {
    int moveIndex = 0, x = 0, y = 0, n, pi = 0, ki = 0;

    do {
        gotoxy(0, 18); cout << "                                         "; 
        gotoxy(0, 18);
        cout << "\t>>\t";
        if (G_DATA.activePlayer == 'p') cout << G_DATA.player.one;
        if (G_DATA.activePlayer == 'c') cout << G_DATA.player.two;
        cout << " - Your Turn!\t<<" << endl;
        drawBoard();

        if (G_DATA.activePlayer == 'p') {
            G_DATA.nrk = 1; 
            G_DATA.nrw = 1;
             calcPosition();
            moveIndex++;
            pi++;
        } else {
            n = bestMove(G_DATA.board, moveIndex);
            y = n / G_DATA.N;
            x = n % G_DATA.N;
            G_DATA.board[y][x] = G_DATA.COMPUTER;
            drawBoard();
            moveIndex++;
            ki++;
        }

        if (checkWin(G_DATA.board)) {
            gotoxy(0, G_DATA.by + 4);
            cout << "\t\tWINNER: ";
            if (G_DATA.activePlayer == 'p') cout << G_DATA.player.one;
            if (G_DATA.activePlayer == 'c') cout << G_DATA.player.two;
            G_DATA.endGame = true;
        }
        else if (checkTie()) {
            gotoxy(0, G_DATA.by + 4);
            cout << "\t\tGAME ENDED IN A DRAW!";
            
            G_DATA.endGame = true;
        }

        G_DATA.activePlayer = (G_DATA.activePlayer == 'c') ? 'p' : 'c';
        G_DATA.activeSign = (G_DATA.activeSign == G_DATA.COMPUTER) ? G_DATA.HUMAN : G_DATA.COMPUTER;

    } while (!G_DATA.endGame && moveIndex != G_DATA.N * G_DATA.N);

    gotoxy(0, 32);
    cout << "Total moves this game: " << moveIndex << ", Player move count: " << pi << ", AI move count: " << ki;
    gotoxy(0, 35);
}

void initGame() {
    printf("\n-------------------------------------------------------------------\n\n");
    cout << "\t\t\t| Tic-Tac-Toe |\n";
    printf("\n-------------------------------------------------------------------\n\n");
    cout << "Enter your name: " << endl; cin >> G_DATA.player.one;
    cout << G_DATA.player.one  << " choose your symbol: " << endl; cin >> G_DATA.HUMAN;
    cout << "Choose the computer's symbol: " << endl; cin >> G_DATA.COMPUTER;
    cout << "Who goes first?\np - Player\nc - Computer\n"; cin >> G_DATA.activePlayer;
    G_DATA.activeSign = (G_DATA.activePlayer == 'p') ? G_DATA.HUMAN : G_DATA.COMPUTER;
}

int main()
{
    initGame();
    initBoard();
    gameLogic();
}
