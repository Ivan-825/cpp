/*
███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗
██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝
███████╗██╔██╗ ██║███████║█████╔╝ █████╗  
╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  
███████║██║ ╚████║██║  ██║██║  ██╗███████╗
╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝

Windows console game made by Iván
                                          
*/

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <conio.h>
#include <chrono>
#define H 25
#define W 25


using namespace std;

void print (int field[H][W], int points) {
    string game_state = "";
    string border = "";

    for (int i = 0; i < W+2; i++) {
        border += "# ";
    }

    game_state += border;
    game_state += "\n";


    for (int i = 0; i < H; i ++) {
        game_state += "# ";
        for (int j = 0; j < W; j++) {
            if (field[i][j] > 0) {
                if (field[i][j] == points+2) game_state += "O ";
                else game_state += "# ";
            }
            else if (field[i][j] == -1) game_state += "o ";
            else if (field[i][j] == -8) game_state += "X ";
            else if (field[i][j] == -4) game_state += "x ";
            else game_state += "  ";
        }

        game_state += "#\n";
    }

    game_state += border;

    system("cls");
    //cout << "Points: " << points << "\n";
    cout << game_state;
}

void genfood(int randx, int randy, int field[H][W]) {
    while (field[randy][randx] != 0) {
        randx = rand()%25;
        randy = rand()%25;
    }
    field[randy][randx] = -1;
}

void game(int field[H][W], int dir, int points, int state[],int &x, int &y) {
    int stepX = 0;
    int stepY = 0;

    switch (dir)
    {
    case 97:
        stepX = -1;
        break;

    case 100:
        stepX = 1;
        break;

    case 115:
        stepY = 1;
        break;
    case 119:
        stepY = -1;
        break;

    default:
        break;
    }

    if (x+stepX < 0 || x + stepX >= W || y+stepY < 0 || y+stepY >= H) state[0] = 0; //out of bounds
    else if (field[y+stepY][x+stepX] == points+1) { //180° turn(forbidden)
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (field[i][j] > 0) field[i][j]--;
            }
        }
        field[y-stepY][x-stepX] = points+2;
        y = y - stepY;
        x = x - stepX;
    }
    else if (field[y+stepY][x+stepX] > 0) state[0] = 0; //ate yourself
    else if (field[y+stepY][x+stepX] == -1) { //if food
        field[y+stepY][x+stepX] = points+2;
        y = y + stepY;
        x = x + stepX;

        points++;
        genfood(x, y, field);
    }
    else {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (field[i][j] > 0) field[i][j]--;
            }
        }
        field[y+stepY][x+stepX] = points+2;
        y = y + stepY;
        x = x + stepX;
    }

    if (state[0] == 0) {
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                if (field[i][j] > 0 && field[i][j] != points+2) field[i][j] = -4;
                if (field[i][j] == points+2) field[i][j] = -8;
            }
        }
    }

    if (points == 100) state[0] = 0;

    
    state[1] = points;
}

