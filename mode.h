#ifndef MODE_H_INCLUDED
#define MODE_H_INCLUDED

#include "graphic.h"
#include "def.h"
#include "snake.h"
#include "button.h"

void game(Graphic graphic, int &score, Levels le);

void setting (Graphic graphic, VolumeSlider &slider, Levels &le);

void renderCountdownTimer(Graphic graphic, Uint32 startTime, int countdownSeconds, int x, int y, int s, bool &game_over);
#endif // MODE_H_INCLUDED
