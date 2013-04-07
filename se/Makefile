PROJ 			= 701
CC 				= g++

CC_FLAGS		= -c -g -Wall -I./include -I./src -I/usr/include/boost 
SRC				= $(wildcard src/*.cpp) 

OBJS	 		= $(addprefix obj/,$(notdir $(SRC:.cpp=.o))) 

LD_FLAGS		= -lboost_iostreams

all: $(PROJ)

#Must put .o before -l flags as the linker expects during static linking that missing symbols in .o files should be filled in with boost header files and not vice verse. In dynamic it doesn't matter
$(PROJ): $(OBJS)
	$(CC) $^ $(LD_FLAGS) -o $@

obj/%.o: src/%.cpp
	$(CC) $(CC_FLAGS) -o $@ $<

clean:
	$(RM) $(OBJS) $(PROJ)


