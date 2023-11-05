

NAME = philo
SRC =	philo_utils_1.c	philo_utils_2.c	philo_utils_3.c philo_utils_4.c philo_utils.c philo.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
R        := $(shell tput -Txterm setaf 1)
G        := $(shell tput -Txterm setaf 2)
Y       := $(shell tput -Txterm setaf 3)

all: $(NAME)
	@echo $(G) "ALL functions are done!"

$(NAME): $(OBJS)
	@echo $(Y) Compiling: $< ... Done!
	@cc $(CFLAGS) $(OBJS) -o $@

%.o: %.c philo.h
	@echo $(Y) Compiling: $< ... Done!
	@cc $(CFLAGS) -c $<

clean:
	@echo $(R) Cleaned
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@echo $(R) Fully cleaned
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re bonus all