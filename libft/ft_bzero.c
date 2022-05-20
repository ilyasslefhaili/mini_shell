/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 14:07:36 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/15 16:11:05 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_bzero(void *str, size_t r)
{
	unsigned char	*pointer;
	size_t			i;

	i = 0;
	pointer = (unsigned char *)str;
	while (i < r)
	{
		pointer[i] = 0;
		i++;
	}
}
