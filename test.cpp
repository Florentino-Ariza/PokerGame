#include"DemoDisplay.hpp"

int main()
{
    DemoDisplay game;
    while(!game.show())game.operate();
    return 0;
}