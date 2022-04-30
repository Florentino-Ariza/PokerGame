# PokerGame

#### 2022.4.28 20:40

完成了游戏的底层逻辑

已实现的功能有：

底层逻辑模块：可以进行以下逻辑

```c++
void pick(int card_id);//将对应序号的牌加入pick表
bool is_legal();//当前pick表是否能合法打出
int is_win();//是否有玩家获胜（返回玩家编号或0）
void play();//将已经pick的牌打出
void pass();//跳过出牌
```

其中，`is_legal()` 暂时只判断单牌和双牌，且不考虑上家牌型

显示模块（后将由QT图形化代替）：读取结构，能够在黑框框里显示当前的结构数据

操作模块（后将由QT按钮触发替代）：键盘输入数字，执行对应操作



后续接口替换：

参考 `DemoDisplay`类，在 `GameBasic` 类上生成 `FileDisplay` 类，将 `show()`替换为文件读入读出的形式？

AI的接口暂未考虑



#### 2022 4.29 20:36

`GameMain` 内所有变量：

```c++
	//写的指令变量接口
	bool if_Command;//是否有指令的更新
    int Command_ID;//指令的类型：从1到5
	//1:添加玩家
	//2:玩家准备
	//3:发牌
	//4:出牌
	//5:PASS
    int U_ID;//发出信号的玩家ID：0，1，2，3
	vector<int>* cards_Picked;//如果是出牌指令，储存出牌牌型

	//显示模块读文件的接口
	bool GameStart;//游戏是否开始（即所有玩家准备）
    bool GameEnd;//游戏结束（有玩家打空手牌）
	int player_num; //合法玩家数量
	int cur_player_num; //当前玩家数量
    bool player_ready[5];//player_ready[i]:第i个玩家是否已经准备

	vector<int>* cards_Played; //上家出的牌型
	vector<int>* player_Hand[5]; //player_Hand[i]:指向第i个玩家的手牌的vector的指针
    int player_on_turn; //当前轮到的玩家ID
    int player_last_play; //上一个出牌的玩家（用于判断是否轮空一轮）

```



基本预期显示：

GameStart = 0：玩家添加与准备界面

1. 玩家头像数量由 `cur_player_num` 决定
2. `player_ready[i]=0` 的玩家有准备按钮
3. `player_ready[i]=1` 的玩家显示准备完成

GameStart = 1 && GameEnd = 0：正式游戏界面

1. pick牌合法时出现出牌按钮
1. 除已轮空一轮的情况，有PASS按钮

GameEnd =1 ：游戏结束界面，显示胜者



#### 2022 4.30 14:09

添加了变量 `uidlist[]`，是uid到玩家0，1，2，3的映射

完成了底层逻辑与文件写的对接，具体写格式见 FILE_DISP

注意：**写入文件的类变量** 与 **读操作的指令变量** 要区分，指令变量不写入文件。



