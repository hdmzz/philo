NAME = philo

SRC = $Smain.c $Sthreads.c

HEADER = include/philo.h

CC = gcc -g3 -pthread
CFLAGS = -Wall -Wextra -Werror
