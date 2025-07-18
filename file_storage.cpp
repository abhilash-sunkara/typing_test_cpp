#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void write_to_file(string result){
    ofstream file;
    file.open("results.txt", ios::app);

    file << result;

    file.close();
}

int get_num_runs(){
    ifstream file;
    file.open("results.txt", ios::app);
    string line;

    int nums = 0; 

    while(file >> line){
        if(line.find(',') != string::npos){
            nums++;
        }
    }

    return nums;
}

float get_avg_accuracy(){
    ifstream file;
    file.open("results.txt", ios::app);
    string line;

    int num_runs = get_num_runs();
    float accuracy_total = 0.0;

    while(file >> line){
        if(line.find(',') != string::npos){
            accuracy_total += stof(line.substr(0, line.length() - 1));
        }
    }

    return accuracy_total / num_runs;
}

float get_avg_wpm(){
    ifstream file;
    file.open("results.txt", ios::app);
    string line;

    int num_runs = get_num_runs();
    float wpm_total = 0.0;

    while(file >> line){
        if(line.find(',') == string::npos){
            wpm_total += stof(line);
        }
    }

    return wpm_total / num_runs;
}