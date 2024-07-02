################################################################################
#### Variables and settings
################################################################################

# Executable name
EXEC 				:= program

# bin, assets, and install directories (bin and build root directories are kept for clean)
BIN_DIR_ROOT 		:= bin
RES_DIR 			:= res

# Sources (searches recursively inside the source directory)
SRC_DIR 			:= src
SRCS 				:= $(SRC_DIR)/*.cpp

# Includes
INCLUDE_DIR 		:= include/
INCLUDES 			:= -I$(INCLUDE_DIR)

# C++ compiler settings
CXX 				:= g++
CXXFLAGS 			:= -std=c++20 -O3 $(INCLUDES)
WARNINGS 			:= -Wall -Wpedantic -Wextra

# Linker flags
LDFLAGS 			:= -Llib/

# Libraries to link
LDLIBS 				:= -lmingw32 -lSDL2main -lSDL2

################################################################################
#### COMPILATION
################################################################################
all: build run over

build:
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRCS) $(WARNINGS) $(LDFLAGS) $(LDLIBS)

run:
	./$(EXEC)

over:
	pause
	cls