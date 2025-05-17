#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "graphic.h"
#include "def.h"
struct Snake;
struct Fruit;

extern int SL;

struct Snake
{
    vector <pair<int,int>> v;

    Snake (int x0, int y0);

    void cap_nhat_vi_tri(Direction dir, int &x, int &y);
    void xu_li_ra_khoi_man_hinh (int &x, int &y);
    bool xu_li_ran_cham_tuong (int x, int y);
    void kt_huong (SDL_Event event, Direction &dir);

    void ve_ran(Graphic graphic ,const char *path_head, const char *path_body, const char *path_tail, const char *path_corner, Direction dir);
    void xu_li_ran(Fruit &fruit, int x0, int y0, Mix_Chunk *gsound, int &score);
    bool kt_ran_cham_duoi(Mix_Chunk *gsound);
    bool kt_ran_cham_tuong();
    bool is_safe (int x, int y);
    void AI (Fruit fruit, Direction &Dir);

    void xu_li_ran_AI(Fruit &fruit, int x0, int y0, Mix_Chunk *gsound,int &score, Snake AI);

};

struct Fruit
{
    pair <int,int> qua;

    void tao_qua (const Snake &snake);
    void tao_qua (const Snake &snake, const Snake &AI);
    bool kt_ran_de_qua (const Snake &snake);
    void ve_qua (Graphic graphic,const char *path);
    bool kt_ran_an_qua(int x0, int y0, Mix_Chunk *gsound);
};

#endif // SNAKE_H_INCLUDED
