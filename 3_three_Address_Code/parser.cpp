#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <algorithm> // Added for std::all_of

// Symbol Table Entry
struct Symbol {
    std::string name;
    int version;
    Symbol(std::string name, int version) : name(name), version(version) {}
};

// Symbol Table
class SymbolTable {
    std::unordered_map<std::string, int> table;
public:
    std::string newName(const std::string& name) {
        int version = ++table[name];
        return name + "_" + std::to_string(version);
    }
    std::string currentName(const std::string& name) {
        return name + "_" + std::to_string(table[name]);
    }
    bool isConstant(const std::string& token) {
        return std::all_of(token.begin(), token.end(), ::isdigit);
    }
};

// Three Address Code Generator
class TACGenerator {
    SymbolTable symTable;
    std::vector<std::string> code;
public:
    void processLine(const std::string &line) {
        std::istringstream iss(line);
        std::string lhs, op, rhs1, rhs2;
        iss >> lhs >> op;
        if (op == "=") {
            iss >> rhs1 >> op;
            if (op == "+" || op == "-" || op == "*" || op == "/") {
                iss >> rhs2;
                std::string t1 = symTable.isConstant(rhs1) ? rhs1 + "_0" : symTable.currentName(rhs1);
                std::string t2 = symTable.isConstant(rhs2) ? rhs2 + "_0" : symTable.currentName(rhs2);
                std::string t3 = symTable.newName(lhs);
                code.push_back(t3 + " = " + t1 + " " + op + " " + t2);
            } else {
                std::string t1 = symTable.isConstant(rhs1) ? rhs1 + "_0" : symTable.currentName(rhs1);
                std::string t2 = symTable.newName(lhs);
                code.push_back(t2 + " = " + t1);
            }
        }
    }
    void printCode() {
        for (const auto &line : code) {
            std::cout << line << std::endl;
        }
    }
};

int main() {
    TACGenerator tacGen;
    std::ifstream infile("example.cpp");
    std::string line;

    if (!infile) {
        std::cerr << "Could not open the file!" << std::endl;
        return 1;
    }

    while (std::getline(infile, line)) {
        tacGen.processLine(line);
    }

    infile.close();
    tacGen.printCode();
    return 0;
}

