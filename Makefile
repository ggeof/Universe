#=======================================#
#	MakeFile for Universe v1.0	#
#	Copyright 2018			#
#		Geoffroy HEURTEL	#
#	Last modified /2019		#
#=======================================#		

CC = g++
CFLAGS = -W -Wall
EXEC = Universe # Name of the executables
BIN = ./bin/ # Folder containing executables

# Rule by default : caches, executable, link
Default: caches $(EXEC) link

# Rule for create the executable 
Executable: $(EXEC) link 

# Rule for compile executable
Universe: Universe.o Draw.o
	$(CC) -o  $(BIN)$(EXEC) Universe.c -lncurses $(CFLAGS)

# Rule for compile Universe.c and Draw.c
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# Rule for create the folder $(BIN)
caches:
	mkdir $(BIN)

# Rule for create the link of Universe
link:
	ln $(BIN)$(EXEC) $(EXEC)

# Rule for delete the executable
clean:
	rm -rf  $(BIN)*.o

# Rule for delete the executable and the folder 
fullclean: clean
	rm -rf $(EXEC) $(BIN)
