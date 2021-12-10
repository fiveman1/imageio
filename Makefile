-include bin/settings
CXXFLAGS = -std=c++11 -O3 -pthread

EXE = image_processor
DEMO = demo.exe
DEMO_DIR = demo
LIBRARY = imageio
SRC_DIR = src
INCL_DIRS = include
LIB_DIR = lib
OBJ_DIR = obj

SOURCES = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
OBJFILES := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))
DEMOOBJFILES := $(patsubst $(DEMO_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(wildcard $(DEMO_DIR)/*.cpp))

INCL_PARAMS := $(foreach dir, $(INCL_DIRS), -I$(dir))

all: $(EXE)

$(EXE): $(LIBRARY) $(OBJ_DIR)/main.o
	$(CXX) $(CXXFLAGS) -Wl,-rpath,$(LIB_DIR) $(OBJ_DIR)/main.o $(INCL_PARAMS) -L$(LIB_DIR) -l$(LIBRARY) -o $@

# Application Targets:
$(LIBRARY): $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(OBJFILES) $(INCL_PARAMS) -shared -o $(LIB_DIR)/lib$@_$(ARCH).so

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CXX) $(CXXFLAGS) $(INCL_PARAMS) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -fPIC $(INCL_PARAMS) -c $< -o $@

$(OBJ_DIR)/demo.o: $(DEMO_DIR)/demo.cpp
	$(CXX) $(CXXFLAGS) $(INCL_PARAMS) -c $< -o $@

demo: $(LIBRARY) $(DEMOOBJFILES)
	$(CXX) $(CXXFLAGS) -Wl,-rpath,$(LIB_DIR) $(DEMOOBJFILES) $(INCL_PARAMS) -L$(LIB_DIR) -l$(LIBRARY) -o $(DEMO)

clean:
	rm -f obj/*.o lib/*.so $(EXE) $(DEMO)

canny: $(EXE)
	./$(EXE) input/statue.png canny-edge-detect output/statue_canny_edge.png 0.1 0.25

gaussian: $(EXE)
	./$(EXE) input/statue.png gaussian-blur output/statue_gaussian.png