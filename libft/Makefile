# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: xchen <xchen@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/12/03 11:28:03 by xchen         #+#    #+#                  #
#    Updated: 2021/03/11 12:47:58 by xchen         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_FILE = 	ft_strlen.c \
			ft_memset.c \
			ft_memcpy.c \
			ft_calloc.c \
			ft_bzero.c \
			ft_comparison.c \
			ft_putstr_fd.c \
			ft_strncmp.c \
			ft_isspace.c \
			ft_count_digit.c \
			ft_str2nbr.c \
			ft_ischar.c

OBJ_FILE = $(SRC_FILE:%.c=%.o)
HEADER_DIR = ./
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ_FILE)
	ar -rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILE)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONEY: all clean fclean re