NAME:=libft.a

GREEN:="\033[32m"
ORANGE:="\033[33m"
RED:="\033[31m"
CLEAR:="\033[0m"

CC:=gcc
CFLAGS:=-Wall -Wextra -Werror
CFLAGS+=-g3

MKDIR:=mkdir -p
RANLIB:=ranlib

OBJ_D:=obj
INC_D:=inc
LIB_D:=..

INCLUDES:= -I inc

ITEM:=\
	ft_print_tab.o\
	free_str.o\
	free_tab.o \
	free_tab_str.o \
	ft_abs.o \
	ft_atoi.o \
	ft_atoi_base.o \
	ft_bzero.o \
	ft_cap_itoa_base.o \
	ft_freechar2.o \
	ft_isalnum.o \
	ft_isalpha.o \
	ft_isascii.o \
	ft_isc.o \
	ft_isdigit.o \
	ft_iseven.o \
	ft_islower.o \
	ft_isnu.o \
	ft_isprint.o \
	ft_isspace.o \
	ft_isupper.o \
	ft_itoa.o \
	ft_itoa_base.o \
	ft_itoa_str.o \
	ft_lltoa_str.o \
	ft_lstadd.o \
	ft_lstadd_back.o \
	ft_lstback.o \
	ft_lstdel.o \
	ft_lstdelone.o \
	ft_lstiter.o \
	ft_lstmap.o \
	ft_lstnew.o \
	ft_lstpop.o \
	ft_ltoa_base.o \
	ft_ltoa_str.o \
	ft_memalloc.o \
	ft_memccpy.o \
	ft_memchr.o \
	ft_memcmp.o \
	ft_memcpy.o \
	ft_memdel.o \
	ft_memmove.o \
	ft_memset.o \
	ft_print_words_tables.o \
	ft_putchar.o \
	ft_putchar_fd.o \
	ft_putchar_uni.o \
	ft_putendl.o \
	ft_putendl_fd.o \
	ft_putnbr.o \
	ft_putnbr_fd.o \
	ft_putstr.o \
	ft_putstr_fd.o \
	ft_putstr_uni.o \
	ft_recursive_power.o \
	ft_splitwhitespaces.o \
	ft_strcat.o \
	ft_strchr.o \
	ft_strclr.o \
	ft_strcmp.o \
	ft_strcpy.o \
	ft_strcpy_ret.o \
	ft_strdel.o \
	ft_strdup.o \
	ft_strequ.o \
	ft_striter.o \
	ft_striteri.o \
	ft_strjoin.o \
	ft_strlcat.o \
	ft_strlen.o \
	ft_strmap.o \
	ft_strmapi.o \
	ft_strncat.o \
	ft_strncmp.o \
	ft_strncpy.o \
	ft_strncpy_ret.o \
	ft_strndup.o \
	ft_strnequ.o \
	ft_strnew.o \
	ft_strnstr.o \
	ft_strrchr.o \
	ft_strsplit.o \
	ft_strstr.o \
	ft_strsub.o \
	ft_strtrim.o \
	ft_strtrimc.o \
	ft_tablen.o \
	ft_tolower.o \
	ft_toupper.o \
	ft_uitoa_str.o \
	ft_ultoa.o \
	get_next_line.o\
	ft_ultoa_base.o

OBJ:=$(addprefix ./obj/, $(ITEM))

VPATH:=src:inc

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) rc $(NAME) $(OBJ)
	@$(RANLIB) $(NAME)
	@echo ${GREEN}$(NAME) built${CLEAR}

$(OBJ_D)/%.o: %.c 
	@$(MKDIR) $(OBJ_D)
	@$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
clean:
	@echo ${ORANGE}Cleaning $(NAME)${CLEAR}
	@$(RM) -r $(OBJ_D)

fclean: clean
	@echo ${RED}Full cleaning $(NAME)${CLEAR}
	@$(RM) $(NAME)

re: fclean all

