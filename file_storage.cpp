#include <fstream>
#include <iostream>
#include <string>
#include "json.hpp"

void print_vector(std::vector<float> vec){
    for(float f : vec){
        std::cout << f;
    }
    std::cout << std::endl;
}

void write_to_json(float accuracy, float wpm){
    std::ifstream read_file("results.json");
    nlohmann::json data;
    std::vector<float> accuracy_list;
    std::vector<float> wpm_list;
    if(read_file.is_open()){
        /* std::cout << "Successfully read / opened json file" << std::endl; */
        data = nlohmann::json::parse(read_file);
        read_file.close();
    }
    data["accuracy"].push_back(accuracy);
    data["wpm"].push_back(wpm);
    /* print_vector(accuracy_list);
    print_vector(wpm_list);
    print_vector(data["accuracy"]);
    print_vector(data["wpm"]); */
    std::ofstream write_file("results.json");
    if(write_file.is_open()){
        write_file << data.dump(4);
        write_file.close();
    }
}

/* void write_to_file(std::string result){
    std::ofstream file;
    file.open("results.txt", std::ios::app);

    file << result;

    file.close();
} */

int get_num_runs(){
    std::ifstream read_file("results.json");
    if(read_file.is_open()){
        nlohmann::json data = nlohmann::json::parse(read_file);
        return data["wpm"].size();
    }
    return -1;
}

float get_avg_accuracy(){
    std::ifstream read_file("results.json");

    float cumulative_accuracy = 0.0;
    int num_runs = get_num_runs();

    if(read_file.is_open()){
        nlohmann::json data = nlohmann::json::parse(read_file);
        for(float acc : data["accuracy"]){
            cumulative_accuracy += acc;
        }
        return cumulative_accuracy / num_runs;
    }
    return -1;
}

float get_avg_wpm(){
    std::ifstream read_file("results.json");

    float cumulative_wpm = 0.0;
    int num_runs = get_num_runs();

    if(read_file.is_open()){
        nlohmann::json data = nlohmann::json::parse(read_file);
        for(float acc : data["wpm"]){
            cumulative_wpm += acc;
        }
        return cumulative_wpm / num_runs;
    }
    return -1;
}