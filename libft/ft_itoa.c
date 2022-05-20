/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 13:06:34 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/15 15:19:41 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	calcul(int n)
{
	int				j;
	unsigned int	e;

	j = 1;
	if (n < 0)
	{
		e = (unsigned int)(n * (-1));
		j++;
	}
	else
		e = (unsigned int)(n);
	while (e >= 10)
	{
		e = e / 10;
		j++;
	}
	return (j);
}

static void	done(int len, char *str, int n)
{
	int				sign;
	unsigned int	e;

	sign = 0;
	if (n < 0)
	{
		sign = 1;
		e = (unsigned int)(n * -1);
		str[0] = '-';
	}
	else
		e = (unsigned int)n;
	str[len] = '\0';
	len = len - 1;
	while (len >= sign)
	{
		str[len] = e % 10 + '0';
		e = e / 10;
		len--;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	len = calcul(n);
	str = malloc (sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	done(len, str, n);
	return (str);
}
