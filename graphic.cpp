#include "graphic.h"

void Graphic :: logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphic :: init(const char* WINDOW_TITLE)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                    Mix_GetError() );
    }

    if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                             TTF_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    //SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Graphic :: prepareScene(SDL_Texture * background)
{
    SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
}

void Graphic :: presentScene()
{
    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphic :: loadTexture(const char *filename)
{
    //SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                   //"Loading %s", filename);
    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
              SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void Graphic :: renderTexture(SDL_Texture *texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}


Mix_Music* Graphic :: loadMusic(const char* path)
{
    Mix_Music *gMusic = Mix_LoadMUS(path);
    if (gMusic == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
            "Could not load music! SDL_mixer Error: %s", Mix_GetError());
    }
    return gMusic;
}

void Graphic :: play(Mix_Music *gMusic)
{
    if (gMusic == nullptr) return;

    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic( gMusic, -1 );
    }
    else if( Mix_PausedMusic() == 1 ) {
        Mix_ResumeMusic();
    }
}

Mix_Chunk* Graphic :: loadSound(const char* path) {
    Mix_Chunk* gChunk = Mix_LoadWAV(path);
    if (gChunk == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
           "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
    }
    return gChunk;
}
void Graphic :: play(Mix_Chunk* gChunk) {
    if (gChunk != nullptr) {
        Mix_PlayChannel( -1, gChunk, 0 );
    }
}

TTF_Font* Graphic :: loadFont(const char* path, int size_)
{
    TTF_Font* gFont = TTF_OpenFont( path, size_ );
    if (gFont == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
                       "Load font %s", TTF_GetError());
    }
}

SDL_Texture* Graphic :: renderText(const char* text,TTF_Font* font, SDL_Color textColor)
{
    SDL_Surface* textSurface =
            TTF_RenderText_Solid( font, text, textColor );
    if( textSurface == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
                       "Render text surface %s", TTF_GetError());
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if( texture == nullptr ) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                       SDL_LOG_PRIORITY_ERROR,
                       "Create texture from text %s", SDL_GetError());
    }
    SDL_FreeSurface( textSurface );
    textSurface = NULL;
    return texture;
}


void Graphic :: quit()
{
    IMG_Quit();
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ve_luoi (SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    for (int i = 0; i <= SCREEN_WIDTH; i += CELL_SIZE)
    {
        SDL_RenderDrawLine(renderer, i, 0, i, SCREEN_HEIGHT);
    }
    for (int i = 0; i <= SCREEN_HEIGHT; i += CELL_SIZE)
    {
        SDL_RenderDrawLine(renderer, 0, i, SCREEN_WIDTH, i);
    }
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT || e.type == SDL_MOUSEBUTTONDOWN) )
            return;
        SDL_Delay(100);
    }
}

void Menu(Graphic graphic, Mode &mo)
{
    SDL_ShowCursor(0);

    SDL_Texture* background = graphic.loadTexture("image\\Menu\\Menu_nature.png");

    Button Play (190,345,390,55);
    Button Setting (250,445,295,55);
    Button High_score (205,540,380,50);
    Button Exit (330,635,135,50);

    SDL_Texture *Play_button;

    SDL_Event event;

    bool running = true;

    int m_x, m_y;

    SDL_Texture *targetterTexture = graphic.loadTexture("image\\Snake\\fruit.png");
    while (running) {
        graphic.prepareScene(background);

        SDL_GetMouseState(&m_x, &m_y);
        if (Play.is_inside(m_x,m_y))
        {
            Play_button = graphic.loadTexture("image\\background\\button_start_red.png");
            graphic.renderTexture(Play_button, 190, 345);
            SDL_DestroyTexture(Play_button);
            Play_button = NULL;
        }
        else if (Setting.is_inside(m_x,m_y))
        {
            Play_button = graphic.loadTexture("image\\background\\button_setting_red.png");
            graphic.renderTexture(Play_button, 250, 443);
            SDL_DestroyTexture(Play_button);
            Play_button = NULL;
        }
        else if (High_score.is_inside(m_x,m_y))
        {
            Play_button = graphic.loadTexture("image\\background\\button_high score_red.png");
            graphic.renderTexture(Play_button, 205, 538);
            SDL_DestroyTexture(Play_button);
            Play_button = NULL;
        }
        else if (Exit.is_inside(m_x,m_y))
        {
            Play_button = graphic.loadTexture("image\\background\\button_exit_red.png");
            graphic.renderTexture(Play_button, 332, 634);
            SDL_DestroyTexture(Play_button);
            Play_button = NULL;
        }
        graphic.renderTexture(targetterTexture, m_x, m_y);

        while (SDL_PollEvent(&event))
        {
            switch (event.type) {
                case SDL_QUIT:
                     exit(0);
                     break;
                case SDL_MOUSEBUTTONDOWN:
                    if (Play.is_inside(m_x,m_y))
                    {
                        mo = PLAY;
                        running = false;
                        break;
                    }
                    else if (Setting.is_inside(m_x,m_y))
                    {
                        mo = SETTING;
                        running = false;
                        break;
                    }
                    else if (High_score.is_inside(m_x,m_y))
                    {
                        mo = SCORE;
                        running = false;
                        break;
                    }
                    else if (Exit.is_inside(m_x,m_y))
                    {
                        mo = EXIT;
                        running = false;
                        break;
                    }
             }
        }

        graphic.presentScene();
    }
    SDL_DestroyTexture(targetterTexture);
    targetterTexture = NULL;
    SDL_DestroyTexture( background );
    background = NULL;
    SDL_ShowCursor(1);
}

