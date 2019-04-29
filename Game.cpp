#include "Game.h"

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
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize IMG loading
				int imgFlags = IMG_INIT_PNG;
				if (!( IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
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
	if (!blankTexture.loadFromFile(renderer, "test/blank.bmp"))
    {
        printf("Failed to load blank texture!\n");
        success = false;
    }

	//Load pacman texture
	if (!pacmanTexture.loadFromFile(renderer, "test/pacman.bmp"))
	{
		printf("Failed to load pacman texture!\n");
		success = false;
	}

	//Load wall tile texture
	if (!wallTexture.loadFromFile(renderer, "test/wall.bmp"))
	{
		printf("Failed to load wall tile texture!\n");
		success = false;
	}

    //Load space tile texture
    if (!spaceTexture.loadFromFile(renderer, "test/space.bmp"))
    {
        printf("Failed to load space tile texture!\n");
        success = false;
    }

	//Load small yummy texture
	if (!smallYummyTexture.loadFromFile(renderer, "test/smallyummy.bmp"))
    {
        printf("Failed to load small yummy texture!\n");
        success = false;
    }

    //Load big yummy texture
    if (!bigYummyTexture.loadFromFile(renderer, "test/bigyummy.bmp"))
    {
        printf("Failed to load big yummy texture!\n");
        success = false;
    }

    //Load blinky texture
    if (!blinkyTexture.loadFromFile(renderer, "test/blinky.bmp"))
    {
        printf("Failed to load blinky texture!\n");
        success = false;
    }

    //Load clyde texture
    if (!clydeTexture.loadFromFile(renderer, "test/clyde.bmp"))
    {
        printf("Failed to load clyde texture!\n");
        success = false;
    }

    //Load inky texture
    if (!inkyTexture.loadFromFile(renderer, "test/inky.bmp"))
    {
        printf("Failed to load inky texture!\n");
        success = false;
    }

    //Load pinky texture
    if (!pinkyTexture.loadFromFile(renderer, "test/pinky.bmp"))
    {
        printf("Failed to load pinky texture!\n");
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

	//Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
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
                    yummy[i] = new Yummy(UNDEFINED_X, UNDEFINED_Y, NO_YUMMY);
                    break;
                case WALL_TILE:
                    yummy[i] = new Yummy(UNDEFINED_X, UNDEFINED_Y, NO_YUMMY);
                    break;
                case SPACE_TILE:
                    if (i == 146 || i == 161 || i == 566 || i == 581)
                    {
                        int _x = tiles[i]->getBox().x + (TILE_WIDTH - BIG_YUMMY_WIDTH) / 2;
                        int _y = tiles[i]->getBox().y + (TILE_HEIGHT - BIG_YUMMY_HEIGHT) / 2;
                        yummy[i] = new Yummy(_x, _y, BIG_YUMMY);
                    }
                    else
                    {
                        int _x = tiles[i]->getBox().x + (TILE_WIDTH - SMALL_YUMMY_WIDTH) / 2;
                        int _y = tiles[i]->getBox().y + (TILE_HEIGHT - SMALL_YUMMY_HEIGHT) / 2;
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
	//Start up SDL and create window
	if(!init())
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//The space and wall tiles
		Tile* tileSet[TOTAL_TILES];

		//The yummy
        Yummy* yummySet[TOTAL_TILES];

		//Load media
		if (!loadTexture())
		{
			printf("Failed to load texture!\n");
		}
		else
		{
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

                //Initialize pacman
                Pacman pacman(TILE_WIDTH, TILE_HEIGHT);

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
                        quit = true;
                        printf("WON!\n");
                    }
                    else
                    {
//                        if (pacman.lose(blinky) || pacman.lose(clyde) || pacman.lose(inky) || pacman.lose(pinky))
                        if (pacman.lose(blinky))
                        {
                            quit = true;
                            printf("LOST!\n");
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
                    pacman.move(tileSet, SCREEN_WIDTH, SCREEN_HEIGHT);

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
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
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
                    pacman.render(pacmanTexture, renderer);

                    //Render ghosts
                    blinky.render(blinkyTexture, renderer);
//                    clyde.render(clydeTexture, renderer);
//                    inky.render(inkyTexture, renderer);
//                    pinky.render(pinkyTexture, renderer);

                    //Update screen
                    SDL_RenderPresent(renderer);

//                    //Debug
//                    SDL_Delay(5000);
                }
			}
		}

		//Free resources and close SDL
		close(tileSet, yummySet);
	}
}
