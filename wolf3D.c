#include "wolf3D.h"

int worldMap[mapWidth][mapHeight]=
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	vertical_stripes(t_vect *v);

int init_sdl(t_vect *v)
{
	if ((SDL_Init(SDL_INIT_VIDEO)) == -1)
	{
		printf("Erreur d'initialisation : %s\n", SDL_GetError());
		return (0);
	}  
	v->ecran = SDL_SetVideoMode(WIDTH, HGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Wolf3D", NULL);
	if (v->ecran == NULL)
	{
		printf("mode video impossible : %s\n", SDL_GetError());
		return (0);
	}
}

void core_wolf(t_vect *v)
{
	v->cont = 1;
	v->event;

	SDL_EnableKeyRepeat(100, 10);
	while (v->cont)
	{
		SDL_FillRect(v->ecran, NULL, SDL_MapRGB(v->ecran->format, 0, 0, 0));
		vertical_stripes(v);
		//timing for input and FPS counter
		v->oldtime = v->time;
		v->time = SDL_GetTicks();
		double frameTime = (v->time - v->oldtime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		//print(1.0 / frameTime); //FPS counter
		// redraw();
		// cls();

		//speed modifiers
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
		SDL_WaitEvent(&v->event);
		if (v->event.type == SDL_QUIT)
			v->cont = 0;
		else if (v->event.type == SDL_KEYDOWN)
		{
			if (v->event.key.keysym.sym == SDLK_ESCAPE)
				v->cont = 0;
			if (v->event.key.keysym.sym == SDLK_UP)
			{
				if(worldMap[(int)(v->posX + v->dirX * moveSpeed)][(int)(v->posY)] == 0) v->posX += v->dirX * moveSpeed;
				if(worldMap[(int)(v->posX)][(int)(v->posY + v->dirY * moveSpeed)] == 0) v->posY += v->dirY * moveSpeed;
			}
			//move backwards if no wall behind you
			if (v->event.key.keysym.sym == SDLK_DOWN)
			{
				if(worldMap[(int)(v->posX + v->dirX * moveSpeed)][(int)(v->posY)] == 0) v->posX -= v->dirX * moveSpeed;
				if(worldMap[(int)(v->posX)][(int)(v->posY + v->dirY * moveSpeed)] == 0) v->posY -= v->dirY * moveSpeed;
			}
			//rotate to the right
			if (v->event.key.keysym.sym == SDLK_RIGHT)
			{
				//both camera direction and camera plane must be rotated
				double oldDirX = v->dirX;
				v->dirX = v->dirX * cos(-rotSpeed) - v->dirY * sin(-rotSpeed);
				v->dirY = oldDirX * sin(-rotSpeed) + v->dirY * cos(-rotSpeed);
				double oldPlaneX = v->planeX;
				v->planeX = v->planeX * cos(-rotSpeed) - v->planeY * sin(-rotSpeed);
				v->planeY = oldPlaneX * sin(-rotSpeed) + v->planeY * cos(-rotSpeed);
			}
			//rotate to the left
			if (v->event.key.keysym.sym == SDLK_LEFT)
			{
				//both camera direction and camera plane must be rotated
				double oldDirX = v->dirX;
				v->dirX = v->dirX * cos(rotSpeed) - v->dirY * sin(rotSpeed);
				v->dirY = oldDirX * sin(rotSpeed) + v->dirY * cos(rotSpeed);
				double oldPlaneX = v->planeX;
				v->planeX = v->planeX * cos(rotSpeed) - v->planeY * sin(rotSpeed);
				v->planeY = oldPlaneX * sin(rotSpeed) + v->planeY * cos(rotSpeed);
			}
		}
		SDL_Flip(v->ecran);
	}
}

void	init_struct(t_vect *v)
{
	v->posX = 22,
		v->posY = 12;  //x and y start position
	v->dirX = -1;
	v->dirY = 0; //initial direction vector
	v->planeX = 0;
	v->planeY = 0.66; //the 2d raycaster version of camera plane
	v->time = 0; //time of current frame
	v->oldtime = 0;
}

void setPixel(t_vect *v, int x, int y)
{
	SDL_Rect pixel;
	pixel.w = 1, pixel.h = 1;
	pixel.x = v->x, pixel.y = y;
	SDL_FillRect(v->ecran, &pixel, v->color);
}

void	verLine(t_vect *v)
{
	int tmp;

	tmp = v->drawStart;
	while(tmp <= v->drawEnd)
	{
		setPixel(v, v->x, tmp);
		tmp++;
	}
}

void	vertical_stripes(t_vect *v)
{
	v->x = 0;
	while(v->x < WIDTH)
	{
		v->camX = 2 * v->x / (double)HGHT - 1;
		v->rayPosX = v->posX;
		v->rayPosY = v->posY;
		v->rayDirX = v->dirX + v->planeX * v->camX;
		v->rayDirY = v->dirY + v->planeY * v->camX;
		v->x++;

		v->mapX = (int)v->rayPosX;
		v->mapY = (int)v->rayPosY;
		v->deltaDistX = sqrt(1 + (v->rayDirY * v->rayDirY) / (v->rayDirX * v->rayDirX));
		v->deltaDistY = sqrt(1 + (v->rayDirX * v->rayDirX) / (v->rayDirY * v->rayDirY));
		v->hit = 0;

		if (v->rayDirX < 0)
		{
			v->stepX = -1;
			v->sideDistX = (v->rayPosX - v->mapX) * v->deltaDistX;
		}
		else
		{
			v->stepX = 1;
			v->sideDistX = (v->mapX + 1.0 - v->rayPosX) * v->deltaDistX;
		}
		if (v->rayDirY < 0)
		{
			v->stepY = -1;
			v->sideDistY = (v->rayPosY - v->mapY) * v->deltaDistY;
		}
		else
		{
			v->stepY = 1;
			v->sideDistY = (v->mapY + 1.0 - v->rayPosY) * v->deltaDistY;
		}
		//perform DDA
		while (v->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (v->sideDistX < v->sideDistY)
			{
				v->sideDistX += v->deltaDistX;
				v->mapX += v->stepX;
				v->side = 0;
			}
			else
			{
				v->sideDistY += v->deltaDistY;
				v->mapY += v->stepY;
				v->side = 1;
			}
			//Check if ray has hit a wall
			if (worldMap[v->mapX][v->mapY] > 0)
				v->hit = 1;
		}
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (v->side == 0)
			v->perpWallDist = (v->mapX - v->rayPosX + (1 - v->stepX) / 2) / v->rayDirX;
		else
			v->perpWallDist = (v->mapY - v->rayPosY + (1 - v->stepY) / 2) / v->rayDirY;

		//Calculate height of line to draw on screen
		v->lineHeight = (int)(HGHT / v->perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		v->drawStart = -v->lineHeight / 2 + HGHT / 2;
		if(v->drawStart < 0)
			v->drawStart = 0;
		v->drawEnd = v->lineHeight / 2 + HGHT / 2;
		if(v->drawEnd >= HGHT)
			v->drawEnd = HGHT - 1;

		if(worldMap[v->mapX][v->mapY])
		{
			if (worldMap[v->mapX][v->mapY] == 1)
				v->color = SDL_MapRGB(v->ecran->format, 255, 0, 0);
			if (worldMap[v->mapX][v->mapY] == 2)
				v->color = SDL_MapRGB(v->ecran->format, 0, 255, 255);
			if (worldMap[v->mapX][v->mapY] == 3)
				v->color = SDL_MapRGB(v->ecran->format, 255, 0, 255);
			if (worldMap[v->mapX][v->mapY] == 4)
				v->color = SDL_MapRGB(v->ecran->format, 255, 255, 0);
			else
				v->color = SDL_MapRGB(v->ecran->format, 0, 255, 0);
		}
		//give x and y sides different brightness
		if (v->side == 1)
			v->color = v->color / 2;

		verLine(v);
	}
}

int main(int ac, char **av)
{
	t_vect v;

	init_struct(&v);
	init_sdl(&v);
	core_wolf(&v);
}
