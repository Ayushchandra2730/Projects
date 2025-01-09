#include<iostream>
#include<conio.h>
#include <windows.h>
using namespace std;

bool GameOver;
const int width = 20;
const int height = 20;
int x,y,fx,fy,score;
int tailx[100],taily[100];
int nTail;
enum eDirection{STOP = 0,LEFT,RIGHT,UP,DOWN};
eDirection dir;

void Setup(){
    GameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fx = rand() % width;
    fy = rand() % height;
    score = 0;
}
void Draw(){
    system("cls");

    for(int i = 0 ; i<width+2 ; i++){
         cout<<"#";
    }
    cout<<endl;
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++)
        {
            if ( j == 0)
                cout<<"#";
            if (i == y && j == x)
                cout<<"O";
            else if ( i == fy && j == fx)
                cout<<"F";
            else{ 
                 bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailx[k] == j && taily[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                      cout<<" ";
            }
            if (j == width - 1)
                cout<<"#";
        }
        cout<<endl;     
    }
    

    for(int i = 0 ; i<width+2 ; i++)
        cout<<"#";
    cout<<endl;
    cout<<"Score: "<<score<<endl;
}
void Input(){
    if(_kbhit()){
        switch (_getch())
        {
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

        case 'q':
           GameOver = true;
         
        }
    }

}
void Logic(){
    int prex = tailx[0];
    int prey = taily[0];
    int pre2x , pre2y;
    tailx[0] = x;
    taily[0] = y;
    for ( int i =1 ; i< nTail ; i++){
        pre2x = tailx[0];
        pre2y = taily[0];
        tailx[i] = prex;
        taily[i] = prey;
        prex = pre2x;
        prey = pre2y;
    }
    switch (dir)
    {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default :
            break;    
    }
    //if ( x > width || x < 0 || y > height || y < 0){
    //   GameOver = true;}
    if ( x >= width) x = 0; else if (x < 0) x = width -1;    
    if ( y >= height) y = 0; else if (y < 0) y = height -1;    
    for (int i = 0; i < nTail; i++)
    {
        if (tailx[i] == x && taily[i] == y)
        {
            GameOver = true;
        }
        
    }
    
    if ( x == fx && y == fy){
        score += 10;
        fx = rand() % width;
        fy = rand() % height;
        nTail++;
    }

}

int main(){
    Setup();
    while(!GameOver){
        Draw();
        Input();
        Logic();
        Sleep(100);
    }

    return 0;
}