#include "libft.h"

void			*ft_expandwrite(void *new, int newlen, void *src, int *srcsize)
{
	int				length;
	int				newlength;
	char			*newbuf;

	length = newlen;
	newlength = *srcsize + length;
	newbuf = (char*)malloc(newlength);
	ft_memcpy(newbuf, src, *srcsize);
	ft_memcpy(newbuf + *srcsize, new, newlen);
	*srcsize = newlength;
	if (src)
		free(src);
	return (newbuf);
}
