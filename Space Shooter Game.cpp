// Space Shooter Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream> 
#include <conio.h> // Including the console input/output library
#include <dos.h> // Header file to handle interruptions and producing time functions
#include <windows.h>
#include <time.h> // Time regulation library
#include <chrono>
#include <thread>
#include <ctime> // ctime library to include time capture functions
#include <fstream> // Library to handle input/output from text files

// Defining necessary screen variables
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define Enemy_DIF 45
using namespace std;
using namespace std::chrono;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

// Declaring variables and constructing player ship
int enemyY[3];
int enemyX[3];
bool enemyFlag[3];
char ship[3][5] = { ' ',' ','#',' ',' ',
                    '|','#','#','#','|',
                    '#','#','#','#','#' };
int shipPos = WIN_WIDTH / 2;
int score = 0;
int bullets[20][4];
int bulletsLife[20];
int bIndex = 0;

// Player information for record storage
// This will ensure that the necessary player information is stored
struct Player {
    string name;
    int highScore;
    double timeElapsed;
};

void gotoxy(int x, int y) {
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

// This method makes the cursor invisible
void setcursor(bool visible, DWORD size) {
    if (size == 0)
        size = 20;

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}
/** drawBorder
* This method draws a border for the game
* It creates a game screen and a section for the instructions and scores
*/
void drawBorder() {

    for (int i = 0; i < SCREEN_WIDTH; i++) {
        gotoxy(i, SCREEN_HEIGHT); cout << "||";
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(0, i); cout << "||";
        gotoxy(SCREEN_WIDTH, i); cout << "||";
    }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        gotoxy(WIN_WIDTH, i); cout << "||";
    }
}

/** drawEnemy
* This method creates enemy ships.
* When called, it generates an enemy ship as designed.
*/
void drawEnemy(int ind) {
    if (enemyFlag[ind]) {
        gotoxy(enemyX[ind], enemyY[ind]);   cout << ".**.";
        gotoxy(enemyX[ind], enemyY[ind] + 1); cout << "****";
        gotoxy(enemyX[ind], enemyY[ind] + 2); cout << "****";
        gotoxy(enemyX[ind], enemyY[ind] + 3); cout << ".**.";
    }
}

// This method generates enemy ships at random.
void genEnemy(int ind) {
    enemyX[ind] = 3 + rand() % (WIN_WIDTH - 10);
}

/** eraseEnemy
* This method deletes an enemy ship when it is destroyed.
* It is called under the condition that an enemy ship has been 
destroyed by the player.
*/
void eraseEnemy(int ind) {
    if (enemyFlag[ind]) {
        gotoxy(enemyX[ind], enemyY[ind]); cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind]+1); cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind]+2); cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind]+3); cout << "    ";
    }
}

/** resetEnemy
* This method erases the enemy ship when it gets to the end of the border.
* It is called under the condition that an enemy ship has not been destroyed 
* by the player and it reaches the border.
*/
void resetEnemy(int ind) {
    eraseEnemy(ind);
    enemyY[ind] = 4;
    genEnemy(ind);
}

/** genBullets
* This method generates bullets for the player.
* It is called under the condition that a player presses the spacebar
* to generate/use bullets.
*/
void genBullet() {
    bullets[bIndex][0] = 22;
    bullets[bIndex][1] = shipPos;
    bullets[bIndex][2] = 22;
    bullets[bIndex][3] = shipPos + 4;
    bIndex++;
    if (bIndex == 20)
        bIndex = 0;
}

/** moveBullet
* This method generates a bullet path after it is shot by a player
*/
void moveBullet() {
    for (int i = 0; i < 20; i++) {
        if (bullets[i][0] > 2)
            bullets[i][0]--;
        else
            bullets[i][0] = 0;

        if (bullets[i][2] > 2)
            bullets[i][2]--;
        else
            bullets[i][2] = 0;
    }
}

/** drawBullets
* This method is for the bullet design
*/
void drawBullets() {
    for (int i = 0; i < 20; i++) {
        if (bullets[i][0] > 1) {
            gotoxy(bullets[i][1], bullets[i][0]); cout << "o";
            gotoxy(bullets[i][3], bullets[i][2]); cout << "o";
        }
    }
}

