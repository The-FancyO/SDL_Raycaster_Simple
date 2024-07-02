#include <SDL2/SDL.h>

#include <stdio.h>
#include <cmath>
#include <map>

#define mapWidth 24
#define mapHeight 24

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

void drawLine(SDL_Renderer *renderer, int x, int y1, int y2, const SDL_Color color)
{

    // Set the drawing color

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

    // Draw the line

    for (int y = y1; y <= y2; y++)
    {

        SDL_RenderDrawPoint(renderer, x, y);
    }
}

std::map<int, bool> keypressed; // for the "keyPressed" function to detect a keypress only once
Uint8 *inkeys = 0;

bool keyDown(int key) // this checks if the key is held down, returns true all the time until the key is up
{
    if (!inkeys)
        return false;
    return (inkeys[key] != 0);
}

int worldMap[mapWidth][mapHeight] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 3, 0, 0, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 2, 2, 0, 2, 2, 0, 0, 0, 0, 3, 0, 3, 0, 3, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 5, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 4, 4, 4, 4, 4, 4, 4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

int main(int argc, char **argv)
{
    double posX = 22, posY = 12;      // x and y start position
    double dirX = -1, dirY = 0;       // initial direction vector
    double planeX = 0, planeY = 0.66; // the 2d raycaster version of camera plane

    double time = 0;    // time of current frame
    double oldTime = 0; // time of previous frame

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SLD test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window)
    {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    bool running = true;
    while (running)
    {
        SDL_Event event;

        SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            // calculate ray position and direction
            double cameraX = 2 * x / (double)SCREEN_WIDTH - 1; // x-coordinate in camera space
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            // which box of the map we're in
            int mapX = int(posX);
            int mapY = int(posY);

            // length of ray from current position to next x or y-side
            double sideDistX;
            double sideDistY;

            // length of ray from one x or y-side to next x or y-side
            // these are derived as:
            // deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
            // deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
            // which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
            // where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
            // unlike (dirX, dirY) is not 1, however this does not matter, only the
            // ratio between deltaDistX and deltaDistY matters, due to the way the DDA
            // stepping further below works. So the values can be computed as below.
            //  Division through zero is prevented, even though technically that's not
            //  needed in C++ with IEEE 754 floating point values.
            double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY);

            double perpWallDist;

            // what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; // was there a wall hit?
            int side;    // was a NS or a EW wall hit?
            // calculate step and initial sideDist
            if (rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if (rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }
            // perform DDA
            while (hit == 0)
            {
                // jump to next map square, either in x-direction, or in y-direction
                if (sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                // Check if ray has hit a wall
                if (worldMap[mapX][mapY] > 0)
                    hit = 1;
            }
            // Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
            // hit to the camera plane. Euclidean to center camera point would give fisheye effect!
            // This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
            // for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
            // because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
            // steps, but we subtract deltaDist once because one step more into the wall was taken above.
            if (side == 0)
                perpWallDist = (sideDistX - deltaDistX);
            else
                perpWallDist = (sideDistY - deltaDistY);

            // Calculate height of line to draw on screen
            int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

            // calculate lowest and highest pixel to fill in current stripe
            int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawStart < 0)
                drawStart = 0;
            int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
            if (drawEnd >= SCREEN_HEIGHT)
                drawEnd = SCREEN_HEIGHT - 1;

            // choose wall color
            SDL_Color red = {255, 0, 0, 255};       // Red
            SDL_Color green = {0, 255, 0, 255};     // Green
            SDL_Color blue = {0, 0, 255, 255};      // Blue
            SDL_Color white = {255, 255, 255, 255}; // White
            SDL_Color yellow = {255, 255, 0, 255};  // Yellow

            SDL_Color color;
            switch (worldMap[mapX][mapY])
            {
            case 1:
                color = red;
                break; // red
            case 2:
                color = green;
                break; // green
            case 3:
                color = blue;
                break; // blue
            case 4:
                color = white;
                break; // white
            default:
                color = yellow;
                break; // yellow
            }

            // give x and y sides different brightness
            if (side == 1)
            {
                color.a = color.a / 2;
            }

            // draw the pixels of the stripe as a vertical line
            drawLine(renderer, x, drawStart, drawEnd, color);
        }
        oldTime = time;
        time = SDL_GetTicks();
        double frameTime = (time - oldTime) / 1000.0; // frameTime is the time this frame has taken, in seconds
        // print(1.0 / frameTime); //FPS counter
        // cls();

        // speed modifiers
        double moveSpeed = frameTime * 5.0; // the constant value is in squares/second
        double rotSpeed = frameTime * 3.0;  // the constant value is in radians/second

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                    break;
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    if (worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false)
                        posX += dirX * moveSpeed;
                    if (worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false)
                        posY += dirY * moveSpeed;
                    break;
                }

                else if (event.key.keysym.sym == SDLK_DOWN) {
                    if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
                        posX -= dirX * moveSpeed;
                    if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
                        posY -= dirY * moveSpeed;
                    break;
                }

                if (event.key.keysym.sym == SDLK_LEFT) {
                    double oldDirX = dirX;
                    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
                    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
                    double oldPlaneX = planeX;
                    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
                    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
                    break;
                }

                else if (event.key.keysym.sym == SDLK_RIGHT) {
                    double oldDirX = dirX;
                    dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
                    dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
                    double oldPlaneX = planeX;
                    planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
                    planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
                    break;
                }

            default:
                break;
            }
        }

        const uint8_t *keystate = SDL_GetKeyboardState(NULL);

        SDL_RenderPresent(renderer);
    }

    return 0;
}