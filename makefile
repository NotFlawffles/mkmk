CXX = c++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -ggdb -o
OBJECT = bin/mkmk
SRC = $(wildcard src/*.cpp)
INSTALLATION_TARGET = /usr/bin/

default: $(SRC)
	@mkdir -p bin
	@$(CXX) $(CXXFLAGS) $(OBJECT) $(SRC)

clean: $(OBJECT)
	@rm $(OBJECT)

install: $(INSTALLATION_TARGET)
	@make default
	@sudo mv $(OBJECT) $(INSTALLATION_TARGET)

uninstall: $(INSTALLATION_TARGET)
	@sudo rm $(INSTALLATION_TARGET)
