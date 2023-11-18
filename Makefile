
NAME = pipex

CC = clang

LIBFT_PATH = libft/ --no-print-directory
LIBFT_NAME = libft/libft.a

CFLAGS = -Wall -Werror -Wextra -g3

SRC = ./src/childs.c \
	./src/error.c \
	./src/free.c \
	./src/pipex.c

OBJ = ${SRC:.c=.o}

all: $(LIBFT_NAME) $(NAME)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
	${CC}  $(OBJ) $(LIBFT_NAME) -o  ${NAME}

$(LIBFT_NAME):
	make -C $(LIBFT_PATH)

clean:
	make clean -C ./libft
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -rf $(NAME)
re: fclean all

.PHONY:
	re all clean fclean
