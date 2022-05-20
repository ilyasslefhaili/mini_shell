# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ilefhail <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/08 20:37:04 by ilefhail          #+#    #+#              #
#    Updated: 2021/11/19 23:41:09 by ilefhail         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = @cc

CFLAGS = -Wall -Wextra -Werror -c

AR = ar -rc

SRCS = ft_putnbr_fd.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putstr_fd.c\
		ft_striteri.c\
		ft_strmapi.c\
		ft_itoa.c\
		ft_split.c\
		ft_strtrim.c\
		ft_strjoin.c\
		ft_substr.c\
		ft_bzero.c\
        ft_isalpha.c\
        ft_isdigit.c\
        ft_isascii.c\
        ft_isalnum.c\
        ft_isprint.c\
        ft_memcpy.c\
        ft_memmove.c\
        ft_memset.c\
        ft_memchr.c\
        ft_memcmp.c\
        ft_strlcat.c\
        ft_strlcpy.c\
        ft_strlen.c\
        ft_strchr.c\
        ft_strncmp.c\
        ft_strnstr.c\
        ft_strrchr.c\
        ft_atoi.c\
        ft_calloc.c\
        ft_toupper.c\
        ft_tolower.c\
        ft_strdup.c\

SRCSB = ft_lstiter_bonus.c\
		ft_lstdelone_bonus.c\
		ft_lstadd_back_bonus.c\
		ft_lstlast_bonus.c\
		ft_lstsize_bonus.c\
		ft_lstadd_front_bonus.c\
		ft_lstnew_bonus.c\
		ft_lstclear_bonus.c\

OBJS = $(subst .c,.o, $(SRCS))
OBJSB = $(subst .c,.o, $(SRCSB))

all: $(NAME)

$(NAME): $(OBJS)
	@${CC} ${CFLAGS} ${SRCS}
	@$(AR) $(NAME) $(OBJS)
bonus: $(OBJSB)
	@$(CC) $(CFLAGS) $(SRCSB)
	@$(AR) $(NAME) $(OBJSB)
clean:
	@rm -f ./*.o
fclean : clean
	@rm -f $(NAME)
re : fclean all
