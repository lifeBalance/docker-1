NAME =	test

FLAGS =	-Wall -Werror -Wextra

SRC =	test.c

OBJ =	test.o

all:	$(NAME)

$(NAME):	$(SRC)
	gcc $(FLAGS) $(SRC) -c
	gcc $(OBJ) -o $(NAME)

docker-valgrind:
	docker run --hostname leaky --rm -itv "${PWD}:/root/leaky" rodrodri/valgrind

valgrind:
	valgrind --leak-check=full ./$(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean:	clean
	/bin/rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re