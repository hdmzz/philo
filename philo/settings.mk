NAME = philo

SRC = $Smain.c $Sthreads.c $Sutils.c $Seat.c $Ssleep.c $Sthink.c $Sdeath.c

HEADER = include/philo.h

CC = gcc -g3 -pthread
CFLAGS = -Wall -Wextra -Werror
