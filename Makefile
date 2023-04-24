NAME 		= pipex
LIBFT		= $(addprefix $(LIBFT_DIR)/,libft.a)
LIBFT_DIR	= includes/libft
OBJ_FILES	= $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
OBJ_DIR 	= objects
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
RM			= rm -f
SRC_FILES 	= main.c pipex.c errors.c files.c
SRC_DIR 	= sources

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(OBJ_FILES) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

clean:
	$(RM)r $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus:
	$(MAKE) BONUS=1 all

.PHONY: all, clean, fclean, re