#ifndef FileDisplay_H
#define FileDisplay_H
#include<vector>
#include"HSON.h"
using namespace std;
class FileDisplay
{
public:
    vector<int>* cards_Played;
	vector<int>* player_Hand[5];
	int player_num;
    int player_on_turn;
    int player_last_play;
    int cur_player_num;
    int GameStart;
    int GameEnd;
    int uid_list[5];
    int player_ready[5];
    FileDisplay();
    ~FileDisplay();
	void FileDisplayRegister();
};

#endif