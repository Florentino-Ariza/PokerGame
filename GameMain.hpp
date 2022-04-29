#ifndef GameMain_H
#define GameMain_H
#include"GameBasic.hpp"

class GameMain : public GameBasic
{
    public:
    bool if_Command;
    int Command_ID;
    int U_ID;
    








    int cur_player_num;
    bool GameStart;
    bool GameEnd;
    bool player_ready[5];
    GameMain();
    ~GameMain();
    //void main_process();//main loop, call the func
    void player_add();//add
    void player_prepare(); 
};
#endif