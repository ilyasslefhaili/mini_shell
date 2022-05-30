/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 11:29:35 by ytouate           #+#    #+#             */
/*   Updated: 2022/05/29 14:54:54 by ytouate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./parsing/parsing.h"
# include "./execution/exec.h"
# include "./libft/libft.h"
// typedef struct s_vars
// {
//     int exit_code;
// }t_vars;
int open_output_files(t_commande *command);
int open_input_files(t_commande *command);
void replace_symbol_by_val(char **s, t_list *env_list);
#endif