/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:09:03 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/15 16:13:26 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void	*pointer, int val, size_t len)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *) pointer;
	i = 0;
	while (i < len)
	{
		str[i] = val;
		i++;
	}
	return (pointer);
}
