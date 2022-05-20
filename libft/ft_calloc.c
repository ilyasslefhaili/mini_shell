/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 14:39:15 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/15 16:09:15 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int		i;
	void	*dest;

	i = 0;
	dest = malloc(count * size);
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, count * size);
	return (dest);
}
