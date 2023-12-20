//
// Created by Lenovo on 2022/7/25.
//
#include "layer1.h"
#include <iostream>

#ifndef PROJECT_LAYER2_H
#define PROJECT_LAYER2_H

//this layer includes a class "Game" and a class "AiBrain"
//as well as a class "virtualBullet" helping the functioning of the Ai.

//the class Game including a constructor, the number of turn and the thickness of the poisonous area
class Game
{
public:
    Game(Board board, Tank &TankA, Tank &TankB);
    int turn;
    int poison;
};

//the class AiBrain which can judge the current situation and make proper choice
class AiBrain
{
public:
    AiBrain()
    {
        scoreForward = 0;
        scoreLeft = 0;
        scoreRight = 0;
    }
    //judge the risk of colliding with another tank or its bullets
    void AiJudgeCollision(Tank &current, Tank &another);
    //return the optimal solution of movement
    Move AiJudgePoison(Game game, Tank &current, Tank &another);
    //the tendency score of choosing different directions
    int scoreForward;
    int scoreLeft;
    int scoreRight;
};

//this class is designed for simplifying the AI judgement
//used to store the virtual position of all the bullets of another tank
class virtualBullet{
public:
    virtualBullet(int x, int y)
    {
        virtual_B_x = x;
        virtual_B_y = y;
    }
    int virtual_B_x;
    int virtual_B_y;
};

#endif //PROJECT_LAYER2_H
