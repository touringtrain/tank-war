//
// Created by Lenovo on 2022/7/25.
//

#ifndef PROJECT_LAYER1_H
#define PROJECT_LAYER1_H
#define BOARD_SIZE 30
#include<iostream>
#include<vector>
using namespace std;

#ifndef TEST_CPP_TANK_H
#define TEST_CPP_TANK_H

//this layer defines the most basic elements of the game
//including the class of tank, the expression of direction, movement, game status and the game board

//enumeration of all the possible direction of the tank
enum Direction {
    D_Left, D_Up, D_Right, D_Down
};

//enumeration of all the possible movement choices of the tank
enum Move {
    M_Forward, M_Left, M_Right
};

//a flag used to judge the game status after each turn
//"T_Cont" means continuing the game, the other three signals the ending of the game
enum Turn {
    T_Cont, T_A_Win, T_B_Win, T_Draw
};

//enumeration of all the possible status of one block in the board
//used for simplifying the initialization of the game board
enum Block {
    Board_Blank, Board_Bullet, Board_Tank_A, Board_Tank_B, Board_Poison
};

//all the possible patterned drown on the board
const char icons[5] = {' ', '*', 'A', 'B', '-'};

//class for each single tank
class Tank{
public:
    //position
    int x,y;
    //health points
    int health;
    //direction
    Direction dir;
    struct Bullet{
        int B_x;
        int B_y;
        Direction B_dir;
    };
    //a vector storing all the bullets of this tank
    vector<Bullet>allBullet;
    //constructor
    Tank(int pos_x,int pos_y,Direction direction, int input_health){x=pos_x;y=pos_y;dir=direction;health = input_health;};
    //position change of the tank
    void change(Move move);
    //add a bullet to the tank every 3 turns
    void addBullet();
    //judge if the tank is attacked by the other tank
    void judgebullet(Tank &another);
    //calculate the movement of all the bullets
    void bulletMove();
    //judge whether the tank is in the poisonous area, and reduce the health points
    void judgePoison(int poison);
    //judge whether the two tanks will crash and output the game result
    Turn crash(Tank &another);
};

//definition of the game board
typedef Block Board[BOARD_SIZE][BOARD_SIZE];
//initialize and draw the game board
void initBoard(Board board, Tank TankA, Tank TankB, int poison);
void drawBoard(Board board, Tank TankA, Tank TankB, int turn);

//output the direction and movement when inputting an integer
//a connection between the user's input (an integer) and the actual direction or movement
Direction switchDirection(int a);
Move switchMove(int a);
#endif //TEST_CPP_TANK_H


#endif //PROJECT_LAYER1_H
