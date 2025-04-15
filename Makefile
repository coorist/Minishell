CC = cc
NAME = minishell
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror -Iincludes

SRC_FILES = srcs/minishell.c


OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES) 
	$(CC) $(OBJ_FILES)  -o $(NAME) $(CFLAGS)  -lreadline


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	rm -f $(OBJ_FILES) 

fclean: clean
	rm -f $(NAME) 

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: $(OBJ_FILES) $(LIBFT_OFILES)