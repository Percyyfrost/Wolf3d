#ifndef HEADER_H
# define HEADER_H

/*
**	Global includes:
*/

#include <SDL.h>

/*
**	Drawing functions:
*/

int		draw_horizontal_line(SDL_Renderer *ren, int x1, int x2, int y);
int		draw_vertical_line(SDL_Renderer *ren, int x, int y1, int y2);
int		draw_box(SDL_Renderer *ren, int x1, int x2, int y1, int y2);
int		draw_block(SDL_Renderer *ren, int x1, int x2, int y1, int y2);
void	draw_line(SDL_Renderer *ren, int x1, int y1, int x2, int y2);

/*
**	Miscelaneous functions:
*/

int		abs(int n);
void	swap(int *n1, int *n2);

#endif
