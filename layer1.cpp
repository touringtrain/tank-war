//
// Created by Lenovo on 2022/7/25.
//
#include"layer1.h"
#include<iostream>
#define BOARD_SIZE 30
using namespace std;

void Tank::change(Move move){
    switch(dir){
        case D_Left:
            switch (move) {
                case M_Left:y++;dir=D_Down;break;
                case M_Right:y--;dir=D_Up;break;
                case M_Forward:x--;break;
            }break;
        case D_Up:
            switch (move) {
                case M_Left:x--;dir =D_Left;break;
                case M_Right:x++;dir = D_Right;break;
                case M_Forward:y--;break;
            }break;
        case D_Right:
            switch (move) {
                case M_Left:y--;dir =D_Up;break;
                case M_Right:y++;dir = D_Down;break;
                case M_Forward:x++;break;
            }break;
        case D_Down:
            switch (move) {
                case M_Left:x++;dir =D_Right;break;
                case M_Right:x--;dir = D_Left;break;
                case M_Forward:y++;break;
            }break;
    }
}
void Tank::addBullet(){
    if (dir== D_Left){
        allBullet.push_back(Bullet{x-1,y,D_Left});}
    if(dir== D_Up){
        allBullet.push_back(Bullet{x,y-1,D_Up});}
    if(dir==D_Right){
        allBullet.push_back(Bullet{x+1,y,D_Right});}
    if(dir== D_Down){
        allBullet.push_back(Bullet{x,y+1,D_Down});}
}
void Tank::bulletMove(){
    int bulletSize=(int)allBullet.size();
    for(int i = 0; i < bulletSize; i++){
        if (allBullet[i].B_dir == D_Left){
            allBullet[i].B_x = allBullet[i].B_x - 2;
        }
        if (allBullet[i].B_dir == D_Up){
            allBullet[i].B_y=allBullet[i].B_y - 2;
        }if (allBullet[i].B_dir == D_Right){
            allBullet[i].B_x=allBullet[i].B_x + 2;
        }if (allBullet[i].B_dir == D_Down){
            allBullet[i].B_y=allBullet[i].B_y + 2;
        }
    }

}
void Tank::judgebullet(Tank &another){
    int bulletSize=another.allBullet.size();
    for(int i=0;i<bulletSize;i++){
        if(x == another.allBullet[i].B_x && y == another.allBullet[i].B_y){
            health -= 2;
            another.allBullet.erase(another.allBullet.begin()+i);
        }
    }
}
Turn Tank::crash(Tank &another) {
    if (x == another.x && y == another.y) {
        if (health > another.health) {
            return T_A_Win;
        }else if(health < another.health){
            return T_B_Win;
        }else{return T_Draw;}
    }else{return T_Cont;}
}

void initBoard(Board board, Tank TankA, Tank TankB, int poison) {
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            if ((i <= BOARD_SIZE - poison - 1 && j <= BOARD_SIZE - poison - 1) &&
                (i >= poison && j >= poison)) { board[i][j] = Board_Blank; }
            else { board[i][j] = Board_Poison; }
            if (j == TankA.x && i == TankA.y) { board[i][j] = Board_Tank_A; }
            if (j == TankB.x && i == TankB.y) { board[i][j] = Board_Tank_B; }
            for (int k = 0; k < TankA.allBullet.size(); k++) {
                if ((j == TankA.allBullet[k].B_x && i == TankA.allBullet[k].B_y)) {
                    board[i][j] = Board_Bullet;
                }
            }
            for (int k = 0; k < TankB.allBullet.size(); k++) {
                if ((j == TankB.allBullet[k].B_x && i == TankB.allBullet[k].B_y)) {
                    board[i][j] = Board_Bullet;
                }
            }
        }
    }
}

void drawBoard(Board board, Tank TankA, Tank TankB, int turn){
    cout << "Life of A: " << TankA.health << "  Life of B: " << TankB.health << "  Turn: " << turn << endl;
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << '|';
            cout << icons[board[i][j]];
        }
        cout << "|" << endl;
    }
    cout << endl;
}

Direction switchDirection(int a){
    if(a==0){
        return D_Left;
    }else if(a==1){
        return D_Up;
    }else if(a==2){
        return D_Right;
    }else{
        return D_Down;
    }
}
Move switchMove(int a)
{
    if(a==0){
        return M_Forward;
    }else if(a==1){
        return M_Left;
    }else {
        return M_Right;
    }
}

//judge if the tank is in the tank is in the poisonous area
void Tank::judgePoison(int poison)
{
    if(!((x <= BOARD_SIZE - poison - 1 && x >= poison) && (y >= poison && y <= BOARD_SIZE - poison - 1)))
    {
        this->health--;
    }
}