#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <SDL2/SDL.h>
# define FPS 5

double inverseInterpolation(double y,  std::vector<std::pair<double, double>> &values)
{
    double res;
    double  c;
    double  denominator;

    res = 0;

    for (int j = 0; j < values.size(); ++j)
    {
        c = 1;
        denominator = 1;
        for (int i = 0; i < values.size(); ++i)
        {
            if (i != j)
            {
                c *= (y - values[i].second);
                denominator *= values[j].second - values[i].second;
            }

        }
        c = (c / denominator) * values[j].first;
        res += c;
    }
    return (res);
}


void drawSDL()
{
    double v;
    std::vector<std::pair<double, double>> values = {{M_E,1}, {M_E * M_E, 2}, {1 / M_E, -1}, {1/ (M_E * M_E), -2}};
    SDL_Window   *window;
    SDL_Renderer *renderer;
    SDL_Event event;
    Uint32       start;

    SDL_CreateWindowAndRenderer(1300, 1000, 0, &window, &renderer);

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    //SDL_RenderClear(renderer);
   // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    while (true)
    {
        SDL_RenderClear(renderer);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
        start = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        //SDL_RenderDrawPoint(renderer, 400, 300);

        for (double y = -30; y < 100; y+=0.001)
        {
            v = inverseInterpolation(y, values);
            SDL_RenderDrawPoint(renderer, v * 10, y * 10);
            SDL_SetRenderDrawColor(renderer, 0, 150, 241, 255);
            SDL_RenderDrawPoint(renderer, pow(M_E, y) * 10, y * 10);
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderPresent(renderer);
      //  SDL_UpdateWindowSurface(window);


        SDL_Delay(5);
        if (1000 / FPS > SDL_GetTicks() - start)
        {
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
        }


    }



    for (double y = -3; y < 3; y+=0.1)
    {
        v = inverseInterpolation(y, values);
        std::cout << "y: " <<y << " x: " << v << std::endl;

    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}



int main()
{
    drawSDL();


    return (0);
}