# include <stdio.h>
# include <math.h>
# include <time.h>
# include <iostream>
# include <fstream>
# include <string>
# include <point.H>
# include <tpl_find_path.H>
# include <tpl_dynArray.H>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_rotozoom.h>
# include <SDL/SDL_mouse.h>
# include "greedySpiders.H"


using namespace std;



int main()
{
	GT Graph;
	Select_level(Graph, 1);
	play(Graph);
}