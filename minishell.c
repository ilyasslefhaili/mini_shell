/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 12:08:28 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/29 16:43:37 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_variable(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=' && i - 1 >= 0 && s[i - 1] != '=')
			return (true);
		i++;
	}
	return (false);
}

int	is_properly_named(char *s)
{
	return (ft_isalpha(s[0]) || s[0] == '_');
}

int	check_echo_flag(char *s)
{
	int	i;

	i = 0;
	if (s[i++] != '-')
		return (false);
	while (s[i])
	{
		if (s[i] != 'n')
			return (false);
		i += 1;
	}
	return (true);
}

char	*join_for_echo(t_list *env_list, char **s, char flag)
{
	int		i;
	char	*result;
	char	**temp;

	if (flag == 'n')
		i = 2;
	else
		i = 1;
	result = "";
	while (s[i])
	{
		if (ft_strcmp(s[i], "~") == 0)
		{
			if (ft_getenv(env_list, "HOME") != NULL)
			{
				temp = ft_split(ft_getenv(env_list, "HOME")->content, '=');
				if (temp[1] != NULL)
					result = ft_strjoin(result, temp[1]);
				free_2d_array(temp);	
			}
		}
		else
			result = ft_strjoin(result, s[i]);
		result = ft_strjoin(result, " ");
		i++;
	}
	result = ft_strtrim(result, " ");
	return (result);
}

void ft_exit(int exit_code, char flag)
{
	if (flag != 'p')
	{
		printf("exit\n");
		exit(exit_code);
	}
}

void	sig_handler(int sig)
{
	if (sig == SIGQUIT)
	{
		set_exit_code(131);
	}
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
		set_exit_code(130);
	}
}

int check_built_in_commands(t_commande *command, t_list *env_list, t_list *export_list, char flag)
{
	char	*temp;
	int		i;

	i = 0;
	if (command->flags[0] != NULL)
	{
		if (ft_strcmp(command->flags[0], "env") == 0)
		{
			ft_env(command, env_list);
			return (true);
		}
		else if (ft_strcmp(command->flags[0], "exit") == 0)
		{
			if (flag != 'p')
				ft_exit(EXIT_SUCCESS, '\0');
			return (true);
		}
		else if (ft_strcmp(command->flags[0], "cd") == 0)
		{
			ft_cd(command->flags[1], env_list);
			return (true);
		}
		else if (ft_strcmp(command->flags[0], "unset") == 0)
		{
			i = 0;
			while (command->flags[++i])
			{
				ft_unset(&env_list, command->flags[i]);
				ft_unset(&export_list, command->flags[i]);
			}
			return (true);
		}
		else if (ft_strcmp(command->flags[0], "export") == 0 || ft_strcmp(command->flags[0], "EXPORT") == 0)
		{
			i = 0;
			if (command->flags[1] == NULL)
				ft_export(command, export_list, NULL);
			else
			{
				while (command->flags[++i])
				{
					temp = ft_split(command->flags[i], '=')[0];
					if (!temp)
						break ;
					else if (is_properly_named(temp) == false)
						printf("export: not an identifier: %s\n", temp);
					else if (ft_getenv(env_list, temp) == NULL)
					{
						if (ft_getenv(export_list, temp) == NULL)
						{
							if (is_variable(command->flags[i]) && command->flags[i])
							{
								ft_export(command, export_list, command->flags[i]);
								ft_export(command, env_list, command->flags[i]);
							}
							else
								ft_export(command, export_list, command->flags[i]);
						}
						else
						{
							if (is_variable(command->flags[i]) && command->flags[i])
							{
								ft_unset(&export_list, temp);
								ft_export(command, export_list, command->flags[i]);
								ft_export(command, env_list, command->flags[i]);
							}
						}
					}
					else
					{
						ft_unset(&export_list, temp);
						ft_unset(&env_list, temp);
						ft_lstadd_back(&export_list, \
						ft_lstnew(ft_strdup(command->flags[i])));
						ft_lstadd_back(&env_list, \
						ft_lstnew(ft_strdup(command->flags[i])));
						sort_list(&export_list);
					}
				}
			}
			return (true);
		}
		else if (ft_strcmp(command->flags[0], "echo") == 0 || ft_strcmp(command->flags[0], "ECHO") == 0)
		{
			if (command->flags[1] == NULL)
				ft_echo(NULL, '0');
			else if ((check_echo_flag(command->flags[1]) == true))
				ft_echo(join_for_echo(env_list, command->flags, 'n'), 'n');
			else
				ft_echo(join_for_echo(env_list, command->flags, '\0'), '\0');
			return (true);
		}
		else
			return (false);
	}
	return (false);
}
void	exec_node(t_commande *command, char **env, t_list *env_list,
			t_list *export_list, int flag)
{
	int		i;

	i = 0;
	if (check_built_in_commands(command, env_list, export_list, flag) == false)
	{
		if (command->input->first_token != NULL)
		{
			// while (command->input->first_token)
			// {
				if (command->input->first_token->token == T_HERDOC)
					ft_herdoc(command, env, env_list);
				else
					redirect_input(command, env, env_list);
				// command->input->first_token = command->input->first_token->next;
			// }
		}
		else if (command->output->first_token != NULL)
		{
			if (command->output->first_token->token == T_OUT)
				ft_redirect_output(command, env, env_list);
			else
				ft_redirect_output_2(command, env, env_list);
		}
		else
			ft_execute(command->flags, env, env_list);
	}
}

