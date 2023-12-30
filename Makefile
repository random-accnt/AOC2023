CXX = g++
CXXFLAGS = -Wall -std=c++11
SRCDIR = src
BUILDDIR = bin
TARGET = aoc2023

ifeq ($(OS),Windows_NT)
	RM = cmd //C del //Q //F
	RMDIR = cmd /C rmdir /Q /S
	MKDIR = mkdir
	TARGET_EXTENSION = .exe
else
	RM = rm -f
	RMDIR = rm -rf
	MKDIR = mkdir -p
	TARGET_EXTENSION =
endif

SRCS := $(wildcard $(SRCDIR)/main.cpp)
SRCS += $(wildcard $(SRCDIR)/*/*.cpp)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(SRCDIR)/%.o,$(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)

$(SRCDIR)/%.o : $(SRCDIR)/%.cpp | $(BUILDDIR)
	echo "Recompiling: " $@
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILDDIR):
	$(MKDIR) $(BUILDDIR)

.PHONY: clean

clean:
	$(RM) $(SRCDIR)\main.o
	$(RM) $(SRCDIR)\*\*.o
	$(RMDIR) $(BUILDDIR)