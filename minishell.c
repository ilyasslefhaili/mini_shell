/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:08:28 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/20 09:34:47 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **combine_flags_with_command(t_commande *command)
// {
//     char **result;
//     if (command->flags[0] != '\0')
//     {
//         result = malloc(sizeof(char *) * 3);
//         result[0] = ft_strdup(command->commande);
//         result[1] = ft_strdup(command->flags);
//         result[2] = NULL;
//     }
//     else
//     {
//         result = malloc(sizeof(char *) * 2);
//         result[0] = ft_strdup(command->commande);
//         result[1] = NULL;
//     }
//     return (result);
// }

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;

    t_list *env_list;
    env_list = get_env_list(env);
    t_head_c *command;
    while(1)
    {
        char *cmd = get_promt();
        if (cmd == NULL)
            return 0;
        cmd = ft_strtrim(cmd, " ");
        if (*cmd)
        {
            command = ft_get_for_exec(cmd);
            if (command)
            {
                while (command->first_c)
                {
                    if (command->first_c->flags[0])
                    {
                        int i = 0;
                        while (command->first_c->flags[i] != NULL)
                        {
                            printf("%s  ", command->first_c->flags[i]);
                            i++;
                        }
                    }
                    if (command->first_c->output->first_token)
                    {
                        while(command->first_c->output->first_token)
                        {
                            printf("%s ",command->first_c->output->first_token->value);
                            command->first_c->output->first_token = command->first_c->output->first_token->next;
                        }
                    }
                    printf("\n");
                    command->first_c = command->first_c->next_comande;
                }
            }
        }
    }
}