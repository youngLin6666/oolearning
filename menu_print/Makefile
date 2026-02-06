
TARGET = menu_print

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET) $(LDFLAGS) $(LIBS)

%.o:%.c
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) -o $@ -c $< $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o $(TARGET)
