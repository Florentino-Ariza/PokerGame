#include"is_legal.hpp"

bool is_legal(vector<int>* cards_Picked,vector<int>* cards_Played)
{
    int num=cards_Picked->size();
    if(!num)return 0;
    int pick_heap[15];
    int play_heap[15];
    for(int i=0;i<13;i++)
    {
        pick_heap[i]=0;
        play_heap[i]=0;
    }
    vector<int>::iterator it_p,it_h;
    for(it_h = cards_Picked->begin();it_h != cards_Picked->end();it_h++)
    {
        
        pick_heap[trans(*it_h)]++;
    }
    for(it_p = cards_Played->begin();it_p != cards_Played->end();it_p++)
    {
        play_heap[trans(*it_p)]++;
    }
    int max_card_pick=0;
    int min_num_pick=4;
    int max_num_pick=0;
    int max_card_play=0;
    int max_num_play=0;
    int min_num_play=4;
    for(int i=0;i<13;i++)
    {
        if(pick_heap[i]>max_num_pick){max_num_pick=pick_heap[i];max_card_pick=i;}
        if(pick_heap[i]<min_num_pick&&pick_heap[i])min_num_pick=pick_heap[i];
        if(play_heap[i]>max_num_play){max_num_play=play_heap[i];max_card_play=i;}
        if(play_heap[i]<min_num_play&&play_heap[i])min_num_play=play_heap[i];
    }
    if(cards_Played->size())
    {
        if(max_num_pick==4&&num==4&&(max_num_play<4||max_card_play<max_card_pick))return true;
        if(max_num_pick!=max_num_play||max_card_pick<=max_card_play)return false;
        if(num!=cards_Played->size()&&max_num_pick!=4&&num!=4)return false;
    }
    int i;
        if(max_num_pick==1&&min_num_pick==1)
        {
            for(i=0;i<num;i++)if(pick_heap[i+max_card_pick]!=1)return false;
            if(num==2)return false;
            return true;
        }
        if(max_num_pick==2&&min_num_pick==2&&!(num%2))
        {
            for(i=0;i<num/2;i++)if(pick_heap[i+max_card_pick]!=2)return false;
            return true;
        }
        if(max_num_pick==3&&(!(num%5)||!(num%3)))
        {
            if(!(num%3)&&min_num_pick==3)
            {
                for(i=0;i<num/3;i++)if(pick_heap[i+max_card_pick]!=3)return false;
                return true;
            }
            else if(!(num%5))
            {
                for(i=0;i<num/5;i++)if(pick_heap[i+max_card_pick]!=3)return false;
                return true;
            }
        }
    return false;
}

int trans(int id)
{
    return (id-3)%13;
}
