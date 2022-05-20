/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:58:08 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/19 18:30:01 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <limits.h>

// s: the string to be printed // flag = -n flag to print s without newline;
void	ft_echo(char **s)
{
	for (int i = 0; s[i]; i++)
		printf("%s\n", s[i]);
	// if (flag == 'n')
	// 	write(1, s, ft_strlen(s));
	// else
	// {
	// 	write(1, s, ft_strlen(s));
	// 	write(1, "\n", 1);
	// }
}

// getting the promt from the stdout using readline function;
char	*get_promt(void)
{
	char	*cmd;

	cmd = readline("\033[0;34mMinishell$> : \033[0m");
	if (cmd && *cmd)
		add_history(cmd);
	return (cmd);
}

void	sig_handler(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
		(void)0;
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		get_promt();
		return ;
	}
}

// gets the path of an command returns NULL if the path not found
char	*get_path(t_list *env_list, char *cmd)
{
	char	*path;
	char	**command_path;
	int		i;
	t_list	*temp;
	temp = ft_getenv(env_list, "PATH");
	if (temp == NULL)
		return NULL;
	path = temp->content;
	i = 0;
	command_path = ft_split(path, ':');
	
	while (command_path[i])
	{
		command_path[i] = ft_strjoin(command_path[i], "/");
		command_path[i] = ft_strjoin(command_path[i], cmd);
		if (access(command_path[i], F_OK | X_OK) == 0)
			return (command_path[i]);
		i++;
	}
	return (NULL);
}

// check the command if it is an excutable
int check_cmd(char **cmd, char **env)
{	
	if (cmd[0][0] == '/')
	{
		if (fork() == 0)
			if (access(cmd[0], F_OK) == 0)
				execve(cmd[0], cmd, env);
		wait(NULL);
		return (0);
	}
	else
	{
		if (fork() == 0)
			if (access(cmd[0], F_OK | X_OK) == 0)
				execve(cmd[0], cmd, env);
		wait(NULL);
	}
	return (0);
}

// excutes commands
void	ft_execute(char **cmd, char **env, t_list *env_list)
{
	char	*command_path;

	command_path = get_path(env_list, cmd[0]);
	if (cmd[0][0] == '/' || cmd[0][0] == '.')
		check_cmd(cmd, env);
	else
	{
		if (command_path == NULL){
			printf("%s:  command not found\n", cmd[0]);
			return ;
		}
		if (fork() == 0)
			execve(command_path, cmd, env);
		wait(NULL);
	}
}

