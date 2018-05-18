CXX 			:= g++
CXXFLAGS		:= `pkg-config --cflags gtk+-3.0` -g
LIBS 			:= `pkg-config --libs gtk+-3.0`
SRC_SUFFIX		:= cpp
SRCS			:= $(patsubst src/%.$(SRC_SUFFIX), %.$(SRC_SUFFIX), $(wildcard src/*.$(SRC_SUFFIX)))
OBJ_DIR 		:= obj/
BIN_DIR 		:= bin/
VPATH 			:= src:$(OBJ_DIR)

CompoundPlanetaryGearCalculator: $(SRCS:.$(SRC_SUFFIX)=.o)
	@mkdir -p $(BIN_DIR)
	cp -u src/UI.glade $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -o $(BIN_DIR)$@ $(patsubst %.$(SRC_SUFFIX), $(OBJ_DIR)%.o, $(SRCS)) $(LIBS)
.PHONY: CompoundPlanetaryGearCalculator

clean: 
	$(RM) -rf $(BIN_DIR)
	$(RM) -rf $(OBJ_DIR)
.PHONY: clean

%.o : %.$(SRC_SUFFIX)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ_DIR)$@ $< $(LIBS)
