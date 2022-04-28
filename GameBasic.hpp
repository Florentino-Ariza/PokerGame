#ifndef GameBasic_H
#define GameBasic_H
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
class GameInfo
{
    public:
	GameInfo();
	~GameInfo();
	vector<int>* cards_Played;
    vector<int>* cards_Picked;
	vector<int>* player_Hand[5];
	int player_num;
    int player_on_turn;
    int player_last_play;
    void pick(int card_id);
    bool is_legal();
    int is_win();
    void play();
    void pass();
};
vector<int>* randGen();

#endif