NAME = philo

SRC = $Smain_bonus.c $Sutils_bonus.c

HEADER = include/philo_bonus.h

CC = gcc -g3 -pthread #-fsanitize=thread
CFLAGS = -Wall -Wextra -Werror
