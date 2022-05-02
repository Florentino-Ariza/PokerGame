#include"GameMain.hpp"
void GameMain::main_process()
    {
        HSON::Inithson();
        FileDisplay* F =new FileDisplay;
        F->FileDisplayRegister();
        do
        {
            operate();//暂时用于指令传输，链接qt后删除
            if(if_Command)
            {
                if_Command=0;
                switch(Command_ID)
                {
                    case 1: this->player_add();break;
                    case 2: this->player_prepare();break;
                    case 3: if(this->GameStart)this->card_deliver();break;
                    case 4: if(this->GameStart)this->play();break;
                    case 5: if(this->GameStart)this->pass();break;
                    default: break;
                }
                this->File_Write(F);
            }
        } while(!(this->GameEnd=this->is_win()));
        return;
    }
    void GameMain::File_Write(FileDisplay* F)
    {
        for(int i=0;i<this->player_num;i++)
        {
            F->player_Hand[i]=this->player_Hand[i];
            F->uid_list[i]=this->uid_list[i];
            F->player_ready[i]=this->player_ready[i];
        }
        F->player_num=this->player_num;
        F->cur_player_num=this->cur_player_num;
        F->GameStart=this->GameStart;
        F->GameEnd=this->GameEnd;
        F->player_on_turn=this->player_on_turn;
        F->player_last_play=this->player_last_play;
        HSON::saveobject("FileDisplay", "FILE_DISP", HVON F);
        return;
    }
    void GameMain::operate()
    {
        int choice=0;
        cout<<"What's your command?"<<endl;
        if(!this->GameStart)cout<<"1.Add player;\n2.Player Prepare\n";
        else cout<<"3.Delievr\n4.Play\n5.Pass\n";
        cin>>this->Command_ID;
        vector<int> tmp;
        switch (Command_ID)
        {
        case 1:
        case 2:
            cout<<"UID:";
            cin>>this->U_ID;
            break;
        case 4:
            cout<<"Play Card:";
            int id;
            cin>>id;
            this->cards_Picked->swap(tmp);
            this->cards_Picked->push_back(id);
            break;
        default:
            break;
        }
        this->if_Command=1;
        return;
    }
    int GameMain::uid_mapping(int uid)
    {
        for(int i=0;i<this->cur_player_num;i++)if(uid==this->uid_list[i])return i;
        return -1;
    }
    void GameMain::player_add()
    {
        this->uid_list[this->cur_player_num++]=this->U_ID;
        return;
    }
    void GameMain::player_prepare()
    {
        int id=this->uid_mapping(this->U_ID);
        if(id==-1)return;
        this->player_ready[id]=1;
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
        for(int i=0;i<this->player_num;i++)this->uid_list[i]=rand()%10000;
    }
    GameMain::~GameMain()
    {
    }