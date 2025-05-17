#include "mode.h"

void game(Graphic graphic,int &score, Levels le)
{
    SDL_Texture* background = graphic.loadTexture("image\\background\\purple.png");
    if (!background) return ;

    Mix_Chunk *gsound_eat = graphic.loadSound("audio\\res_audio_sound_eating.wav");
    Mix_Chunk *gsound_dead = graphic.loadSound("audio\\res_audio_sound_lose.wav");

    int x = START_LOCATION_SNAKE_X;
    int y = START_LOCATION_SNAKE_Y;

    Snake snake (x,y);
    Fruit fruit;

    fruit.tao_qua(snake);

    bool running = true;
    bool gameover = true;

    SDL_Event event;
    Direction dir = RIGHT;
    if (le == EASY)
    {
        while (running) {
            // Kiểm tra sự kiện thoát chương trình
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
                else if (event.type == SDL_KEYDOWN)
                {
                    snake.kt_huong(event,dir);
                }
            }

            //snake.AI(fruit,dir);
            // Cập nhật vị trí
            snake.cap_nhat_vi_tri(dir,x,y);


            // Nếu đi ra khỏi màn hình, quay lại từ đầu
            snake.xu_li_ra_khoi_man_hinh(x,y);
            //graphic.prepareScene(background);

            SDL_RenderClear(graphic.renderer);
            graphic.renderTexture(background,0,0);

            // Vẽ lưới
            ve_luoi(graphic.renderer);

            snake.xu_li_ran(fruit,x,y, gsound_eat,score);

            gameover = snake.kt_ran_cham_duoi(gsound_dead);

            running = gameover && running;

            fruit.ve_qua(graphic,"image\\Snake\\fruit.png");

            snake.ve_ran(graphic,"image\\Snake\\snake_green_head.png","image\\Snake\\body_green.png","image\\Snake\\last_tail_green.png","image\\Snake\\curve_green.png",dir);

            SDL_SetRenderDrawColor(graphic.renderer, 128, 128, 128, 160);
            SDL_Rect re {0,760,800,40};
            SDL_RenderFillRect(graphic.renderer,&re);

            updateScore(graphic,score, 300,760,30);

            graphic.presentScene();

            SDL_Delay(DELAY_TIME);
        }

    }
    else if (le == MEDIUM)
    {
        while (running) {
            // Kiểm tra sự kiện thoát chương trình
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
                else if (event.type == SDL_KEYDOWN)
                {
                    snake.kt_huong(event,dir);
                }
            }

            //snake.AI(fruit,dir);
            // Cập nhật vị trí
            snake.cap_nhat_vi_tri(dir,x,y);


            // Nếu đi ra khỏi màn hình, quay lại từ đầu
            //snake.xu_li_ra_khoi_man_hinh(x,y);

            //graphic.prepareScene(background);

            SDL_RenderClear(graphic.renderer);
            graphic.renderTexture(background,0,0);

            // Vẽ lưới
            ve_luoi(graphic.renderer);

            snake.xu_li_ran(fruit,x,y, gsound_eat,score);

            gameover = snake.kt_ran_cham_duoi(gsound_dead) && !snake.kt_ran_cham_tuong();

            running = gameover && running;

            fruit.ve_qua(graphic,"image\\Snake\\fruit.png");

            snake.ve_ran(graphic,"image\\Snake\\snake_green_head.png","image\\Snake\\body_green.png","image\\Snake\\last_tail_green.png","image\\Snake\\curve_green.png",dir);

            SDL_SetRenderDrawColor(graphic.renderer, 128, 128, 128, 160);
            SDL_Rect re {0,760,800,40};
            SDL_RenderFillRect(graphic.renderer,&re);

            updateScore(graphic,score, 300,760,30);

            graphic.presentScene();

            SDL_Delay(DELAY_TIME);
        }
    }
    else if (le == HARD)
    {
        Uint32 startTime = SDL_GetTicks();
        int countdownSeconds = 30;

        int a =5;
        int b = 10;
        Snake snake_AI (a,b);
        int score_AI =0;
        bool endd = false;
        bool gameover_AI = true;
        Direction dir_AI;


        while (running) {
            // Kiểm tra sự kiện thoát chương trình
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) running = false;
                else if (event.type == SDL_KEYDOWN)
                {
                    snake.kt_huong(event,dir);
                }
            }

            snake_AI.AI(fruit,dir_AI);
            // Cập nhật vị trí
            snake.cap_nhat_vi_tri(dir,x,y);
            snake_AI.cap_nhat_vi_tri(dir_AI,a,b);


            // Nếu đi ra khỏi màn hình, quay lại từ đầu
            snake.xu_li_ra_khoi_man_hinh(x,y);
            snake_AI.xu_li_ra_khoi_man_hinh(a,b);

            //graphic.prepareScene(background);

            SDL_RenderClear(graphic.renderer);
            graphic.renderTexture(background,0,0);

            // Vẽ lưới
            ve_luoi(graphic.renderer);

            snake_AI.xu_li_ran(fruit,a,b,gsound_eat,score_AI);

            snake.xu_li_ran_AI(fruit,x,y, gsound_eat,score,snake_AI);

            gameover = snake.kt_ran_cham_duoi(gsound_dead);
            gameover_AI = snake_AI.kt_ran_cham_duoi(gsound_dead);

            running = gameover && running && !endd && gameover_AI;

            fruit.ve_qua(graphic,"image\\Snake\\fruit.png");

            snake_AI.ve_ran(graphic,"image\\Snake\\snake_red_head.png","image\\Snake\\body-red.png","image\\Snake\\last_tail_red.png","image\\Snake\\curve_red.png",dir_AI);
            snake.ve_ran(graphic,"image\\Snake\\snake_green_head.png","image\\Snake\\body_green.png","image\\Snake\\last_tail_green.png","image\\Snake\\curve_green.png",dir);


            SDL_SetRenderDrawColor(graphic.renderer, 128, 128, 128, 160);
            SDL_Rect re {0,760,800,40};
            SDL_RenderFillRect(graphic.renderer,&re);

            updateScore(graphic,score, 50,760,30);
            updateScore_AI(graphic,score_AI,550,760,30);

            renderCountdownTimer(graphic,startTime, countdownSeconds, 350,760,30,endd);

            graphic.presentScene();

            SDL_Delay(DELAY_TIME);
        }
        SDL_DestroyTexture(background);
        if ( gameover_AI == false)
        {
            background = graphic.loadTexture("image\\background\\You_win.png");
        }
        else if (gameover == false)
        {
            background = graphic.loadTexture("image\\background\\AI_win.png");
        }
        else if(score > score_AI)
        {
            background = graphic.loadTexture("image\\background\\You_win.png");
        }
        else if (score < score_AI)
        {
            background = graphic.loadTexture("image\\background\\AI_win.png");
        }
        else
        {
            background = graphic.loadTexture("image\\background\\tie.png");
        }
        graphic.prepareScene(background);
        updateScore(graphic,score, 100,70,70);
        updateScore_AI (graphic,score_AI,100,140,70);
        graphic.presentScene();
        waitUntilKeyPressed();
    }
    Mix_FreeChunk(gsound_eat);
    Mix_FreeChunk(gsound_dead);
    SDL_DestroyTexture(background);
    background = NULL;
}


