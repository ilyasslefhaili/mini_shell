/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 04:54:13 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/19 14:58:19 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

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
# include <sys/stat.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <sys/stat.h>
typedef struct context {
    int fd[2];
    int to_be_closed;
}t_context;
char	*get_path(t_list *env_list, char *cmd);
int		get_parts(char	*s, char c);
void	sort_list(t_list **env_list);
t_list	*ft_getenv(t_list *env_list, char *var_name);
void	ft_setenv(t_list **env_list, char *var_name, char *var_val);
void	ft_setenv(t_list **env_list, char *var_name, char *var_val);
t_list	*ft_getenv(t_list *env_list, char *var_name);
void	ft_pwd(void);
void	sort_list(t_list **env_list);
void	ft_unset(t_list **env_list, char *to_delete);
void	ft_cd(char *path, t_list *env_list);
void	ft_export(t_list *env, char *arg);
void	ft_env(t_list *env_list);
t_list	*get_env_list(char **env);
int	ft_strcmp(char *s, char *str);
void	ft_redirect_output_2(char *cmd, char *file, char **env, t_list *env_list);
void	ft_redirect_output(char	*cmd, char *file, char **env, t_list *env_list);
int check_cmd(char **cmd, char **env);
char	*get_path(t_list *env_list, char *cmd);
void	sig_handler(int sig);
char	*get_promt(void);
void	ft_herdoc(char *cmd, char *delimeter, char **env, t_list *env_list);
void	ft_execute(char **cmd, char **env, t_list *env_list);
void	ft_echo(char **s);
#endif