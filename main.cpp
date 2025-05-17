#include <iostream>
#include <fstream>
#include "def.h"
#include "graphic.h"
#include "button.h"
#include "snake.h"
#include "mode.h"

using namespace std;

int main(int argc, char* argv[])
{
    srand(time(NULL));

    Graphic graphic;
    graphic.init("Snake");

    Mix_Music *gMusic = graphic.loadMusic("audio\\nhạc_nền.mp3");
    graphic.play(gMusic);

    Mode mo;
    Levels le = EASY;

    int score = 0;
    int max_score;

    ifstream in;
    ofstream out;
    in.open("input.txt");
    in >> max_score;
    in.close();
    out.open("input.txt");

    VolumeSlider slider(130, 710, 300, 30);

    bool quit = false;
    while (!quit)
    {
        Menu(graphic,mo);
        SL = 7;

        if (mo == PLAY)
        {
            score = 0;
            game(graphic,score, le);
            if (le!= HARD)
            {
                Gameover(graphic,score);
            }
            max_score = max (max_score,score);

        }
        else if (mo == SETTING) setting(graphic, slider, le);
        else if (mo == SCORE) show_score(graphic, max_score);
        else if (mo == EXIT) quit = true;
    }
    out << max_score;

    out.close();
    Mix_FreeMusic(gMusic);
    graphic.quit();

    return 0;
}
