/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnxele <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 09:18:01 by vnxele            #+#    #+#             */
/*   Updated: 2018/06/13 11:42:52 by vnxele           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
#define WOLF3D_H

#include <header.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define mapWidth 24
#define mapHeight 24

typedef struct		s_var
{
	SDL_Renderer    *ren;
	SDL_Event       event;
	int             quit;
	int             h;
	int             w;
	int				fd;
	int             exit;
	int				x;
	int				i;
	double			posX;
	double			posY;  //x and y start position
	double			dirX;
	double			dirY; //initial direction vector
	double			planeX;
	double			planeY; //the 2d raycaster version of camera plane
	double			time; //time of current frame
	double			oldTime; //time of previous frame
	char			*line;
	int				**map;
}					t_var;

typedef struct		s_ray
{
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side; //was a NS or a EW wall hit?
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
}					t_ray;

typedef struct		s_mov
{
	double		frameTime;
	double		moveSpeed;
	double		rotSpeed;
	double		oldDirX;
	double		oldPlaneX;
}					t_mov;
#endif
