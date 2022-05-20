/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 09:30:22 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/19 19:17:48 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char	*str, const char	*to_find, size_t	n)
{
	size_t	i;
	size_t	j;
	char	*c;
	size_t	a;

	c = NULL;
	i = 0;
	j = 0;
	if (*to_find == 0)
		return ((char *)str);
	while (to_find[i] != '\0')
		i++;
	a = i;
	while (str[j] != '\0' && a <= n)
	{
		if (ft_strncmp(to_find, &str[j], i) == 0)
		{
			c = (char *)&str[j];
			return (c);
		}
		a++;
		j++;
	}
	return (0);
}
