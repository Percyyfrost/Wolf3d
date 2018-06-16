#include "../include/wolf3d.h"

int     readmap(char *string, t_var *var)
{
	int i;
	int j;
	int k;
	int fd;
	char **arr;

	j = 0;
	if (!(var->fd = open(string, O_RDWR)))
	{
		ft_putendl("Invaild file");
		return (-1);
	}
	arr = (char**)malloc(sizeof(char*) * 25);
	var->map = (int**)malloc(sizeof(int*) * 25);
	while (get_next_line(var->fd, &var->line))
	{
		k = 0;
		i = 0;
		arr[j] = (char*)malloc(sizeof(char*) * 25);
		var->map[j] = (int*)malloc(sizeof(int*) * 25);
		while (var->line[i])
		{
			arr[j][i] = var->line[i];
			var->map[j][i] = ft_atoi(&arr[j][i]);
			i++;
		}
		free(arr[j]);
		j++;
	}
	free(arr);

	return (0);
}

SDL_Renderer *init(char *title, int h, int w)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *win = SDL_CreateWindow(title, 100, 100, w, h, SDL_WINDOW_SHOWN);
	SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);

	return (ren);
}

void var_init(t_var *var)
{
	var->posX = 22;
	var->posY = 12;
	var->dirX = -1;
	var->dirY = 0;
	var->planeX = 0;
	var->planeY = 0.66;
	var->time = 0;
	var->oldTime = 0;
	var->exit = 0;
	var->w = 640;
	var->h = 480;
	var->i = 0;
	var->ren = init("Wolf3D", var->h, var->w);
}

void	color(t_var *var, t_ray *ray)
{
	//Calculate height of line to draw on screen
	ray->lineHeight	= (int)(var->h / ray->perpWallDist);
	//calculate lowest and highest pixel to fill in current stripe

	ray->drawStart = -ray->lineHeight / 2 + var->h / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + var->h / 2;
	if(ray->drawEnd >= var->h)
		ray->drawEnd = var->h - 1;
	if (var->map[ray->mapX][ray->mapY] == 1)
		SDL_SetRenderDrawColor(var->ren, 255, 0, 0, 255);
	else if (var->map[ray->mapX][ray->mapY] == 2)
		SDL_SetRenderDrawColor(var->ren, 0, 255, 0, 255);
	else if (var->map[ray->mapX][ray->mapY] == 3)
		SDL_SetRenderDrawColor(var->ren, 0, 0, 255, 255);
	else if (var->map[ray->mapX][ray->mapY] == 4)
		SDL_SetRenderDrawColor(var->ren, 255, 255, 255, 255);
	else
		SDL_SetRenderDrawColor(var->ren, 255, 255, 0, 255);
	if (ray->side == 1)
	{
		if (var->map[ray->mapX][ray->mapY] == 1)
			SDL_SetRenderDrawColor(var->ren, 255/2, 0, 0, 255/2);
		else if (var->map[ray->mapX][ray->mapY] == 2)
			SDL_SetRenderDrawColor(var->ren, 0, 255/2, 0, 255/2);
		else if (var->map[ray->mapX][ray->mapY] == 3)
			SDL_SetRenderDrawColor(var->ren, 0, 0, 255/2, 255/2);
		else if (var->map[ray->mapX][ray->mapY] == 4)
			SDL_SetRenderDrawColor(var->ren, 255/2, 255/2, 255/2, 255/2);
		else
			SDL_SetRenderDrawColor(var->ren, 255/2, 255/2, 0, 255/2);
	}
}

