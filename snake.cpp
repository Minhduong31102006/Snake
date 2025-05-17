#include "snake.h"

int SL = 7;

Snake :: Snake (int x0, int y0)
{
    v = vector<pair<int, int>> (MAX);
    for (int i = 0; i < SL; ++i) {
        v[i] = {x0--, y0};
    }
}

//ham xu li ran
void Snake :: cap_nhat_vi_tri(Direction dir, int &x, int &y)
{
    switch(dir)
        {
        case UP:
            {
                y--;
                return;
            }
        case DOWN:
            {
                y++;
                return;
            }
        case LEFT:
            {
                x--;
                return;
            }
        case RIGHT:
            {
                x++;
                return;
            }
        }
}

void Snake :: xu_li_ra_khoi_man_hinh (int &x, int &y)
{
    if (x >= SCREEN_WIDTH / CELL_SIZE)
    {
        x = 0;
        return;
    }

    else if (y >= SCREEN_HEIGHT / CELL_SIZE-1)
    {
        y = 0;
        return;
    }

    else if (x < 0)
    {
        x = SCREEN_WIDTH / CELL_SIZE - 1;
        return;
    }
    else if (y < 0)
    {
        y = SCREEN_HEIGHT / CELL_SIZE - 2;
        return;
    }
}

bool Snake :: xu_li_ran_cham_tuong (int x, int y)
{
    if (x == 0 || y == 0 || x == SCREEN_WIDTH/CELL_SIZE-1 || y == SCREEN_HEIGHT/ CELL_SIZE-2)
        return true;
    return false;
}

void Snake :: kt_huong (SDL_Event event, Direction &dir)
{
    if (event.key.keysym.sym == SDLK_LEFT && dir != RIGHT)
    {
        dir = LEFT;
    }
    else if (event.key.keysym.sym == SDLK_RIGHT && dir != LEFT)
    {
        dir = RIGHT;
    }
    else if (event.key.keysym.sym == SDLK_UP && dir != DOWN)
    {
        dir =UP;
    }
    else if (event.key.keysym.sym == SDLK_DOWN && dir != UP)
    {
        dir = DOWN;
    }
}

