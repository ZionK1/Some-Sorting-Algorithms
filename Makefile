CC       = clang
CFLAGS   = -Wall -Wpedantic -Werror -Wextra

SOURCES  = $(wildcard *.c)
OBJECTS  = $(SOURCES:%.c=%.o)

all: sorting

sorting: $(OBJECTS)
	$(CC) -o $@ $^
	
%.o : %.c
	$(CC) $(CFLAGS) -c $<
	
clean:
	rm -f sorting $(OBJECTS)
	
format:
	clang-format -i -style=file *.[ch]
