#ifndef is_legal_H
#define is_legal_H
#include<vector>
#include<algorithm>
using namespace std;
bool is_legal(vector<int>* cards_Picked,vector<int>* cards_Played);//输入当前卡牌和上家的卡牌，返回是否合法
int trans(int id);
bool card_cmp(int a,int b);
#endif