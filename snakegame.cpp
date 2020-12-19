#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;
bool gameover;
const int width = 20;
const int height = 16;
int x, y, fX, fY, score;
int tailX[100], tailY[100];
int ntail;
enum eDirection {STOP =0, Left, Right, Up, Down};
eDirection dir;
void Setup()
{
    gameover = false;
    dir = STOP;
    x = width/2;
    y = width/2;
    fX = rand() % width;
    fY = rand() % height;
    score = 0;
}
void Draw()
{
    system("cls");
    for(int i = 0; i < width; i++)
        cout<<"#";
    cout<<endl;

    for(int i=0; i<height; i++)
    {
        for(int j=0; j<width; j++)
        {
            if(j==0)
                cout<<"#";
            if(j==width-1)
                    cout<<"#";
                else
                    cout<<" ";
            if (i==y && j==x)
                cout<<"o";
            if(i==fY && j==fX)
                cout<<"*";
            else{
                bool print=false;
                for(int k=0; k<ntail; k++)
                {
                    if(tailX[k] == j && tailY[k] == i){
                        cout<<"0";
                        print = true;
                    }
                }
                if(!print)
                    cout<<" ";   
            }

        }
    cout<<endl;
    }

    for(int i = 0; i < width; i++)
        cout<<"#";
    cout<<endl;
    cout<<"SCORE : "<<score;
}
void Input()
{
    if(_kbhit())
    {
        switch (_getch())
        {
            case 'a': 
                dir = Left ;
                break;
            case 'd': 
                dir = Right ;
                break;
            case 'w': 
                dir = Up ;
                break;
            case 's': 
                dir = Down ;
                break;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i=1; i<ntail; i++){
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
    }
    switch(dir){
        case Left :
        x--;
        break;
    case Right :
        x++;
        break;
    case Up :
        y++;
        break;
    case Down :
        y--;
        break;
    default :
        break;
    }
    if (x>width || x<0 || y<0 || y>height)
        gameover = true;
    for(int i =0; i<ntail;i++)
    {
        if(tailX[i] == x && tailY[i] == y)
            gameover=true;
    }
    if(x == fX && y==fY){
        score += 10;
        fX = rand() % width;
        fY = rand() % height;
        ntail++;
    }
}

int main()
{
    Setup();
    while(!gameover)
    {
        Draw();
        Input();
        Logic();
        Sleep(10);
    }
    cout<<"!!!!!!!  GAME OVER  !!!!!!!  "<<endl;
    cout<<"Your Final Score is "<<score<<endl;
    return 0;
}