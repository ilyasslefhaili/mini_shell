/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:53:13 by ilefhail          #+#    #+#             */
/*   Updated: 2021/11/16 11:07:32 by ilefhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	freetab(char **str, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void	allocationtab(char **split, const char *s, char c, int len)
{
	int	i;
	int	index;
	int	j;

	i = 0;
	j = 0;
	while (j < len - 1)
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		index = i;
		while (s[i] != c && s[i] != '\0')
			i++;
		split[j] = ft_substr(s, index, i - index);
		if (!split[j])
		{
			freetab(split, j);
			break ;
		}
		j++;
	}
	split[j] = NULL;
}

static int	strlen_str(const char	*s, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i] != '\0')
	{
		if ((s[0] != c && i == 0)
			|| (s[i] != c && s[i] != '\0' && s[i - 1] == c))
			len++;
		i++;
	}
	return (len);
}

char	**ft_split(char const *s, char c)
{
	int		len;
	char	**str;

	if (s == NULL)
		return (NULL);
	len = strlen_str(s, c) + 1;
	str = malloc(sizeof (char *) * len);
	if (str == NULL)
		return (NULL);
	allocationtab(str, s, c, len);
	return (str);
}
