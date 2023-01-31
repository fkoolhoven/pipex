NAME = libft.a
SRCMAN = ft_isalpha.c ft_isdigit.c ft_strlen.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_substr.c ft_strjoin.c ft_straddchar.c ft_strtrim.c ft_split.c ft_split_q.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putnbr_fd.c
SRCBONUS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJMAN = ${SRCMAN:c=o}
OBJBONUS = ${SRCBONUS:c=o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
REMOVE = rm -f

ifdef BONUS
OBJECTS = $(OBJMAN) ${OBJBONUS}
else
OBJECTS = $(OBJMAN)
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	ar -rs $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	$(RM) $(OBJBONUS) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

bonus:
	$(MAKE) BONUS=1 all
