#ifndef DemoDisplay_H
#define DemoDisplay_H
#include<iostream>
#include<string.h>
#include"GameBasic.hpp"
class DemoDisplay : public GameInfo
{
    public:
    char* int_to_char(int card_id); 
    int show();
    void operate();
};
#endif