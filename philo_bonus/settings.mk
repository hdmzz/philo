NAME = philo_bonus

<<<<<<< HEAD
SRC = $Smain_bonus.c $Sinit_bonus.c $Sutils_bonus.c

HEADER = include/philo_bonus.h

CC = gcc -g3 -pthread #-fsanitize=thread
=======
SRC = $Smain_bonus.c $Sinit_bonus.c $Sutils_bonus.c $Sutils2_bonus.c $Sfork_bonus.c \
		$Sdeath_bonus.c $Ssleep_bonus.c

HEADER = include/philo_bonus.h

CC = gcc -g3 -pthread -fsanitize=thread
>>>>>>> version-ok
CFLAGS = -Wall -Wextra -Werror
