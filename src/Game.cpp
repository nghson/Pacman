#include "Game.h"

Game::Game()
{
    frame = 0;
    std::ifstream HighScoreIn("resources/HighScore.txt");
    if (!HighScoreIn.is_open())
    {
        printf("Unable to load high score file! Setting high score to 0\n");
        highScore = 0;
    }
    else
    {
        HighScoreIn >> highScore;
    }
}

bool Game::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow("PACMAN", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

				//Initialize SDL_image
				int imgFlags = IMG_INIT_PNG;
				if (!( IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() < 0)
                {
                    printf("SDL_ttf could not be initialized! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }

                //Initialize SDL_mixer
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not be initialized! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
			}
		}
	}

	return success;
}

bool Game::loadTexture()
{
	//Loading success flag
	bool success = true;

	//Load blank texture
	if (!blankTexture.loadFromFileBMP(renderer, "resources/Blank.bmp"))
    {
        printf("Failed to load blank texture!\n");
        success = false;
    }

    //Load start logo texture
    if (!startEndLogoTexture.loadFromFileBMP(renderer, "resources/StartLogo.bmp"))
    {
        printf("Failed to load start logo texture!\n");
        success = false;
    }

    //Load logo texture
    if (!logoTexture.loadFromFileBMP(renderer, "resources/Logo.bmp"))
    {
        printf("Failed to load logo texture!\n");
        success = false;
    }

    //Load life texture
    if (!lifeTexture.loadFromFileBMP(renderer, "resources/Life.bmp"))
    {
        printf("Failed to load life texture!\n");
        success = false;
    }

	//Load pacman texture
	if (!pacmanTexture.loadFromFileBMP(renderer, "resources/Pacman.bmp"))
	{
		printf("Failed to load pacman texture!\n");
		success = false;
	}
	else
    {
        pacmanSpriteClips[0][0] = {0, 0, 20, 20};
        pacmanSpriteClips[0][1] = {0, 0, 20, 20};
        pacmanSpriteClips[0][2] = {20, 0, 20, 20};
        pacmanSpriteClips[0][3] = {20, 0, 20, 20};
        pacmanSpriteClips[1][0] = {40, 0, 20, 20};
        pacmanSpriteClips[1][1] = {40, 0, 20, 20};
        pacmanSpriteClips[1][2] = {60, 0, 20, 20};
        pacmanSpriteClips[1][3] = {60, 0, 20, 20};
        pacmanSpriteClips[2][0] = {0, 20, 20, 20};
        pacmanSpriteClips[2][1] = {0, 20, 20, 20};
        pacmanSpriteClips[2][2] = {20, 20, 20, 20};
        pacmanSpriteClips[2][3] = {20, 20, 20, 20};
        pacmanSpriteClips[3][0] = {40, 20, 20, 20};
        pacmanSpriteClips[3][1] = {40, 20, 20, 20};
        pacmanSpriteClips[3][2] = {60, 20, 20, 20};
        pacmanSpriteClips[3][3] = {60, 20, 20, 20};
    }

    //Load dead pacman texture
    if (!deadPacmanTexture.loadFromFileBMP(renderer, "resources/DeadPacman.bmp"))
    {
        printf("Failed to load dead pacman texture!\n");
        success = false;
    }
    else
    {
        pacmanDeadSpriteClips[0] = {0, 0, 20, 20};
        pacmanDeadSpriteClips[1] = {20, 0, 20, 20};
        pacmanDeadSpriteClips[2] = {40, 0, 20, 20};
        pacmanDeadSpriteClips[3] = {60, 0, 20, 20};
        pacmanDeadSpriteClips[4] = {0, 20, 20, 20};
        pacmanDeadSpriteClips[5] = {20, 20, 20, 20};
        pacmanDeadSpriteClips[6] = {40, 20, 20, 20};
        pacmanDeadSpriteClips[7] = {60, 20, 20, 20};
    }

	//Load wall tile texture
	if (!wallTexture.loadFromFileBMP(renderer, "resources/Wall.bmp"))
	{
		printf("Failed to load wall tile texture!\n");
		success = false;
	}

    //Load space tile texture
    if (!spaceTexture.loadFromFileBMP(renderer, "resources/Space.bmp"))
    {
        printf("Failed to load space tile texture!\n");
        success = false;
    }

	//Load small yummy texture
	if (!smallYummyTexture.loadFromFileBMP(renderer, "resources/SmallYummy.bmp"))
    {
        printf("Failed to load small yummy texture!\n");
        success = false;
    }

    //Load big yummy texture
    if (!bigYummyTexture.loadFromFileBMP(renderer, "resources/BigYummy.bmp"))
    {
        printf("Failed to load big yummy texture!\n");
        success = false;
    }

    //Load blinky texture
    if (!blinkyTexture.loadFromFileBMP(renderer, "resources/Blinky.bmp"))
    {
        printf("Failed to load blinky texture!\n");
        success = false;
    }
    else
    {
        blinkySpriteClips[3][0] = {0, 0, 20, 20};
        blinkySpriteClips[3][1] = {0, 0, 20, 20};
        blinkySpriteClips[3][2] = {20, 0, 20, 20};
        blinkySpriteClips[3][3] = {20, 0, 20, 20};
        blinkySpriteClips[1][0] = {40, 0, 20, 20};
        blinkySpriteClips[1][1] = {40, 0, 20, 20};
        blinkySpriteClips[1][2] = {60, 0, 20, 20};
        blinkySpriteClips[1][3] = {60, 0, 20, 20};
        blinkySpriteClips[2][0] = {0, 20, 20, 20};
        blinkySpriteClips[2][1] = {0, 20, 20, 20};
        blinkySpriteClips[2][2] = {20, 20, 20, 20};
        blinkySpriteClips[2][3] = {20, 20, 20, 20};
        blinkySpriteClips[0][0] = {40, 20, 20, 20};
        blinkySpriteClips[0][1] = {40, 20, 20, 20};
        blinkySpriteClips[0][2] = {60, 20, 20, 20};
        blinkySpriteClips[0][3] = {60, 20, 20, 20};
    }

    //Load clyde texture
    if (!clydeTexture.loadFromFileBMP(renderer, "resources/Clyde.bmp"))
    {
        printf("Failed to load clyde texture!\n");
        success = false;
    }
    else
    {
        clydeSpriteClips[3][0] = {0, 0, 20, 20};
        clydeSpriteClips[3][1] = {0, 0, 20, 20};
        clydeSpriteClips[3][2] = {20, 0, 20, 20};
        clydeSpriteClips[3][3] = {20, 0, 20, 20};
        clydeSpriteClips[1][0] = {40, 0, 20, 20};
        clydeSpriteClips[1][1] = {40, 0, 20, 20};
        clydeSpriteClips[1][2] = {60, 0, 20, 20};
        clydeSpriteClips[1][3] = {60, 0, 20, 20};
        clydeSpriteClips[2][0] = {0, 20, 20, 20};
        clydeSpriteClips[2][1] = {0, 20, 20, 20};
        clydeSpriteClips[2][2] = {20, 20, 20, 20};
        clydeSpriteClips[2][3] = {20, 20, 20, 20};
        clydeSpriteClips[0][0] = {40, 20, 20, 20};
        clydeSpriteClips[0][1] = {40, 20, 20, 20};
        clydeSpriteClips[0][2] = {60, 20, 20, 20};
        clydeSpriteClips[0][3] = {60, 20, 20, 20};
    }

    //Load inky texture
    if (!inkyTexture.loadFromFileBMP(renderer, "resources/Inky.bmp"))
    {
        printf("Failed to load inky texture!\n");
        success = false;
    }
    else
    {
        inkySpriteClips[3][0] = {0, 0, 20, 20};
        inkySpriteClips[3][1] = {0, 0, 20, 20};
        inkySpriteClips[3][2] = {20, 0, 20, 20};
        inkySpriteClips[3][3] = {20, 0, 20, 20};
        inkySpriteClips[1][0] = {40, 0, 20, 20};
        inkySpriteClips[1][1] = {40, 0, 20, 20};
        inkySpriteClips[1][2] = {60, 0, 20, 20};
        inkySpriteClips[1][3] = {60, 0, 20, 20};
        inkySpriteClips[2][0] = {0, 20, 20, 20};
        inkySpriteClips[2][1] = {0, 20, 20, 20};
        inkySpriteClips[2][2] = {20, 20, 20, 20};
        inkySpriteClips[2][3] = {20, 20, 20, 20};
        inkySpriteClips[0][0] = {40, 20, 20, 20};
        inkySpriteClips[0][1] = {40, 20, 20, 20};
        inkySpriteClips[0][2] = {60, 20, 20, 20};
        inkySpriteClips[0][3] = {60, 20, 20, 20};
    }

    //Load pinky texture
    if (!pinkyTexture.loadFromFileBMP(renderer, "resources/Pinky.bmp"))
    {
        printf("Failed to load pinky texture!\n");
        success = false;
    }
    else
    {
        pinkySpriteClips[3][0] = {0, 0, 20, 20};
        pinkySpriteClips[3][1] = {0, 0, 20, 20};
        pinkySpriteClips[3][2] = {20, 0, 20, 20};
        pinkySpriteClips[3][3] = {20, 0, 20, 20};
        pinkySpriteClips[1][0] = {40, 0, 20, 20};
        pinkySpriteClips[1][1] = {40, 0, 20, 20};
        pinkySpriteClips[1][2] = {60, 0, 20, 20};
        pinkySpriteClips[1][3] = {60, 0, 20, 20};
        pinkySpriteClips[2][0] = {0, 20, 20, 20};
        pinkySpriteClips[2][1] = {0, 20, 20, 20};
        pinkySpriteClips[2][2] = {20, 20, 20, 20};
        pinkySpriteClips[2][3] = {20, 20, 20, 20};
        pinkySpriteClips[0][0] = {40, 20, 20, 20};
        pinkySpriteClips[0][1] = {40, 20, 20, 20};
        pinkySpriteClips[0][2] = {60, 20, 20, 20};
        pinkySpriteClips[0][3] = {60, 20, 20, 20};
    }

	return success;
}

