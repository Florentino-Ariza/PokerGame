#ifndef GameMain_H
#define GameMain_H
#include"GameBasic.hpp"
#include"Hson.h"
class GameMain : public GameBasic
{
    public:
    int if_Command;
    int Command_ID;
    int U_ID;
    int cur_player_num;
    int GameStart;
    int GameEnd;
    int uid_list[5];
    int player_ready[5];
    GameMain();
    ~GameMain();
    void player_add();//add
    void player_prepare(); 
    int uid_mapping(int uid);
    void operate();
    void main_process();
    void FileDisplayRegister();
    void File_Write();
};
#endif