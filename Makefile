CC = gcc
CFLAGS = -Wall -pthread

SRCS = main.c task_manager.c \
       tasks/cpu_task.c tasks/io_task.c \
       utils/timer.c

OBJS = $(SRCS:.c=.o)
EXEC = task_analyzer

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(EXEC)

clean:
	rm -f $(EXEC) *.o tasks/*.o utils/*.o