bool Game::loadFont()
{
    //Flag
    bool success = true;

    //Open the font
    font = TTF_OpenFont("resources/Arcade.ttf", 22);
    if (font == NULL)
    {
        printf("Failed to load arcade font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    return success;
}

bool Game::loadAudio()
{
    //Flag
    bool success = true;

    //Load music
    introMusic = Mix_LoadMUS("resources/Intro.wav");
    if (introMusic == NULL)
    {
        printf("Failed to load intro music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    winMusic = Mix_LoadMUS("resources/Win.wav");
    if (winMusic == NULL)
    {
        printf("Failed to load win music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    lostMusic = Mix_LoadMUS("resources/Lost.wav");
    if (lostMusic == NULL)
    {
        printf("Failed to load lost music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    //Load sound effects
    pacmanDie = Mix_LoadWAV("resources/Die.wav");
    if (pacmanDie == NULL)
    {
        printf("Failed to load die sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    pacmanEat = Mix_LoadWAV("resources/Eat.wav");
    if (pacmanEat == NULL)
    {
        printf("Failed to load eat sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    }

    return success;
}

void Game::freeTiles(Tile* tiles[], Yummy* yummy[])
{
    //Deallocate space and wall tiles
	for (int i = 0; i < TOTAL_TILES; i++)
	{
		 if (tiles[i] != NULL)
		 {
			delete tiles[i];
			tiles[i] = NULL;
		 }
	}

    //Deallocate yummy
    for (int i = 0; i < TOTAL_TILES; i++)
    {
        if (yummy[i] != NULL)
        {
            delete yummy[i];
            yummy[i] = NULL;
        }
    }
}

void Game::close()
{
	//Free loaded images
	blankTexture.free();
	pacmanTexture.free();
	wallTexture.free();
	spaceTexture.free();
	smallYummyTexture.free();
	bigYummyTexture.free();
	blinkyTexture.free();
	clydeTexture.free();
	inkyTexture.free();
	pinkyTexture.free();
	deadPacmanTexture.free();
	textYScoreTexture.free();
    textYourScoreTexture.free();
    textHScoreTexture.free();
    textHighScoreTexture.free();
    textLifeTexture.free();
    lifeTexture.free();
    logoTexture.free();
    startEndLogoTexture.free();
    textStartTexture.free();
    textEndTexture.free();
    textPlayAgainTexture.free();

    //Free music
    Mix_FreeMusic(introMusic);
    introMusic = NULL;
    Mix_FreeMusic(winMusic);
    winMusic = NULL;
    Mix_FreeMusic(lostMusic);
    lostMusic = NULL;

    //Free sound effects
    Mix_FreeChunk(pacmanEat);
    pacmanEat = NULL;
    Mix_FreeChunk(pacmanDie);
    pacmanDie = NULL;

	//Free font
	TTF_CloseFont(font);
	font = NULL;

	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Game::setTiles(Tile* tiles[], Yummy* yummy[])
{
	//Success flag
	bool success = true;

    //The tile offsets
    int x = 0, y = 0;

    //Open the map
    std::ifstream Map("resources/Map.txt");

    //If the map couldn't be loaded
    if(!Map.is_open())
    {
		printf("Unable to load map file!\n");
		success = false;
    }
	else
	{
		//Initialize the tiles
		for (int i = 0; i < TOTAL_TILES; i++)
		{
			//Determines what kind of tile will be made
			int tileType;

			//Read tile from map file
			Map >> tileType;

			//If the was a problem in reading the map
			if (Map.fail())
			{
				//Stop loading map
				printf("Error loading map: Unexpected end of file!\n");
				success = false;
				break;
			}

			//If the number is a valid tile number
			if (((tileType >= 0) && (tileType < TOTAL_TILE_TYPES)) || tileType == 9)
			{
				tiles[i] = new Tile(x, y, tileType);

				//Set big/small yummy
				switch (tileType)
                {
                //Blank tile
                case 9:
                    //Type = NO_YUMMY
                    yummy[i] = new Yummy(0, 0, 1);
                    break;
                //Wall tile
                case 1:
                    //Type = NO_YUMMY
                    yummy[i] = new Yummy(0, 0, 1);
                    break;
                //Space tile
                case 0:
                    if (i == 146 || i == 161 || i == 566 || i == 581)
                    {
                        int _x = tiles[i]->getBox().x;
                        int _y = tiles[i]->getBox().y;
                        yummy[i] = new Yummy(_x, _y, BIG_YUMMY);
                    }
                    else
                    {
                        int _x = tiles[i]->getBox().x;
                        int _y = tiles[i]->getBox().y;
                        yummy[i] = new Yummy(_x, _y, SMALL_YUMMY);
                    }
                    break;
                }
			}
			//If we don't recognize the tile type
			else
			{
				//Stop loading map
				printf( "Error loading map: Invalid tile type at %d!\n", i );
				success = false;
				break;
			}

			//Move to next tile spot
			x += TILE_WIDTH;

			//If we've gone too far
			if (x >= LEVEL_WIDTH)
			{
				//Move back
				x = 0;

				//Move to the next row
				y += TILE_HEIGHT;
			}
		}
	}

    //Close the file
    Map.close();

    //If the map was loaded fine
    return success;
}

void Game::play()
{
    //Initialize and load media
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadTexture())
        {
            printf("Failed to load texture!\n");
        }
        if (!loadAudio())
        {
            printf("Failed to load audio!\n");
        }
        if (!loadFont())
        {
            printf("Failed to load font!\n");
        }
    }

    //Play again?
    bool playAgain = true;

    //Play-again loop
    while (playAgain == true)
    {
        //The space and wall tiles
        Tile* tileSet[TOTAL_TILES];

        //The yummy
        Yummy* yummySet[TOTAL_TILES];

        //Set tiles
        if (!setTiles(tileSet, yummySet))
        {
            printf("Failed to load tile set!\n");
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Render start screen
            textStartTexture.loadFromRenderedText("Start [Y/N]", textColor, font, renderer);

            //For flashing "Start game" and animation
            int start = 0; //0 = no action, 1 = play, 2 = quit
            int flashStart = 0;

            //Play the intro music
            Mix_PlayMusic(introMusic, -1);

            while (true)
            {
                if (flashStart <= 15)
                {
                    //Clear screen
                    SDL_RenderClear(renderer);

                    //Render start screen
                    startEndLogoTexture.render(180, 200, renderer);
                    textStartTexture.render(300, 400, renderer);
                    SDL_RenderPresent(renderer);
                }
                else
                {
                    //Clear screen
                    SDL_RenderClear(renderer);

                    //Render start screen
                    startEndLogoTexture.render(180, 200, renderer);
                    SDL_RenderPresent(renderer);
                }
                if (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                        break;
                    }

                    //Handle Y/N
                    if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_y:
                            start = 1;
                            break;
                        case SDLK_n:
                            start = 2;
                            break;
                        }
                    }
                }

                //If user wants to play game
                if (start == 1)
                {
                    break;
                }

                //If user does not want to play game
                else if (start == 2)
                {
                    quit = true;
                    break;
                }

                //Update flashStart
                if (flashStart > 30) flashStart = 0;
                else flashStart++;
            }

            //Stop the intro music
            Mix_HaltMusic();

            //Clear screen
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);

            //Initialize pacman at (20, 20)
            Pacman pacman(20, 20, TOTAL_YUMMY);

            //Initialize ghosts
            Ghost blinky(180, 220, 0, 2); //the chasing ghost initially
            Ghost clyde(360, 220, 2, 1);
            Ghost inky(180, 340, 2, 0);
            Ghost pinky(360, 340, 3, 0);

            //While the user does not quit
            while (!quit)
            {
                //Check if pacman loses
                if (pacman.lose())
                {
                    break;
                }
                //Check if pacman wins
                else if (pacman.win())
                {
                    break;
                }

                //Handle events on queue
                if (SDL_PollEvent(&e) != 0)
                {
                    //User requests quit
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }

                    //Handle input for the pacman and update velocity
                    pacman.handleEvent(e, tileSet);
                }
                else
                {
                    pacman.handlePending(tileSet);
                }

                //Move pacman
                pacman.move(tileSet, PLAYSCREEN_WIDTH);

                //Did pacman eat some yummy?
                std::vector<int> eatenYummy = pacman.eatYummy(yummySet, TOTAL_TILES);
                for (std::vector<int>::iterator itr = eatenYummy.begin(); itr != eatenYummy.end(); itr++)
                {
                    yummySet[*itr]->deleteYummy();
                }

                //If pacman ate some yummy, play a sound
                if (eatenYummy.size() > 0) Mix_PlayChannel(-1, pacmanEat, 0);

                //Move ghost
                blinky.move(pacman.getPos(), tileSet);
                clyde.move(pacman.getPos(), tileSet);
                inky.move(pacman.getPos(), tileSet);
                pinky.move(pacman.getPos(), tileSet);

                //Clear screen
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderClear(renderer);

                //Render space tiles and wall tiles
                for (int i = 0; i < TOTAL_TILES; i++)
                {
                    switch (tileSet[i]->getType())
                    {
                    //Render space tiles along with big yummy and small yummy
                    case 0:
                        tileSet[i]->render(spaceTexture, renderer);
                        break;
                    case 1:
                        tileSet[i]->render(wallTexture, renderer);
                        break;
                    case 9:
                        tileSet[i]->render(blankTexture, renderer);
                        break;
                    default:
                        break;
                    }
                }

                //Render big yummy and small yummy
                for (int i = 0; i < TOTAL_TILES; i++)
                {
                    switch (yummySet[i]->getType())
                    {
                    case SMALL_YUMMY:
                        yummySet[i]->render(smallYummyTexture, renderer);
                        break;
                    case BIG_YUMMY:
                        yummySet[i]->render(bigYummyTexture, renderer);
                        break;
                    case NO_YUMMY:
                        break;
                    default:
                        break;
                    }
                }

                //Render info screen
                logoTexture.render(580, 50, renderer);
                textYourScoreTexture.loadFromRenderedText("Your Score", textColor, font, renderer);
                textYourScoreTexture.render(600, 200, renderer);
                textYScoreTexture.loadFromRenderedText(std::to_string(pacman.getScore()), textColor, font, renderer);
                textYScoreTexture.render(600, 260, renderer);
                textHighScoreTexture.loadFromRenderedText("High Score", textColor, font, renderer);
                textHighScoreTexture.render(600, 320, renderer);
                textHScoreTexture.loadFromRenderedText(std::to_string(highScore), textColor, font, renderer);
                textHScoreTexture.render(600, 380, renderer);
                textLifeTexture.loadFromRenderedText("Life", textColor, font, renderer);
                textLifeTexture.render(600, 440, renderer);

                //Render number of lives in info screen according to pacman.getLife()
                switch (pacman.getLife())
                {
                case 1:
                    lifeTexture.render(600, 475, renderer);
                    break;
                case 2:
                    lifeTexture.render(600, 475, renderer);
                    lifeTexture.render(630, 475, renderer);
                    break;
                case 3:
                    lifeTexture.render(600, 475, renderer);
                    lifeTexture.render(630, 475, renderer);
                    lifeTexture.render(660, 475, renderer);
                }

                //Animation when pacman dies
                if (pacman.die(blinky) || pacman.die(clyde) || pacman.die(inky) || pacman.die(pinky))
                {
                    //Play sound when pacman dies
                    Mix_PlayChannel(-1, pacmanDie, 0);

                    //Dead position
                    int deadX = pacman.getPos().x, deadY = pacman.getPos().y;

                    //Play animation after pacman died
                    for (int i = 0; i < 8; i++)
                    {
                        deadPacmanTexture.render(deadX, deadY, renderer, &pacmanDeadSpriteClips[i]);
                        SDL_RenderPresent(renderer);
                        SDL_Delay(250);
                    }

                    //Reset frame
                    frame = 0;

                    //Reset to initial position
                    pacman.resetPos();
                    blinky.resetPos();
                    clyde.resetPos();
                    inky.resetPos();
                    pinky.resetPos();

                    continue;
                }

                //Render pacman
                pacman.render(pacmanTexture, pacmanSpriteClips, frame, renderer);

                //Render ghosts
                blinky.render(blinkyTexture, blinkySpriteClips, frame, renderer);
                clyde.render(clydeTexture, clydeSpriteClips, frame, renderer);
                inky.render(inkyTexture, inkySpriteClips, frame, renderer);
                pinky.render(pinkyTexture, pinkySpriteClips, frame, renderer);

                //Update screen
                SDL_RenderPresent(renderer);

                //Update frame
                frame++;
                if (frame/(ANIMATION_FRAMES) >= ANIMATION_FRAMES)
                {
                    frame = 0;
                }

            } // end main while loop

            //If the user closed the window
            if (e.type == SDL_QUIT) break;

            //If the user chose not to play game
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_n) break;

            //Check for new high score
            if (pacman.getScore() > highScore)
            {
                std::ofstream HighScoreOut("resources/HighScore.txt");
                HighScoreOut << pacman.getScore();
            }

            //Render end screen
            textPlayAgainTexture.loadFromRenderedText("Play Again? [Y/N]", textColor, font, renderer);
            if (pacman.win()) textEndTexture.loadFromRenderedText("YOU WIN!", textColor, font, renderer);
            else textEndTexture.loadFromRenderedText("YOU LOSE!", textColor, font, renderer);

            //For flashing "Play Again"
            int flashEnd = 0;
            bool end = false;

            //Play endgame music
            if (pacman.win()) Mix_PlayMusic(winMusic, -1);
            else Mix_PlayMusic(lostMusic, -1);

            while (end == false)
            {
                if (flashEnd <= 15)
                {
                    SDL_RenderClear(renderer);
                    textEndTexture.render(325, 150, renderer);
                    textPlayAgainTexture.render(225, 400, renderer);
                    textHighScoreTexture.render(175, 250, renderer);
                    textHScoreTexture.render(175, 300, renderer);
                    textYourScoreTexture.render(450, 250, renderer);
                    textYScoreTexture.render(450, 300 ,renderer);
                    SDL_RenderPresent(renderer);
                }
                else
                {
                    SDL_RenderClear(renderer);
                    textEndTexture.render(325, 150, renderer);
                    textHighScoreTexture.render(175, 250, renderer);
                    textHScoreTexture.render(175, 300, renderer);
                    textYourScoreTexture.render(450, 250, renderer);
                    textYScoreTexture.render(450, 300 ,renderer);
                    SDL_RenderPresent(renderer);
                }

                if (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        playAgain = false;
                        end = true;
                    }

                    else if (e.type == SDL_KEYDOWN)
                    {
                        switch (e.key.keysym.sym)
                        {
                        case SDLK_y:
                            playAgain = true;
                            end = true;
                            break;
                        case SDLK_n:
                            playAgain = false;
                            end = true;
                            break;
                        }
                    }
                }

                if (flashEnd > 30) flashEnd = 0;
                else flashEnd++;
            }
            //Stop playing endgame music
            Mix_HaltMusic();
        }
        //Free the tiles
        freeTiles(tileSet, yummySet);
	}
    //Free resources and close SDL
    close();
}
