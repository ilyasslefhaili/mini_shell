/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:42:10 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/15 16:12:52 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*p;
	size_t			i;
	unsigned char	*k;
	unsigned char	e;

	i = 0;
	p = (unsigned char *) s;
	e = (unsigned char) c;
	while (i < n)
	{
		if (p[i] == e)
		{
			k = &p[i];
			return (k);
		}
		i++;
	}
	return (NULL);
}
