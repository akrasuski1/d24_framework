

CC_FLAGS=-std=c++11 -Wall -Wextra -MMD
LIBS=-pthread -lboost_system -lboost_iostreams -lX11
SOURCES=$(wildcard src/*.cpp)
OBJECTS := $(addprefix obj/,$(notdir $(SOURCES:.cpp=.o)))
DEPS=$(OBJECTS:.o=.d)
EXEC=client

all: $(EXEC)

$(EXEC): $(OBJECTS)
	g++ $(OBJECTS) -o $(EXEC) $(LIBS)

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	rm -f $(EXEC)
	rm -f $(OBJECTS) $(DEPS)

-include $(DEPS)
