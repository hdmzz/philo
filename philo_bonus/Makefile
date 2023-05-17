O		= objs/
S		= srcs/

include settings.mk

OBJ = $(SRC:$S%=$O%.o)

.PHONY:	all fclean re

all: $(NAME)

$O:
	@mkdir -p $@

$(OBJ): | $O

$(OBJ): $O%.o: $S% Makefile settings.mk $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(SRC:$S%=$O%.o)

fclean:	clean
	rm -rf $(NAME)
	rm -rf $O

re:	fclean all
