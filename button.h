#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "def.h"

struct Button
{
    SDL_Rect rect;

    Button (int x, int y,int w, int h);
    void get_rect (int x, int y,int w, int h);
    bool is_inside (int x, int y);
};


class VolumeSlider {
private:
    int x, y, width, height;
    int volume;

public:

    VolumeSlider(int x, int y, int w, int h, int initial = 64);

    void render(SDL_Renderer* renderer);

    void handleEvent(SDL_Event& e);

    int getVolume() const;
    void setVolume(int v);
};

#endif // BUTTON_H_INCLUDED
