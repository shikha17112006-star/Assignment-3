🚀 DEFENDER – Console Shooting Game (C Language)

A fast-paced 2D console shooter made in pure C using Windows console functions.
You control a spaceship, shoot enemies, dodge incoming ships, and survive as long as you can!

🎮 Game Features

Smooth ship movement using arrow keys

Shooting using SPACEBAR

Enemies spawn dynamically from the right

Increasing difficulty after score 15

Console-rendered gameplay (no graphics library needed)

Clean cursor-based rendering (no flicker)

Bullet–Enemy collision detection

Ship width = 2 chars (>>)

ESC to instantly exit game

Play Again system with loop

🕹️ Controls
Key	Action
↑ Up Arrow	Move Up
↓ Down Arrow	Move Down
← Left Arrow	Move Left
→ Right Arrow	Move Right
SPACE	Shoot Bullet
ESC	Exit Game
🛡️ Gameplay Rules
⭐ Your Ship

Displayed as:

>>

⭐ Enemies

Displayed as:

W


They continuously move from right to left.

⭐ Bullets

Displayed as:

-


You can have multiple bullets active at the same time.

❤️ Lives & Game Over

You start with 3 lives

If an enemy touches your ship → you lose 1 life

When lives reach 0, you get GAME OVER

After finishing, the game asks:

Play Again (Y/N)

🔥 Difficulty System

Initial spawn rate: slower

After Score 15:

Enemies spawn faster

Game speed increases (faster movement)

More challenge!

📐 Game Dimensions

Width: 60 columns

Height: 20 rows

All objects (ship, bullets, enemies) stay within this grid.

📦 Requirements

Windows OS (because of <conio.h> and <windows.h>)

C compiler:

MinGW (recommended)

Turbo C/C++

MSVC

CodeBlocks with GCC

▶️ How to Compile & Run
Compile:
gcc defender.c -o defender

Run:
defender

🧠 Internal Mechanics
Cursor System

The game uses:

SetConsoleCursorPosition()


to update the screen without flickering.

Game Loop Includes:

Input handling

Enemy spawn + movement

Bullet spawn + movement

Collision detection

Screen redraw

Difficulty scaling

Collision Logic

Bullet hits Enemy:

if (bullet.x == enemy.x && bullet.y == enemy.y)


Enemy hits Player:

if (enemy.x == shipX || enemy.x == shipX + 1)

📂 File Structure
defender.c     → Full game code
README.md      → Game documentation
