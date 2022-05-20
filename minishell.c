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

char **combine_flags_with_command(t_commande *command)
{
    char **result;
    if (command->flags[0] != '\0')
    {
        result = malloc(sizeof(char *) * 3);
        result[0] = ft_strdup(command->commande);
        result[1] = ft_strdup(command->flags);
        result[2] = NULL;
    }
    else
    {
        result = malloc(sizeof(char *) * 2);
        result[0] = ft_strdup(command->commande);
        result[1] = NULL;
    }
    return (result);
}
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    char **temp;
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
            temp = combine_flags_with_command(command->first_c);
            if (ft_strcmp(temp[0], "cd") == 0)
                ft_cd(temp[1], env_list);
            else if (ft_strcmp(temp[0], "export") == 0)
                ft_export(env_list, temp[1]);
            else if (ft_strcmp(temp[0], "unset") == 0)
                ft_unset(&env_list, temp[1]);
            else if (ft_strcmp(temp[0], "env") == 0)
                ft_env(env_list);
            else if (ft_strcmp(temp[0], "pwd") == 0)
                ft_pwd();
            else if (ft_strcmp(temp[0], "exit") == 0)
                exit(EXIT_SUCCESS);
            else
                ft_execute(arg, env, env_list);
        }
    }
}