// ham hien thi ran
void Snake :: ve_ran(Graphic graphic ,const char *path_head, const char *path_body, const char *path_tail, const char *path_corner, Direction dir) {
    SDL_Texture *texture;

    for (int i = 0; i < SL; i++)
    {
        double angle = 0.0;
        SDL_Point center = {CELL_SIZE / 2, CELL_SIZE / 2}; // Tâm xoay
        SDL_Rect rect = { v[i].first * CELL_SIZE, v[i].second * CELL_SIZE, CELL_SIZE, CELL_SIZE };

        // Xử lý đầu rắn
        if (i == 0) {
            texture = graphic.loadTexture(path_head);
            switch (dir) {
                case RIGHT: angle = 0; break;
                case LEFT: angle = 180; break;
                case UP: angle = 270; break;
                case DOWN: angle = 90; break;
            }
        }
        // Xử lý đuôi rắn
        else if (i == SL - 1) {
            texture = graphic.loadTexture(path_tail);
            pair<int, int> beforeTail = v[i - 1];

            if (beforeTail.first < v[i].first)
            {
                if (dir == RIGHT && beforeTail.first == 0)
                {
                    angle = 0;
                }
                else angle = 180;
            }
            else if (beforeTail.first > v[i].first)
            {
                if (dir == LEFT && beforeTail.first == SCREEN_WIDTH/CELL_SIZE-1)
                {
                    angle = 180;
                }
                else angle = 0;
            }

            else if (beforeTail.second < v[i].second)
            {
                if (dir == DOWN && beforeTail.second == 0)
                {
                    angle = 90;
                }
                else angle = 270;
            }

            else if (beforeTail.second > v[i].second)
            {
                if (dir == UP && beforeTail.second == SCREEN_HEIGHT/CELL_SIZE-2)
                {
                    angle = 270;
                }
                else angle = 90;
            }
        }
        // Xử lý thân rắn
        else {
            pair<int, int> prev = v[i - 1]; // Vị trí trước đó
            pair<int, int> next = v[i + 1]; // Vị trí tiếp theo

            // Nếu là đoạn thân thẳng
            if (prev.first == next.first) { // Cùng cột => đi dọc
                texture = graphic.loadTexture(path_body);
                angle = 90;
            }
            else if (prev.second == next.second) { // Cùng hàng => đi ngang
                texture = graphic.loadTexture(path_body);
                angle = 0;
            }
            // Nếu là đoạn bo góc
            else {
                texture = graphic.loadTexture(path_corner);

                if ((prev.first < v[i].first && next.second < v[i].second) || (next.first < v[i].first && prev.second < v[i].second)) {
                    if ((prev.second == 0 && next.second == SCREEN_HEIGHT/CELL_SIZE -2)|| ( prev.second == SCREEN_HEIGHT/CELL_SIZE -2 && next.second == 0))
                    {
                        angle = 270;
                    }
                    else if ((prev.first == 0 && next.first == SCREEN_HEIGHT/CELL_SIZE -1) || (prev.first == SCREEN_HEIGHT/ CELL_SIZE-1 && next .first == 0))
                    {
                        angle = 90;
                    }
                    else angle = 0;
                }
                else if ((prev.first > v[i].first && next.second < v[i].second) || (next.first > v[i].first && prev.second < v[i].second)) {
                    if ((prev.second == 0 && next.second == SCREEN_HEIGHT/CELL_SIZE -2)|| ( prev.second == SCREEN_HEIGHT/CELL_SIZE -2 && next.second == 0))
                    {
                        angle = 180;
                    }
                    else if ((prev.first == 0 && next.first == SCREEN_HEIGHT/CELL_SIZE -1) || (prev.first == SCREEN_HEIGHT/ CELL_SIZE-1 && next .first == 0))
                    {
                        angle = 0;
                    }
                    else angle = 90;
                }
                else if ((prev.first < v[i].first && next.second > v[i].second) || (next.first < v[i].first && prev.second > v[i].second)) {
                    if ((prev.second == 0 && next.second == SCREEN_HEIGHT/CELL_SIZE -2)|| ( prev.second == SCREEN_HEIGHT/CELL_SIZE -2 && next.second == 0))
                    {
                        angle = 0;
                    }
                    else if ((prev.first == 0 && next.first == SCREEN_HEIGHT/CELL_SIZE -1) || (prev.first == SCREEN_HEIGHT/ CELL_SIZE-1 && next .first == 0))
                    {
                        angle = 180;
                    }
                    else angle = 270;
                }
                else if ((prev.first > v[i].first && next.second > v[i].second) || (next.first > v[i].first && prev.second > v[i].second)) {
                    if ((prev.second == 0 && next.second == SCREEN_HEIGHT/CELL_SIZE -2)|| ( prev.second == SCREEN_HEIGHT/CELL_SIZE -2 && next.second == 0))
                    {
                        angle = 90;
                    }
                    else if ((prev.first == 0 && next.first == SCREEN_HEIGHT/CELL_SIZE -1) || (prev.first == SCREEN_HEIGHT/ CELL_SIZE-1 && next .first == 0))
                    {
                        angle = 270;
                    }
                    else angle = 180;
                }
            }
        }

        SDL_RenderCopyEx(graphic.renderer, texture, NULL, &rect, angle, &center, SDL_FLIP_NONE);
        SDL_DestroyTexture(texture);
    }
}

void Snake :: xu_li_ran(Fruit &fruit, int x0, int y0, Mix_Chunk *gsound,int &score)
{
    if (!fruit.kt_ran_an_qua(v[0].first,v[0].second, gsound))
    {
        v.pop_back();
        SL--;
    }
    else
    {
        fruit.tao_qua(*this);
        score++;
    }

    v.insert(v.begin(),{x0,y0});
    SL++;
}

void Snake :: xu_li_ran_AI(Fruit &fruit, int x0, int y0, Mix_Chunk *gsound,int &score, Snake AI)
{
    if (!fruit.kt_ran_an_qua(v[0].first,v[0].second, gsound))
    {
        v.pop_back();
        SL--;
    }
    else
    {
        fruit.tao_qua(*this,AI);
        score++;
    }

    v.insert(v.begin(),{x0,y0});
    SL++;
}


