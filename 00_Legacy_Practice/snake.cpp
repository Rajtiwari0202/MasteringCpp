#include <bits/stdc++.h>
#if defined(_WIN32) || defined(_WIN64)
  #include <conio.h>
  #include <windows.h>
#else
  #include <termios.h>
  #include <unistd.h>
  #include <sys/select.h>
#endif

using namespace std;

int width = 40;
int height = 20;

enum Direction { STOP=0, LEFT, RIGHT, UP, DOWN };

#if !(defined(_WIN32) || defined(_WIN64))
// POSIX helpers: kbhit() and getch()
int kbhit() {
    timeval tv{0,0};
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(STDIN_FILENO, &readfds);
    return select(STDIN_FILENO+1, &readfds, nullptr, nullptr, &tv) > 0;
}

int getch_posix() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return c;
}
#endif

// clear screen (ANSI)
void clear_screen() {
    // Use ANSI escape
    cout << "\x1B[2J\x1B[H";
}

void sleep_ms(int ms) {
#if defined(_WIN32) || defined(_WIN64)
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

struct Point { int x, y; };

class SnakeGame {
public:
    SnakeGame() {
        reset();
    }

    void reset() {
        dir = STOP;
        snake.clear();
        snake.push_back({width/2, height/2});
        place_food();
        gameOver = false;
        score = 0;
        speed = 120; // ms per frame (lower -> faster)
    }

    void place_food() {
        srand((unsigned)time(nullptr) + rand());
        while (true) {
            int fx = rand() % width;
            int fy = rand() % height;
            bool onSnake = false;
            for (auto &s : snake) if (s.x==fx && s.y==fy) { onSnake = true; break; }
            if (!onSnake) { food = {fx, fy}; break; }
        }
    }

    void input() {
#if defined(_WIN32) || defined(_WIN64)
        if (_kbhit()) {
            int c = _getch();
            // handle arrow keys - Windows returns 0 or 224 then code
            if (c == 0 || c == 224) {
                int code = _getch();
                if (code == 75) changeDir(LEFT);    // left arrow
                else if (code == 77) changeDir(RIGHT); // right arrow
                else if (code == 72) changeDir(UP);    // up arrow
                else if (code == 80) changeDir(DOWN);  // down arrow
            } else {
                handleChar(c);
            }
        }
#else
        if (kbhit()) {
            int c = getchar();
            if (c == 27) { // possible arrow sequence
                if (kbhit() && getchar() == '[') {
                    int code = getchar();
                    if (code == 'A') changeDir(UP);
                    else if (code == 'B') changeDir(DOWN);
                    else if (code == 'C') changeDir(RIGHT);
                    else if (code == 'D') changeDir(LEFT);
                }
            } else {
                handleChar(c);
            }
        }
#endif
    }

    void handleChar(int c) {
        if (c == 'q' || c == 'Q') gameOver = true;
        else if (c == 'a' || c == 'A') changeDir(LEFT);
        else if (c == 'd' || c == 'D') changeDir(RIGHT);
        else if (c == 'w' || c == 'W') changeDir(UP);
        else if (c == 's' || c == 'S') changeDir(DOWN);
    }

    void changeDir(Direction nd) {
        // Prevent reversing directly
        if (dir == LEFT && nd == RIGHT) return;
        if (dir == RIGHT && nd == LEFT) return;
        if (dir == UP && nd == DOWN) return;
        if (dir == DOWN && nd == UP) return;
        dir = nd;
    }

    void logic() {
        if (dir == STOP) return; // not started

        // new head position
        Point head = snake.front();
        Point newHead = head;
        if (dir == LEFT) newHead.x--;
        else if (dir == RIGHT) newHead.x++;
        else if (dir == UP) newHead.y--;
        else if (dir == DOWN) newHead.y++;

        // wrap around screen edges:
        if (newHead.x < 0) newHead.x = width-1;
        if (newHead.x >= width) newHead.x = 0;
        if (newHead.y < 0) newHead.y = height-1;
        if (newHead.y >= height) newHead.y = 0;

        // check collision with self
        for (size_t i = 0; i < snake.size(); ++i) {
            if (snake[i].x == newHead.x && snake[i].y == newHead.y) {
                gameOver = true;
                return;
            }
        }

        // move snake
        snake.insert(snake.begin(), newHead);

        // eat food?
        if (newHead.x == food.x && newHead.y == food.y) {
            score += 10;
            // speed up slightly
            if (speed > 40) speed -= 3;
            place_food();
        } else {
            snake.pop_back();
        }
    }

    void draw() {
        clear_screen();

        // top border
        for (int i=0;i<width+2;i++) cout << '#';
        cout << '\n';

        for (int y=0; y<height; ++y) {
            cout << '#';
            for (int x=0; x<width; ++x) {
                if (x == food.x && y == food.y) {
                    cout << 'O'; // food
                } else {
                    bool printed = false;
                    for (size_t k=0;k<snake.size();++k) {
                        if (snake[k].x == x && snake[k].y == y) {
                            if (k==0) cout << '@'; // head
                            else cout << 'o';      // body
                            printed = true;
                            break;
                        }
                    }
                    if (!printed) cout << ' ';
                }
            }
            cout << "#\n";
        }
        // bottom border
        for (int i=0;i<width+2;i++) cout << '#';
        cout << "\nScore: " << score << "   Length: " << snake.size() << "   Speed: " << (120 - speed + 20)/5 << "\n";
        cout << "Controls: Arrow keys or WASD. Press 'q' to quit.\n";
    }

    void run() {
#if !(defined(_WIN32) || defined(_WIN64))
        // set terminal to raw mode to avoid line buffering for arrow keys
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
#endif

        while (!gameOver) {
            input();
            logic();
            draw();
            sleep_ms(speed);
        }

#if !(defined(_WIN32) || defined(_WIN64))
        // restore terminal
        tcsetattr(STDIN_FILENO, TCSANOW, & (struct termios){});
#endif

        cout << "\nGame Over! Final score: " << score << "\n";
    }

private:
    vector<Point> snake;
    Point food;
    Direction dir;
    bool gameOver;
    int score;
    int speed;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== Snake (Console) in C++ ===\n";
    cout << "Press any arrow key or WASD to start. 'q' to quit.\n";
    cout << "Press Enter to begin...";
    cin.get();

    SnakeGame game;
    game.run();

    return 0;
}