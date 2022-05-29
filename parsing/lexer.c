/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:57:34 by ilefhail          #+#    #+#             */
/*   Updated: 2022/05/19 12:04:58 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_lexer	*ft_init_lexer(char *content)
{
	t_lexer	*lexer;

	lexer = ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->content = content;
	lexer->i = 0;
	lexer->c = content[0];
	return (lexer);
}

void	ft_advance(t_lexer	*lexer)
{
	if (lexer->i < ft_strlen(lexer->content))
	{
		lexer->i += 1;
		lexer->c = lexer->content[lexer->i];
	}
}

void	ft_skip_spaces(t_lexer	*lexer)
{
	while (lexer->content[lexer->i] == ' ' && lexer->content[lexer->i] != '\0')
		ft_advance(lexer);
}

t_token	*ft_get_next_token(t_lexer *lexer)
{
	while (lexer->i < ft_strlen(lexer->content))
	{
		if (lexer->c == ' ')
			ft_skip_spaces(lexer);
		else if (lexer->c == '|')
		{
			ft_advance(lexer);
			ft_skip_spaces(lexer);
			return (ft_init_token(T_PIPE, ""));
		}
		else if (lexer->c == '"' || lexer->c == '\'')
			return (ft_init_token(T_WORD, ft_get_value(lexer)));
		else if (ft_strncmp(&lexer->content[lexer->i], "<<", 2) == 0)
		{
			ft_advance(lexer);
			ft_advance(lexer);
			ft_skip_spaces(lexer);
			if (lexer->content[lexer->i] == '\0')
				return (ft_init_token(T_HERDOC, NULL));
			return (ft_init_token(T_HERDOC, ft_get_value(lexer)));
		}
		else if (ft_strncmp(&lexer->content[lexer->i], ">>", 2) == 0)
		{
			ft_advance(lexer);
			ft_advance(lexer);
			ft_skip_spaces(lexer);
			if (lexer->content[lexer->i] == '\0')
				return (ft_init_token(T_HERDOC, NULL));
			return (ft_init_token(T_APPEND, ft_get_value(lexer)));
		}
		else if (lexer->c == '<')
		{
			ft_skip_spaces(lexer);
			if (lexer->content[lexer->i] == '\0')
				return (ft_init_token(T_HERDOC, NULL));
			return (ft_init_token(T_IN, ft_get_value(lexer)));
		}
		else if (lexer->c == '>')
		{
			ft_advance(lexer);
			ft_skip_spaces(lexer);
			if (lexer->content[lexer->i] == '\0')
				return (ft_init_token(T_HERDOC, NULL));
			return (ft_init_token(T_OUT, ft_get_value(lexer)));
		}
		else
			return (ft_init_token(T_WORD, ft_get_value(lexer)));
	}
	return (NULL);
}


char	*ft_get_value(t_lexer *lexer)
{
	char	*str;
	char	*temp;
	char	*s;

	str = ft_strdup("");
	ft_skip_spaces(lexer);
	while (lexer->content[lexer->i] && lexer->c != ' ' && lexer->c != '>' && lexer->c != '<' && lexer->c != '|')
	{
		if (lexer->c == '\'')
		{
			temp = str;
			s = ft_collect_string(lexer, '\'');
			if (s == NULL)
				return (NULL);
			str = ft_strjoin(str, s);
			free(temp);
			free(s);
			ft_advance(lexer);
		}
		else if (lexer->c == '"')
		{
			temp = str;
			s = ft_collect_string(lexer, '"');
			if (s == NULL)
				return (NULL);
			str = ft_strjoin(str, s);
			free(temp);
			free(s);
			ft_advance(lexer);
		}
		else if (lexer->i < ft_strlen(lexer->content) - 1 && lexer->c == '$' && (lexer->content[lexer->i + 1] == '\'' || lexer->content[lexer->i + 1] == '"'))
			ft_advance(lexer);
		else
		{
			temp = str;
			str = ft_strjoin(str, ft_get_str_without_quote(lexer));
			free(temp);
		}
	}
	return(str);
}

char	*ft_get_str_without_quote(t_lexer *lexer)
{
	char	*str;
	char	*temp;
	char	*s;

	str = ft_strdup("");
	s = ft_strdup("");
	while (lexer->content[lexer->i] && lexer->c != ' ' && lexer->c != '\'' && lexer->c != '"' && lexer->c != '>' && lexer->c != '<' && lexer->c != '|')
	{
		if (lexer->c == '$' && lexer->i < ft_strlen(lexer->content) - 1 && lexer->content[lexer->i + 1] != ' ')
		{
			ft_advance(lexer);
			if (lexer->c == '?')
			{
				temp = str;
				str = ft_strjoin(str, "0");
				free(temp);
				ft_advance(lexer);
			}
			else
			{
				while (lexer->content[lexer->i] && lexer->c != ' ' && lexer->c != '$' && lexer->c != '\'' && lexer->c != '"' && lexer->c != '?' && 
						lexer->c != '!' && (ft_isalnum(lexer->c) != 0 || ft_isalpha(lexer->c) != 0))
				{
					temp = s;
					s = ft_strjoin(s, &lexer->c);
					free(temp);
					ft_advance(lexer);
				}
				if (getenv(s))
				{
					temp = str;
					str = ft_strjoin(str, getenv(s));
					free(temp);
				}
				else
				{
					temp = str;
					str = ft_strjoin(str, "\n");
					free(temp);
				}
			}
		}
		temp = str;
		if (lexer->c == '"' || lexer->c == '\'')
			break ;
		str = ft_strjoin(str, &lexer->c);
		free(temp);
		ft_advance(lexer);
	}
	return(str);
}

char	*ft_collect_string(t_lexer *lexer, char c)
{
	char	*str;
	char	*temp;
	char	*s;

	str = ft_strdup("");
	s = ft_strdup("");
	ft_advance(lexer);
	while(lexer->content[lexer->i] && lexer->c != c)
	{
		if (c == '"' && lexer->c == '$' && lexer->i < ft_strlen(lexer->content) - 1 && lexer->content[lexer->i + 1] != ' ')
		{
			ft_advance(lexer);
			if (lexer->c == '?')
			{
				temp = str;
				str = ft_strjoin(str, "0");
				free(temp);
				ft_advance(lexer);
			}
			else
			{
				while (lexer->content[lexer->i] && lexer->c != ' ' && lexer->c != '$' && lexer->c != '\'' && lexer->c != '"' && lexer->c != '?' && 
							lexer->c != '!' && (ft_isalnum(lexer->c) != 0 || ft_isalpha(lexer->c) != 0))
				{
					temp = s;
					s = ft_strjoin(s, &lexer->c);
					free(temp);
					ft_advance(lexer);
				}
				if (getenv(s))
				{
					temp = str;
					str = ft_strjoin(str, getenv(s));
					free(temp);
				}
				else
				{
					temp = str;
					str = ft_strjoin(str, "\n");
					free(temp);
				}
			}
		}
		else
		{
			temp = str;
			str = ft_strjoin(str, &lexer->c);
			free(temp);
			ft_advance(lexer);
		}
	}
	if (lexer->c != c)
		return (NULL);
	return (str);
}
