NAME = philo

SRC = $Smain.c $Sthreads.c $Sutils.c $Seat.c $Ssleep.c $Sthink.c $Sdeath.c $Sinit.c

HEADER = include/philo.h

CC = gcc -g3 -lpthread #-fsanitize=thread
CFLAGS = -Wall -Wextra -Werror
