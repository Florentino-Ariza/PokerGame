#ifndef GameBasic_H
#define GameBasic_H
#include<vector>
#include<algorithm>
#include"is_legal.hpp"
#include<Windows.h>
using namespace std;
class GameBasic
{
    public:
	GameBasic();
	~GameBasic();
	vector<int>* cards_Played;
	vector<int>* player_Hand[5];
    vector<int>* cards_Picked;
	int player_num;
    int player_on_turn;
    int player_last_play;
    int is_win();
    void play();
    void pass();
    void card_deliver();
    int is_legal(vector<int>* cards_Picked,vector<int>* cards_Played);
};
vector<int>* randGen();

#endif