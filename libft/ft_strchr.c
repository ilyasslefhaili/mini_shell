/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 11:34:10 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/15 16:10:17 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char			*reslt;
	char			*buuf;
	size_t			i;
	unsigned char	e;

	i = 0;
	e = (unsigned char) c;
	buuf = (char *) str;
	while (i < ft_strlen(str) + 1)
	{
		if (buuf[i] == e)
		{
			reslt = &buuf[i];
			return (reslt);
		}
		i++;
	}
	return (NULL);
}
