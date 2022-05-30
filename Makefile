all :
		cd execution && make && cd ..
		cd parsing && make && cd ..
		cd libft && make && make bonus && cd ..
		gcc -Wall -Wextra -Werror ./libft/libft.a ./execution/exec.a ./parsing/pars.a minishell.c -o minishell -lreadline -L

clean :
	cd execution && make clean && cd ..
	cd libft && make fclean && cd ..
	# cd parsing && make clean && cd ..
fclean :
		cd execution && make fclean && cd ..
		cd libft && make fclean && cd ..
		cd parsing && make fclean && cd ..