/** eraseBullets
* This method erases the bullets after they hit their target
*/
void eraseBullet(int i) {
    gotoxy(bullets[i][1], bullets[i][0]); cout << " ";
    gotoxy(bullets[i][3], bullets[i][2]); cout << " ";
}

/** resetBullets
* This method erases bullets when they reach the edge of the border
*/
void resetBullets() {
    for (int i = 0; i < 20; i++) {
        if (bullets[i][0] >= 1) {
            gotoxy(bullets[i][1], bullets[i][0]); cout << " ";
            gotoxy(bullets[i][3], bullets[i][2]); cout << " ";
        }
    }
}

// This method constructs player ship 
void drawShip() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            gotoxy(j + shipPos, i + 22); cout << ship[i][j];
        }
    }
}

// This method erases the player ship when they get hit by obstacles
void eraseShip() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 5; j++) {
            gotoxy(j + shipPos, i + 22); cout << " ";
        }
    }
}

/** playerCollision
* This method checks for collisions between the player ship and obstacles
*/
int playerCollision() {
    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 5; j++) {
                if (enemyFlag[k] &&
                    ship[i][j] != ' ' &&
                    enemyY[k] + i >= 22 && enemyY[k] + i <= 24 && // Adjust height range for collision
                    enemyX[k] + j >= shipPos && enemyX[k] + j <= shipPos + 4) {
                    return 1; // Collision detected
                }
            }
        }
    }
    return 0; // No collision detected
}

