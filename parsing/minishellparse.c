/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellparse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 12:52:46 by ilefhail          #+#    #+#             */
/*   Updated: 2022/05/19 15:18:37 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_init_head(t_head_c *head)
{
	head->first_c = NULL;
	head->taille = 0;
}

void	ft_add_red(t_token_head *head, t_token *t)
{
	t_token	*temp;

	temp = head->first_token;
	if (temp == NULL)
	{
		head->first_token = t;
		return;
	}
	while (temp->next)
		temp = temp->next;
	temp->next = t;
}

void	ft_add_node(t_head_c *head, t_commande *commande)
{
	t_commande	*temp;

	temp = head->first_c;
	if (temp == NULL)
	{
		head->first_c = commande;
		commande->next_comande = NULL;
		return;
	}
	while (temp->next_comande)
		temp = temp->next_comande;
	temp->next_comande = commande;
	commande->next_comande = NULL;
}

void ft_free(t_head_c *head)
{
	t_commande	*temp;

	while (head->first_c != NULL)
	{
		temp = head->first_c;
		head->first_c = head->first_c->next_comande;
		free(temp);
	}
}

void	ft_add_commande(t_head_c *head, t_lexer *lexer)
{
	t_token		*token;
	int			j;
	t_commande	*re;
	char **temp;
	int i;
	int e;
	int k = 0;

	e = 0;
	j = 0;
	i = 1;
	re = malloc(sizeof(t_commande));
	re->input = malloc(sizeof(t_token_head));
	re->input->first_token = NULL;
	re->output = malloc(sizeof(t_token_head));
	re->output->first_token = NULL;
	re->flags = malloc(sizeof(char *));
	re->flags[0] = NULL;
	token = ft_get_next_token(lexer);
	while (token)
	{
		if (token->token == 0)
		{
			if (token->value == NULL)
			{
				printf("minishell:syntax error\n");
				ft_free(head);
				return ;
			}
			temp = malloc(sizeof(char *) * (i + 1));
			e = 0;
			while (e < i - 1)
			{
				temp[e] = re->flags[e];
				e++;
			}	
			i++;
			temp[e] = token->value;
			temp[e + 1] = NULL;
			free(re->flags);
			re->flags = temp;
		}
		else if (token->token == 2 || token->token == 4)
		{
			if (token->value == NULL)
			{
				printf("minishell:syntax error\n");
				ft_free(head);
				return ;
			}
			ft_add_red(re->output, token);
		}
		else if (token->token == 3 || token->token == 1)
		{
			if (token->value == NULL)
			{
				printf("minishell:syntax error\n");
				ft_free(head);
				return ;
			}
			ft_add_red(re->input, token);
		}
		else if (token->token == 5)
		{
			free(token);
			ft_skip_spaces(lexer);
			if (lexer->content[lexer->i] == '\0' || k == 0)
			{
				printf("minishell:syntax error\n");
				ft_free(head);
				return ;
			}
			break ;
		}
		k++;
		token = ft_get_next_token(lexer);
	}
	ft_add_node(head, re);
}

t_head_c	*ft_get_for_exec(char *content)
{
	t_head_c	*head_of_commande;
	int			i;
	t_lexer		*lexer;

	head_of_commande = malloc(sizeof(t_head_c));
    ft_init_head(head_of_commande);
	i = 0;
	lexer = ft_init_lexer(content);
	while (lexer->content[lexer->i])
	{
		ft_add_commande(head_of_commande, lexer);
		if (head_of_commande->first_c == NULL)
			return (NULL);
	}
	return (head_of_commande);
}
