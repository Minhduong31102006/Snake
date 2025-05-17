#ifndef DEF_H_INCLUDED
#define DEF_H_INCLUDED

#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <string>
#include <utility>

#define MAX 100

using namespace std;

//screen
const int SNAKE_LENGTH_START = 7;
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

const int MONITOR_WIDTH = 800;
const int MONITOR_HEIGHT = 900;
const int CELL_SIZE = 40;
const int DELAY_TIME = 100;

// Số lượng rắn
extern int SL;

//snake
const int START_LOCATION_SNAKE_X = 5;
const int START_LOCATION_SNAKE_Y = 5;

// nút bấm

enum Direction{
        UP,
        DOWN,
        LEFT,
        RIGHT
};

enum Mode
{
    PLAY,
    SETTING,
    SCORE,
    EXIT
};
enum Levels
{
    EASY,
    MEDIUM,
    HARD
};


#endif // DEF_H_INCLUDED
