all: calc

calc: calc.c
	$(CC) -o $@ $^

clean:
	$(RM) calc

.PHONY: all clean
