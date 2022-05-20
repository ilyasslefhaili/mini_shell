/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:49:47 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/19 20:01:43 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lendest;
	size_t	lensrc;

	lensrc = ft_strlen(src);
	i = 0;
	lendest = ft_strlen(dest);
	if (lendest >= dstsize)
		return (lensrc + dstsize);
	while (i < dstsize - lendest - 1 && src[i] != '\0')
	{
		dest[lendest + i] = src[i];
		i++;
	}
	dest[lendest + i] = '\0';
	return (lendest + lensrc);
}
