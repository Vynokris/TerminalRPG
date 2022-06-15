# List of c files to build.
OBJS = text_rpg.o

# List of parameters for build (Preprocessor, C compilation, and Linking).
CPPFLAGS = 
CFLAGS = -O0 -g -Wall -lm
LDFLAGS = 

# .PHONY: Rules that won't generate files
.PHONY: run clean

# First rule, default one to be executed when launching make without argument.
game.out: $(OBJS)
	-gcc -o $@ $^ $(CFLAGS)
	
# Pattern matching (compiles all the OBJS files).
%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

run: game.out
	./game.out

clean:
	rm -f $(OBJS) game.out
