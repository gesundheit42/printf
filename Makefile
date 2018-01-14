CC = gcc
SRC = *.c
OBJ = *.o
NAME = libftprintf.a

all: $(NAME)

$(NAME): $(OBJ)
				@ar rc $(NAME) $(OBJ)
				@ranlib $(NAME)

$(OBJ):
				$(CC) -c $(CFLAGS) $(SRC)

clean:
				@rm -f $(OBJ)

fclean: clean
				@rm -f $(NAME)
				rm -f *.a

re: fclean all
