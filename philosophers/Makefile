SRC =			main.c init.c philo.c utils.c monitor.c utils_2.c free.c 
HEAD =			
OBJ =			$(SRC:.c=.o)
FLAGS = -Wall -Werror -Wextra
DEBUG_FLAGS = -fsanitize=thread -ggdb3
NAME = philo
CC = clang

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -pthread $(FLAGS) $(OBJ) -o $(NAME) 

%.o: %.c
	$(CC) -pthread $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re