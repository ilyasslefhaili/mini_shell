/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:53:04 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/29 14:53:54 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
/* excutes cmd if exits and reads the input
    from stdin until the delimeter is found; */

void	read_for_herdoc(int *fd, t_commande *cmd)
{
	char	*result;

	pipe(fd);
	while (1)
	{
		result = readline(">");
		if (result == NULL || ft_strcmp(result, cmd->redi->first_token->value) == 0)
			break ;
		ft_putendl_fd(result, fd[1]);
	}
}

void	ft_close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	ft_herdoc(t_commande *cmd, char **env, t_list *env_list)
{
	int		temp_fd;
	int		fd[2];
	int 	temp1;
	int		temp2;

	temp1 = dup(STDOUT_FILENO);
	temp2 = dup(STDIN_FILENO);
	fprintf(stdin, "temp1 %d temp2 %d\n", temp1, temp2);
	read_for_herdoc(fd, cmd);
	if (cmd->flags[0] == NULL)
		return ;
	dup2(fd[0], STDIN_FILENO);
	if (cmd->redi->first_token != NULL)
	{
		if (cmd->redi->first_token->token == T_OUT)
			temp_fd = open(cmd->redi->first_token->value, O_CREAT | O_RDWR | \
				O_TRUNC, 0644);
		else
			temp_fd = open(cmd->redi->first_token->value, O_CREAT | O_RDWR | \
				O_APPEND, 0644);
		dup2(temp_fd, STDOUT_FILENO);
	}
	ft_close_fd(fd);
	if (fork() == 0)
	{
		execve(get_path(env_list, cmd->flags[0]), cmd->flags, env);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	ft_close_fd(fd);
	dup2(temp2,STDIN_FILENO);
	dup2(temp1,STDOUT_FILENO);
}

// redirect the output of cmd to file with file being overriten;
void	ft_redirect_output(t_commande *cmd, char **env, t_list *env_list)
{
	int		fd;
	char	*path;

	fd = open_output_files(cmd);
	if (fd == -1)
		perror("Error: ");
	else if (cmd->flags[0] == NULL)
		return ;
	else
	{
		if (fork() == 0)
		{
			path = get_path(env_list, cmd->flags[0]);
			if (path == NULL)
				perror("Error: ");
			else
			{
				dup2(fd, STDOUT_FILENO);
				execve(path, cmd->flags, env);
			}
			close(fd);
			exit(EXIT_SUCCESS);
		}
		wait(NULL);
	}
}

// append the output of cmd to file;
void	ft_redirect_output_2(t_commande *cmd, char **env, t_list *env_list)
{
	int		fd;
	char	*path;

	fd = open(cmd->redi->first_token->value, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (cmd->flags[0] == NULL)
		return ;
	else
	{
		if (fork() == 0)
		{
			path = get_path(env_list, cmd->flags[0]);
			if (path == NULL)
				perror("Error: ");
			else
			{
				dup2(fd, STDOUT_FILENO);
				execve(path, cmd->flags, env);
			}
			close(fd);
			exit(EXIT_SUCCESS);
		}
		else
			wait(NULL);
	}
}

void	redirect_input(t_commande *cmd, char **env, t_list *env_list)
{
	int		fd;
	char	*path;

	if (cmd->redi->first_token->value == NULL)
		return ;
	fd = open_input_files(cmd);
	if (fd == -1)
		perror(NULL);
	if (cmd->flags[0] != NULL)
	{
		path = get_path(env_list, cmd->flags[0]);
		if (path == NULL)
			printf("Command Not Found\n");
		else
		{
			if (fork() == 0)
			{
				dup2(fd, STDIN_FILENO);
				ft_execute(cmd->flags, env, env_list);
				exit(EXIT_SUCCESS);
			}
			close(fd);
			wait(NULL);
		}
	}
}
