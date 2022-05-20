/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 11:57:11 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/15 11:54:06 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(char	*src)
{
	char	*pstr;
	int		i;

	i = 0;
	pstr = malloc((ft_strlen(src) + 1) * sizeof (char));
	if (pstr == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		pstr[i] = src[i];
		i++;
	}
	pstr[i] = '\0';
	return (pstr);
}
