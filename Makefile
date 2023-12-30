CXX = g++
CXXFLAGS = -Wall -std=c++11
SRCDIR = src
BUILDDIR = build
TARGET = aoc2023

ifeq ($(OS),Windows_NT)
	RM = cmd /C del /Q
	RMDIR = cmd /C rmdir /Q /S
	MKDIR = mkdir
	TARGET_EXTENSION = .exe
	SRCS := $(wildcard $(SRCDIR)/main.cpp)
	SRCS += $(wildcard $(SRCDIR)/*/*.cpp)
	OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(BUILDDIR)/%.o)
else
	RM = rm -f
	RMDIR = rm -rf
	MKDIR = mkdir -p
	TARGET_EXTENSION =
	SRCS := $(wildcard $(SRCDIR)/*.cpp)
	SRCS += $(wildcard $(SRCDIR)/*/*.cpp)
	OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))
endif

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET)$(TARGET_EXTENSION) $(BUILDDIR)/*.o

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp | $(BUILDDIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $(BUILDDIR)/$(notdir $@)

$(BUILDDIR):
	$(MKDIR) $(BUILDDIR)

.PHONY: clean

clean:
	$(RM) $(TARGET)$(TARGET_EXTENSION)
	$(RMDIR) $(BUILDDIR)