void setting (Graphic graphic,VolumeSlider &slider, Levels &le)
{
    SDL_Texture *background = graphic.loadTexture ("image\\background\\setting.jpg");

    pair <char*, char*> sound_name= {"image\\Menu\\sound_button.png","image\\Menu\\un_sound_button.png"};
    char * path = sound_name.first;
    SDL_Texture *sound;
    SDL_Texture *levels_easy= graphic.loadTexture("image\\Menu\\easy.png");
    SDL_Texture *levels_medium = graphic.loadTexture ("image\\Menu\\medium.png");
    SDL_Texture *levels_hard = graphic.loadTexture ("image\\Menu\\hard.png");
    Button sound_button (70,700,50,50);
    Button easy {250,200,310,79};
    Button medium {250,400,310,79};
    Button hard {250,600,310,79};
    Button x {678,37,98,65};

    bool quit = false;
    SDL_Event e;
    int m_x,m_y;
    while (!quit) {
        graphic.prepareScene(background);

        SDL_GetMouseState(&m_x, &m_y);

        if (slider.getVolume() >0) path = sound_name.first;
        else path = sound_name.second;

        sound = graphic.loadTexture(path);
        graphic.renderTexture(sound,sound_button.rect.x,sound_button.rect.y);

        SDL_DestroyTexture(sound);

        sound = NULL;

        graphic.renderTexture(levels_easy, 250,200);
        graphic.renderTexture(levels_medium, 250, 400);
        graphic.renderTexture(levels_hard, 250,600);


        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (sound_button.is_inside(e.button.x,e.button.y))
                {
                    if (path == sound_name.first)
                    {
                        slider.setVolume(0);
                    }
                    else if (path == sound_name.second)
                    {
                        slider.setVolume(64);
                    }
                }
                else if (easy.is_inside(m_x,m_y))
                {
                    le = EASY;
                    return;
                }
                else if (medium.is_inside (m_x,m_y))
                {
                    le = MEDIUM;
                    return;
                }
                else if (hard.is_inside(m_x,m_y))
                {
                    le = HARD;
                    return;
                }
                else if (x.is_inside(m_x,m_y))
                {
                    return;
                }
            }
            slider.handleEvent(e);
        }

        slider.render(graphic.renderer);

        graphic.presentScene();
    }

    SDL_DestroyTexture(background);
    background = NULL;

    SDL_DestroyTexture(levels_easy);
    levels_easy = NULL;

    SDL_DestroyTexture(levels_medium);
    levels_medium = NULL;

    SDL_DestroyTexture(levels_hard);
    levels_hard = NULL;
}

void renderCountdownTimer(Graphic graphic, Uint32 sT, int countdownSeconds, int x, int y, int s, bool &game_over) {
    Uint32 currentTime = SDL_GetTicks();
    int elapsedSeconds = (currentTime - sT)/1000;
    int remainingSeconds = countdownSeconds - elapsedSeconds;
    if (remainingSeconds < 0) remainingSeconds = 0;
    if (remainingSeconds == 0) game_over = true;

    TTF_Font* font = graphic.loadFont("font\\howdy_koala\\Howdy Koala.ttf", s);
    SDL_Color color = {255, 255, 255, 0};

    char timeleft[64];
    sprintf(timeleft, " TIME: %d", remainingSeconds);

    SDL_Texture* helloText = graphic.renderText(timeleft, font, color);
    graphic.renderTexture(helloText, x, y);
    SDL_DestroyTexture(helloText);
    helloText = NULL;
    TTF_CloseFont(font);
}

