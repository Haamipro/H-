#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <fstream> // For file I/O
#include <windows.h>
#include <shlobj.h> // For SHGetFolderPath

std::unordered_map<std::string, int> variables;
std::unordered_map<std::string, std::vector<std::string>> functions;
std::vector<std::string> programCommands;

void execute(const std::string& line);

void execute_function(const std::string& name) {
    if (functions.find(name) != functions.end()) {
        for (const auto& command : functions[name]) {
            execute(command);
        }
    }
    else {
        std::cerr << "Unknown function: " << name << std::endl;
    }
}

void execute(const std::string& line) {
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "set") {
        std::string var;
        int value;
        iss >> var >> value;
        variables[var] = value;
    }
    else if (command == "print") {
        std::string var;
        iss >> var;
        std::cout << variables[var] << std::endl;
    }
    else if (command == "add") {
        std::string var1, var2, result;
        iss >> var1 >> var2 >> result;
        variables[result] = variables[var1] + variables[var2];
    }
    else if (command == "subtract") {
        std::string var1, var2, result;
        iss >> var1 >> var2 >> result;
        variables[result] = variables[var1] - variables[var2];
    }
    else if (command == "def") {
        std::string funcName;
        iss >> funcName;
        std::vector<std::string> body;
        std::string line;
        while (std::getline(std::cin, line) && line != "end") {
            body.push_back(line);
        }
        functions[funcName] = body;
    }
    else if (command == "random") {
        std::string var;
        int max_value;
        iss >> var >> max_value;
        variables[var] = rand() % max_value + 1; // Generate a random number between 1 and max_value
    }
    else if (command == "loop") {
        int iterations;
        iss >> iterations;
        std::vector<std::string> body;
        std::string line;
        while (std::getline(std::cin, line) && line != "end") {
            body.push_back(line);
        }
        for (int i = 0; i < iterations; ++i) {
            for (const auto& cmd : body) {
                execute(cmd);
            }
        }
    }
    else if (command == "while") {
        std::string conditionVar;
        int conditionValue;
        iss >> conditionVar >> conditionValue;
        std::vector<std::string> whileBody;
        std::vector<std::string> elseBody;
        std::string line;
        bool elseBlock = false;

        while (std::getline(std::cin, line) && line != "end") {
            if (line == "else") {
                elseBlock = true;
                continue;
            }

            if (elseBlock) {
                elseBody.push_back(line);
            }
            else {
                whileBody.push_back(line);
            }
        }

        if (variables[conditionVar] != conditionValue) {
            for (const auto& cmd : whileBody) {
                execute(cmd);
            }
        }
        else {
            for (const auto& cmd : elseBody) {
                execute(cmd);
            }
        }
    }
    else if (functions.find(command) != functions.end()) {
        execute_function(command);
    }
    else {
        std::cerr << "Unknown command: " << command << std::endl;
    }
}

void saveProgram(const std::string& filePath) {
    std::ofstream outFile(filePath);
    if (outFile.is_open()) {
        for (const auto& command : programCommands) {
            outFile << command << std::endl;
        }
        outFile.close();
        std::cout << "Program saved to: " << filePath << std::endl;
    }
    else {
        std::cerr << "Could not open file for writing: " << filePath << std::endl;
    }
}

std::string getDesktopPath() {
    char path[MAX_PATH];
    if (SHGetFolderPathA(NULL, CSIDL_DESKTOPDIRECTORY, NULL, 0, path) != S_OK) {
        std::cerr << "Failed to get the desktop path." << std::endl;
        return "";
    }
    return std::string(path);
}

int main() {
    std::string line;
    std::cout << "Simple Programming Language Interpreter" << std::endl;

    // Initialize random seed
    srand(static_cast<unsigned int>(time(0)));

    while (std::getline(std::cin, line)) {
        if (line == "exit") {
            std::string desktopPath = getDesktopPath();
            if (!desktopPath.empty()) {
                std::string filePath = desktopPath + "\\H#project.txt";
                saveProgram(filePath);
            }
            break;
        }
        programCommands.push_back(line);
        execute(line);
    }

    return 0;
}
