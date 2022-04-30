#include"DemoDisplay.hpp"
int DemoDisplay::show()
    {
        system("cls");
        if(!this->GameStart)
        {
            cout<<"There are "<<this->cur_player_num<<" players"<<endl;
            return 0;
        }
        if(this->is_win()){
            cout<<"Player "<<this->is_win()<<" win !"<<endl;
            system("pause");
            return 1;
        }
        for(int i=0;i<this->player_num;i++)
        {
            cout<<"Player "<<i+1<<" card: ";
            for (vector<int>::iterator bg = this->player_Hand[i]->begin(); bg != this->player_Hand[i]->end(); bg++)
	        {
                cout<<*bg<<" ";
	        }
            cout<<endl;
            for (vector<int>::iterator bg = this->player_Hand[i]->begin(); bg != this->player_Hand[i]->end(); bg++)
	        {
		        //printf("%s",this->int_to_char(*bg));
	        }
        }
        cout<<"Now it's the Player "<<this->player_on_turn+1<<" turn!"<<endl;
        cout<<"The card on table: ";
        for (vector<int>::iterator bg = this->cards_Played->begin(); bg != this->cards_Played->end(); bg++)
	    {
            cout<<*bg<<" ";
		    //printf("%s",this->int_to_char(*bg));
	    }
        cout<<endl;
        return 0;
    }
char* DemoDisplay::int_to_char(int card_id)
{
    /*char* ch;
    strcpy(ch,"AA");
    cout<<ch;
    switch(card_id%13)
    {
        case 0 : strcpy(ch,"2 "); break;
        case 1 : strcpy(ch,"3 "); break;
        case 2 : strcpy(ch,"4 "); break;
        case 3 : strcpy(ch,"5 "); break;
        case 4 : strcpy(ch,"6 "); break;
        case 5 : strcpy(ch,"7 "); break;
        case 6 : strcpy(ch,"8 "); break;
        case 7 : strcpy(ch,"9 "); break;
        case 8 : strcpy(ch,"10 "); break;
        case 9 : strcpy(ch,"J "); break;
        case 10 : strcpy(ch,"Q "); break;
        case 11 : strcpy(ch,"K "); break;
        case 12 : strcpy(ch,"A "); break;
        default : strcpy(ch,"? "); break;
    }*/
    char* ch;
    strcpy(ch,"?");
    return ch;
} 
void DemoDisplay::operate()
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
    void DemoDisplay::main_process()
    {
        do
        {
            show();
            operate();
            if(this->if_Command)
            {
                this->if_Command=0;
                switch(this->Command_ID)
                {
                    case 1: this->player_add();break;
                    case 2: this->player_prepare();break;
                    case 3: if(this->GameStart)this->card_deliver();break;
                    case 4: if(this->GameStart)this->play();break;
                    case 5: if(this->GameStart)this->pass();break;
                    default: break;
                }
            }
        } while(!(this->GameEnd=this->is_win()));
        return;
    }
