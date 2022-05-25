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
			return (ft_init_token(T_HERDOC, ft_get_value(lexer)));
		}
		else if (ft_strncmp(&lexer->content[lexer->i], ">>", 2) == 0)
		{
			ft_advance(lexer);
			ft_advance(lexer);
			return (ft_init_token(T_APPEND, ft_get_value(lexer)));
		}
		else if (lexer->c == '<')
		{
			ft_advance(lexer);
			return (ft_init_token(T_IN, ft_get_value(lexer)));
		}
		else if (lexer->c == '>')
		{
			ft_advance(lexer);
			return (ft_init_token(T_OUT, ft_get_value(lexer)));
		}
		else
			return (ft_init_token(T_WORD, ft_get_value(lexer)));
	}
	return (NULL);
}

// char	*ft_her_app(t_lexer *lexer)
// {
// 	char	*str;
// 	int		i;
// 	char	c;

// 	i = 0;
// 	ft_advance(lexer);
// 	ft_advance(lexer);
// 	ft_skip_spaces(lexer);
// 	if (lexer->c == '|' || lexer->c == '<' || lexer->c == '>' || lexer->c == ')' || lexer->c == '(')
// 	{
// 		write(2, "minishell: syntax error near unexpected token `", 48);
// 		if (lexer->content[lexer->i + 1] == lexer->c)
// 			write(2, &lexer->content[lexer->i], 2);
// 		else
// 			write(2, &lexer->c, 1);
// 		write(2, "'\n", 2);
// 		return (NULL);
// 	}
// 	// if (lexer->c == '"' || lexer->c == '\'')
// 	// 	return (ft_collect_string(lexer));
// 	c = ' ';
// 	str = malloc(sizeof(char) * ft_count_str_for_value(&lexer->content[lexer->i], c) + 1);
// 	while (lexer->content[lexer->i] && lexer->c != c && lexer->c != '|' && lexer->c != '<' && lexer->c != '>')
// 	{
// 		str[i] = lexer->content[lexer->i];
// 		i++;
// 		ft_advance(lexer);
// 	}
// 	if (lexer->c == c)
// 		ft_advance(lexer);
// 	str[i] = '\0';
// 	return (str);
// }

// char	*get_str(t_lexer *lexer)
// {
// 	char	*str;
// 	int		i;
// 	char	c;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	c = ' ';
// 	str = malloc(sizeof(char) * ft_count_str(&lexer->content[lexer->i], ' ') + 1);
// 	while (lexer->content[lexer->i] && lexer->c != c && lexer->c != '|' && lexer->c != '<' && lexer->c != '>')
// 	{
// 		str[i] = lexer->content[lexer->i];
// 		if (lexer->c == '"' && j == 0)
// 		{
// 			c = '"';
// 			j++;
// 		}
// 		else if (lexer->c == '\'' && j == 0)
// 		{
// 			c = '\'';
// 			j++;
// 		}
// 		i++;
// 		ft_advance(lexer);
// 	}
// 	str[i] = '\0';
// 	return (str);
// }

// char	*ft_collect_string(t_lexer *lexer)
// {
// 	char	*str;
// 	char	c;
// 	int		i;

// 	i = 0;
// 	c = lexer->c;
// 	while (lexer->c == c)
// 		ft_advance(lexer);
// 	str = malloc(sizeof(char) * ft_count_str_for_value(&lexer->content[lexer->i], c) + 1);
// 	while (lexer->c != c && lexer->content[lexer->i])
// 	{
// 		str[i] = lexer->c;
// 		i++;
// 		ft_advance(lexer);
// 	}
// 	if (lexer->c != c)
// 	{
// 		printf("minishell: syntax error\n");
// 		return (NULL);
// 	}
// 	str[i] = '\0';
// 	while (lexer->c == c)
// 		ft_advance(lexer);
// 	return (str);
// }

// int ft_count_str_for_value(char *content, char c)
// {
// 	int	i;

// 	i = 0;
// 	if (c == '\'' || c == '"')
// 	{
// 		while(content[i] && c != content[i])
// 			i++;
// 	}
// 	else
// 	{
// 		while (content[i] && content[i] != c && content[i] != '|' && content[i] != '<' && content[i] != '>')
// 			i++;
// 	}
// 	return (i);
// }

// int ft_count_str(char *content, char c)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (content[i] && content[i] != c && content[i] != '|' && content[i] != '<' && content[i] != '>')
// 	{
// 		if (content[i] == '"' && j == 0)
// 		{
// 			c = '"';
// 			j++;
// 		}
// 		else if (content[i] == '\'' && j == 0)
// 		{
// 			c = '\'';
// 			j++;
// 		}
// 		else
// 			i++;
// 	}
// 	return (i);
// }

// char *ft_get_value(t_lexer *lexer)
// {
// 	char	*str;
// 	int		i;
// 	char	c;

// 	i = 0;
// 	ft_advance(lexer);
// 	ft_skip_spaces(lexer);
// 	// if (lexer->c == '"' || lexer->c == '\'')
// 	// 	return (ft_collect_string(lexer));
// 	if (lexer->c == '|' || lexer->c == '<' || lexer->c == '>' || lexer->c == ')' || lexer->c == '(')
// 	{
// 		write(2, "minishell: syntax error near unexpected token `", 48);
// 		if (lexer->content[lexer->i + 1] == lexer->c)
// 			write(2, &lexer->content[lexer->i], 2);
// 		else
// 			write(2, &lexer->c, 1);
// 		write(2, "'\n", 2);
// 		return (NULL);
// 	}
// 	c = ' ';
// 	str = malloc(sizeof(char) * ft_count_str_for_value(&lexer->content[lexer->i], c) + 1);
// 	while (lexer->content[lexer->i] && lexer->c != c && lexer->c != '|' && lexer->c != '<' && lexer->c != '>')
// 	{
// 		str[i] = lexer->content[lexer->i];
// 		i++;
// 		ft_advance(lexer);
// 	}
// 	str[i] = '\0';
// 	if (lexer->c  == c)
// 		ft_advance(lexer);
// 	return (str);
// }
char	*ft_get_value(t_lexer *lexer)
{
	char *str;
	char *temp;

	str = ft_strdup("");
	ft_skip_spaces(lexer);
	while (lexer->content[lexer->i] && lexer->c != ' ' && lexer->c != '>' && lexer->c != '<' && lexer->c != '|')
	{
		if (lexer->c == '\'')
		{
			temp = str;
			str = ft_strjoin(str, ft_collect_string(lexer, '\''));
			free(temp);
			ft_advance(lexer);
		}
		else if (lexer->c == '"')
		{
			temp = str;
			str = ft_strjoin(str, ft_collect_string(lexer, '"'));
			free(temp);
			ft_advance(lexer);
		}
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

	str = ft_strdup("");
	while (lexer->content[lexer->i] && lexer->c != ' ' && lexer->c != '\'' && lexer->c != '"' && lexer->c != '>' && lexer->c != '<' && lexer->c != '|')
	{
		temp = str;
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

	str = ft_strdup("");
	while(lexer->content[lexer->i] && lexer->c != c)
	{
		temp = str;
		str = ft_strjoin(str, &lexer->c);
		free(temp);
		ft_advance(lexer);
	}
	return (str);
}
