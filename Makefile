SRC = main.c ft_split_pipex.c
OBJ = ${SRC:c=o}
CC = gcc
FLAGS = -Wall -Wextra -Werror
NAME = pipex

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) libft.a -o $(NAME)

%.o: %.c
	$(CC) -c $(FLAGS) -o $@ $<

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all