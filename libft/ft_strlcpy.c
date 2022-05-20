/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:10:28 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/19 20:01:51 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char	*dest, const char	*src, size_t	lent)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	if (lent == 0)
		return (ft_strlen(src));
	while (src[c] && c < lent - 1)
	{
		dest[c] = src[c];
		c++;
	}
	dest[c] = '\0';
	return (ft_strlen(src));
}
