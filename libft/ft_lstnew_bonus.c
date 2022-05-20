/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:34:04 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/19 18:46:11 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void	*content)
{
	t_list	*new;

	new = (t_list *) malloc(sizeof(t_list) * 1);
	if (!new)
		return (NULL);
	new -> next = NULL;
	new -> content = content;
	return (new);
}
