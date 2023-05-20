NAME = philo_bonus

SRC = $Smain_bonus.c $Sinit_bonus.c $Sutils_bonus.c

HEADER = include/philo_bonus.h

CC = gcc -g3 -pthread #-fsanitize=thread
CFLAGS = -Wall -Wextra -Werror
