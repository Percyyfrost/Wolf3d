/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnxele <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 12:46:15 by vnxele            #+#    #+#             */
/*   Updated: 2018/06/18 15:56:22 by vnxele           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	forward(t_var **var, t_mov **mov)
{
	if (!((*var)->map[(int)((*var)->posX + (*var)->dirX
					* (*mov)->moveSpeed)][(int)((*var)->posY)]))
		(*var)->posX += (*var)->dirX * (*mov)->moveSpeed;
	if (!((*var)->map[(int)((*var)->posX)][(int)((*var)->posY
					+ (*var)->dirY * (*mov)->moveSpeed)]))
		(*var)->posY += (*var)->dirY * (*mov)->moveSpeed;
}

void	backward(t_var **var, t_mov **mov)
{
	if (!((*var)->map[(int)((*var)->posX - (*var)->dirX
					* (*mov)->moveSpeed)][(int)((*var)->posY)]))
		(*var)->posX -= (*var)->dirX * (*mov)->moveSpeed;
	if (!((*var)->map[(int)((*var)->posX)][(int)((*var)->posY
					- (*var)->dirY * (*mov)->moveSpeed)]))
		(*var)->posY -= (*var)->dirY * (*mov)->moveSpeed;
}

void	left(t_var **var, t_mov **mov)
{
	(*var)->dirX = (*var)->dirX * cos((*mov)->rotSpeed)
		- (*var)->dirY * sin((*mov)->rotSpeed);
	(*var)->dirY = (*mov)->oldDirX * sin((*mov)->rotSpeed)
		+ (*var)->dirY * cos((*mov)->rotSpeed);
	(*var)->planeX = (*var)->planeX * cos((*mov)->rotSpeed)
		- (*var)->planeY * sin((*mov)->rotSpeed);
	(*var)->planeY = (*mov)->oldPlaneX * sin((*mov)->rotSpeed)
		+ (*var)->planeY * cos((*mov)->rotSpeed);
}

void	right(t_var **var, t_mov **mov)
{
	(*var)->dirX = (*var)->dirX * cos(-(*mov)->rotSpeed)
		- (*var)->dirY * sin(-(*mov)->rotSpeed);
	(*var)->dirY = (*mov)->oldDirX * sin(-(*mov)->rotSpeed)
		+ (*var)->dirY * cos(-(*mov)->rotSpeed);
	(*var)->planeX = (*var)->planeX * cos(-(*mov)->rotSpeed)
		- (*var)->planeY * sin(-(*mov)->rotSpeed);
	(*var)->planeY = (*mov)->oldPlaneX * sin(-(*mov)->rotSpeed)
		+ (*var)->planeY * cos(-(*mov)->rotSpeed);
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
			forward(&var, &mov);
		if (var->event.key.keysym.sym == SDLK_DOWN)
			backward(&var, &mov);
		if (var->event.key.keysym.sym == SDLK_RIGHT)
			right(&var, &mov);
		if (var->event.key.keysym.sym == SDLK_LEFT)
			left(&var, &mov);
	}
}
