//
// Created by Lenovo on 2022/7/26.
//
#include <fstream>
#include "layer3.h"

void PVPNextStep(Game game, Block (*board)[30], Tank TankA, Tank TankB, string filename)
{
    Turn situation=T_Cont;
    int tempAmove,tempBmove;
    while(situation==T_Cont){
        //user's inputs
        cout << "Please input the movements of Tank A and Tank B, in sequence." << endl;
        cin>>tempAmove>>tempBmove;
        //Tank A moves
        TankA.change(switchMove(tempAmove));
        //Tank A shoots
        if(game.turn%3==1){TankA.addBullet();}
        //Tank B moves
        TankB.change(switchMove(tempBmove));
        //Tank B shoots
        if(game.turn%3==1){TankB.addBullet();}
        //check tank collision
        situation=TankA.crash(TankB);
        if(situation!=T_Cont){
            break;
        }
        //move bullets and check bullet collision
        TankA.bulletMove();
        TankB.bulletMove();
        TankA.judgebullet(TankB);
        TankB.judgebullet(TankA);
        //shrink border
        game.poison=(game.turn) / 16 + 5;
        //check if tanks are out of the border
        TankA.judgePoison(game.poison);
        TankB.judgePoison(game.poison);
        //life check
        if(TankA.health <= 0 && TankB.health > 0){
            situation=T_B_Win;break;
        }else if(TankB.health <= 0 && TankA.health > 0) {
            situation = T_A_Win;break;
        }else if(TankA.health <= 0 && TankB.health <= 0) {
            situation = T_Draw;break;
        }else {situation=T_Cont;
            initBoard(board, TankA, TankB, game.poison);
            drawBoard(board, TankA, TankB, game.turn);
        }
        //add information to the log file
        write_log(game,board, TankA,TankB, filename);
        game.turn++;
    }
    //output the result if the game is finished
    fstream log_file;
    log_file.open(filename,ios::out|ios::app);
    if(situation==T_Draw){
        initBoard(board, TankA, TankB, game.poison);
        drawBoard(board, TankA, TankB, game.turn);
        write_log(game,board, TankA,TankB, filename);
        log_file << "No one wins!" << endl;
        cout<<"No one wins!"<<endl;
    }else if(situation==T_A_Win){
        initBoard(board, TankA, TankB, game.poison);
        drawBoard(board, TankA, TankB, game.turn);
        write_log(game,board, TankA,TankB, filename);
        log_file << "Tank A wins!" << endl;
        cout<<"Tank A wins!"<<endl;
    }else if(situation==T_B_Win){
        initBoard(board, TankA, TankB, game.poison);
        drawBoard(board, TankA, TankB, game.turn);
        write_log(game,board, TankA,TankB, filename);
        log_file << "Tank B wins!" << endl;
        cout<<"Tank B wins!"<<endl;
    }
    log_file.close();
}

void PVENextStep(Game game,Board board, Tank &TankA, Tank &TankB, AiBrain Ai, string filename)
{
    Turn situation=T_Cont;
    int tempPlayerMove;
    while(situation==T_Cont){
        //refresh the tendency score points of the AI after each turn
        Ai.scoreRight = 0;
        Ai.scoreForward = 0;
        Ai.scoreLeft = 0;
        //user's inputs
        cout << "Please input the movement of your tank (Tank A)." << endl;
        cin>>tempPlayerMove;
        //Tank A moves
        TankA.change(switchMove(tempPlayerMove));
        //Tank A shoots
        if(game.turn%3==1){TankA.addBullet();}
        //Tank B moves
        Ai.AiJudgeCollision(TankA, TankB);
        Move AiMove = Ai.AiJudgePoison(game, TankB, TankA);
        TankB.change(switchMove(AiMove));
        //Tank B shoots
        if(game.turn%3==1){TankB.addBullet();}
        //check tank collision
        situation=TankA.crash(TankB);
        if(situation!=T_Cont){
            break;
        }
        //move bullets and check bullet collision
        TankA.bulletMove();
        TankB.bulletMove();
        TankA.judgebullet(TankB);
        TankB.judgebullet(TankA);
        //shrink border
        game.poison=(game.turn) / 16 + 5;
        //check if tanks are out of the border
        TankA.judgePoison(game.poison);
        TankB.judgePoison(game.poison);
        //life check
        if(TankA.health <= 0 && TankB.health > 0){
            situation=T_B_Win;break;
        }else if(TankB.health <= 0 && TankA.health > 0) {
            situation = T_A_Win;break;
        }else if(TankA.health <= 0 && TankB.health <= 0) {
            situation = T_Draw;break;
        }else {situation=T_Cont;
            initBoard(board, TankA, TankB, game.poison);
            drawBoard(board, TankA, TankB, game.turn);
        }
        //add information to the log file
        write_log(game,board, TankA,TankB, filename);
        game.turn++;
    }
    //output the result if the game is finished
    fstream log_file;
    log_file.open(filename,ios::out|ios::app);
    if(situation==T_Draw){
        initBoard(board, TankA, TankB, game.poison);
        drawBoard(board, TankA, TankB, game.turn);
        write_log(game,board, TankA,TankB, filename);
        log_file << "No one wins!" << endl;
        cout<<"No one wins!"<<endl;
    }else if(situation==T_A_Win){
        initBoard(board, TankA, TankB, game.poison);
        drawBoard(board, TankA, TankB, game.turn);
        write_log(game,board, TankA,TankB, filename);
        log_file << "Tank A wins!" << endl;
        cout<<"Tank A wins!"<<endl;
    }else if(situation==T_B_Win){
        initBoard(board, TankA, TankB, game.poison);
        drawBoard(board, TankA, TankB, game.turn);
        write_log(game,board, TankA,TankB, filename);
        log_file << "Tank B wins!" << endl;
        cout<<"Tank B wins!"<<endl;
    }
    log_file.close();
}