bool menu() {
    system("cls");
    system("color 0a");


    cout << "          _____                    _____                    _____                    _____                    _____   \n" 
"         /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\     \n" 
"        /::\\    \\                /::\\____\\                /::\\    \\                /::\\____\\                /::\\    \\    \n"    
"       /::::\\    \\              /::::|   |               /::::\\    \\              /:::/    /               /::::\\    \\       \n"
"      /::::::\\    \\            /:::::|   |              /::::::\\    \\            /:::/    /               /::::::\\    \\      \n"
"     /:::/\\:::\\    \\          /::::::|   |             /:::/\\:::\\    \\          /:::/    /               /:::/\\:::\\    \\   \n"  
"    /:::/__\\:::\\    \\        /:::/|::|   |            /:::/__\\:::\\    \\        /:::/____/               /:::/__\\:::\\    \\   \n" 
"    \\:::\\   \\:::\\    \\      /:::/ |::|   |           /::::\\   \\:::\\    \\      /::::\\    \\              /::::\\   \\:::\\    \\ \n"   
"  ___\\:::\\   \\:::\\    \\    /:::/  |::|   | _____    /::::::\\   \\:::\\    \\    /::::::\\____\\________    /::::::\\   \\:::\\    \\ \n"  
" /\\   \\:::\\   \\:::\\    \\  /:::/   |::|   |/\\    \\  /:::/\\:::\\   \\:::\\    \\  /:::/\\:::::::::::\\    \\  /:::/\\:::\\   \\:::\\    \\ \n" 
"/::\\   \\:::\\   \\:::\\____\\/:: /    |::|   /::\\____\\/:::/  \\:::\\   \\:::\\____\\/:::/  |:::::::::::\\____\\/:::/__\\:::\\   \\:::\\____\\ \n"
"\\:::\\   \\:::\\   \\::/    /\\::/    /|::|  /:::/    /\\::/    \\:::\\  /:::/    /\\::/   |::|~~~|~~~~~     \\:::\\   \\:::\\   \\::/    / \n"
" \\:::\\   \\:::\\   \\/____/  \\/____/ |::| /:::/    /  \\/____/ \\:::\\/:::/    /  \\/____|::|   |           \\:::\\   \\:::\\   \\/____/  \n"
"  \\:::\\   \\:::\\    \\              |::|/:::/    /            \\::::::/    /         |::|   |            \\:::\\   \\:::\\    \\     \n"
"   \\:::\\   \\:::\\____\\             |::::::/    /              \\::::/    /          |::|   |             \\:::\\   \\:::\\____\\    \n"
"    \\:::\\  /:::/    /             |:::::/    /               /:::/    /           |::|   |              \\:::\\   \\::/    /    \n"
"     \\:::\\/:::/    /              |::::/    /               /:::/    /            |::|   |               \\:::\\   \\/____/     \n"
"      \\::::::/    /               /:::/    /               /:::/    /             |::|   |                \\:::\\    \\         \n"
"       \\::::/    /               /:::/    /               /:::/    /              \\::|   |                 \\:::\\____\\        \n"
"        \\::/    /                \\::/    /                \\::/    /                \\:|   |                  \\::/    /        \n"
"         \\/____/                  \\/____/                  \\/____/                  \\|___|                   \\/____/         \n";

    cout << "\n\n\n\n\n\n" << "Real good snake game made by Ivan.";
    cout << "\n\n\n\n" << "WARNING: Do not play if you are sensitive to flashing lights!";
    cout << "\n\n\n" << "Press Enter to start the game!";

    while (true) {
        if (_kbhit()) {
            int ch = getch();
            if (ch == 13 || ch == 32) return true;
            else return false;
        }
    }                               

}

int main() {
    if (menu());
    else return -1;
    srand(time(0));
    bool running = true;
    int points = 0;
    int state[2];
    int dir = 119;
    int x = H/2;
    int y = H/2;

    int field [H][W] = {0};

    field[y][x] = 2;
    field[(H/2)+1][W/2] = 1;

    int randx = x;
    int randy = y;

    genfood(randx, randy, field);


    while (running) {
        char inp;
        auto start = chrono::high_resolution_clock::now();
        auto now = chrono::high_resolution_clock::now();

        while (chrono::duration_cast<chrono::milliseconds>(now - start).count() < 80) {
            if (_kbhit()) {
                inp = getch();
                if (inp == 3 || inp == 27 || inp == 97 || inp == 100 || inp == 115 || inp == 119) dir = inp;
            }  
            now = chrono::high_resolution_clock::now();
        }

        if (dir == 3 || dir == 27) running = false;
        game(field, dir, points, state, x, y);
        if (state[0] == 0) running = false;
        points = state[1];
        print(field, points);
    }
    for (int i = 0; i < 3; i++) {
        system("color 04");
        system("timeout /t 0 /nobreak>nul");
        system("color 48");
        system("timeout /t 0 /nobreak>nul");
        system("color 0a");
    }
    system("color 04");

    cout << "\n\n" << "Score: " << points << "\n\n\n\n\n";

    return 0;
}