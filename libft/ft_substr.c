/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:37:18 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/19 18:48:50 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	done(int start, const char	*s, char *str, size_t len)
{
	size_t	j;
	int		i;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (i == start)
		{
			while (j < len && s[i])
			{
				str[j] = s[i];
				j++;
				i++;
			}
			str[j] = '\0';
			break ;
		}
		i++;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	str = malloc(sizeof (char) * len + 1);
	if (str == NULL)
		return (NULL);
	done(start, s, str, len);
	return (str);
}
