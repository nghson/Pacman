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
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
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
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (renderer == NULL)
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
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
	if (!blankTexture.loadFromFile(renderer, "resources/Blank.bmp"))
    {
        printf("Failed to load blank texture!\n");
        success = false;
    }

    //Load start logo texture
    if (!startEndLogoTexture.loadFromFile(renderer, "resources/StartLogo.bmp"))
    {
        printf("Failed to load start logo texture!\n");
        success = false;
    }

    //Load logo texture
    if (!logoTexture.loadFromFile(renderer, "resources/Logo.bmp"))
    {
        printf("Failed to load logo texture!\n");
        success = false;
    }

    //Load life texture
    if (!lifeTexture.loadFromFile(renderer, "resources/Life.bmp"))
    {
        printf("Failed to load life texture!\n");
        success = false;
    }

	//Load pacman texture
	if (!pacmanTexture.loadFromFile(renderer, "resources/Pacman.bmp"))
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

	//Load wall tile texture
	if (!wallTexture.loadFromFile(renderer, "test/wall.bmp"))
	{
		printf("Failed to load wall tile texture!\n");
		success = false;
	}

    //Load space tile texture
    if (!spaceTexture.loadFromFile(renderer, "resources/Space.bmp"))
    {
        printf("Failed to load space tile texture!\n");
        success = false;
    }

	//Load small yummy texture
	if (!smallYummyTexture.loadFromFile(renderer, "resources/SmallYummy.bmp"))
    {
        printf("Failed to load small yummy texture!\n");
        success = false;
    }

    //Load big yummy texture
    if (!bigYummyTexture.loadFromFile(renderer, "resources/BigYummy.bmp"))
    {
        printf("Failed to load big yummy texture!\n");
        success = false;
    }

    //Load blinky texture
    if (!blinkyTexture.loadFromFile(renderer, "resources/Blinky.bmp"))
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
    if (!clydeTexture.loadFromFile(renderer, "resources/Clyde.bmp"))
    {
        printf("Failed to load clyde texture!\n");
        success = false;
    }

    //Load inky texture
    if (!inkyTexture.loadFromFile(renderer, "resources/Inky.bmp"))
    {
        printf("Failed to load inky texture!\n");
        success = false;
    }

    //Load pinky texture
    if (!pinkyTexture.loadFromFile(renderer, "resources/Pinky.bmp"))
    {
        printf("Failed to load pinky texture!\n");
        success = false;
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

void Game::close(Tile* tiles[], Yummy* yummy[])
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
	textYScoreTexture.free();
    textYourScoreTexture.free();
    textHScoreTexture.free();
    textHighScoreTexture.free();
    lifeTexture.free();
    logoTexture.free();

	//Free font
	TTF_CloseFont(font);
	font = NULL;

	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
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
    std::ifstream Map("test/Map.txt");

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
			if (((tileType >= 0) && (tileType < TOTAL_TILE_TYPES)) || tileType == BLANK_TILE)
			{
				tiles[i] = new Tile(x, y, tileType);

				//Set big/small yummy
				switch (tileType)
                {
                case BLANK_TILE:
                    //Type = NO_YUMMY
                    yummy[i] = new Yummy(0, 0, 1);
                    break;
                case WALL_TILE:
                    //Type = NO_YUMMY
                    yummy[i] = new Yummy(0, 0, 1);
                    break;
                case SPACE_TILE:
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
    //Play again?
    bool playAgain = true;
    while (playAgain == true)
    {
        //The space and wall tiles
        Tile* tileSet[TOTAL_TILES];

        //The yummy
        Yummy* yummySet[TOTAL_TILES];

        //Start up SDL and create window
        if(!init())
        {
            printf("Failed to initialize!\n");
        }
        else
        {
            //Load texture and font
            if (!loadTexture())
            {
                printf("Failed to load texture!\n");
            }
            else if (!loadFont())
            {
                printf("Failed to load font!\n");
            }
            else
            {
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
                    int start = 0; //0 = no action, 1 = play, 2 = quit
                    int flashStart = 0;
                    while (true)
                    {
                        if (flashStart <= 15)
                        {
                            //Clear screen
                            SDL_RenderClear(renderer);

                            //Render start screen
                            startEndLogoTexture.render(180, 200, renderer);
                            textStartTexture.render(300, 350, renderer);
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

                    //Clear screen
                    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
                    SDL_RenderClear(renderer);

                    //Initialize pacman at (20, 20)
                    Pacman pacman(20, 20, TOTAL_YUMMY);

                    //Initialize ghosts
                    Ghost blinky(180, 220);
    //                Ghost clyde(360, 220);
    //                Ghost inky(180, 340);
    //                Ghost pinky(360, 340);

                        //While the user does not quit
                        while (!quit)
                        {
                            //Check if pacman wins
                            if (pacman.win())
                            {
                                break;
                            }
                            else
                            {
    //                            if (pacman.lose(blinky) || pacman.lose(clyde) || pacman.lose(inky) || pacman.lose(pinky))
                                if (pacman.lose(blinky))
                                {
                                    break;
                                }
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
                            std::vector<int> eatenYummy = pacman.eatYummy(yummySet);
                            for (std::vector<int>::iterator itr = eatenYummy.begin(); itr != eatenYummy.end(); itr++)
                            {
                                yummySet[*itr]->deleteYummy();
                            }

                            //Move ghost
                            blinky.move(pacman.getPos(), tileSet);
        //                    clyde.move(pacman.getPos(), tileSet);
        //                    inky.move(pacman.getPos(), tileSet);
        //                    pinky.move(pacman.getPos(), tileSet);

                            //Clear screen
                            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
                            SDL_RenderClear(renderer);

                            //Render space tiles and wall tiles
                            for (int i = 0; i < TOTAL_TILES; i++)
                            {
                                switch (tileSet[i]->getType())
                                {
                                //Render space tiles along with big yummy and small yummy
                                case SPACE_TILE:
                                    tileSet[i]->render(spaceTexture, renderer);
                                    break;
                                case WALL_TILE:
                                    tileSet[i]->render(wallTexture, renderer);
                                    break;
                                case BLANK_TILE:
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

                            //Render pacman
                            pacman.render(pacmanTexture, pacmanSpriteClips, frame, renderer);

                            //Render ghosts
                            blinky.render(blinkyTexture, blinkySpriteClips, frame, renderer);
        //                    clyde.render(clydeTexture, renderer);
        //                    inky.render(inkyTexture, renderer);
        //                    pinky.render(pinkyTexture, renderer);

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
                            lifeTexture.render(600, 500, renderer);

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

                        int flashEnd = 0;
                        bool end = false;
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
                }
                }
            }

            //Free resources and close SDL
            close(tileSet, yummySet);
	}
}
