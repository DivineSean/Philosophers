

NAME = philo_bonus
SRC =	philo_bonus_1.c philo_bonus_2.c philo_bonus_3.c bonus.c
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

%.o: %.c philo_bonus.h
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