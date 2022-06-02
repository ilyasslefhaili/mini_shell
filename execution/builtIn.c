/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtIn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 16:46:18 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/27 14:53:12 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

// prints the current working directory;
void	ft_pwd(void)
{
	char	working_directory[PATH_MAX];

	getcwd(working_directory, sizeof(working_directory));
	printf("%s\n", working_directory);
}

void	delete_head(t_list **env_list, char **cmd)
{
	t_list	*temp;

	temp = *env_list;
	*env_list = (*env_list)->next;
	free(temp);
	free_2d_array(cmd);
}

// deletes a variable from the environment variables list being passed to it;
void	ft_unset(t_list **env_list, char *to_delete)
{
	t_list	*first;
	t_list	*second;
	t_list	*temp;
	char	**cmd;

	first = *env_list;
	cmd = ft_split((*env_list)->content, '=');
	if (cmd[0] == NULL)
		return ;
	else if (ft_strcmp(cmd[0], to_delete) == 0)
	{
		delete_head(env_list, cmd);
		return ;
	}
	else
	{
		second = first->next;
		while (second)
		{
			cmd = ft_split(second->content, '=');
			if (ft_strcmp(cmd[0], to_delete) == 0)
			{
				temp = second;
				first->next = second->next;
				free(temp);
				free_2d_array(cmd);
				return ;
			}
			free_2d_array(cmd);
			first = second;
			second = second->next;
		}
	}
}

void	cd_oldwd(t_list *env_list)
{
	char	current_wd[PATH_MAX];
	char	buffer[PATH_MAX];
	char	*temp_path;
	t_list	*old_wd;

	getcwd(current_wd, sizeof(current_wd));
	old_wd = ft_getenv(env_list, "OLDPWD");
	if (old_wd)
	{
		temp_path = ft_split(old_wd->content, '=')[1];
		if (chdir(temp_path) == -1)
			perror(temp_path);
		ft_setenv(&env_list, "OLDPWD", current_wd);
		getcwd(buffer, sizeof(buffer));
		ft_setenv(&env_list, "PWD", buffer);
	}
	else
		printf("OLDPWD not set\n");
}

void	cd_home(t_list *env_list)
{
	char	*home_path;
	char	current_wd[PATH_MAX];

	if (ft_getenv(env_list, "HOME") != NULL)
			home_path = ft_split(ft_getenv(env_list, "HOME")->content, '=')[1];
	else
	{
		write(2, "HOME not set\n", 14);
		return ;
	}
	if (home_path != NULL)
	{
		getcwd(current_wd, sizeof(current_wd));
		if (chdir(home_path) == -1)
			perror(home_path);
		ft_setenv(&env_list, "OLDPWD", current_wd);
	}
}

// like the cd command (change directory)
void	ft_cd(char *path, t_list *env_list)
{
	char	current_wd[PATH_MAX];

	if (path == NULL)
		path = ft_strdup("~");
	if (ft_strcmp("-", path) == 0)
		cd_oldwd(env_list);
	else if (ft_strcmp("~", path) == 0)
		cd_home(env_list);
	else
	{
		getcwd(current_wd, sizeof(current_wd));
		if (chdir(path) == -1)
			perror(path);
		ft_setenv(&env_list, "OLDPWD", current_wd);
	}
}

/* exports a varible to the env_list; when it is being called with
	no arguments it prints out the environment variables sorted; */

int check_for_redirection(t_commande *command)
{
	int	fd;

	fd = 1;
	if (command->redi->first_token != NULL)
	{
		if (command->redi->first_token->token == T_OUT)
			fd = open (command->redi->first_token->value, O_RDWR | O_CREAT \
				| O_TRUNC, 0644);
		else
			fd = open (command->redi->first_token->value, O_RDWR | O_CREAT \
				| O_APPEND, 0644);
	}
	return (fd);
}

void	ft_export(t_commande *command, t_list *env, char *arg)
{
	int	fd;

	fd = check_for_redirection(command);
	if (arg == NULL)
	{
		sort_list(&env);
		while (env)
		{
			ft_putstr_fd("declare -x\t", fd);
			ft_putendl_fd(env->content, fd);
			env = env->next;
		}
	}
	else
	{
		ft_lstadd_front(&env, ft_lstnew(arg));
		sort_list(&env);
	}
}

// prints the all the environment variables
void	ft_env(t_commande *command, t_list *env_list)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (command->redi->first_token != NULL)
	{
		if (command->redi->first_token->token == T_OUT)
			fd = open(command->redi->first_token->value, O_CREAT | O_WRONLY \
				| O_TRUNC, 0644);
		else
			fd = open(command->redi->first_token->value, O_CREAT | O_WRONLY \
				| O_APPEND, 0644);
	}
	while (env_list)
	{
		ft_putendl_fd(env_list->content, fd);
		env_list = env_list->next;
	}
}

// s: the string to be printed // flag = -n flag to print s without newline;
void	ft_echo(char *s, char flag)
{
	if (s == NULL)
	{
		write(1, "\n", 2);
		return ;
	}
	if (flag == 'n')
		write(1, s, ft_strlen(s));
	else
	{
		write(1, s, ft_strlen(s));
		write(1, "\n", 1);
	}
}
