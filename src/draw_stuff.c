#include <header.h>

int	draw_horizontal_line(SDL_Renderer *ren, int x1, int x2, int y)
{
	int	i;

	i = 0;
	while (x1 < x2)
		i += SDL_RenderDrawPoint(ren, x1++, y);
	while (x2 < x1)
		i += SDL_RenderDrawPoint(ren, x2++, y);
	return (i == 0);
}

int	draw_vertical_line(SDL_Renderer *ren, int x, int y1, int y2)
{
	int	i;

	i = 0;
	while (y1 < y2)
		i += SDL_RenderDrawPoint(ren, x, y1++);
	while (y2 < y1)
		i += SDL_RenderDrawPoint(ren, x, y2++);
	return (i == 0);
}

int	draw_box(SDL_Renderer *ren, int x1, int x2, int y1, int y2)
{
	int i;

	i = draw_horizontal_line(ren, x1, x2, y1);
	i += draw_horizontal_line(ren, x1, x2, y2);
	i += draw_vertical_line(ren, x1, y1, y2);
	i += draw_vertical_line(ren, x2, y1, y2);
	return (i == 0);
}

int draw_block(SDL_Renderer *ren, int x1, int x2, int y1, int y2)
{
	int i;

	i = 0;
	while (y1 < y2)
		i += draw_horizontal_line(ren, x1, x2, y1++);
	while (y2 < y1)
		i += draw_horizontal_line(ren, x1, x2, y2++);
	return (i);
}

void	draw_line(SDL_Renderer *ren, int x1, int y1, int x2, int y2)
{
	double	slope;
	double	offset;
	int		iterate;
	int		*a;
	int		*b;

	slope = 0;
	offset = 0;
	if (abs(x1 - x2) >= abs(y1 - y2))
	{
		a = &x1;
		b = &y1;
	}
	else
	{
		swap(&x1, &y1);
		swap(&x2, &y2);
		a = &y1;
		b = &x1;
	}
		iterate = -1 + (2 * (x1 < x2));
		slope = ((double)abs(y1 - y2) / (double)abs(x1 - x2)) * (-1 + (2 * (y1 < y2)));
		while (x1 != x2)
		{
			if (offset >= 0.49999 || offset <= -0.5)
			{
				offset -= -1 + (2 * (y1 < y2));
				y1 += -1 + (2 * (y1 < y2));
			}
			SDL_RenderDrawPoint(ren, *a, *b);
			x1 += iterate;
			offset += slope;
		}
}
