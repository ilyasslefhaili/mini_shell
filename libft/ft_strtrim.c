/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:33:01 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/19 19:11:46 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_cmp(const char	*s, char c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

static void	done(int i, int len, char *str, const char *s1)
{
	int	j;

	j = 0;
	while (j <= len)
	{
		str[j++] = s1[i++];
	}
	str[j] = '\0';
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		len;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i] != '\0' && ft_cmp(set, s1[i]) != 1)
		i++;
	j = ft_strlen(s1) - 1;
	while (j >= 0 && ft_cmp(set, s1[j]) != 1)
		j--;
	len = j - i;
	if (len < 0)
		len = 0;
	str = malloc(sizeof (char) * (len + 2));
	if (!str)
		return (NULL);
	done(i, len, str, s1);
	return (str);
}
