/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnxele <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 17:38:55 by vnxele            #+#    #+#             */
/*   Updated: 2017/11/29 17:39:08 by vnxele           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strnchr(const char *s, int c, size_t size)
{
	size_t					len;

	len = 0;
	while ((unsigned char)*s != (unsigned char)c && *s && len++ < size)
		(void)*s++;
	if ((!*s && c != 0) || len >= size)
		return (0);
	return ((char*)s);
}
