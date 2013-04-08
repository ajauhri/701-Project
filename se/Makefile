AGG 			= aggregate
PREP 			= prepare

CC 				= g++

CC_FLAGS		= -c -g -Wall -I./include -I./src/agg -I/usr/include/boost 

AGG_SRC				= $(wildcard src/agg/*.cpp) 
AGG_OBJS	 		= $(addprefix src/agg/obj/,$(notdir $(AGG_SRC:.cpp=.o))) 

PREP_SRC 			= $(wildcard src/prep/*.cpp)
PREP_OBJS			= $(addprefix src/prep/obj/,$(notdir $(PREP_SRC:.cpp=.o)))


LD_FLAGS		= -lboost_iostreams

all: $(AGG) $(PREP)
agg: $(AGG)
prep: $(PREP)


#Must put .o before -l flags as the linker expects during static linking that missing symbols in .o files should be filled in with boost header files and not vice verse. In dynamic it doesn't matter
$(AGG): $(AGG_OBJS)
	$(CC) $^ $(LD_FLAGS) -o $@

$(PREP): $(PREP_OBJS)
	$(CC) $^ $(LD_FLAGS) -o $@

src/agg/obj/%.o: src/agg/%.cpp
	$(CC) $(CC_FLAGS) -o $@ $<

src/prep/obj/%.o: src/prep/%.cpp
	$(CC) $(CC_FLAGS) -o $@ $<



clean:
	$(RM) $(AGG_OBJS) $(PREP_OBJS) $(AGG) $(PREP)


