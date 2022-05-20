/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 20:46:08 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/16 18:28:22 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	e;

	e = nb;
	if (e < 0)
	{
		write(fd, "-", 1);
		e *= -1;
	}
	if (e <= 9)
	{
		ft_putchar_fd(e + '0', fd);
	}
	else
	{
		ft_putnbr_fd(e / 10, fd);
		ft_putnbr_fd(e % 10, fd);
	}
}