void Gameover (Graphic graphic, int score)
{
    SDL_ShowCursor(0);
    SDL_Texture* game_over = graphic.loadTexture ("image\\background\\gameover_2.jpg");

    Button button_menu {150,600,150,73};
    Button button_exit {500,600,150,73};

    SDL_Texture *Menu_button;
    SDL_Texture *Exit_button;

    SDL_Event event;

    bool running = true;

    int m_x, m_y;

    SDL_Texture *targetterTexture = graphic.loadTexture("image\\Snake\\fruit.png");
    while (running)
    {
        graphic.prepareScene(game_over);
        updateScore(graphic,score,200,500, 50);
        SDL_GetMouseState(&m_x, &m_y);
        if (button_menu.is_inside(m_x,m_y))
        {
            Menu_button = graphic.loadTexture("image\\background\\button_menu_red.png");
            graphic.renderTexture(Menu_button, 150, 600);
            SDL_DestroyTexture(Menu_button);
            Menu_button = NULL;
        }
        else
        {
            Menu_button = graphic.loadTexture("image\\background\\button_menu_green.png");
            graphic.renderTexture(Menu_button, 150, 600);
            SDL_DestroyTexture(Menu_button);
            Menu_button = NULL;
        }
        if (button_exit.is_inside(m_x,m_y))
        {
            Exit_button = graphic.loadTexture("image\\background\\button_exit_red_game_over.png");
            graphic.renderTexture(Exit_button, 500, 600);
            SDL_DestroyTexture(Exit_button);
            Exit_button = NULL;
        }
        else{
            Exit_button = graphic.loadTexture("image\\background\\button_exit_green.png");
            graphic.renderTexture(Exit_button, 500, 600);
            SDL_DestroyTexture(Exit_button);
            Exit_button = NULL;
        }
        graphic.renderTexture(targetterTexture, m_x, m_y);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (button_menu.is_inside(m_x,m_y))
                    return;
                if (button_exit.is_inside(m_x,m_y))
                {
                    exit(0);
                    break;
                }

            }
        }

        graphic.presentScene();
    }

    SDL_DestroyTexture(game_over);
    game_over = NULL;
    SDL_DestroyTexture(targetterTexture);
    targetterTexture = NULL;
    SDL_ShowCursor(1);
}

void show_score (Graphic graphic, int score)
{
    SDL_ShowCursor(0);
    SDL_Texture *background = graphic.loadTexture("image\\background\\max_score.jpg");
    Button button_menu {330,500,150,73};

    SDL_Texture *Menu_button;

    SDL_Event event;

    bool running = true;

    int m_x, m_y;

    SDL_Texture *targetterTexture = graphic.loadTexture("image\\Snake\\fruit.png");
    while (running)
    {
        graphic.prepareScene(background);
        updateScore(graphic,score,100,350, 70);
        SDL_GetMouseState(&m_x, &m_y);
        if (button_menu.is_inside(m_x,m_y))
        {
            Menu_button = graphic.loadTexture("image\\background\\button_menu_red.png");
            graphic.renderTexture(Menu_button, 330, 500);
            SDL_DestroyTexture(Menu_button);
            Menu_button = NULL;
        }
        else
        {
            Menu_button = graphic.loadTexture("image\\background\\button_menu_green.png");
            graphic.renderTexture(Menu_button, 330, 500);
            SDL_DestroyTexture(Menu_button);
            Menu_button = NULL;
        }
        graphic.renderTexture(targetterTexture, m_x, m_y);
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                exit(0);
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (button_menu.is_inside(m_x,m_y))
                    return;
            }
        }

        graphic.presentScene();
    }

    SDL_DestroyTexture(background);
    background = NULL;
    SDL_DestroyTexture(targetterTexture);
    targetterTexture = NULL;

    SDL_ShowCursor(1);
}

void updateScore (Graphic graphic, int score, int x, int y, int s)
{
    TTF_Font* font = graphic.loadFont("font\\howdy_koala\\Howdy Koala.ttf", s);
    SDL_Color color = {255, 255, 255, 0};

    char scoreText[64];
    sprintf(scoreText, "YOUR SCORE: %d0", score);

    SDL_Texture* helloText = graphic.renderText(scoreText, font, color);
    graphic.renderTexture(helloText, x, y);
    SDL_DestroyTexture(helloText);
    helloText = NULL;
    TTF_CloseFont(font);
}
void updateScore_AI (Graphic graphic, int score, int x, int y, int s)
{
    TTF_Font* font = graphic.loadFont("font\\howdy_koala\\Howdy Koala.ttf", s);
    SDL_Color color = {255, 255, 255, 0};

    char scoreText[64];
    sprintf(scoreText, "AI SCORE: %d0", score);

    SDL_Texture* helloText = graphic.renderText(scoreText, font, color);
    graphic.renderTexture(helloText, x, y);
    SDL_DestroyTexture(helloText);
    helloText = NULL;
    TTF_CloseFont(font);
}
