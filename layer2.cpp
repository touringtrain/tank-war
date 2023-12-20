//
// Created by Lenovo on 2022/7/25.
//
#include <iostream>
#include "layer2.h"

//initializing the game as well as the properties of the two tanks
Game::Game(Block (*board)[30], Tank &TankA, Tank &TankB)
{
    this->turn = 1;
    this->poison = 5;
    int tempAdir,tempBdir;
    int ax, ay, bx, by;
    cout << "Please input: the position of Tank A, the position of Tank B, \n"
            "the direction of Tank A, the direction of Tank B, in sequence." << endl;
    cin>> ax>>ay>>bx>>by>>tempAdir>>tempBdir;
    TankA.x = ax + poison;
    TankA.y = ay + poison;
    TankB.x = bx + poison;
    TankB.y = by + poison;
    TankA.dir= switchDirection(tempAdir);
    TankB.dir= switchDirection(tempBdir);
}

//in the AIJudgeCollision and AiJudgeNext functions, the tendency score of all the three different directions
//will change under specific situations

//and the AiJudgeNext function will return the movement with the highest tendency points
//in case two or three directions have the same points, the function will choose randomly

void AiBrain::AiJudgeCollision(Tank &current, Tank &another)
{
    vector<virtualBullet> anotherBullet;
    int bulletSize=(int)another.allBullet.size();
    for(int i = 0; i < bulletSize; i++){
        if (another.allBullet[i].B_dir == D_Left){
            virtualBullet bullet (another.allBullet[i].B_x - 2, another.allBullet[i].B_y);
            anotherBullet.push_back(bullet);
        }
        if (another.allBullet[i].B_dir == D_Up){
            virtualBullet bullet (another.allBullet[i].B_x, another.allBullet[i].B_y - 2);
            anotherBullet.push_back(bullet);
        }if (another.allBullet[i].B_dir == D_Right){
            virtualBullet bullet (another.allBullet[i].B_x + 2, another.allBullet[i].B_y);
            anotherBullet.push_back(bullet);
        }if (another.allBullet[i].B_dir == D_Down){
            virtualBullet bullet (another.allBullet[i].B_x, another.allBullet[i].B_y + 2);
            anotherBullet.push_back(bullet);
        }
    }
    if (current.dir == D_Up)
    {
        for(int i = 0; i < bulletSize; i++){
            if (current.x == anotherBullet[i].virtual_B_x && current.y - 1 == anotherBullet[i].virtual_B_y)
            {
                scoreForward -= 10;
                break;
            }
            if (current.x - 1== anotherBullet[i].virtual_B_x && current.y == anotherBullet[i].virtual_B_y)
            {
                scoreLeft -=10;
                break;
            }
            if (current.x + 1 == anotherBullet[i].virtual_B_x && current.y == anotherBullet[i].virtual_B_y)
            {
                scoreRight -= 10;
                break;
            }
        }
        if (current.x > another.x && current.y > another.y)
        {
            if (current.health >= another.health) {
                scoreForward += 5;
                scoreLeft += 5;
            }
            else
            {
                scoreLeft += 8;
            }
        }
        else if (current.x > another.x && current.y < another.y)
        {
            if (current.health >= another.health){
                scoreLeft += 8;
            }
            else
            {
                scoreForward += 5;
                scoreRight += 5;
            }
        }
        else if (current.x < another.x && current.y > another.y)
        {
            if (current.health >= another.health) {
                scoreForward += 5;
                scoreRight += 5;
            }
            else
            {
                scoreLeft += 8;
            }
        }
        else if (current.x < another.x && current.y < another.y)
        {
            if (current.health >= another.health) {
                scoreRight += 8;
            }
            else
            {
                scoreForward += 5;
                scoreLeft += 5;
            }
        }
        else if (current.x == another.x && current.y > another.y)
        {
            if (current.health >= another.health)
            {
                scoreForward += 10;
            }
            else
            {
                scoreLeft += 5;
                scoreRight += 5;
            }
        }
        else if (current.x == another.x && current.y < another.y)
        {
            if (current.health >= another.health)
            {
                scoreLeft += 5;
                scoreRight += 5;

            }
            else
            {
                scoreForward += 10;
            }
        }
        else if (current.x > another.x && current.y == another.y)
        {
            if (current.health >= another.health)
            {
                scoreLeft += 8;
            }
            else
            {
                scoreForward += 5;
                scoreRight += 5;
            }
        }
        else if (current.x < another.x && current.y == another.y)
        {
            if (current.health >= another.health)
            {
                scoreRight += 8;
            }
            else
            {
                scoreForward += 5;
                scoreLeft += 5;
            }
        }
    }
    else if (current.dir == D_Right)
    {
        for(int i = 0; i < bulletSize; i++){
            if (current.x + 1 == anotherBullet[i].virtual_B_x && current.y == anotherBullet[i].virtual_B_y)
            {
                scoreForward -= 10;
                break;
            }
            if (current.x== anotherBullet[i].virtual_B_x && current.y - 1 == anotherBullet[i].virtual_B_y)
            {
                scoreLeft -= 10;
                break;
            }
            if (current.x == anotherBullet[i].virtual_B_x && current.y + 1 == anotherBullet[i].virtual_B_y)
            {
                scoreRight -= 10;
                break;
            }
        }
        if (current.x > another.x && current.y > another.y)
        {
            if (current.health >= another.health) {
                scoreLeft += 8;
            }
            else
            {
                scoreForward += 5;
                scoreRight += 5;
            }
        }
        else if (current.x > another.x && current.y < another.y)
        {
            if (current.health >= another.health){
                scoreRight += 8;
            }
            else
            {
                scoreForward += 5;
                scoreLeft += 5;
            }
        }
        else if (current.x < another.x && current.y > another.y)
        {
            if (current.health >= another.health) {
                scoreForward += 5;
                scoreLeft += 5;
            }
            else
            {
                scoreRight += 8;
            }
        }
        else if (current.x < another.x && current.y < another.y)
        {
            if (current.health >= another.health) {
                scoreForward += 5;
                scoreRight += 5;
            }
            else
            {
                scoreLeft += 8;
            }
        }
        else if (current.x == another.x && current.y > another.y)
        {
            if (current.health >= another.health)
            {
                scoreLeft += 8;
            }
            else
            {
                scoreForward += 5;
                scoreRight += 5;
            }
        }
        else if (current.x == another.x && current.y < another.y)
        {
            if (current.health >= another.health)
            {
                scoreRight += 8;
            }
            else
            {
                scoreForward += 5;
                scoreLeft += 5;
            }
        }
        else if (current.x > another.x && current.y == another.y)
        {
            if (current.health >= another.health)
            {
                scoreLeft += 5;
                scoreRight += 5;
            }
            else
            {
                scoreForward += 8;
            }
        }
        else if (current.x < another.x && current.y == another.y)
        {
            if (current.health >= another.health)
            {
                scoreForward += 10;
            }
            else
            {
                scoreRight += 5;
                scoreLeft += 5;
            }
        }
    }
    else if (current.dir == D_Down)
    {
        for(int i = 0; i < bulletSize; i++){
            if (current.x == anotherBullet[i].virtual_B_x && current.y + 1 == anotherBullet[i].virtual_B_y)
            {
                scoreForward -= 10;
                break;
            }
            if (current.x + 1== anotherBullet[i].virtual_B_x && current.y == anotherBullet[i].virtual_B_y)
            {
                scoreLeft -= 10;
                break;
            }
            if (current.x - 1 == anotherBullet[i].virtual_B_x && current.y == anotherBullet[i].virtual_B_y)
            {
                scoreRight -= 10;
                break;
            }
        }
        if (current.x > another.x && current.y > another.y)
        {
            if (current.health >= another.health) {
               scoreRight += 8;
            }
            else
            {
               scoreForward += 5;
               scoreLeft += 5;
            }
        }
        else if (current.x > another.x && current.y < another.y)
        {
            if (current.health >= another.health){
                scoreForward += 5;
                scoreRight += 5;
            }
            else
            {
                scoreLeft += 8;
            }
        }
        else if (current.x < another.x && current.y > another.y)
        {
            if (current.health >= another.health) {
                scoreLeft += 8;
            }
            else
            {
                scoreForward += 5;
                scoreRight += 5;
            }
        }
        else if (current.x < another.x && current.y < another.y)
        {
            if (current.health >= another.health) {
                scoreForward += 5;
                scoreLeft += 5;
            }
            else
            {
                scoreRight += 8;
            }
        }
        else if (current.x == another.x && current.y > another.y)
        {
            if (current.health >= another.health)
            {
                scoreLeft += 5;
                scoreRight += 5;
            }
            else
            {
                scoreForward += 8;
            }
        }
        else if (current.x == another.x && current.y < another.y)
        {
            if (current.health >= another.health)
            {
                scoreForward += 10;
            }
            else
            {
                scoreRight += 5;
                scoreLeft += 5;
            }
        }
        else if (current.x > another.x && current.y == another.y)
        {
            if (current.health >= another.health)
            {
                scoreLeft += 5;
                scoreRight += 5;
            }
            else
            {
                scoreForward += 8;
            }
        }
        else if (current.x < another.x && current.y == another.y)
        {
            if (current.health >= another.health)
            {
                scoreLeft += 8;
            }
            else
            {
                scoreForward += 5;
                scoreRight += 5;
            }
        }
    }
    else if (current.dir == D_Left)
    {
        for(int i = 0; i < bulletSize; i++){
            if (current.x - 1 == anotherBullet[i].virtual_B_x && current.y == anotherBullet[i].virtual_B_y)
            {
                scoreForward -= 10;
                break;
            }
            if (current.x== anotherBullet[i].virtual_B_x && current.y + 1 == anotherBullet[i].virtual_B_y)
            {
                scoreLeft -= 10;
                break;
            }
            if (current.x == anotherBullet[i].virtual_B_x && current.y - 1 == anotherBullet[i].virtual_B_y)
            {
                scoreRight -= 10;
                break;
            }
        }
        if (current.x > another.x && current.y > another.y)
        {
            if (current.health >= another.health) {
                scoreForward += 5;
                scoreRight += 5;
            }
            else
            {
                scoreLeft += 8;
            }
        }
        else if (current.x > another.x && current.y < another.y)
        {
            if (current.health >= another.health){
                scoreForward += 5;
                scoreLeft += 5;
            }
            else
            {
                scoreRight += 8;
            }
        }
        else if (current.x < another.x && current.y > another.y)
        {
            if (current.health >= another.health) {
                scoreRight += 8;
            }
            else
            {
                scoreForward += 5;
                scoreLeft += 5;
            }
        }
        else if (current.x < another.x && current.y < another.y)
        {
            if (current.health >= another.health) {
                scoreLeft += 8;
            }
            else
            {
                scoreForward += 5;
                scoreRight += 5;
            }
        }
        else if (current.x == another.x && current.y > another.y)
        {
            if (current.health >= another.health)
            {
                scoreRight += 8;
            }
            else
            {
                scoreForward += 5;
                scoreLeft += 5;
            }
        }
        else if (current.x == another.x && current.y < another.y)
        {
            if (current.health >= another.health)
            {
                scoreLeft += 8;
            }
            else
            {
                scoreForward += 5;
                scoreRight += 5;
            }
        }
        else if (current.x > another.x && current.y == another.y)
        {
            if (current.health >= another.health)
            {
               scoreForward += 10;
            }
            else
            {
              scoreLeft += 5;
              scoreRight += 5;
            }
        }
        else if (current.x < another.x && current.y == another.y)
        {
            if (current.health >= another.health)
            {
                scoreLeft += 5;
                scoreRight += 5;
            }
            else
            {
                scoreForward += 8;
            }
        }
    }
}