void DEMONextStep(Game game,Board board, Tank &TankA, Tank &TankB, AiBrain AiA, AiBrain AiB, string filename)
{
    Turn situation=T_Cont;
    while(situation==T_Cont){
        //refresh the tendency score points of the two AIs after each turn
        AiA.scoreRight = 0;
        AiA.scoreForward = 0;
        AiA.scoreLeft = 0;
        AiB.scoreRight = 0;
        AiB.scoreForward = 0;
        AiB.scoreLeft = 0;
        //Tank A moves
        TankA.change(switchMove(AiA.AiJudgePoison(game, TankA, TankB)));
        //Tank A shoots
        if(game.turn%3==1){TankA.addBullet();}
        //Tank B moves
        TankB.change(switchMove(AiB.AiJudgePoison(game, TankB, TankA)));
        //Tank B shoots
        if(game.turn%3==1){TankB.addBullet();}
        //check tank collision
        situation=TankA.crash(TankB);
        if(situation!=T_Cont){
            break;
        }
        //move bullets and check bullet collision
        TankA.bulletMove();
        TankB.bulletMove();
        TankA.judgebullet(TankB);
        TankB.judgebullet(TankA);
        //shrink border
        game.poison=(game.turn) / 16 + 5;
        //check if tanks are out of the border
        TankA.judgePoison(game.poison);
        TankB.judgePoison(game.poison);
        //life check
        if(TankA.health <= 0 && TankB.health > 0){
            situation=T_B_Win;break;
        }else if(TankB.health <= 0 && TankA.health > 0) {
            situation = T_A_Win;break;
        }else if(TankA.health <= 0 && TankB.health <= 0) {
            situation = T_Draw;break;
        }else {situation=T_Cont;
            initBoard(board, TankA, TankB, game.poison);
            drawBoard(board, TankA, TankB, game.turn);
        }
        //add information to the log file
        write_log(game, board, TankA, TankB, filename);
        game.turn++;
    }
    //output the result if the game is finished
    fstream log_file;
    log_file.open(filename,ios::out|ios::app);
    if(situation==T_Draw){
        initBoard(board, TankA, TankB, game.poison);
        drawBoard(board, TankA, TankB, game.turn);
        write_log(game,board, TankA,TankB, filename);
        log_file << "No one wins!" << endl;
        cout<<"No one wins!"<<endl;
    }else if(situation==T_A_Win){
        initBoard(board, TankA, TankB, game.poison);
        drawBoard(board, TankA, TankB, game.turn);
        write_log(game,board, TankA,TankB, filename);
        log_file << "Tank A wins!" << endl;
        cout<<"Tank A wins!"<<endl;
    }else if(situation==T_B_Win){
        initBoard(board, TankA, TankB, game.poison);
        drawBoard(board, TankA, TankB, game.turn);
        write_log(game,board, TankA,TankB, filename);
        log_file << "Tank B wins!" << endl;
        cout<<"Tank B wins!"<<endl;
    }
    log_file.close();
}

void write_log(Game game, Board board, Tank &TankA, Tank &TankB, string &filename)
{
    fstream log_file;
    log_file.open(filename,ios::out|ios::app);
    log_file << "A: " << TankA.health << "  B: " << TankB.health << "  Turn: " << game.turn << endl;
    log_file << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            log_file << '|';
            log_file << icons[board[i][j]];
        }
        log_file << "|" << endl;
    }
    log_file << endl;
}

void help() {
    cout << "Usage: ./tankwar [OPTIONS]\n";
    cout << "-h | --help              print this help message\n";
    cout << "--log-file filename      write the logs in filename (default: tankwar.log)\n";
    cout << "-m m|--mode=m            play tank war in m (PVP/PVE/DEMO) mode (default: PVP)\n";
    cout << "-p p|--initial-life=p    each tank has p life points initially, p >= 1 (default: 5)\n";
}