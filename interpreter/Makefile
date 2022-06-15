CXX       := g++
CXX_FLAGS := -std=c++11 -ggdb

BIN     := bin
SRC     := src
INCLUDE := include

LIBRARIES   :=
EXECUTABLE  := myapp


all: $(BIN)/$(EXECUTABLE)

run: clean all
	clear
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBRARIES) -I $(INCLUDE) -Wall

clean:
	-rm $(BIN)/*