// redirect the output of cmd to file with file being overriten;
void	ft_redirect_output(char	*cmd, char *file, char **env, t_list *env_list)
{
	int		fd;
	char	**command_args;
	char	*path;

	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		perror("Error: ");
	command_args = ft_split(cmd, ' ');
	if (fork() == 0)
	{
		path = get_path(env_list, command_args[0]);
		if (path == NULL)
			perror("Error: ");
		else
		{
			dup2(fd, STDOUT_FILENO);
			execve(path, command_args, env);
		}
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
}

// append the output of cmd to file;
void	ft_redirect_output_2(char *cmd, char *file, char **env, t_list *env_list)
{
	int		fd;
	char	**command_args;
	char	*path;

	fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
		perror("Error: ");
	command_args = ft_split(cmd, ' ');
	if (fork() == 0)
	{
		path = get_path(env_list, command_args[0]);
		if (path == NULL)
			perror("Error: ");
		else
		{
			dup2(fd, STDOUT_FILENO);
			execve(path, command_args, env);
		}	
		exit(EXIT_SUCCESS);
	}
	wait(NULL);
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

//  excutes cmd if exits and reads the input from stdin until the delimeter is found;
void	ft_herdoc(char *cmd, char *delimeter, char **env, t_list *env_list)
{
	char	*result;
	char *temp;
	temp = "";
	int fd = open("temp", O_CREAT | O_RDWR  , 0644);
	if (fd == -1)
		return ;
	while (1)
	{
		result = readline("heredoc>");
		if (ft_strcmp(ft_strtrim(result, "\n") , delimeter) == 0 || !result)
			break ;
		temp = ft_strjoin(temp, result);
		temp = ft_strjoin(temp, "\n");
		write(fd, result, ft_strlen(result));
		write(fd, "\n", ft_strlen(result));
	}
	if (cmd != NULL)
	{
		fd = open("temp", O_RDONLY);
		if (fork() == 0)
		{
			dup2(fd, STDIN_FILENO);
			(void)env;
			(void)env_list;
			// ft_execute(cmd, env, env_list);
			exit(EXIT_SUCCESS);
		}
		close(fd);
		wait(NULL);
	}
	else
		printf("%s", temp);
}

// converts the 2d array env to a linked list to be used in further commands;
t_list	*get_env_list(char **env)
{
	t_list	*env_list;
	int		i;

	i = 0;
	env_list = ft_lstnew(env[i++]);
	while (env[i++ + 1])
		ft_lstadd_back(&env_list, ft_lstnew(ft_strdup(env[i])));
	return (env_list);
}

// prints the all the environment variables
void	ft_env(t_list *env_list)
{
	while (env_list)
	{
		printf("%s\n", env_list->content);
		env_list = env_list->next;
	}
}

// exports a varible to the env_list; when it is being called with no arguments it prints out the environment variables sorted;
void	ft_export(t_list *env, char *arg)
{
	if (arg == NULL)
	{
		sort_list(&env);
		while (env)
		{
			printf("%s\n", env->content);
			env = env->next;
		}
	}
	else
	{
		ft_lstadd_front(&env, ft_lstnew(arg));
		sort_list(&env);
		while (env)
		{
			printf("%s\n", env->content);
			env = env->next;
		}
	}
}

// like the cd command (change directory)
void	ft_cd(char *path, t_list *env_list)
{
	t_list	*old_wd;
	char	current_wd[PATH_MAX];
	char	buffer[PATH_MAX];
	if (path == NULL)
		path = ft_strdup("~");
	if (ft_strcmp("-", path) == 0)
	{
		getcwd(current_wd, sizeof(current_wd));
		old_wd = ft_getenv(env_list, "OLDPWD");
		if(old_wd)
		{
			char *path = ft_split(old_wd->content, '=')[1];
			chdir(path);
			ft_setenv(&env_list, "OLDPWD", current_wd);
			getcwd(buffer, sizeof(buffer)); 
			ft_setenv(&env_list, "PWD", buffer);
		}
		else
			printf("OLDPWD not set\n");
	}
	else if (ft_strcmp("~", path) == 0)
	{
		char *home_path = ft_split(ft_getenv(env_list, "HOME")->content, '=')[1];
		getcwd(current_wd, sizeof(current_wd));
		chdir(home_path);
		ft_setenv(&env_list, "OLDPWD", current_wd);
		printf("here\n");
		return ;
	}
	else
	{
		getcwd(current_wd, sizeof(current_wd));
		if (chdir(path) == -1)
			return ;
		ft_setenv(&env_list, "OLDPWD", current_wd);
	}
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
	if (ft_strcmp(cmd[0], to_delete) == 0)
	{
		temp = *env_list;
		*env_list = (*env_list)->next;
		free(temp);
		return ;
	}
	second = first->next;
	while (second)
	{
		cmd = ft_split(second->content, '='); /// wa9ila che9itha hna
		if (ft_strcmp(cmd[0], to_delete) == 0)
		{
			temp = second;
			first->next = second->next;
			free(temp);
			return ;
		}
		first = second;
		second = second->next;
	}
}

// sorts the environment variables list to be printed when exports get called;
void	sort_list(t_list **env_list)
{
	t_list	*p;
	t_list	*q;
	char	*val;

	p = *env_list;
	while (p)
	{
		q = *env_list;
		while (q->next)
		{
			if (ft_strcmp(q->content, q->next->content) > 0)
			{
				val = q->content;
				q->content = q->next->content;
				q->next->content = val;
			}
			q = q->next;
		}
		p = p ->next;
	}
}

// prints the current working directory;
void	ft_pwd(void)
{
	char	working_directory[PATH_MAX];
	getcwd(working_directory, sizeof(working_directory));
	printf("%s\n", working_directory);
}

/* returns the node in env_list that containts var_name
	if var_name not found it returns NULL; */
t_list	*ft_getenv(t_list *env_list, char *var_name)
{
	char	*temp;

	while (env_list)
	{
		temp = ft_split(env_list->content, '=')[0];
		if (!temp || !*temp)
			return (NULL);
		if (ft_strcmp(temp, var_name) == 0)
			return (env_list);
		env_list = env_list ->next;
	}
	return (NULL);
}

// assign the var_val to var_name and and add it to env_list
void	ft_setenv(t_list **env_list, char *var_name, char *var_val)
{
	char	*var;
	t_list	*temp;

	temp = ft_getenv(*env_list, var_name);
	if (temp == NULL)
	{
		var = ft_strjoin(var_name, "=");
		var = ft_strjoin(var, var_val);
		ft_lstadd_back(env_list, ft_lstnew(var));
	}
	else
	{
		ft_unset(env_list, var_name);
		ft_setenv(env_list, var_name, var_val);
	}
}

// int main(int ac, char **av, char **env)
// {
// 	char	*cmd;
// 	t_list	*temp_env_vars;
// 	t_list	*env_list;
	
// 	(void)ac;
// 	(void)av;
// 	cmd = NULL;
// 	temp_env_vars = ft_lstnew(ft_strdup(""));
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, sig_handler);
// 	env_list = get_env_list(env);
// 	while (true)
// 	{
// 		cmd = ft_strtrim(get_promt(), " ");
// 		if (cmd == NULL)
// 			exit(EXIT_SUCCESS);
// 		if (*cmd)
// 		{
// 			if (ft_strnstr(cmd, "=", ft_strlen(cmd)) != NULL)
// 				ft_lstadd_front(&temp_env_vars, ft_lstnew(cmd));
// 			else if (ft_strnstr(cmd, ">", ft_strlen(cmd)) != NULL)
// 			{
// 				char *temp = ft_strnstr(cmd, ">>", ft_strlen(cmd));
// 				if (temp == NULL)
// 				{
// 					char **args = ft_split(cmd, '>');
// 					ft_redirect_output(args[0], args[1], env, env_list);
// 				}
// 				else
// 				{
// 					char **args = ft_split(cmd, '>');
// 					ft_redirect_output_2(args[0], args[1], env, env_list);
// 				}
// 			}
// 			else if (ft_strnstr(cmd, "cd", ft_strlen(cmd)) != NULL)
// 			{
// 				char *path = ft_split(cmd, ' ')[1];
// 				ft_cd(path, env_list);
// 			}
// 			else if (ft_strnstr(cmd, "export", ft_strlen(cmd)) != NULL)
// 			{
// 				char **export_args = ft_split(cmd, ' ');
// 				if (export_args[1] == NULL)
// 					ft_export(env_list, NULL);
// 				t_list *temp = ft_getenv(temp_env_vars, export_args[1]);
// 				if (temp)
// 				{
// 					char **splitted_var = ft_split(temp->content, '=');
// 					ft_setenv(&env_list, splitted_var[0], splitted_var[1]);
// 				}
// 			}
// 			else if (ft_strcmp(cmd, "env") == 0)
// 				ft_env(env_list);
// 			else if (ft_strnstr(cmd, "unset", ft_strlen(cmd)) != NULL)
// 			{
// 				char **unset_args = ft_split(cmd, ' ');
// 				if (unset_args[1] != NULL)
// 				{
// 					ft_unset(&env_list, unset_args[1]);
// 					ft_unset(&temp_env_vars, unset_args[1]);
// 				}
// 				else
// 					write(2, "unset: Not enough arguments\n", 29);
// 			}
// 			else if (ft_strcmp(cmd, "pwd") == 0)
// 				ft_pwd();
// 			else if (ft_strcmp(cmd, "exit") == 0)
// 				exit(EXIT_SUCCESS);
// 			else if (ft_strnstr(cmd, "echo", ft_strlen(cmd)) != NULL)
// 			{
// 				int i = 0;
// 				for (; i < (int)ft_strlen(cmd); i++)
// 					if (cmd[i] == ' ')
// 						break;
// 				ft_echo(cmd+ ++i, '\n');
// 			}
// 			else
// 				ft_execute(cmd, env, env_list);
// 		}
// 	}
// }