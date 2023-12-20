//
// Created by Lenovo on 2022/8/4.
//

#ifndef PROJECT_LAYER3_H
#define PROJECT_LAYER3_H

#include "layer2.h"

//this layer includes functions in the surface and interaction part

//perform one turn in PVP mode
void PVPNextStep(Game game, Board board, Tank TankA, Tank TankB, string filename);

//perform one turn in PVE mode
void PVENextStep(Game game,Board board, Tank &TankA, Tank &TankB, AiBrain Ai, string filename);

//perform one turn in DEMO mode
void DEMONextStep(Game game,Board board, Tank &TankA, Tank &TankB, AiBrain AiA, AiBrain AiB, string filename);

//judge the "play" status according to the command line arguments
enum Play
{
    Not_chosen, PVP_STATUS, PVE_STATUS, DEMO_STATUS
};

//write the log file
void write_log(Game game, Board board, Tank &TankA, Tank &TankB, string &filename);

//print the help message
void help();

#endif //PROJECT_LAYER3_H