void ft_pipe(t_commande *command, t_list *env_list, t_list *export_list, char **env, int size)
{
    int fd[2];
    int temp_fd;
    int i;
    int id;
    int ids[size];
    i = 0;
    while (i < size && command)
    {
        if (pipe(fd) == -1)
		{
            perror("pipe");
			return ;
		}
        id = fork();
		if (id == -1)
            perror("fork");
        else if (id == 0)
        {
			replace_symbol_by_val(command->flags, env_list);
            if (i == 0)
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                exec_node(command, env, env_list, export_list, 'p');
            }
            else if (i == size - 1)
            {
                close (fd[0]);
                close(fd[1]);
                dup2(temp_fd, STDIN_FILENO);
                exec_node(command, env, env_list, export_list, 'p');
            }
            else
            {
                close(fd[0]);
                dup2(fd[1], STDOUT_FILENO);
                dup2(temp_fd, STDIN_FILENO);
                exec_node(command, env, env_list, export_list, 'p');
            }
			exit(0);
        }
        ids[i] = id;
        temp_fd = dup(fd[0]);
        close(fd[0]);
        close(fd[1]);
        command = command->next_comande;
        i++;
    }
    close(temp_fd);
    while (--i >= 0)
        waitpid(ids[i], 0, 0);

}

void lower(char *s)
{
	while (*s)
	{
		*s = ft_tolower(*s);
		s++;
	}
}
void upper(char *s)
{
	while (*s)
	{
		*s = ft_toupper(*s);
		s++;
	}
}

void replace_symbol_by_val(char **s, t_list *env_list)
{
	int i;
	i = 0;
	(void)env_list;
	while (s[i])
	{
		if (ft_strcmp(s[i], "~") == 0)
		{
			free(s[i]);
			if (getenv("HOME") != NULL)
				s[i] = ft_strdup(getenv("HOME"));
		}
		i++;
	}
}

int open_output_files(t_commande *command)
{
	int fd;
	while (command->output->first_token != NULL)
	{
		if (command->output->first_token->token == T_OUT)
			fd = open(command->output->first_token->value, O_CREAT | O_RDWR | O_TRUNC , 0644);
		command->output->first_token = command->output->first_token->next;
	}
	return (fd);
}

int open_input_files(t_commande *command)
{
	int fd;
	while (command->input->first_token != NULL)
	{
		if (command->input->first_token->token == T_IN)
			fd = open(command->input->first_token->value, O_RDONLY , 0644);
		command->input->first_token = command->input->first_token->next;
	}
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	
	t_list		*env_list;
	t_list		*export_list;
	t_list		*temp_env_list;
	t_head_c	*command;
	char		*temp;
	char		*cmd;
	temp_env_list = ft_lstnew(ft_strdup(""));
	env_list = get_env_list(env);
	export_list = get_env_list(env);
	sort_list(&export_list);
	signal(SIGQUIT, sig_handler);
	signal(SIGINT, sig_handler);
	while (true)
	{
		cmd = get_promt();
		temp = cmd;
		if (cmd == NULL)
			exit(130);
		cmd = ft_strtrim(cmd, " ");
		free(temp);
		if (*cmd)
		{
			command = ft_get_for_exec(cmd, env_list);
			if (command != NULL)
			{
				replace_symbol_by_val(command->first_c->flags, env_list);
				if (command->first_c->next_comande != NULL)
				{
					ft_pipe(command->first_c, env_list, export_list, \
						env, command->taille+1);
				}
				else
					exec_node(command->first_c, env, env_list, export_list, '\0');
			}
			
		}
		free(cmd);
	}
}