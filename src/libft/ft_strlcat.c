/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnxele <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 09:10:23 by vnxele            #+#    #+#             */
/*   Updated: 2017/06/10 03:24:21 by vnxele           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	s_dst;
	size_t	s_src;

	s_dst = ft_strlen(dst);
	s_src = ft_strlen((char *)src);
	if (s_dst > size)
		return (size + s_src);
	ft_strncat(dst, src, size - s_dst - 1);
	return (s_dst + s_src);
}
