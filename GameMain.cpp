#include"GameMain.hpp"
/*
    void GameMain::main_process()
    {
        do
        {
            if(if_Command)
            {
                if_Command=0;
                switch(Command_ID)
                {
                    case 0: this->player_add();break;
                    case 1: this->player_prepare();break;
                    case 2: if(GameStart)this->card_deliver();break;
                    case 3: if(GameStart)this->play();break;
                    case 4: if(GameStart)this->pass();break;
                    default: break;
                }
            }
        } while(!(this->GameEnd=this->is_win()));
        return;
    }*/
    void GameMain::player_add()
    {
        this->cur_player_num++;
        return;
    }
    void GameMain::player_prepare()
    {
        if(this->U_ID>this->cur_player_num)return;
        this->player_ready[this->U_ID]=1;
        int i;
        for(i=0;i<=this->player_num;i++)if(!this->player_ready[i])break;
        if(i==this->player_num)this->GameStart=1;
        return;
    }
    GameMain::GameMain():GameBasic()
    {
        this->GameStart=0;
        this->GameEnd=0;
        this->if_Command=0;
        this->cur_player_num=0;
        for(int i=0;i<this->player_num;i++)this->player_ready[i]=0;
    }
    GameMain::~GameMain()
    {
    }