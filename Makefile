
NAME = pipex

BONUS = pipex_bonus

CC = clang

LIBFT_PATH = libft/ --no-print-directory
LIBFT_NAME = libft/libft.a

CFLAGS = -Wall -Werror -Wextra -g3

SRC = ./src/childs.c \
	./src/error.c \
	./src/free.c \
	./src/pipex.c

SRC_BONUS = ./bonus/child_bonus.c \
	./bonus/error_bonus.c \
	./bonus/files_bonus.c \
	./bonus/free_bonus.c \
	./bonus/here_doc_bonus.c \
	./bonus/pipex_bonus.c

OBJ = ${SRC:.c=.o}

OBJ_BONUS = ${SRC_BONUS:.c=.o}

all: $(LIBFT_NAME) $(NAME)

bonus: $(LIBFT_NAME) $(BONUS)

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
	${CC}  $(OBJ) $(LIBFT_NAME) -o  ${NAME}

$(BONUS): $(OBJ_BONUS)
	${CC} $(OBJ_BONUS) $(LIBFT_NAME) -o ${BONUS}

$(LIBFT_NAME):
	make -C $(LIBFT_PATH)

clean:
	make clean -C ./libft
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean: clean
	make fclean -C $(LIBFT_PATH)
	rm -rf $(NAME) $(BONUS)

re: fclean all

.PHONY:
	re all clean fclean bonus
