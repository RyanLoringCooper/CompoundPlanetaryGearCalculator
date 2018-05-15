CXX 			:= g++
CXXFLAGS		:= `pkg-config --cflags gtk+-3.0` -O2
LIBS 			:= `pkg-config --libs gtk+-3.0`
SRC_SUFFIX		:= cpp
SRCS			:= $(patsubst src/%.$(SRC_SUFFIX), %.$(SRC_SUFFIX), $(wildcard src/*.$(SRC_SUFFIX)))
OBJ_DIR 		:= obj/
BUILD_DIR 		:= bin/
VPATH 			:= src $(OBJ_DIR)

PlanetaryGearCalculator: $(SRC:.$(SRC_SUFFIX)=.o)
	@mkdir -p $(BUILD_DIR)
	cp src/UI.glade $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)$@ $(patsubst %.$(SRC_SUFFIX), $(OBJ_DIR)%.o, $(SRCS)) $(LIBS)
.PHONY: PlanetaryGearCalculator

clean: 
	$(RM) -rf $(BUILD_DIR)
	$(RM) -rf $(OBJ_DIR)
.PHONY: clean

%.o : %.$(SRC_SUFFIX)
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $(OBJ_DIR)$@ $< $(LIBS)
