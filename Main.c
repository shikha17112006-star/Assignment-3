#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

#define WIDTH 60
#define HEIGHT 20
#define MAX_ENEMIES 20
#define MAX_BULLETS 20

typedef struct {
    int x, y;
    int active;
} Enemy;

typedef struct {
    int x, y;
    int active;
} Bullet;

void hideCursor() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info = {1, FALSE};
    SetConsoleCursorInfo(console, &info);
}

void cursor(int x, int y) {
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

// -------------------- TITLE SCREEN --------------------
void showTitle() {
    system("cls");
    printf("\n\n\n");
    printf("  ==================================\n");
    printf("              DEFENDER\n");
    printf("  ==================================\n\n");
    printf("  Move: Arrow Keys\n");
    printf("  Shoot: Space\n");
    printf("  Exit: ESC\n\n");
    printf("  Press any key to start...\n");

    getch(); // wait for any key
    system("cls");
}

int main() {
    srand((unsigned)time(NULL));
    hideCursor();

    while (1)  // Play Again Loop
    {
        showTitle(); // Show Defender screen before game starts

        int shipX = 2;
        int shipY = HEIGHT / 2;
        int score = 0;
        int lives = 3;

        int spawnRate = 10;
        int speedDelay = 55;

        Enemy enemies[MAX_ENEMIES];
        Bullet bullets[MAX_BULLETS];

        for (int i = 0; i < MAX_ENEMIES; i++) enemies[i].active = 0;
        for (int i = 0; i < MAX_BULLETS; i++) bullets[i].active = 0;

        while (lives > 0)
        {
            // Difficulty bump at score 15
            if (score >= 15) {
                spawnRate = 6;
                speedDelay = 35;
            }

            // INPUT
            if (_kbhit())
            {
                int ch = getch();
                if (ch == 0 || ch == 224) {
                    ch = getch();
                    if (ch == 72 && shipY > 0)            shipY--;      // UP
                    if (ch == 80 && shipY < HEIGHT - 1)    shipY++;      // DOWN
                    if (ch == 75 && shipX > 0)             shipX--;      // LEFT
                    if (ch == 77 && shipX < WIDTH - 2)     shipX++;      // RIGHT (ship width = 2 chars)
                }
                else if (ch == ' ' || ch == 32) {
                    for (int i = 0; i < MAX_BULLETS; i++) {
                        if (!bullets[i].active) {
                            bullets[i].active = 1;
                            bullets[i].x = shipX + 2; // spawn after '>>'
                            bullets[i].y = shipY;
                            break;
                        }
                    }
                }
                else if (ch == 27) {  // ESC
                    cursor(0, HEIGHT + 2);
                    printf("Exited Game.\n");
                    return 0;
                }
            }

            // SPAWN ENEMY from right in random row
            if (rand() % spawnRate == 0)
            {
                for (int i = 0; i < MAX_ENEMIES; i++) {
                    if (!enemies[i].active) {
                        enemies[i].active = 1;
                        enemies[i].x = WIDTH - 2;
                        enemies[i].y = rand() % HEIGHT;
                        break;
                    }
                }
            }

            // MOVE ENEMIES left
            for (int i = 0; i < MAX_ENEMIES; i++) {
                if (enemies[i].active) {
                    enemies[i].x--;
                    if (enemies[i].x < 0)
                        enemies[i].active = 0;
                }
            }

            // MOVE BULLETS right
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (bullets[i].active) {
                    bullets[i].x++;
                    if (bullets[i].x >= WIDTH)
                        bullets[i].active = 0;
                }
            }

            // BULLET hits ENEMY
            for (int e = 0; e < MAX_ENEMIES; e++) {
                if (!enemies[e].active) continue;
                for (int b = 0; b < MAX_BULLETS; b++) {
                    if (!bullets[b].active) continue;

                    if (bullets[b].x == enemies[e].x &&
                        bullets[b].y == enemies[e].y)
                    {
                        bullets[b].active = 0;
                        enemies[e].active = 0;
                        score++;
                        break;
                    }
                }
            }

            // ENEMY hits SHIP
            for (int e = 0; e < MAX_ENEMIES; e++) {
                if (!enemies[e].active) continue;

                // ship is 2 chars: >>  (shipX, shipX+1)
                if (enemies[e].y == shipY &&
                   (enemies[e].x == shipX || enemies[e].x == shipX + 1))
                {
                    enemies[e].active = 0;
                    lives--;
                }
            }

            // DRAW
            cursor(0,0);
            printf("Score: %d   Lives: %d\n\n", score, lives);

            for (int y = 0; y < HEIGHT; y++) {
                for (int x = 0; x < WIDTH; x++) {
                    char ch = ' ';

                    // Draw Ship >> 
                    if (y == shipY && x == shipX)     ch = '>';
                    if (y == shipY && x == shipX + 1) ch = '>';

                    // Enemies
                    for (int i = 0; i < MAX_ENEMIES; i++)
                        if (enemies[i].active &&
                            enemies[i].x == x &&
                            enemies[i].y == y)
                            ch = 'W';

                    // Bullets
                    for (int i = 0; i < MAX_BULLETS; i++)
                        if (bullets[i].active &&
                            bullets[i].x == x &&
                            bullets[i].y == y)
                            ch = '-';

                    putchar(ch);
                }
                putchar('\n');
            }

            Sleep(speedDelay);
        }

        // GAME OVER SCREEN
        cursor(0, HEIGHT + 2);
        printf("\n*** GAME OVER ***\n");
        printf("Final Score: %d\n", score);
        printf("Play Again (Y/N): ");

        while (1)
        {
            int ch = getch();
            if (ch == 'y' || ch == 'Y') {
                system("cls");
                break;
            }
            if (ch == 'n' || ch == 'N') {
                printf("\nThanks for playing!\n");
                getch();
                return 0;
            }
        }
    }
}