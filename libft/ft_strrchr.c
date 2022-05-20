/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:04:44 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/19 19:14:02 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*d;
	char	*f;

	i = ft_strlen(s);
	d = (char *)s;
	while (i >= 0)
	{
		if (d[i] == (char ) c)
		{
			f = &d[i];
			return (f);
		}
		i--;
	}
	return (NULL);
}
