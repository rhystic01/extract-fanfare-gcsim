#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>

int main() {
    // opening "sample.txt" file for reading
    std::string input_filePath = "sample.txt";
    std::ifstream inputFile(input_filePath);
    if (!inputFile.is_open()) {
        std::cerr << "Error opening file for input: " << input_filePath << std::endl;
        return 1;
    }
    std::stringstream input_buffer;
    input_buffer << inputFile.rdbuf();
    std::string input = input_buffer.str();
    inputFile.close();

    // searching for these patterns in sample.txt file
    std::regex pattern_1 ("\"furina-burst-damage-buff\",\\[\"status: added\",\"expiry_frame: -1\",\"dmg%: [0-1]\\.[0-9]?[0-9]?");
    std::regex pattern_2_rev ("[0-9]?[0-9]?[0-9]?[0-9]?:\"emarf\"");

    // the algorithm
    std::smatch match_1;
    std::smatch match_2_rev;
    std::string newString;
    std::size_t cutoff;
    std::string outputString;
    std::vector<std::string> outputVector;

    while (true) {
        if (!std::regex_search(input.cbegin(), input.cend(), match_1, pattern_1)) {
            break;
        }

        newString = input.substr(0, match_1.position()); 
        std::reverse(newString.begin(), newString.end());

        if (std::regex_search(newString.cbegin(), newString.cend(), match_2_rev, pattern_2_rev)) {
            std::string backtonormal = match_2_rev[0];
            std::reverse(backtonormal.begin(), backtonormal.end());
            outputString = backtonormal.append(match_1[0]);
        }

        outputVector.push_back(outputString);

        cutoff = match_1.position() + match_1.length();
        if(input.length() >= cutoff) {
            input = input.substr(cutoff);
        } 
    }

    // opening file output.txt for writing data
    std::string output_filePath = "output.txt";
    std::ofstream outputFile(output_filePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for output: " << output_filePath << std::endl;
        return 1;
    }

    std::regex pattern_finish_1 ("[0-9]?[0-9]?[0-9]?[0-9]");
    std::regex pattern_finish_2 ("[0-1]\\.[0-9]?[0-9]?");
    std::smatch match_pattern_finish_1;
    std::smatch match_pattern_finish_2;

    for (const auto& str : outputVector) {
        if (std::regex_search(str, match_pattern_finish_1, pattern_finish_1)) {
            outputFile << std::stof(match_pattern_finish_1[0])/60  << " ";
        }

        if (std::regex_search(str, match_pattern_finish_2, pattern_finish_2)) {
            outputFile << std::stof(match_pattern_finish_2[0])/0.0023 << std::endl;
        }
    }

    outputFile.close(); 

    return 0;
}