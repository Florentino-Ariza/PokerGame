#include"GameBasic.hpp"
vector<int>* randGen()
{
    vector<int>* res = new vector<int>;
    for(int i=0; i<54; i++)
    {
        res->push_back(rand()%13+1);
    }
    sort(res->begin(),res->end());
    return res;
}
GameBasic::GameBasic()
{
    this->cards_Played = new vector<int>;
    this->cards_Picked = new vector<int>;
    this->player_num = 4;//默认
    for(int i=0;i<player_num;i++) this->player_Hand[i] = randGen();
}
GameBasic::~GameBasic()
{
}
int GameBasic::is_win()
{
    for(int i=0;i<this->player_num;i++)
    {
        if(!this->player_Hand[i]->size())
        {
            return i+1;
        }
    }
    return 0;
}
void GameBasic::play()
{
        vector<int>::iterator it_p,it_h;
        vector<int> tmp;
        this->cards_Played->swap(tmp);
        sort(this->cards_Picked->begin(),this->cards_Picked->end(),card_cmp);
        it_p = this->cards_Picked->begin();
        it_h = this->player_Hand[this->player_on_turn]->begin();
        for(;it_p!=cards_Picked->end();)
        {
            for(;it_h != this->player_Hand[this->player_on_turn]->end();)
            {
                if(*it_h==*it_p)
                {it_h = this->player_Hand[this->player_on_turn]->erase(it_h);
                break;}
                else ++it_h;
            }
            this->cards_Played->push_back(*it_p);
            it_p = this->cards_Picked->erase(it_p);
        }
        this->player_on_turn=(this->player_on_turn+1)%this->player_num;
        this->player_last_play = this->player_on_turn;
        return;
}
void GameBasic::pass()
{
    this->player_on_turn=(this->player_on_turn+1)%this->player_num;
    if(this->player_on_turn==this->player_last_play)
    {
        vector<int> tmp;
        this->cards_Played->swap(tmp);
    } 
    return;
}

void GameBasic::card_deliver()
{
    for(int i=0;i<this->player_num;i++)
    {
        vector<int> tmp;
        this->player_Hand[i]->swap(tmp);
    }   
    int arr[53];
    for(int i=0;i<52;i++)arr[i]=i+3;
    for(int i=0;i<52;i++)
    {
        int j=rand()%52;
        int tmp=arr[j];
        arr[j]=arr[i];
        arr[i]=tmp;
    }
    for(int i=0;i<this->player_num;i++) 
    {
        for(int j=0;j<13;j++)this->player_Hand[i]->push_back(arr[i*13+j]);
        sort(this->player_Hand[i]->begin(),this->player_Hand[i]->end(),card_cmp);
    }
    this->player_on_turn = rand()%4 +1;
    this->player_last_play = this->player_on_turn;
    return;
}