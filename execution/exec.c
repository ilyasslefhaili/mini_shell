/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/29 15:46:21 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
int exit_code;

void set_exit_code(int num)
{
	while (num > 255)
		num -= 256;
	exit_code = num;
}

int get_exit_code()
{
	return (exit_code);
}
void	free_2d_array(char **a)
{
	int	i;

	i = 0;
	while (a[i])
		free(a[i++]);
	free(a);
}

// getting the promt from the stdout using readline function;
char	*get_promt(void)
{
	char	*cmd;

	cmd = readline("Minishell$> :");
	if (cmd && *cmd)
		add_history(cmd);
	return (cmd);
}

// gets the path of an command returns NULL if the path not found
char	*get_path(t_list *env_list, char *cmd)
{
	char	*path;
	char	**command_path;
	int		i;

	path = ft_get_env_val(env_list, "PATH");
	if (path == NULL)
		return (NULL);
	i = 0;
	command_path = ft_split(path, ':');
	while (command_path[i])
	{
		command_path[i] = ft_strjoin(command_path[i], "/");
		command_path[i] = ft_strjoin(command_path[i], cmd);
		if (access(command_path[i], F_OK) == 0)
			return (command_path[i]);
		i++;
	}
	return (NULL);
}

// check the command if it is an excutable
int	check_cmd(char **cmd, char **env)
{
	int status;
	if (cmd[0][0] == '/')
	{
		if (fork() == 0)
		{
			if (access(cmd[0], F_OK) == 0)
			{
				if (execve(cmd[0], cmd, env) == -1)
				{
					exit_code = 128;
					perror("execve");
				}
			}
			exit(EXIT_SUCCESS);
		}
		wait(&status);
		set_exit_code(status);
		return (0);
	}
	else
	{
		if (fork() == 0)
		{
			if (access(cmd[0], F_OK | X_OK) == 0)
			{
				if (execve(cmd[0], cmd, env) == -1)
				{
					exit_code = 126;
					perror("execve");
				}
			}
			exit(EXIT_SUCCESS);
		}		
		wait(&status);
		set_exit_code(status);
	}
	return (0);
}

// excutes commands
void	ft_execute(char **cmd, char **env, t_list *env_list)
{
	char	*command_path;
	int status;
	command_path = get_path(env_list, cmd[0]);

	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		check_cmd(cmd, env);
	else
	{
		if (command_path == NULL)
		{
			ft_putstr_fd("command not found\n", STDERR_FILENO);
			exit_code = 127;
			return ;
		}
		if (fork() == 0)
		{
			execve(command_path, cmd, env);
			exit(EXIT_SUCCESS);
		}
		wait(&status);
		set_exit_code(status);
	}
}

// like the built in strcmp
int	ft_strcmp(char *s, char *str)
{
	int	i;

	i = 0;
	while (s[i] || str[i])
	{
		if (s[i] != str[i])
			return (s[i] - str[i]);
		i++;
	}
	return (0);
}
