CXX := g++
CXXFLAGS := -O2 -Wall -Wextra -Wshadow -Wfatal-errors -std=c++23 -fsanitize=address,undefined -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC

a: a.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

r: a
	./a
