#include "GameMain.hpp"

class FileDisplay :GameMain
{
public:

	void FileDisplayRegister()
	{
		HSON::classRegister<FileDisplay>("FileDisplay");
		HSON::classItemRegister("FileDisplay", "vector<int>",
			HCON this, HCON & this->cards_Played);
        for(int i=0;i<player_num;i++)
        {
            HSON::classItemRegister("FileDisplay", "vector<int>",
			HCON this, HCON & this->player_Hand[i]);
        }
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->player_num);
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->cur_player_num);
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->GameStart);
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->GameEnd);
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->player_on_turn); 
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->player_last_play); 
        for(int i=0;i<player_num;i++)
        {
            HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->uid_list[i]);
        }
        for(int i=0;i<player_num;i++)
        {
            HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->player_ready[i]);
        }
	}
};



int main()
{
    HSON::Inithson();
    // 启用库之前需要初始化
    FileDisplay* tmp = new FileDisplay;
    tmp->FileDisplayRegister();
    // 一定要先注册一下， 一个类只要注册过一次就可以了
    HSON::saveobject("FileDisplay", "FILE_DISP", HVON tmp);
    // 保存到文件里面
    return 0;
}