bool Snake :: kt_ran_cham_duoi(Mix_Chunk *gsound)
{
    for (int i = 1 ;i < SL;i++)
    {
        if (v[0].first == v[i].first && v[0].second == v[i].second)
        {
            Mix_PlayChannel(-1,gsound, 0 );
            return false;
        }
    }
    return true;
}

bool Snake :: kt_ran_cham_tuong ()
{
    if (v[0].first == 0 || v[0].second == 0 || v[0].first == SCREEN_WIDTH/CELL_SIZE-1 || v[0].second == SCREEN_HEIGHT/ CELL_SIZE-2)
        return true;
    return false;
}

bool Snake :: is_safe (int x, int y)
{
    for (int i = 1 ;i < SL;i++)
    {
        if (x == v[i].first && y == v[i].second)
            return false;
    }
    return true;
}

void Snake :: AI (Fruit fruit, Direction &Dir)
{
    int x0 = fruit.qua.first;
    int y0 = fruit.qua.second;
    int x = v[0].first;
    int y = v[0].second;
    if ((x > x0 && Dir == RIGHT) && is_safe(x,y+1))
    {
        Dir = DOWN;
        return;
    }
    if ((x < x0 && Dir == LEFT) && is_safe(x,y-1))
    {
        Dir = UP;
        return;
    }
    if ((y > y0 && Dir == DOWN) && is_safe(x-1,y))
    {
        Dir = LEFT;
        return;
    }
    if ((y < y0 && Dir == UP) && is_safe(x+1,y))
    {
        Dir = RIGHT;
        return;
    }
    if (x > x0 && is_safe(x-1,y)) Dir = LEFT;
    else if (x < x0 && is_safe(x+1,y)) Dir = RIGHT;
    else if (y > y0 && is_safe(x,y-1)) Dir = UP;
    else if (y < y0 && is_safe(x,y+1)) Dir = DOWN;
    else
    {
        if (Dir == DOWN && !is_safe(x,y+1)) Dir = RIGHT;
        else if (Dir == UP && !is_safe(x,y-1)) Dir = LEFT;
        else if (Dir == LEFT && !is_safe(x-1,y)) Dir = DOWN;
        else if (Dir == RIGHT && !is_safe(x+1,y)) Dir = UP;
    }
}


// xư li qua

void Fruit :: tao_qua (const Snake &snake)
{
    do
    {
        qua.first = rand()%(SCREEN_WIDTH/CELL_SIZE-1);
        qua.second = rand()%(SCREEN_HEIGHT/CELL_SIZE-2);
    }while(this -> kt_ran_de_qua(snake));
}

void Fruit :: tao_qua (const Snake &snake, const Snake &AI)
{
    do
    {
        qua.first = rand()%(SCREEN_WIDTH/CELL_SIZE-1);
        qua.second = rand()%(SCREEN_HEIGHT/CELL_SIZE-2);
    }while(this -> kt_ran_de_qua(snake) && this-> kt_ran_de_qua(AI));
}

bool Fruit :: kt_ran_de_qua (const Snake &snake)
{
    for (int i=0 ;i< SL ;i++)
    {
        if (qua.first == snake.v[i].first && qua.second == snake.v[i].second)
        {
            return true;
        }
    }
    return false;
}
void Fruit :: ve_qua (Graphic graphic,const char *path)
{
    SDL_Texture *texture = graphic.loadTexture (path);
    //SDL_Rect rect = {qua.first*CELL_SIZE,qua.second*CELL_SIZE,CELL_SIZE,CELL_SIZE};
    graphic.renderTexture(texture,qua.first*CELL_SIZE, qua.second*CELL_SIZE);
    SDL_DestroyTexture(texture);
}

bool Fruit :: kt_ran_an_qua(int x0, int y0, Mix_Chunk *gsound)
{
    if (qua.first == x0 && qua.second == y0)
    {
        Mix_PlayChannel(-1,gsound, 0 );
        return true;
    }
    return false;
}

