NAME = philo

SRCS = $(shell find '.' -name "*.c")

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror -I.

CC = gcc

.c.o : 
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean: 
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean re all fclean

