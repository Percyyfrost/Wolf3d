/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vnxele <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/11 15:23:10 by vnxele            #+#    #+#             */
/*   Updated: 2017/06/11 17:50:40 by vnxele           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t		i;
	size_t		len;
	char		*str;

	if (s == 0)
		return (0);
	i = 0;
	len = ft_strlen(s) - 1;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == '\t' || s[i] == '\n' || s[i] == ' ')
			i++;
		else if (s[len] == '\t' || s[len] == '\n' || s[len] == ' ')
			len--;
		else
			break ;
	}
	if (i == ft_strlen(s))
		return ("");
	str = ft_strsub(s, i, (len - i + 1));
	return (str);
}
