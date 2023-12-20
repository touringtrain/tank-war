#include "layer1.h"
#include "layer2.h"
#include "layer3.h"
#include <iostream>
#include <cstring>
#include <string>
#define BOARD_SIZE 30

using namespace std;

int main(int argc, char* argv[]){
    //initialize the default elements
    int initLife = 5;
    Play game_status = Not_chosen;
    string filename = "tankwar.log";
    //store the command line arguments
    vector<string> input;
    for (int i = 0; i < argc; i++)
    {
        input.push_back(argv[i]);
    }
    //check the commandline arguments one by one and perform corresponding functions
    if (argc > 8)
    {
        printf("Too many arguments!\n");
        return 0;
    }
    else
    {
        int position = 1;
        while (position <= argc - 1)
        {
            if (input[position] == "-h" || input[position] == "--help")
            {
                help();
                position++;
            }
            else if (!strcmp(argv[position], "--log-file"))
            {
                filename = argv[position + 1];
                position += 2;
            }
            else if (!(input[position].compare("-m"))) {
                if (position < argc - 1) {
                    if (!(input[position + 1].compare("PVP"))) {
                        game_status = PVP_STATUS;
                        position += 2;
                        cout << "You have chosen the PVP mode." << endl;
                    } else if (!(input[position + 1].compare("PVE"))) {
                        game_status = PVE_STATUS;
                        position += 2;
                        cout << "You have chosen the PVE mode." << endl;
                    } else if (!(input[position + 1].compare("DEMO"))) {
                        game_status = DEMO_STATUS;
                        position += 2;
                        cout << "You have chosen the DEMO mode." << endl;
                    } else {
                        cout << "Unknown argument!\n";
                        cout << "Please check your mode input." << endl;
                        position += 6;
                    }
                }
                else
                {
                    cout << "Unknown argument!\n";
                    cout << "You didn't enter the mode." << endl;
                    position += 6;
                }
            }
            else if (!(input[position].compare(0, 7, "--mode=", 0, 7)))
            {
                string mode_string = input[position].substr(7, input[position].size() - 7);
                if (!(mode_string.compare("PVP"))) {
                    game_status = PVP_STATUS;
                    position += 2;
                    cout << "You have chosen the  PVP mode." << endl;
                } else if (!(mode_string.compare("PVE"))) {
                    game_status = PVE_STATUS;
                    position += 2;
                    cout << "You have chosen the PVE mode." << endl;
                } else if (!(mode_string.compare("DEMO"))) {
                    game_status = DEMO_STATUS;
                    position += 2;
                    cout << "You have chosen the DEMO mode." << endl;
                } else {
                    cout << "Unknown argument!\n";
                    cout << "Please check your mode input." << endl;
                    position += 6;
                }
            }
            else if (!(input[position].compare("-p"))) {
                if (position < argc - 1) {
                    for (int i = 0; i < input[position + 1].size(); i++)
                    {
                        if (isdigit(input[position + 1][i]) == 0)
                        {
                            cout << "Unknown argument!\n";
                            cout << "Please check your initial life input." << endl;
                            position += 6;
                        }
                    }
                    initLife = stoi(input[position + 1]);
                    cout << "You have set the initial life of the tanks be: " << initLife << endl;
                    position += 2;
                } else {
                    cout << "Unknown argument!\n";
                    cout << "You didn't enter the initial life." << endl;
                    position += 6;
                }
            }
            else if (!(input[position].compare(0, 15, "--initial-life=", 0, 15)))
            {
                for (int i = 15; i < input[position].size(); i++)
                {
                    if (isdigit(input[position][i]) == 0)
                    {
                        cout << "Unknown argument!\n";
                        cout << "Please check your initial life input." << endl;
                        position += 6;
                    }
                }
                string life_string = input[position].substr(15, input[position].size() - 15);
                initLife = stoi(life_string);
                cout << "You have set the initial life of the tanks be: " << initLife << endl;
                position++;
            }
            else
            {
                cout << "Unknown argument!" << endl;
                position += 6;
            }
        }
    }
    if (game_status == Not_chosen)
    {
        cout << "You have not chosen game mode, now you enter PVP mode by default." << endl;
    }
    //initialize the game
    Board board;
    Tank TankA(0,0,D_Up, initLife);
    Tank TankB(0,0,D_Up, initLife);
    //start the game according to the mode selected
    if (game_status == PVP_STATUS || game_status == Not_chosen)
        {
            Game game(board, TankA, TankB);
            PVPNextStep(game, board, TankA, TankB, filename);
        }
    else if (game_status == PVE_STATUS)
        {
            cout << "You are controlling Tank A, and the AI controls Tank B." << endl;
            Game game(board, TankA, TankB);
            AiBrain AiA;
            PVENextStep(game, board, TankA, TankB, AiA, filename);
        }
    else if (game_status == DEMO_STATUS)
        {
            Game game(board, TankA, TankB);
            AiBrain AiA;
            AiBrain AiB;
            DEMONextStep(game, board, TankA, TankB, AiA, AiB, filename);
        }
}
