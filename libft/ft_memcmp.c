/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 19:50:58 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/15 11:36:44 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void	*s1, const void	*s2, size_t	n)
{
	unsigned char	*os;
	unsigned char	*ts;
	size_t			i;

	os = (unsigned char *) s1;
	ts = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (os[i] != ts[i])
			return (os[i] - ts[i]);
		i++;
	}
	return (0);
}
