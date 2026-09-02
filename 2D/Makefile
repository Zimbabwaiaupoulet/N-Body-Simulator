CXX = g++
CPPFLAGS = -Iheaders

SRCDIR = src
BINDIR = bin
CSV_DIR = csv
TARGET = $(BINDIR)/main
TARGET_A2 = $(BINDIR)/mainA2
TARGET_N = $(BINDIR)/mainN
TARGET_BRUTE = $(BINDIR)/mainBrute
TARGET_B2 = $(BINDIR)/mainB2
TARGET_B3 = $(BINDIR)/mainB3
TARGET_B1 = $(BINDIR)/testB1
TARGET_VECTOR = $(BINDIR)/testVector2D
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/Vector2D.cpp
SOURCES_A2 = $(SRCDIR)/mainA2.cpp $(SRCDIR)/Vector2D.cpp
SOURCES_N = $(SRCDIR)/mainN.cpp $(SRCDIR)/Vector2D.cpp
SOURCES_BRUTE = $(SRCDIR)/mainBrute.cpp $(SRCDIR)/Vector2D.cpp
SOURCES_B2 = $(SRCDIR)/mainB2.cpp $(SRCDIR)/Vector2D.cpp
SOURCES_B3 = $(SRCDIR)/mainB3.cpp $(SRCDIR)/Vector2D.cpp
SOURCES_B1 = $(SRCDIR)/testB1.cpp
SOURCES_VECTOR = $(SRCDIR)/testVector2D.cpp $(SRCDIR)/Vector2D.cpp

all: $(TARGET) $(TARGET_A2) $(TARGET_N) $(TARGET_BRUTE) $(TARGET_B2) $(TARGET_B3) $(TARGET_B1) $(TARGET_VECTOR)

$(BINDIR):
	mkdir -p $(BINDIR)

$(CSV_DIR):
	mkdir -p $(CSV_DIR)

$(TARGET): $(SOURCES) | $(BINDIR)
	$(CXX) $(CPPFLAGS) $(SOURCES) -o $(TARGET)

$(TARGET_A2): $(SOURCES_A2) | $(BINDIR)
	$(CXX) $(CPPFLAGS) $(SOURCES_A2) -o $(TARGET_A2)

$(TARGET_N): $(SOURCES_N) | $(BINDIR)
	$(CXX) $(CPPFLAGS) $(SOURCES_N) -o $(TARGET_N)

$(TARGET_BRUTE): $(SOURCES_BRUTE) | $(BINDIR)
	$(CXX) $(CPPFLAGS) $(SOURCES_BRUTE) -o $(TARGET_BRUTE)

$(TARGET_B2): $(SOURCES_B2) | $(BINDIR)
	$(CXX) $(CPPFLAGS) $(SOURCES_B2) -o $(TARGET_B2)

$(TARGET_B3): $(SOURCES_B3) | $(BINDIR)
	$(CXX) $(CPPFLAGS) $(SOURCES_B3) -o $(TARGET_B3)

$(TARGET_B1): $(SOURCES_B1) | $(BINDIR)
	$(CXX) $(CPPFLAGS) $(SOURCES_B1) -o $(TARGET_B1)

$(TARGET_VECTOR): $(SOURCES_VECTOR) | $(BINDIR)
	$(CXX) $(CPPFLAGS) $(SOURCES_VECTOR) -o $(TARGET_VECTOR)

run: $(TARGET) | $(CSV_DIR)
	./$(TARGET)

runA2: $(TARGET_A2) | $(CSV_DIR)
	./$(TARGET_A2)

runA3: $(TARGET_N) | $(CSV_DIR)
	./$(TARGET_N)

runBrute: $(TARGET_BRUTE) | $(CSV_DIR)
	./$(TARGET_BRUTE)

runB2: $(TARGET_B2) | $(CSV_DIR)
	./$(TARGET_B2)

runB3: $(TARGET_B3) | $(CSV_DIR)
	./$(TARGET_B3)

runB1: $(TARGET_B1)
	./$(TARGET_B1)

runVector2D: $(TARGET_VECTOR)
	./$(TARGET_VECTOR)

runall: all | $(CSV_DIR)
	$(MAKE) -j run runA2 runN runBrute runB2 runB3 runB1 runVector2D

clean:
	rm -rf $(BINDIR) $(CSV_DIR)

.PHONY: all run runA2 runN runBrute runB2 runB3 runB1 runVector2D runall clean
