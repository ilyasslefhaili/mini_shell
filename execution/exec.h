/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:54:13 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/29 11:37:09 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../parsing/parsing.h"
# include <stdio.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/stat.h>
# include <limits.h>
# include "../minishell.h"
int get_exit_code();
void set_exit_code(int num);
void	ft_env(t_commande *command, t_list *env_list);
void	ft_redirect_output_2(t_commande *cmd, char **env, t_list *env_list);
void	ft_redirect_output(t_commande *cmd, char **env, t_list *env_list);
void	redirect_input(t_commande *cmd, char **env, t_list *env_list);
void	ft_export(t_commande *command, t_list *env, char *arg);
t_list	*ft_getenv(t_list *env_list, char *var_name);
t_list	*ft_getenv(t_list *env_list, char *var_name);
t_list	*get_env_list(char **env);
void	free_2d_array(char **a);
void	ft_execute(char **cmd, char **env, t_list *env_list);
void	ft_echo(char *s, char flag);
void	sig_handler(int sig);
void	ft_pwd(void);
void	sort_list(t_list **env_list);
void	ft_unset(t_list **env_list, char *to_delete);
void	ft_cd(char *path, t_list *env_list);
void	ft_setenv(t_list **env_list, char *var_name, char *var_val);
void	ft_setenv(t_list **env_list, char *var_name, char *var_val);
void	sort_list(t_list **env_list);
// void	pipe_herdoc(t_commande *cmd, char **env, t_list *env_list);
char	*get_promt(void);
char	*join_for_echo(t_list *env_list, char **s, char flag);
char	*get_path(t_list *env_list, char *cmd);
char	*get_path(t_list *env_list, char *cmd);
int		get_parts(char	*s, char c);
int		ft_strcmp(char *s, char *str);
int		check_cmd(char **cmd, char **env);
void	ft_herdoc(t_commande *cmd, char **env, t_list *env_list);
char *ft_get_env_val(t_list *env_list, char *var_name);

#endif