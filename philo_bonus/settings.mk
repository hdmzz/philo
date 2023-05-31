NAME = philo_bonus

SRC = $Smain_bonus.c $Sinit_bonus.c $Sutils_bonus.c $Sutils2_bonus.c $Sfork_bonus.c \
		$Sdeath_bonus.c $Ssleep_bonus.c $Smax_meal_bonus.c

HEADER = include/philo_bonus.h

CC = gcc -g3 -pthread -fsanitize=thread
CFLAGS = -Wall -Wextra -Werror
