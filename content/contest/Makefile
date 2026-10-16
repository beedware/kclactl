CXX := g++
CXXFLAGS := -O3 -Wall -Wconversion -Wfatal-errors -g -std=c++20

.DEFAULT_GOAL := help

.PHONY: clean help
help:
	@echo "Usage: make <program> (builds <program>.cpp into out/<program>)"

%: %.cpp
	mkdir -p out
	$(CXX) $(CXXFLAGS) $< -o out/$@

clean:
	rm -rf out
