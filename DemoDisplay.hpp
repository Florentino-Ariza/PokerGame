#ifndef DemoDisplay_H
#define DemoDisplay_H
#include<iostream>
#include<string.h>
#include"GameMain.hpp"
class DemoDisplay : public GameMain
{
    public:
    char* int_to_char(int card_id); 
    void main_process();
    int show();
    void operate();
};
#endif