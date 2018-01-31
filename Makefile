NAME := rtv1
HEAD = inc/rtv1.h

CC := gcc
CFLAGS = -Wall -Werror -Wextra -O2
INC_D:=inc
SCR_D:=src
LIB_D:=lib
OBJ_D:=obj

INCLUDES = \
		-I inc \
		-I lib/libft/inc \
		-I lib/minilibx_macos

LIBRARIES = \
		-L lib/libft -lft \
		-L lib/minilibx_macos -lmlx

ITEM = \
	cam_manip.o\
	col_fun.o\
	cone.o\
	cylinder.o\
	dot_op.o\
	dot_op2.o\
	dot_op3.o\
	forms.o\
	init.o\
	main.o\
	parser.o\
	parser2.o\
	parser3.o\
	parser4.o\
	plane.o\
	push_shapes.o\
	rot_matrix.o\
	sphere.o\
	utils.o

OBJ:=$(addprefix $(OBJ_D)/, $(ITEM))

vpath %.c src

vpath %.h inc lib/libft/inc lib/minilibx_macos/

all: $(NAME)

$(NAME): $(OBJ) $(HEAD) Makefile
	@$(MAKE) -C lib/libft
	@$(MAKE) -C lib/minilibx_macos
	@$(CC) $(CFLAGS) -o $(NAME) $(INCLUDES) $(LIBRARIES) $(OBJ) \
		-framework OpenGL -framework AppKit

./${OBJ_D}/%.o: %.c
	@mkdir -p $(OBJ_D)
	@$(CC) $(CFLAGS) -c -o $@ $<  $(INCLUDES)

clean:
	@$(MAKE) -C lib/libft clean
	@$(MAKE) -C lib/minilibx_macos clean
	@$(RM) -r $(OBJ_D)

fclean: clean
	@$(MAKE) -C lib/libft fclean
	@$(RM) $(NAME)

re: fclean all

git :
	@git add .
	@git commit -m "${MSG}"

gitp : fclean git
	git push

.PHONY: clean fclean re
