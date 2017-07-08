# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: narajaon <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/05/10 13:20:13 by narajaon          #+#    #+#              #
#    Updated: 2017/07/08 20:16:25 by narajaon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
HEAD = rtv1.h
LIB = libft.a
LIBDIR = libft
SRC = *.c
FLAG = -g -O2 -framework OpenGL -framework AppKit
OBJ = $(SRC:.c=.o)
MLX = minilibx_macos/libmlx.a

all: $(NAME)

$(NAME): $(SRC) $(HEAD)
	@echo "Compiling \033[92m$(LIB)\033[0m..."
	@make -C $(LIBDIR)/
	@make -C minilibx_macos/
	@echo "Compiling \033[92m$(NAME)\033[0m..."
	@gcc $(SRC) $(FLAG) $(MLX) $(LIBDIR)/$(LIB) -o $(NAME)
	@echo "$(NAME) compilation:\033[92m OK\033[0m"

clean:
	@echo "Deleting:\033[33m $(LIB) and *.o\033[0m"
	@rm -f $(OBJ)
	@make -C $(LIBDIR)/ clean
	@make -C minilibx_macos/ clean

fclean: clean
	@echo "Deleting:\033[33m $(NAME)\033[0m"
	@echo "Deleting:\033[33m $(LIB)\033[0m"
	@rm -f $(MLX)
	@rm -f $(NAME)
	@rm -f $(LIBDIR)/$(LIB)

re: fclean all

.PHONY: clean fclean re
