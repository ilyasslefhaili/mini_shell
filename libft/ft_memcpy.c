/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:06:58 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/15 11:38:44 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void	*dest, const void	*src, size_t	n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*p;

	t = (unsigned char *) dest;
	p = (unsigned char *) src;
	i = 0;
	if (!p && !t)
		return (t);
	while (i < n)
	{
		t[i] = p[i];
		i++;
	}
	return (t);
}
