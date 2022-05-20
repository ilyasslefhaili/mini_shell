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

void	ft_add_commande(t_head_c *head, t_lexer *lexer)
{
	t_token		*token;
	int			j;
	t_commande	*re;
	char **temp;
	int i = 1;
	int e;

	e = 0;
	j = 0;
	re = malloc(sizeof(t_commande));
	re->input = NULL;
	re->output = NULL;
	re->flags = malloc(sizeof(char *));
	re->flags[0] = NULL;
	token = ft_get_next_token(lexer);
	while (token)
	{
		if (token->token == 0)
		{
			temp = malloc(sizeof(char *) * (i + 2));
			if (e > 0)
			{
				e = 0;
				while (e < i)
				{
					temp[e] = re->flags[e];
					e++;
				}
				i++;
			}
			temp[e] = token->value;
			temp[e + 1] = NULL;
			free(re->flags);
			re->flags = temp;
			e++;
		}
		else if (token->token == 2 || token->token == 4)
			re->output = token;
		else if (token->token == 3 || token->token == 1)
			re->input = token;
		else if (token->token == 5)
		{
			free(token);
			break ;
		}
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
		ft_add_commande(head_of_commande, lexer);
	return (head_of_commande);
}

// int main(int ac, char **av)
// {
// 	t_head_c *l;

// 	ac = 0;
// 	(void)av;
// 	char *cmd;
// 	while (1)
// 	{
// 		cmd = readline("Minishell$>");
// 		l = ft_get_for_exec(cmd);
// 		while (l->first_c)
// 		{
// 			printf("%s    ", l->first_c->commande);
// 			if (l->first_c->input)
// 				printf("%s  ", l->first_c->input->value);
// 			if (l->first_c->output)
// 				printf("%s", l->first_c->output->value);
// 			l->first_c = l->first_c->next_comande;
// 			printf("\n");
// 		}
// 	}
// }
