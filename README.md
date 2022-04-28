# PokerGame
# PokerGame

2022.4.28 20:40

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

