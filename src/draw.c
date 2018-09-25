/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnxele <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 12:28:37 by vnxele            #+#    #+#             */
/*   Updated: 2018/06/26 10:48:31 by vnxele           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/wolf3d.h"

void	init_ray(t_var **var, t_ray **ray)
{
	(*ray)->lineHeight = (int)((*var)->h / (*ray)->perpWallDist);
	(*ray)->drawStart = -(*ray)->lineHeight / 2 + (*var)->h / 2;
	if ((*ray)->drawStart < 0)
		(*ray)->drawStart = 0;
	(*ray)->drawEnd = (*ray)->lineHeight / 2 + (*var)->h / 2;
	if ((*ray)->drawEnd >= (*var)->h)
		(*ray)->drawEnd = (*var)->h - 1;
}

void	color(t_var **var, t_ray **ray)
{
	if ((*var)->map[(*ray)->mapX][(*ray)->mapY] == 1)
		SDL_SetRenderDrawColor((*var)->ren, 255, 0, 0, 255);
	else if ((*var)->map[(*ray)->mapX][(*ray)->mapY] == 2)
		SDL_SetRenderDrawColor((*var)->ren, 0, 255, 0, 255);
	else if ((*var)->map[(*ray)->mapX][(*ray)->mapY] == 3)
		SDL_SetRenderDrawColor((*var)->ren, 0, 0, 255, 255);
	else if ((*var)->map[(*ray)->mapX][(*ray)->mapY] == 4)
		SDL_SetRenderDrawColor((*var)->ren, 255, 255, 255, 255);
	else
		SDL_SetRenderDrawColor((*var)->ren, 255, 255, 0, 255);
	if ((*ray)->side)
	{
		if ((*var)->map[(*ray)->mapX][(*ray)->mapY] == 1)
			SDL_SetRenderDrawColor((*var)->ren, 128, 0, 0, 128);
		else if ((*var)->map[(*ray)->mapX][(*ray)->mapY] == 2)
			SDL_SetRenderDrawColor((*var)->ren, 0, 128, 0, 128);
		else if ((*var)->map[(*ray)->mapX][(*ray)->mapY] == 3)
			SDL_SetRenderDrawColor((*var)->ren, 0, 0, 128, 128);
		else if ((*var)->map[(*ray)->mapX][(*ray)->mapY] == 4)
			SDL_SetRenderDrawColor((*var)->ren, 128, 128, 128, 128);
		else
			SDL_SetRenderDrawColor((*var)->ren, 128, 128, 0, 128);
	}
}

void	wall_hit(t_ray **ray, t_var **var)
{
	while ((*ray)->hit == 0)
	{
		if ((*ray)->sideDistX < (*ray)->sideDistY)
		{
			(*ray)->sideDistX += (*ray)->deltaDistX;
			(*ray)->mapX += (*ray)->stepX;
			(*ray)->side = 0;
		}
		else
		{
			(*ray)->sideDistY += (*ray)->deltaDistY;
			(*ray)->mapY += (*ray)->stepY;
			(*ray)->side = 1;
		}
		if ((*var)->map[(*ray)->mapX][(*ray)->mapY] > 0)
			(*ray)->hit = 1;
	}
}

void	wall_dist(t_ray **ray, t_var **var)
{
	if ((*ray)->rayDirX < 0)
	{
		(*ray)->stepX = -1;
		(*ray)->sideDistX = ((*var)->posX - (*ray)->mapX) * (*ray)->deltaDistX;
	}
	else
	{
		(*ray)->stepX = 1;
		(*ray)->sideDistX = ((*ray)->mapX + 1.0 - (*var)->posX) *
			(*ray)->deltaDistX;
	}
	if ((*ray)->rayDirY < 0)
	{
		(*ray)->stepY = -1;
		(*ray)->sideDistY = ((*var)->posY - (*ray)->mapY) * (*ray)->deltaDistY;
	}
	else
	{
		(*ray)->stepY = 1;
		(*ray)->sideDistY = ((*ray)->mapY + 1.0 - (*var)->posY) *
			(*ray)->deltaDistY;
	}
}

void	draw(t_ray *ray, t_var *var)
{
	ray->cameraX = 2 * var->x / (double)var->w - 1;
	ray->rayDirX = var->dirX + var->planeX * ray->cameraX;
	ray->rayDirY = var->dirY + var->planeY * ray->cameraX;
	ray->mapX = (int)var->posX;
	ray->mapY = (int)var->posY;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
	ray->hit = 0;
	wall_dist(&ray, &var);
	wall_hit(&ray, &var);
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - var->posX +
				(1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - var->posY +
				(1 - ray->stepY) / 2) / ray->rayDirY;
	init_ray(&var, &ray);
	color(&var, &ray);
	var->i = ray->drawStart;
	while (var->i < ray->drawEnd)
		SDL_RenderDrawPoint(var->ren, var->x, var->i++);
}