void	move(t_var *var, t_ray *ray, t_mov *mov)
{

	while (SDL_PollEvent(&var->event))
	{
		mov->oldDirX = var->dirX;
		mov->oldPlaneX = var->planeX;
		if (var->event.key.keysym.sym == SDLK_ESCAPE)
			var->exit = 1;
		if (var->event.key.keysym.sym == SDLK_UP)
		{
			if (var->map[(int)(var->posX + var->dirX * mov->moveSpeed)][(int)(var->posY)] == 0)
				var->posX += var->dirX * mov->moveSpeed;
			if(var->map[(int)(var->posX)][(int)(var->posY + var->dirY * mov->moveSpeed)] == 0)
				var->posY += var->dirY * mov->moveSpeed;
		}
		//move backwards if no wall behind you
		if (var->event.key.keysym.sym == SDLK_DOWN)
		{
			if (var->map[(int)(var->posX - var->dirX * mov->moveSpeed)][(int)(var->posY)] == 0)
				var->posX -= var->dirX * mov->moveSpeed;
			if (var->map[(int)(var->posX)][(int)(var->posY - var->dirY * mov->moveSpeed)] == 0)
				var->posY -= var->dirY * mov->moveSpeed;
		}
		//rotate to the right
		if (var->event.key.keysym.sym == SDLK_RIGHT)
		{
			//both camera direction and camera plane must be rotated
			var->dirX = var->dirX * cos(-mov->rotSpeed) - var->dirY * sin(-mov->rotSpeed);
			var->dirY = mov->oldDirX * sin(-mov->rotSpeed) + var->dirY * cos(-mov->rotSpeed);
			var->planeX = var->planeX * cos(-mov->rotSpeed) - var->planeY * sin(-mov->rotSpeed);
			var->planeY = mov->oldPlaneX * sin(-mov->rotSpeed) + var->planeY * cos(-mov->rotSpeed);
		}
		//rotate to the left
		if (var->event.key.keysym.sym == SDLK_LEFT)
		{
			//both camera direction and camera plane must be rotated
			var->dirX = var->dirX * cos(mov->rotSpeed) - var->dirY * sin(mov->rotSpeed);
			var->dirY = mov->oldDirX * sin(mov->rotSpeed) + var->dirY * cos(mov->rotSpeed);
			var->planeX = var->planeX * cos(mov->rotSpeed) - var->planeY * sin(mov->rotSpeed);
			var->planeY = mov->oldPlaneX * sin(mov->rotSpeed) + var->planeY * cos(mov->rotSpeed);
		}
	}
}

void	wall_hit(t_ray *ray, t_var *var)
{
	while (ray->hit == 0)
	{
		//jump to next map square, OR in x-direction, OR in y-direction
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		//Check if ray has hit a wall
		if (var->map[ray->mapX][ray->mapY] > 0)
			ray->hit = 1;
	}
}

void	mov_init(t_var *var, t_mov *mov)
{
	var->oldTime = var->time;
	var->time = SDL_GetTicks();
	mov->frameTime = (var->time - var->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
	mov->moveSpeed = mov->frameTime * 15.0; //the constant value is in squares/second
	mov->rotSpeed = mov->frameTime * 8.0; //the constant value is in radians/second
}

int		main(int ac, char **av)
{
	t_var	var;
	t_ray	ray;
	t_mov	mov;

	var_init(&var);
	if (ac == 2)
		readmap(av[1], &var);
	else
	{
		ft_putendl("Invalid input");
		return (-1);
	}
	while (!var.exit)
	{
		SDL_SetRenderDrawColor(var.ren, 0, 0, 0, 255);
		SDL_RenderClear(var.ren);
		var.x = -1;
		while ( var.x++ < var.w)
		{
			ray.cameraX = 2 * var.x / (double)var.w - 1; //x-coordinate in camera space
			ray.rayDirX = var.dirX + var.planeX * ray.cameraX;
			ray.rayDirY = var.dirY + var.planeY * ray.cameraX;
			//which box of the map we're in
			ray.mapX = (int)var.posX;
			ray.mapY = (int)var.posY;
			//length of ray from current position to next x or y-side
			//length of ray from one x or y-side to next x or y-side
			ray.deltaDistX = fabs(1 / ray.rayDirX);
			ray.deltaDistY = fabs(1 / ray.rayDirY);
			//what direction to step in x or y-direction (either +1 or -1)
			ray.hit = 0; //was there a wall hit?
			//calculate step and initial sideDist
			if (ray.rayDirX < 0)
			{
				ray.stepX = -1;
				ray.sideDistX = (var.posX - ray.mapX) * ray.deltaDistX;
			}
			else
			{
				ray.stepX = 1;
				ray.sideDistX = (ray.mapX + 1.0 - var.posX) * ray.deltaDistX;
			}
			if (ray.rayDirY < 0)
			{
				ray.stepY = -1;
				ray.sideDistY = (var.posY - ray.mapY) * ray.deltaDistY;
			}
			else
			{
				ray.stepY = 1;
				ray.sideDistY = (ray.mapY + 1.0 - var.posY) * ray.deltaDistY;
			}
			//perform DDA
			wall_hit(&ray, &var);
			//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
			if (ray.side == 0)
				ray.perpWallDist = (ray.mapX - var.posX + (1 - ray.stepX) / 2) / ray.rayDirX;
			else
				ray.perpWallDist = (ray.mapY - var.posY + (1 - ray.stepY) / 2) / ray.rayDirY;
			color(&var, &ray);
			//draw the pixels of the stripe as a vertical line
			var.i = ray.drawStart;
			while (var.i < ray.drawEnd)
				SDL_RenderDrawPoint(var.ren, var.x, var.i++);
		}
		mov_init(&var, &mov);
		SDL_RenderPresent(var.ren);
		SDL_RenderClear(var.ren);
		move(&var,&ray, &mov);
	}
}
