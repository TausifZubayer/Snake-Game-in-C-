#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

bool gameOver;
bool gameStart;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;
enum eDirection {
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

eDirection dir;

void Setup(){

	gameOver = false;
	gameStart = false;
	dir= STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	nTail = 5;

	for(int i = 0; i < nTail; i++){

        tailX[i] = x + i + 1;
        tailY[i] = y;

	}

}

void Draw(){

    int indicator;

	system("cls"); // on Linux we have to type system("clear");

	for(int i = 0; i < width; i++){
		cout << "#";
	}
	cout << endl;

	for(int i = 0; i < height; i++){

		for(int j = 0; j < width; j++){

			if(j == 0)
				cout << "#";
            else if(i == y && j == x)
                cout << "O";
            else if(i == fruitY && j == fruitX)
                cout << "F";
			else if(j == width - 1)
				cout << "#";
			else{
                indicator = 0;
                for(int k = 0; k < nTail; k++){
                    if(i == tailY[k] && j == tailX[k]){
                        cout << "o";
                        indicator = 1;
                    }
                }
                if(indicator == 0)
                    cout << " ";
			}

		}

		cout << endl;

	}

	for(int i = 0; i < width; i++){
		cout << "#";
	}
	cout << endl;
	cout << "Score : " << score << endl;
}

void Input(){

    if(_kbhit()){

        gameStart = true;

        switch(_getch()){

        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;

        }
    }

}

void Logic(){

    if(gameStart){

        int prevX = x;
        int prevY = y;
        int prev2X, prev2Y;

        for(int i = 0; i < nTail; i++){

            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;

        }

    }

    switch(dir){

    case LEFT:
        x--;
        Sleep(100);
        break;
    case RIGHT:
        x++;
        Sleep(100);
        break;
    case UP:
        y--;
        Sleep(100);
        break;
    case DOWN:
        y++;
        Sleep(100);
        break;

    }

    //if(x == width - 1 || x == 0 || y == height || y == -1)
        //gameOver = true;
    if(x >= width)
        x = 0;
    else if(x <= 0)
        x = width - 1;
    if(y > height)
        y = 0;
    else if(y < 0)
        y = width - 1;
    for(int i = 0; i < nTail; i++){

        if(x == tailX[i] && y == tailY[i])
            gameOver = true;

    }
    if(x == fruitX && y == fruitY){

        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;

    }

}

int main() {

	Setup();

	while(!gameOver){
		Draw();
		Input();
		Logic();
		//Sleep(10); or in Linux, sleep(10);
	}

	return 0;
}
