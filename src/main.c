/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnxele <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 14:17:31 by vnxele            #+#    #+#             */
/*   Updated: 2018/06/26 10:38:53 by vnxele           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

int					readmap(char *string, t_var *var)
{
	t_read			r;

	r.j = 0;
	if (!(var->fd = open(string, O_RDWR)))
	{
		ft_putendl("Invaild file");
		return (-1);
	}
	r.arr = (char**)malloc(sizeof(char*) * mapSize);
	var->map = (int**)malloc(sizeof(int*) * mapSize);
	while (get_next_line(var->fd, &var->line))
	{
		r.i = 0;
		r.arr[r.j] = (char*)malloc(sizeof(char*) * mapSize);
		var->map[r.j] = (int*)malloc(sizeof(int*) * mapSize);
		while (var->line[r.i])
		{
			r.arr[r.j][r.i] = var->line[r.i];
			var->map[r.j][r.i] = ft_atoi(&r.arr[r.j][r.i++]);
		}
		free(r.arr[r.j]);
		r.j++;
	}
	free(r.arr);
	return (0);
}

SDL_Renderer		*init(char *title, int h, int w)
{
	SDL_Window		*win;
	SDL_Renderer	*ren;

	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow(title, 100, 100, w, h, SDL_WINDOW_SHOWN);
	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED
			| SDL_RENDERER_PRESENTVSYNC);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);
	return (ren);
}

void				var_init(t_var *var)
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

void				mov_init(t_var *var, t_mov *mov)
{
	var->oldTime = var->time;
	var->time = SDL_GetTicks();
	mov->frameTime = (var->time - var->oldTime) / 1000.0;
	mov->moveSpeed = mov->frameTime * 15.0;
	mov->rotSpeed = mov->frameTime * 8.0;
}

int					main(int ac, char **av)
{
	t_var			var;
	t_ray			ray;
	t_mov			mov;

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
		while (var.x++ < var.w)
			draw(&ray, &var);
		mov_init(&var, &mov);
		SDL_RenderPresent(var.ren);
		SDL_RenderClear(var.ren);
		move(&var, &ray, &mov);
	}
	return (0);
}