Move AiBrain::AiJudgePoison(Game game, Tank &current, Tank &another) {
    int up_distance = current.y - game.poison;
    int down_distance = BOARD_SIZE - game.poison - current.y - 1;
    int left_distance = current.x - game.poison;
    int right_distance = BOARD_SIZE - game.poison - current.x - 1;
    if ((current.x <= BOARD_SIZE - game.poison - 1 && current.x >= game.poison)
        && (current.y >= game.poison && current.y <= BOARD_SIZE - game.poison - 1)) {
        if (current.dir == D_Up) {
            if (up_distance <= 1) {
                scoreForward -= 10;
            }
            if (left_distance <= 1) {
                scoreLeft -= 10;
            }
            if (right_distance <= 1) {
                scoreRight -= 10;
            }
        }
        if (current.dir == D_Right) {
            if (up_distance <= 1) {
                scoreLeft -= 10;
            }
            if (down_distance <= 1) {
                scoreRight -= 10;
            }
            if (right_distance <= 1) {
                scoreForward -= 10;
            }
        }
        if (current.dir == D_Down) {
            if (down_distance <= 1) {
                scoreForward -= 10;
            }
            if (left_distance <= 1) {
                scoreRight -= 10;
            }
            if (right_distance <= 1) {
                scoreLeft -= 10;
            }
        }
        if (current.dir == D_Left) {
            if (up_distance <= 1) {
                scoreRight -= 10;
            }
            if (left_distance <= 1) {
                scoreForward -= 10;
            }
            if (down_distance <= 1) {
                scoreLeft -= 10;
            }
        }
    }
    else {
        if (up_distance < 0) {
            if (current.x >= game.poison && current.x <= BOARD_SIZE - game.poison - 1) {
                if (current.dir == D_Up)
                {
                    scoreForward -= 20;
                    if (current.x - game.poison <= 2)
                    {
                        scoreLeft -= 5;
                    }
                }
                if (current.dir == D_Left)
                {
                    scoreLeft += 20;
                }
                if (current.dir == D_Right)
                {
                    scoreRight += 20;
                }
                if (current.dir == D_Down)
                {
                    scoreForward += 20;
                }
            }
            if (current.x <= game.poison - 1) {
                if (current.dir == D_Up)
                {
                    scoreRight += 20;
                }
                if (current.dir == D_Left)
                {
                    scoreLeft += 20;
                }
                if (current.dir == D_Right)
                {
                    scoreForward += 10;
                    scoreRight += 10;
                    if (game.poison - current.x > game.poison - current.y)
                    {
                        scoreForward += 10;
                    }
                    if (game.poison - current.x < game.poison - current.y)
                    {
                        scoreRight += 10;
                    }
                }
                if (current.dir == D_Down)
                {
                    scoreForward += 10;
                    scoreLeft += 10;
                    if (game.poison - current.x > game.poison - current.y)
                    {
                        scoreLeft += 10;
                    }
                    if (game.poison - current.x < game.poison - current.y)
                    {
                        scoreForward += 10;
                    }
                }
            }
            if (current.x >= BOARD_SIZE - game.poison - 1) {
                if (current.dir == D_Up)
                {
                    scoreLeft += 20;
                }
                if (current.dir == D_Right)
                {
                    scoreRight += 20;
                }
                if (current.dir == D_Left)
                {
                    scoreForward += 10;
                    scoreLeft += 10;
                    if (current.x - (BOARD_SIZE - game.poison - 1) > game.poison - current.y)
                    {
                        scoreForward += 10;
                    }
                    if (current.x - (BOARD_SIZE - game.poison - 1) < game.poison - current.y)
                    {
                        scoreLeft += 10;
                    }
                }
                if (current.dir == D_Down)
                {
                    scoreForward += 10;
                    scoreRight += 10;
                    if (current.x - (BOARD_SIZE - game.poison - 1) > game.poison - current.y)
                    {
                        scoreRight += 10;
                    }
                    if (current.x - (BOARD_SIZE - game.poison - 1) < game.poison - current.y)
                    {
                        scoreForward += 10;
                    }
                }
            }
        }
        if (down_distance < 0) {
            if (current.x >= game.poison && current.x <= BOARD_SIZE - game.poison - 1) {
                if (current.dir == D_Up) {
                    scoreForward += 20;
                }
                if (current.dir == D_Left) {
                    scoreRight += 20;
                }
                if (current.dir == D_Right) {
                    scoreLeft += 20;
                }
                if (current.dir == D_Down) {
                    scoreForward -= 20;
                    if (current.x - game.poison <= 2) {
                        scoreRight -= 5;
                    }
                }
            }
            if (current.x <= game.poison - 1) {
                if (current.dir == D_Left) {
                    scoreRight += 20;
                }
                if (current.dir == D_Down) {
                    scoreLeft += 20;
                }
                if (current.dir == D_Right) {
                    scoreForward += 10;
                    scoreLeft += 10;
                    if (game.poison - current.x > current.y - (BOARD_SIZE - game.poison - 1)) {
                        scoreForward += 10;
                    }
                    if (game.poison - current.x < current.y - (BOARD_SIZE - game.poison - 1)) {
                        scoreLeft += 10;
                    }
                }
                if (current.dir == D_Up) {
                    scoreForward += 10;
                    scoreRight += 10;
                    if (game.poison - current.x > current.y - (BOARD_SIZE - game.poison - 1)) {
                        scoreRight += 10;
                    }
                    if (game.poison - current.x < current.y - (BOARD_SIZE - game.poison - 1)) {
                        scoreForward += 10;
                    }
                }
            }
            if (current.x >= BOARD_SIZE - game.poison - 1) {
                if (current.dir == D_Right) {
                    scoreLeft += 20;
                }
                if (current.dir == D_Down) {
                    scoreRight += 20;
                }
                if (current.dir == D_Left) {
                    scoreForward += 10;
                    scoreRight += 10;
                    if (current.x - (BOARD_SIZE - game.poison - 1) > current.y - (BOARD_SIZE - game.poison - 1)) {
                        scoreForward += 10;
                    }
                    if (current.x - (BOARD_SIZE - game.poison - 1) < current.y - (BOARD_SIZE - game.poison - 1)) {
                        scoreRight += 10;
                    }
                }
                if (current.dir == D_Up) {
                    scoreForward += 10;
                    scoreLeft += 10;
                    if (current.x - (BOARD_SIZE - game.poison - 1) > current.y - (BOARD_SIZE - game.poison - 1)) {
                        scoreLeft += 10;
                    }
                    if (current.x - (BOARD_SIZE - game.poison - 1) < current.y - (BOARD_SIZE - game.poison - 1)) {
                        scoreForward += 10;
                    }
                }
            }
        }
        if (up_distance >= 0 && down_distance >= 0)
        {
            if (left_distance < 0)
            {
                if (current.dir == D_Right) {
                    scoreForward += 20;
                }
                if (current.dir == D_Up) {
                    scoreRight += 20;
                }
                if (current.dir == D_Down) {
                    scoreLeft += 20;
                }
                if (current.dir == D_Left) {
                    scoreForward -= 20;
                    if (current.y - game.poison <= 2) {
                        scoreRight -= 5;
                    }
                }
            }
            if (right_distance < 0)
            {
                if (current.dir == D_Left) {
                    scoreForward += 20;
                }
                if (current.dir == D_Down) {
                    scoreRight += 20;
                }
                if (current.dir == D_Up) {
                    scoreLeft += 20;
                }
                if (current.dir == D_Right) {
                    scoreForward -= 20;
                    if (current.y - game.poison <= 2) {
                        scoreLeft -= 5;
                    }
                }
            }
        }
    }
    if (scoreForward > scoreLeft && scoreForward > scoreRight)
    {
        return M_Forward;
    }
    if (scoreRight > scoreForward && scoreRight > scoreLeft)
    {
        return M_Right;
    }
    if (scoreLeft > scoreForward && scoreLeft > scoreRight)
    {
        return M_Left;
    }
    if (scoreForward == scoreRight && scoreForward > scoreLeft)
    {
        int num = rand();
        if (num == 0)
        {
            return M_Forward;
        }
        else
        {
            return M_Right;
        }
    }
    if (scoreForward == scoreLeft && scoreForward > scoreRight)
    {
        int num = rand();
        if (num == 0)
        {
            return M_Forward;
        }
        else
        {
            return M_Left;
        }
    }
    if (scoreLeft == scoreRight && scoreLeft > scoreForward)
    {
        int num = rand();
        if (num == 0)
        {
            return M_Left;
        }
        else
        {
            return M_Right;
        }
    }
    if (scoreForward == scoreRight && scoreForward == scoreLeft)
    {
        int num = rand() % 2;
        if (num == 0)
        {
            return M_Forward;
        }
        else if (num == 1)
        {
            return M_Left;
        }
        else
        {
            return M_Right;
        }
    }
    return M_Forward;
}