/** collisionDetector
* This method ensures that obstacles are destroyed when hit by bullets
*/
int collisionDetector() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 4; j += 2) {
            if (bullets[i][j] != 0) {
                for (int k = 0; k < 3; k++) {  // Check all three obstacles
                    if (bullets[i][j] >= enemyY[k] && bullets[i][j] <= enemyY[k] + 3) {
                        if (bullets[i][j + 1] >= enemyX[k] && bullets[i][j + 1] <= enemyX[k] + 3) {
                            eraseBullet(i);
                            bullets[i][j] = 0;
                            resetEnemy(k);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/** updateScore
* This method ensures that the score is updated as the game goes by
*/
void updateScore() {
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Score: " << score << endl;
}

/** instructions
* This method displays the instructions of the game when this option is
* selected in the main menu
*/
void instructions() {
    system("cls");
    cout << "Instructions";
    cout << "\n--------------------";
    cout << "\n Press spacebar to make ship fly";
    cout << "\n--------------------" << endl;
    cout << "Press any key to go back to menu";
    _getch(); // Keeps the screen active until the user presses any key
}

// Declaring variables to track time
clock_t startTime; // Start time
clock_t endTime; // End time
// Time counter method - Start
void startTimer() {
    startTime = clock();
}

// Time counter method - Stop
void stopTimer() {
    endTime = clock();
}

// Method to calculate the elapsed time in seconds
double calculateTimeElapsed() {
    return double(endTime - startTime) / CLOCKS_PER_SEC; // Converts from milliseconds to seconds
}

/** gameOver
* This method displays a "Game Over" screen when the player gets hit by
* an obstacle
*/
void gameOver() {

    stopTimer(); // Stops the timer when the game ends
    double timeElapsed = calculateTimeElapsed(); // Retrieves the elapsed time in seconds

    system("cls");
    cout << endl;
    cout << "\t\t-------------------------------------" << endl;
    cout << "\t\t------------- Game Over -------------" << endl;
    cout << "\t\t-------------------------------------" << endl << endl;;
    cout << "\n";
    cout << "\t\t------------------------------------------" << endl;
    cout << "\t\tTime Elapsed: " << timeElapsed << " seconds" << endl; // Displays the time in seconds
    cout << "\t\tScore: " << score << endl; // Displays the player score
    cout << "\t\t------------------------------------------" << endl << endl;
    cout << "\t\t Press any key to go back to menu.";
    _getch(); // Keeps the display on screen until the user presses any key
}

/** savePlayerRecord
* This method saves the recorded player data: player name, score and time elapsed
* It also updates the record to overwrite old data and replace with new one when a player
* beats their previous high score
*/
void savePlayerRecord(const Player& player) {
    ifstream file("player_records.txt");
    ofstream tempFile("temp.txt");

    bool recordUpdated = false;
    bool playerFound = false;

    if (file.is_open() && tempFile.is_open()) {
        string name;
        int score;
        double time;

        while (file >> name >> score >> time) {
            if (name == player.name) {
                playerFound = true;
                if (player.highScore > score || (player.highScore == score && player.timeElapsed < time)) {
                    tempFile << player.name << " " << player.highScore << " " << player.timeElapsed << endl;
                    recordUpdated = true;
                }
                else {
                    tempFile << name << " " << score << " " << time << endl;
                }
            }
            else {
                tempFile << name << " " << score << " " << time << endl;
            }
        }

        if (!playerFound) {
            tempFile << player.name << " " << player.highScore << " " << player.timeElapsed << endl;
            recordUpdated = true;
        }

        file.close();
        tempFile.close();

        remove("player_records.txt");
        rename("temp.txt", "player_records.txt");
    }
    else {
        cout << "Unable to open file!" << endl;
    }

    if (!recordUpdated) {
        cout << "Record not updated." << endl;
    }
}


// Display high scores
void displayHighScores() {
    system("cls");

    ifstream file("player_records.txt");
    if (!file.is_open()) {
        ofstream createFile("player_records.txt", ios::out);
        createFile.close();
        file.open("player_records.txt");
    }

    if (file.is_open()) {
         // cout << "--------------------------------------------------------" << endl;
         // cout << "|   Player Name\t| Player High Score\t| Player Time Elapsed   |" << endl;
         // cout << "--------------------------------------------------------" << endl;
        cout << "High Scores" << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;

        string name;
        int score;
        double time;
        while (file >> name >> score >> time) {
            cout << "| Player Name: " << name << "\t| Player High Score: " << score << "\t| Player Time Elapsed: " << time << " seconds\t|" << endl;
        }

        cout << "-----------------------------------------------------------------------------------------" << endl;
        file.close();
        cout << "\nPress any key to go back to the menu";
        _getch();
    }
    else {
        cout << "Unable to open file!" << endl;
    }
}


/** Creating load screen
* Defining the functions for icon/text placements
* coordxy - coordinates x/y represents coordinates where elements of 
* the loading screen will be displayed
*/
void coordxy(int x, int y) {
    HANDLE console;
    COORD position;

    position.X = x;
    position.Y = y;
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(console, position);
}

// Loading bar method
void loadingBar() {

    system("cls"); // Clears the screen/Creates a new screen

    // Adding some text
    coordxy(44, 13);
    cout << "LOADING...";
    coordxy(100, 26);
    cout << "SPACE SHOOTER V1.0";

    // Level in % to be displayed
    int level = 13; // Starts at 13% and goes to 100%

    // Drawing the frames of the loading bar
    for (int x = 44; x < 74; x++) { // 2 Horizontal lines
        coordxy(x, 14);
        printf("%c", 205);
        coordxy(x, 16);
        printf("%c", 205);
    }

    for (int y = 15; y < 16; y++) { // 2 Vertical lines
        coordxy(44, y);
        printf("%c", 186);
        coordxy(74, y);
        printf("%c", 186);
    }

    // Corners of the Loading bar
    // Top Left - (x, y) coordinates
    coordxy(44, 14);
    printf("%c", 201); // 201 - ASCII code for left angled side-bars

    // Top right - (x, y) coordinates
    coordxy(74, 14);
    printf("%c", 187); // 187 - ASCII code for right angled side-bars

    // Bottom left - (x, y) coordinates
    coordxy(44, 16);
    printf("%c", 200);

    // Bottom right - (x, y) coordinates
    coordxy(74, 16);
    printf("%c", 188);

    // Loading Bar Design
    for (int load = 45; load <= 73; load++) {
        coordxy(load, 15);
        // cout << "#"; // Alternative loading bar display option
        printf("%c", 219); // 219 ASCII code for a square
        // 178 could not be displayed on the console
        Sleep(100); // This pauses the action at every loop to create the loading effect

        // Updating the number with the loaded level
        level += 3; // Since it starts at level 13, it adds 3 to every cycle
        coordxy(58, 17);
        cout << level << "%"; // Shows the level
    }
}

/** play
* This method initiates the game when called.
* It is called under the condition that the player pressed the "play" option
*/
void play() {

    Player player;
    gotoxy(10, 15); cout << "Enter your name: ";
    cin >> player.name;
    loadingBar(); // Calls loading bar function
    gotoxy(46, 21); cout << "Press any key to continue... "; 
    _getch(); // Pauses loading bar screen

    startTimer();

    shipPos = -1 + WIN_WIDTH / 2;
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 1;
    enemyY[0] = enemyY[1] = 4;

    for (int i = 0; i < 20; i++) {
        bullets[i][0] = bullets[i][1] = 0;
    }

    system("cls");
    drawBorder();
    genEnemy(0);
    genEnemy(1);
    updateScore();

    // Setting up the x, y position of text in the side menu display
    // WIN_WIDTH + X-postion (left-right), Y-position (up-down)
    gotoxy(WIN_WIDTH + 3, 2); cout << " Space Shooter ";
    gotoxy(WIN_WIDTH + 3, 4); cout << "---------------";
    gotoxy(WIN_WIDTH + 3, 6); cout << "---------------";
    gotoxy(WIN_WIDTH + 7, 12); cout << "Controls ";
    gotoxy(WIN_WIDTH + 3, 13); cout << "----------------";
    gotoxy(WIN_WIDTH + 2, 14); cout << " A key - Left ";
    gotoxy(WIN_WIDTH + 2, 15); cout << " D key - Right ";
    gotoxy(WIN_WIDTH + 2, 16); cout << " Spacebar = Shoot ";

    // Loop to set up the movement pattern of the player ship
    // A - moves Left; D - moves Right
    // Using kbhit() to check if the respective key has been pressed
    while (1) {
        if (_kbhit()) {
            char ch = _getch();
            if (ch == 'a' || ch == 'A') { // Moving Left - A key
                if (shipPos > 2)
                    shipPos -= 2;
            }
            if (ch == 'd' || ch == 'D') { // Moving Right - D key
                if (shipPos < WIN_WIDTH - 7)
                    shipPos += 2;
            }
            if (ch == 32) { // Shooting - SpaceBar
                genBullet();
            }
            if (ch == 27) {
                break;
            }
        }
        drawShip();
        drawEnemy(0);
        drawEnemy(1);
        drawBullets();
        if (playerCollision() == 1) {
            gameOver();
            break;
        }
        if (collisionDetector() == 1) {
            score++;
            updateScore();
        }
        Sleep(200);
        eraseShip();
        eraseEnemy(0);
        eraseEnemy(1);
        resetBullets();
        moveBullet();

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 5) {
            resetEnemy(0);
        }
        if (enemyY[1] > SCREEN_HEIGHT - 5) {
            resetEnemy(1);
        }
    }

    player.highScore = score;
    player.timeElapsed = calculateTimeElapsed();

    savePlayerRecord(player);
}

// Main method
int main()
{
    setcursor(0, 0); // Set cursor at centre of the screen
    srand((unsigned)time(NULL));

    // Do-While loop to initiate the game process
    do {
        system("cls");
        gotoxy(10, 5); cout << " --------------------------- ";
        gotoxy(10, 6); cout << " |      SPACE SHOOTER      | ";
        gotoxy(10, 7); cout << " --------------------------- ";
        gotoxy(10, 9); cout << "1. Start Game";
        gotoxy(10, 10); cout << "2. Instructions";
        gotoxy(10, 11); cout << "3. High Scores";
        gotoxy(10, 12); cout << "4. Quit";
        gotoxy(10, 14); cout << "Select Option: ";
        char op = _getche(); // Keeps the screen active for the player to select an option

        if (op == '1') 
            play(); // Signals the start of the game
        else if (op == '2')
            instructions(); // Opens the Instruction screen when the option is selected
        else if (op == '3')
            displayHighScores(); // Displays the high scores when the option is chosen
        else if (op == '4')
            exit(0); // Exits the game when the option is selected
    } while (1);

    return 0;
}