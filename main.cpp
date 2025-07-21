#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <chrono>
#include "string_generator.cpp"
#include "file_storage.cpp"
#include "CLI11.hpp"

enum run_type {API, QUOTE, NORMAL};

float compare_accuracy(std::string, std::string);
float getWPM(float, float);
int is_num(std::string);
void run_typingtest(int, run_type);
void run_total_runs();
void run_accuracy();
void run_wpm();

/*IMPORTANT : compile with these flags "-std=c++11 -lssl -lcrypto -lws2_32 -lcrypt32" or api call won't work*/
int main(int argc, char* argv[]){

    CLI::App app{"Typing Test"};

    int num_words = -1;
    bool api{false};
    bool quote{false};

    auto run = app.add_subcommand("run", "Run a typing test");
    auto total_runs = app.add_subcommand("total_runs", "Get total number of typing test runs");
    auto accuracy = app.add_subcommand("accuracy", "Gets average accuracy from all typing test runs");
    auto wpm = app.add_subcommand("wpm", "Gets average wpm from all typing test runs");
    /* auto api = app.add_subcommand("api", "Gets and outputs random word from word api"); */

    run->add_option("num_words", num_words, "Number of words to be used for typing test")->default_val(-1);
    run->add_flag("-a", api, "Flag used to check for API request");
    run->add_flag("-q", quote, "Flag used to check for quote request");

    CLI11_PARSE(app, argc, argv);

    if(*run){
        if(api){
            run_typingtest(num_words, API);
        } else if(quote){
            run_typingtest(num_words, QUOTE);
        } else {
            run_typingtest(num_words, NORMAL);
        }
    } else if(*total_runs){
        run_total_runs();
    } else if(*accuracy){
        run_accuracy();
    } else if(*wpm){
        run_wpm();
    }

    /* if(argc > 2 && !strcmp(argv[1], "echo")){
        cout << argv[2] << endl;
    }
    if(argc > 1 && !strcmp(argv[1], "timer")){
        auto start = chrono::system_clock::now();
        string str;
        cin >> str; 
        auto end = chrono::system_clock::now();
        const chrono::duration<double> time = end - start;
        cout << "Printed " << str << " in " << time.count() << "s.";
    } */
    

    /*if(argc == 1){
        std::cout << "No parameters specified" << std::endl;
    } else if(argc > 1 && !strcmp(argv[1], "accuracy")){
        std::cout << "Your average accuracy is: "  << get_avg_accuracy() << std::endl;
    } else if(argc > 1 && !strcmp(argv[1], "total_runs")){
        std::cout << get_num_runs() << std::endl;
    } else if(argc > 1 && !strcmp(argv[1], "wpm")){
        std::cout << "Your average wpm is: " <<  get_avg_wpm() << std::endl;
    } else if(argc == 2 && !strcmp(argv[1], "run")){
        std::string ref_str = generate_reference_string();
        std::cout << "Your sentence is: " << ref_str << std::endl;
        std::string ans_str;
        auto start = std::chrono::high_resolution_clock::now();
        getline(std::cin, ans_str);
        auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double> elapsed_time = end - start;
        float accuracy = compare_accuracy(ref_str, ans_str);
        std::cout << "Your accuracy is: " << accuracy * 100 << "%, in " << elapsed_time.count() << "s" << std::endl;
        std::cout << "Your calculated WPM is: " << getWPM(elapsed_time.count(), ref_str.length() / 5.0) << std::endl;
        std::string result;
        result.append(std::to_string(accuracy * 100));
        result.append(", ");
        result.append(std::to_string(getWPM(elapsed_time.count(), ref_str.length() / 5.0)));
        result.append("\n");
        write_to_file(result);
    } else if(argc == 3 && !strcmp(argv[1], "run")){
        char* p;
        int num = strtol(argv[2], &p, 10);
        if(*p){
            std::cout << "Input for number of words is nonnumeric" << std::endl;
        } else {
            if(num > (int) words.size()){
                std::cout << "Input for number of words is incorrect" << std::endl;
                return 0;
            }
            std::string ref_str = generate_reference_string(num);
            std::cout << "Your sentence is: " << ref_str << std::endl;
            std::string ans_str;
            auto start = std::chrono::high_resolution_clock::now();
            getline(std::cin, ans_str);
            auto end = std::chrono::high_resolution_clock::now();
            const std::chrono::duration<double> elapsed_time = end - start;
            float accuracy = compare_accuracy(ref_str, ans_str);
            std::cout << "Your accuracy is: " << accuracy * 100 << "%, in " << elapsed_time.count() << "s" << std::endl;
            std::cout << "Your calculated WPM is: " << getWPM(elapsed_time.count(), ref_str.length() / 5.0) << std::endl;
            std::string result;
            result.append(std::to_string(accuracy * 100));
            result.append(", ");
            result.append(std::to_string(getWPM(elapsed_time.count(), ref_str.length() / 5.0)));
            result.append("\n");
            write_to_file(result);
        }
    }
    else{
        std::cout << "Invalid argument: " << argv[1] << std::endl;
    } */
} 

void run_typingtest(int num_words, run_type rt){

    std::string ref_str;
    if(rt == API){
        ref_str = generate_reference_string_api(num_words);
    } else if (rt == QUOTE){
        ref_str = generate_reference_quote();
    } else {
        std::string ref_str = generate_reference_string(num_words);
    }
    std::cout << "Your sentence is: " << ref_str << std::endl;
    std::string ans_str;
    auto start = std::chrono::high_resolution_clock::now();
    getline(std::cin, ans_str);
    auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> elapsed_time = end - start;
    float accuracy = compare_accuracy(ref_str, ans_str) * 100;
    float wpm = getWPM(elapsed_time.count(), ref_str.length() / 5.0);
    std::cout << "Your accuracy is: " << accuracy << "%, in " << elapsed_time.count() << "s" << std::endl;
    std::cout << "Your calculated WPM is: " << wpm << std::endl;
    write_to_json(accuracy, wpm);
    /* std::string result;
    result.append(std::to_string(accuracy));
    result.append(", ");
    result.append(std::to_string(wpm));
    result.append("\n");
    write_to_file(result); */
}

void run_total_runs(){
    std::cout << get_num_runs() << std::endl;
}

void run_accuracy(){
    std::cout << "Your average accuracy is: "  << get_avg_accuracy() << std::endl;
}

void run_wpm(){
    std::cout << "Your average wpm is: "  << get_avg_wpm() << std::endl;
}

float compare_accuracy(std::string reference, std::string answer){
    int answer_length = answer.length();
    int reference_length = reference.length();
    int mistakes = 0;

    if(answer_length > reference_length){
        mistakes += answer_length - reference_length;
        for(int i = 0; i < (int) reference.length(); i++){
            /* cout << "comparing " << reference.at(i) << " with " << answer.at(i) << endl; */
            if(reference.at(i) != answer.at(i)){
                mistakes++;
            }
        }
    } else {
        mistakes += reference_length - answer_length;
        for(int i = 0; i < (int) answer.length(); i++){
            /* cout << "comparing " << reference.at(i) << " with " << answer.at(i) << endl; */
            if(reference.at(i) != answer.at(i)){
                mistakes++;
            }
        }
    }

    /* cout << "Mistakes: " << mistakes << ", Reference string length: " << reference_length << endl;  */
    return 1 - ((float) mistakes / reference_length);
}

float getWPM(float time, float words){
    return words / (time / 60);
}
