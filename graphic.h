#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "def.h"
#include "button.h"


struct Graphic
{
    SDL_Window *window;
    SDL_Renderer *renderer;

    void logErrorAndExit(const char* msg, const char* error);

    void init(const char* WINDOW_TITLE);

    void prepareScene(SDL_Texture * background);
    void presentScene();

    SDL_Texture* loadTexture(const char *filename);
    void renderTexture(SDL_Texture *texture, int x, int y);

    Mix_Music* loadMusic(const char* path);
    void play(Mix_Music *gMusic);

    Mix_Chunk* loadSound(const char* path);
    void play(Mix_Chunk* gChunk);

    TTF_Font* loadFont(const char* path, int size);
    SDL_Texture* renderText(const char* text,TTF_Font* font, SDL_Color textColor);

    void quit();
};

void ve_luoi (SDL_Renderer *renderer);

void waitUntilKeyPressed();

void Menu(Graphic graphic,Mode &mo);

void Gameover (Graphic graphic, int score);

void updateScore (Graphic graphic, int score, int x, int y, int s);

void updateScore_AI (Graphic graphic, int score, int x, int y, int s);

void show_score (Graphic graphic, int score);
//void show_score (Graphic graphic, int score, int score_AI);
#endif // GRAPHIC_H_INCLUDED
