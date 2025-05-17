#include "button.h"

Button :: Button (int x, int y,int w, int h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

void Button :: get_rect (int x, int y,int w, int h)
{
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
}

bool Button :: is_inside (int x, int y)
{
    if (x >= rect.x && x <= rect.x+rect.w && y >= rect.y && y <= rect.y+ rect.h)
        return true;
    return false;
}

// thanh am luong
VolumeSlider::VolumeSlider (int x, int y, int w, int h, int i): x(x), y(y), width(w), height(h),volume(i)
{
    Mix_VolumeMusic(volume);
}

void VolumeSlider :: render(SDL_Renderer* renderer) {

    SDL_Rect background = { x, y, width, height };
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_RenderFillRect(renderer, &background);

    SDL_Rect fill_ = { x, y, volume * width / 128, height };
    SDL_SetRenderDrawColor(renderer, 50, 200, 50, 255);
    SDL_RenderFillRect(renderer, &fill_);
}

void VolumeSlider :: handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN){
        int mx = e.button.x;
        int my = e.button.y;
        if (mx >= x && mx <= x + width && my >= y && my <= y + height) {
            volume = (mx - x) * 128 / width;
            if (volume < 0) volume = 0;
            if (volume > 128) volume = 128;
            Mix_VolumeMusic(volume);
        }
    }
}

int VolumeSlider :: getVolume()const{ return volume; }

void VolumeSlider :: setVolume(int v)
{
    volume = (v < 0) ? 0 : (v > 128 ? 128 : v);
    Mix_VolumeMusic(volume);
}
