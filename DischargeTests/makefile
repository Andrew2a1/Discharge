CC = g++
CXXFLAGS=-g -std=c++11 -Wall -pedantic
PROG_NAME = discharge_tests

OUT_DIR = bin
BUILD_DIR = build

WORK_DIRS = ../physical/ ../toolbox/

TESTS_SRC = src
INCLUDE_DIRS = $(patsubst %, -I%, $(WORK_DIRS)) -Iinclude -I..

SRC = $(foreach dir, $(WORK_DIRS), $(wildcard $(dir)*.cpp))

ifeq ($(OS),Windows_NT)
	EXT = .exe
else
	EXT = 
endif

OUT = $(OUT_DIR)/$(PROG_NAME)$(EXT)

FILES = $(notdir $(wildcard $(TESTS_SRC)/*.cpp) $(SRC))
OBJS = $(foreach file,$(subst .cpp,.o,$(FILES)),$(BUILD_DIR)/$(file))

all: build_dirs $(OBJS)
	$(CC) $(CXXFLAGS) $(INCLUDE_DIRS) -o $(OUT) $(OBJS)

$(BUILD_DIR)/%.o: $(TESTS_SRC)/%.cpp
	$(CC) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

$(BUILD_DIR)/%.o: ../*/%.cpp
	$(CC) $(CXXFLAGS) $(INCLUDE_DIRS) -c $< -o $@

build_dirs:
	-mkdir $(BUILD_DIR)
	-mkdir $(OUT_DIR)

run:
	$(OUT)

clean:
	-rm -f $(OBJS) $(OUT)
