#include <fstream>
#include <iostream>
#include <filesystem>

#define MINIMUM_ARGV_REQUIRED 4

int main(int argc, char** argv) {
    if (argc < MINIMUM_ARGV_REQUIRED) {
	std::cerr << "expected 4 arguments" << std::endl;
	return EXIT_FAILURE;
    }

    std::string name = argv[1];
    std::string compiler = argv[2];
    std::string type = argv[3];

    if (compiler != "c" && compiler != "cpp") {
	std::cerr << "expected c or cpp for the second argument" << std::endl;
	return EXIT_FAILURE;
    }

    if (type != "simple" && type != "complex") {
	std::cerr << "expected simple or complex for the third argument" << std::endl;
	return EXIT_FAILURE;
    }

    std::filesystem::remove("makefile");
    std::fstream file("makefile", std::ios::app);

    if (compiler == "c") {
	file << "CC = cc" << std::endl
	     << "CFLAGS = ";
    } else {
	file << "CXX = c++" << std::endl
	     << "CXXFLAGS = ";
    }

    file << "-Wall -Wextra -pedantic -ggdb -o" << std::endl
	 << "OBJECT = " << "bin/" << name << std::endl
	 << "SRC = ";

    if (type == "simple") {
	file << "$(wildcard src/*." << compiler << ')' << std::endl;
    } else {
	file << "$(shell find src/ -type f -name *." << compiler << ')' << std::endl;
    }

    file << "INSTALLATION_TARGET = /usr/bin/" << std::endl;

    file << std::endl
	 << "default: $(SRC)"
	 << std::endl
	 << "\t@mkdir -p bin" << std::endl
	 << "\t@" << (compiler == "c" ? "$(CC) $(CFLAGS)" : "$(CXX) $(CXXFLAGS)") << " $(OBJECT) $(SRC)" << std::endl;

    file << std::endl
	 << "clean: $(OBJECT)" << std::endl
	 << "\t@rm $(OBJECT)" << std::endl;

    file << std::endl
	 << "install: $(INSTALLATION_TARGET)" << std::endl
	 << "\t@make default" << std::endl
	 << "\t@sudo mv $(OBJECT) $(INSTALLATION_TARGET)" << std::endl;

    file << std::endl
	 << "uninstall: $(INSTALLATION_TARGET)" << std::endl
	 << "\t@sudo rm $(INSTALLATION_TARGET)";

    file.close();
    return EXIT_SUCCESS;
}
