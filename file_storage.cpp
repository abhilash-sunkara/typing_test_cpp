#include <fstream>
#include <iostream>
#include <string>

void write_to_file(std::string result){
    std::ofstream file;
    file.open("results.txt", std::ios::app);

    file << result;

    file.close();
}

int get_num_runs(){
    std::ifstream file;
    file.open("results.txt", std::ios::app);
    std::string line;

    int nums = 0; 

    while(file >> line){
        if(line.find(',') != std::string::npos){
            nums++;
        }
    }

    return nums;
}

float get_avg_accuracy(){
    std::ifstream file;
    file.open("results.txt", std::ios::app);
    std::string line;

    int num_runs = get_num_runs();
    float accuracy_total = 0.0;

    while(file >> line){
        if(line.find(',') != std::string::npos){
            accuracy_total += std::stof(line.substr(0, line.length() - 1));
        }
    }

    return accuracy_total / num_runs;
}

float get_avg_wpm(){
    std::ifstream file;
    file.open("results.txt", std::ios::app);
    std::string line;

    int num_runs = get_num_runs();
    float wpm_total = 0.0;

    while(file >> line){
        if(line.find(',') == std::string::npos){
            wpm_total += std::stof(line);
        }
    }

    return wpm_total / num_runs;
}