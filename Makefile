# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ytouate <ytouate@student.1337.ma>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/19 11:29:17 by ytouate           #+#    #+#              #
#    Updated: 2022/05/19 17:06:39 by ytouate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all :
		cd execution && make && cd ..
		cd parsing && make && cd ..
		cd libft && make && make bonus && cd ..
		gcc -Wall -Wextra -Werror ./libft/libft.a ./execution/exec.a ./parsing/pars.a minishell.c -o minishell -lreadline -fsanitize=address -g

fclean :
		cd execution && make fclean && cd ..
		cd libft && make fclean && cd ..
		cd parsing && make fclean && cd ..
