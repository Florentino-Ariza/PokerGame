#include "hson.hpp"

class FileDisplay
{
public:
	FileDisplay();
	~FileDisplay() {}
	vector<int>* cards_Played;
	vector<int>* player_1_Hand;
	vector<int>* player_2_Hand;
	vector<int>* player_3_Hand;
	vector<int>* player_4_Hand;
	int player_1_Uid;
	int player_2_Uid;
	int player_3_Uid;
	int player_4_Uid;
    int player_on_turn;
	void FileDisplayRegister()
	{
		HSON::classRegister<FileDisplay>("FileDisplay");
		HSON::classItemRegister("FileDisplay", "vector<int>",
			HCON this, HCON & this->cards_Played);
		HSON::classItemRegister("FileDisplay", "vector<int>",
			HCON this, HCON & this->player_1_Hand);
		HSON::classItemRegister("FileDisplay", "vector<int>",
			HCON this, HCON & this->player_2_Hand);
		HSON::classItemRegister("FileDisplay", "vector<int>",
			HCON this, HCON & this->player_3_Hand);
		HSON::classItemRegister("FileDisplay", "vector<int>",
			HCON this, HCON & this->player_4_Hand);
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->player_1_Uid);
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->player_2_Uid);
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->player_3_Uid);
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->player_4_Uid);
        HSON::classItemRegister("FileDisplay", "int", 
            HCON this, HCON &this->player_on_turn);
	}
};

vector<int>* randGen()
{
    vector<int>* res = new vector<int>;
    for(int i=0; i<10; i++)
    {
        res->push_back(rand()%10);
    }
    return res;
}

FileDisplay::FileDisplay()
{
    this->cards_Played = randGen();
    this->player_1_Hand = randGen();
    this->player_2_Hand = randGen();
    this->player_3_Hand = randGen();
    this->player_4_Hand = randGen();
    this->player_1_Uid = rand()%9;
    this->player_2_Uid = rand()%9;
    this->player_3_Uid = rand()%9;
    this->player_4_Uid = rand()%9;
    this->player_on_turn = rand()%4 +1;
}


int main()
{
    HSON::Inithson();
    // 启用库之前需要初始化
    FileDisplay* tmp = new FileDisplay;
    tmp->FileDisplayRegister();
    // 一定要先注册一下， 一个类只要注册过一次就可以了

    // HSON::saveobject("FileDisplay", "FILE_DISP", HVON tmp);
    // 保存到文件里面

    FileDisplay* ttmp =
    HSON::getobject<FileDisplay>("FileDisplay", "FILE_DISP");
    for(int i=0; i<10; i++)
    {
        cout << (*ttmp->player_1_Hand)[i] << " " ;
    }
    // 传回一个和存储时候一模一样的数据结构的指针

    return 0;
}