NAME 		= pipex
INCLUDES 	= includes
LIBFT_DIR	= includes/libft
LIBFT		= includes/libft/libft.a
SRC_DIR 	= sources
OBJ_DIR 	= objects
SRC_FILES 	= main.c pipex.c errors.c
OBJ_FILES	= $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	$(CC) $(OBJ_FILES) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(LIBFT):
	make bonus -C $(LIBFT_DIR)

clean:
	$(RM)r $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all, clean, fclean, re