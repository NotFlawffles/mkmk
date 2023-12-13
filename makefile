CXX = c++
CXXFLAGS = -Wall -Wextra -pedantic -ggdb -o
OBJECT = mkmk
SRC = $(wildcard src/*.cpp)
INSTALLATION_TARGET = /usr/bin/mkmk

default: $(SRC)
	@$(CXX) $(CXXFLAGS) $(OBJECT) $(SRC)

clean: $(OBJECT)
	@rm $(OBJECT)

install: $(INSTALLATION_TARGET)
	@make default
	@sudo mv $(OBJECT) $(INSTALLATION_TARGET)

uninstall: $(INSTALLATION_TARGET)
	@sudo rm $(INSTALLATION_TARGET)