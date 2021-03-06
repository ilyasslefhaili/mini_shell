/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:57:34 by ilefhail          #+#    #+#             */
/*   Updated: 2022/05/29 16:39:44 by ytouate          ###   ########.fr       */
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

t_token	*ft_red(t_lexer *lexer, t_list *env_list)
{
	if (lexer->c == '<')
	{
		ft_skip_spaces(lexer);
		ft_advance(lexer);
		if (lexer->content[lexer->i] == '\0' || lexer->c == '<' || lexer->c == '>')
			return (ft_init_token(T_IN, NULL));
		return (ft_init_token(T_IN, ft_get_value(lexer, env_list)));
	}
	else
	{
		ft_advance(lexer);
		ft_skip_spaces(lexer);
		if (lexer->content[lexer->i] == '\0' || lexer->c == '<' || lexer->c == '>')
			return (ft_init_token(T_OUT, NULL));
		return (ft_init_token(T_OUT, ft_get_value(lexer, env_list)));
	}
}

t_token	*ft_her_app(t_lexer *lexer, t_list *env_list)
{
	if (ft_strncmp(&lexer->content[lexer->i], "<<", 2) == 0)
	{
		ft_advance(lexer);
		ft_advance(lexer);
		ft_skip_spaces(lexer);
		if (lexer->content[lexer->i] == '\0' || lexer->c == '<' || lexer->c == '>')
			return (ft_init_token(T_HERDOC, NULL));
		return (ft_init_token(T_HERDOC, ft_get_value(lexer, env_list)));
	}
	else
	{
		ft_advance(lexer);
		ft_advance(lexer);
		ft_skip_spaces(lexer);
		if (lexer->content[lexer->i] == '\0' || lexer->c == '<' || lexer->c == '>')
			return (ft_init_token(T_APPEND, NULL));
		return (ft_init_token(T_APPEND, ft_get_value(lexer, env_list)));
	}
}

t_token	*ft_get_next_token(t_lexer *lexer, t_list *env_list)
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
			return (ft_init_token(T_WORD, ft_get_value(lexer, env_list)));
		else if (ft_strncmp(&lexer->content[lexer->i], "<<", 2) == 0 || ft_strncmp(&lexer->content[lexer->i], ">>", 2) == 0)
			return (ft_her_app(lexer, env_list));
		else if (lexer->c == '<' || lexer->c == '>')
			return(ft_red(lexer, env_list));
		else	
			return (ft_init_token(T_WORD, ft_get_value(lexer, env_list)));
	}
	return (NULL);
}

char	*ft_str_for_join(t_lexer *lexer, t_list *env_list)
{
	char	*s;

	if(lexer->c == '\'' || lexer->c == '"')
	{
		s = ft_collect_string(lexer, lexer->c, env_list);
		ft_advance(lexer);
		return (s);
	}
	else
		return (ft_get_str_without_quote(lexer, env_list));
}

char	*ft_get_value(t_lexer *lexer, t_list *env_list)
{
	char	*str;
	char	*temp;
	char	*s;

	str = ft_strdup("");
	ft_skip_spaces(lexer);
	while (lexer->content[lexer->i] && lexer->c != ' ' && lexer->c != '>' && lexer->c != '<' && lexer->c != '|')
	{
		if (lexer->i < ft_strlen(lexer->content) - 1 && lexer->c == '$' && (lexer->content[lexer->i + 1] == '\'' || lexer->content[lexer->i + 1] == '"'))
			ft_advance(lexer);
		else
		{
			s = ft_str_for_join(lexer, env_list);
			if (s == NULL)
				return (NULL);
			temp = str;
			str = ft_strjoin(str, s);
			free(temp);
		}
	}
	return(str);
}

char	*ft_after_dollar(t_lexer *lexer, t_list *env_list)
{
	char	*str;
	char	*s;

	ft_advance(lexer);
	if (lexer->c == '?')
	{
		str = ft_itoa(get_exit_code());
		ft_advance(lexer);
	}
	else if (ft_isdigit(lexer->c) != 0)
	{
		ft_advance(lexer);
		return (ft_strdup(""));
	}
	else
	{
		s = ft_strdup("");
		while (lexer->content[lexer->i] && lexer->c != ' ' && lexer->c != '$' && lexer->c != '\'' && lexer->c != '"' && lexer->c != '?' && 
				lexer->c != '!' && (ft_isalnum(lexer->c) != 0 || ft_isalpha(lexer->c) != 0))
		{
			str = s;
			s = ft_strjoin(s, &lexer->c);
			free(str);
			ft_advance(lexer);
		}
		if (ft_get_env_val(env_list, s))
			str = ft_get_env_val(env_list, s);
		else
			str = "";
	}
	return (str);
}

char		*ft_get_str(t_lexer *lexer, t_list *env_list)
{
	char	*str;

	if (lexer->c == '$' && lexer->i < ft_strlen(lexer->content) - 1 &&
		 (ft_isalnum(lexer->content[lexer->i + 1]) != 0|| ft_isalpha(lexer->content[lexer->i + 1]) != 0 || lexer->content[lexer->i + 1] == '?'))
		str = ft_after_dollar(lexer, env_list);
	else if (lexer->c == '\\' && lexer->i < ft_strlen(lexer->content) - 1)
	{
		ft_advance(lexer);
		str = &lexer->c;
		ft_advance(lexer);
	}
	else if (lexer->c == '\\' && lexer->i == ft_strlen(lexer->content) - 1)
		return (NULL);
	else
	{
		str = ft_strdup(&lexer->c);
		ft_advance(lexer);
	}
	return (str);
}

char	*ft_get_str_without_quote(t_lexer *lexer, t_list *env_list)
{
	char	*str;
	char	*temp;
	char	*s;

	str = ft_strdup("");
	while (lexer->content[lexer->i] && lexer->c != ' ' && lexer->c != '\'' && lexer->c != '"' && lexer->c != '>' && lexer->c != '<' && lexer->c != '|')
	{
		s = ft_strdup("");
		if (lexer->c == '&')
		{
			free(s);
			free(str);
			return (NULL);
		}
		temp = s;
		s = ft_get_str(lexer, env_list);
		if (s == NULL)
			return (NULL);
		temp = str;
		str = ft_strjoin(str, s);
		free(temp);
	}
	return(str);
}

char	*ft_collect_string(t_lexer *lexer, char c, t_list *env_list)
{
	char	*str;
	char	*temp;
	char	*s;

	str = ft_strdup("");
	ft_advance(lexer);
	while(lexer->content[lexer->i] && lexer->c != c)
	{
		s = ft_strdup("");
		if (c == '"' && lexer->c == '$' && lexer->i < ft_strlen(lexer->content) - 1 &&
				 (ft_isalnum(lexer->content[lexer->i + 1]) != 0|| ft_isalpha(lexer->content[lexer->i + 1]) != 0 || lexer->content[lexer->i + 1] == '?'))
		{
			temp = str;
			str = ft_strjoin(str, ft_after_dollar(lexer, env_list));
			free(temp);
		}
		else if (lexer->c == '\\' && lexer->i < ft_strlen(lexer->content) - 1 && (lexer->content[lexer->i + 1] == '\\' || lexer->content[lexer->i + 1] == c))
		{
			ft_advance(lexer);
			temp = str;
			str = ft_strjoin(str, &lexer->c);
			ft_advance(lexer);
		}
		else
		{
			temp = str;
			str = ft_strjoin(str, &lexer->c);
			free(temp);
			ft_advance(lexer);
			free(s);
		}
	}
	if (lexer->c != c)
		return (NULL);
	return (str);
}
