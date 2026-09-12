#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <ctime>
#include <fstream>
using namespace std;

// ------------------------- CONFIG -------------------------
const int WIDTH = 40;
const int HEIGHT = 20;

struct Position {
    int x, y;
};

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct GameState {
    Position head;
    Position fruit;
    vector<Position> tail;
    Direction dir;
    int score;
    int speed;
    bool gameOver;
};

string highscoreFile = "highscore.txt";

// ------------------------- UTILITIES -------------------------
void SetCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ClearScreen() {
    // ANSI clear and move cursor to 0,0
    cout << "\033[2J\033[1;1H";
}

int RandomInt(int a, int b) {
    return a + rand() % (b - a + 1);
}

// ------------------------- DRAW -------------------------
void Draw(const GameState &game) {
    ClearScreen();

    // Top border
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\n";

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) cout << "#";

            if (game.head.x == j && game.head.y == i)
                cout << "@"; // Head
            else if (game.fruit.x == j && game.fruit.y == i)
                cout << "F"; // Fruit
            else {
                bool printed = false;
                for (auto &t : game.tail) {
                    if (t.x == j && t.y == i) {
                        cout << "o"; printed = true;
                        break;
                    }
                }
                if (!printed) cout << " ";
            }

            if (j == WIDTH - 1) cout << "#";
        }
        cout << "\n";
    }

    // Bottom border
    for (int i = 0; i < WIDTH + 2; i++) cout << "#";
    cout << "\n";

    cout << "Score: " << game.score << "  Length: " << game.tail.size() + 1 
         << "  Speed: " << game.speed << "\n";
    cout << "Controls: Arrow keys or WASD. Press 'q' to quit.\n";
}

// ------------------------- INPUT -------------------------
void Input(GameState &game) {
    if (_kbhit()) {
        char c = _getch();
        switch (c) {
            case 'a': case 75: game.dir = LEFT; break;
            case 'd': case 77: game.dir = RIGHT; break;
            case 'w': case 72: game.dir = UP; break;
            case 's': case 80: game.dir = DOWN; break;
            case 'q': game.gameOver = true; break;
        }
    }
}

// ------------------------- LOGIC -------------------------
void Logic(GameState &game) {
    Position prev = game.head;
    Position prev2;

    // Move tail
    for (int i = 0; i < game.tail.size(); i++) {
        prev2 = game.tail[i];
        game.tail[i] = prev;
        prev = prev2;
    }

    // Move head
    switch (game.dir) {
        case LEFT: game.head.x--; break;
        case RIGHT: game.head.x++; break;
        case UP: game.head.y--; break;
        case DOWN: game.head.y++; break;
        default: break;
    }

    // Wrap-around
    if (game.head.x >= WIDTH) game.head.x = 0;
    if (game.head.x < 0) game.head.x = WIDTH - 1;
    if (game.head.y >= HEIGHT) game.head.y = 0;
    if (game.head.y < 0) game.head.y = HEIGHT - 1;

    // Check collision with tail
    for (auto &t : game.tail)
        if (t.x == game.head.x && t.y == game.head.y)
            game.gameOver = true;

    // Eat fruit
    if (game.head.x == game.fruit.x && game.head.y == game.fruit.y) {
        game.score += 10;
        game.fruit.x = RandomInt(0, WIDTH - 1);
        game.fruit.y = RandomInt(0, HEIGHT - 1);
        game.tail.push_back({-1,-1}); // Grow tail
    }
}

// ------------------------- HIGHSCORE -------------------------
int LoadHighscore() {
    ifstream file(highscoreFile);
    int score = 0;
    if (file >> score) return score;
    return 0;
}

void SaveHighscore(int score) {
    int hs = LoadHighscore();
    if (score > hs) {
        ofstream file(highscoreFile);
        file << score;
    }
}

// ------------------------- MAIN MENU -------------------------
void Menu() {
    srand(time(0));
    while (true) {
        ClearScreen();
        cout << "=== Snake: Full Edition ===\n";
        cout << "1) Start Player mode\n";
        cout << "2) Start AI mode (demo)\n";
        cout << "3) Settings (speed)\n";
        cout << "4) Show Highscore\n";
        cout << "5) Exit\n";
        cout << "Enter choice: ";
        int choice; cin >> choice;

        if (choice == 1) {
            // Initialize game
            GameState game;
            game.head = {WIDTH/2, HEIGHT/2};
            game.fruit = {RandomInt(0, WIDTH-1), RandomInt(0, HEIGHT-1)};
            game.dir = STOP;
            game.score = 0;
            game.speed = 100;
            game.tail.clear();
            game.gameOver = false;

            cout << "Starting... Controls: Arrow/WASD. Q=Quit\nPress Enter to begin.\n";
            cin.ignore(); cin.get();

            while (!game.gameOver) {
                Draw(game);
                Input(game);
                Logic(game);
                Sleep(game.speed);
            }

            cout << "\nGame Over! Final score: " << game.score << "\n";
            SaveHighscore(game.score);
            cout << "Press Enter to return to menu.\n";
            cin.ignore(); cin.get();
        }
        else if (choice == 2) {
            cout << "AI mode not implemented yet.\nPress Enter.";
            cin.ignore(); cin.get();
        }
        else if (choice == 3) {
            cout << "Enter speed (50=fast, 200=slow): ";
            int sp; cin >> sp;
            cout << "Speed set to " << sp << "\nPress Enter.";
            cin.ignore(); cin.get();
        }
        else if (choice == 4) {
            cout << "Highscore: " << LoadHighscore() << "\nPress Enter.";
            cin.ignore(); cin.get();
        }
        else if (choice == 5) {
            exit(0);
        }
    }
}

// ------------------------- MAIN -------------------------
int main() {
    Menu();
    return 0;
}
