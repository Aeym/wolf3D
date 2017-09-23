#include <SDL/SDL.h>
#include <math.h>

#define WIDTH 640
#define HGHT 510
#define mapWidth 24
#define mapHeight 24

typedef struct s_vect
{
	int x;
	int w;
	int cont;
	int mapX;
	int mapY;
	int stepX;
	int stepY;
	int hit;
	int side;
	int lineHeight;
	int drawStart;
	int drawEnd;
	int color;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldtime;
	double camX;
	double rayPosX;
	double rayPosY;
	double rayDirX;
	double rayDirY;
	SDL_Event event;
	SDL_Surface *ecran;
}				t_vect;