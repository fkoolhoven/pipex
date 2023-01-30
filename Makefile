NAME 		= pipex
INCLUDES 	= ./includes
LIBFT		= ./includes/libft.a
SRC_DIR 	= sources
OBJ_DIR 	= objects
SRC_FILES 	= main.c pipex.c errors.c ft_split_pipex.c
OBJ_FILES	= $(addprefix $(OBJ_DIR)/,$(SRC_FILES:.c=.o))
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -fsanitize=address -g
RM			= rm -f

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) -fsanitize=address -g $(OBJ_FILES) $(LIBFT) -o $(NAME)
	
# $(NAME): $(OBJ_FILES) $(LIBFT)
# 	cp $(LIBFT) ./$(NAME)
# 	$(AR) $(NAME) $(OBJ_FILES) 

# $(LIBFT):
# make bonus -C libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@	

clean:
	$(RM)r $(OBJ_DIR)
# make clean -C libft

fclean: clean
	$(RM) $(NAME)
# make fclean -C libft

re: fclean all

.PHONY: all, clean, fclean, re




