using namespace std;

#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <chrono>
#include "string_generator.cpp"
#include "file_storage.cpp"

float compare_accuracy(string, string);
float getWPM(float, float);
int is_num(string);


int main(int argc, char* argv[]){

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
    

    if(argc == 1){
        cout << "No parameters specified" << endl;
    } else if(argc > 1 && !strcmp(argv[1], "accuracy")){
        cout << "Your average accuracy is: "  << get_avg_accuracy() << endl;
    } else if(argc > 1 && !strcmp(argv[1], "total_runs")){
        cout << get_num_runs() << endl;
    } else if(argc > 1 && !strcmp(argv[1], "wpm")){
        cout << "Your average wpm is: " <<  get_avg_wpm() << endl;
    } else if(argc == 2 && !strcmp(argv[1], "run")){
        string ref_str = generate_reference_string();
        cout << "Your sentence is: " << ref_str << endl;
        string ans_str;
        auto start = chrono::high_resolution_clock::now();
        getline(cin, ans_str);
        auto end = chrono::high_resolution_clock::now();
        const chrono::duration<double> elapsed_time = end - start;
        float accuracy = compare_accuracy(ref_str, ans_str);
        cout << "Your accuracy is: " << accuracy * 100 << "%, in " << elapsed_time.count() << "s" << endl;
        cout << "Your calculated WPM is: " << getWPM(elapsed_time.count(), ref_str.length() / 5.0) << endl;
        string result;
        result.append(to_string(accuracy * 100));
        result.append(", ");
        result.append(to_string(getWPM(elapsed_time.count(), ref_str.length() / 5.0)));
        result.append("\n");
        write_to_file(result);
    } else if(argc == 3 && !strcmp(argv[1], "run")){
        char* p;
        int num = strtol(argv[2], &p, 10);
        if(*p){
            cout << "Input for number of words is nonnumeric" << endl;
        } else {
            if(num > (int) words.size()){
                cout << "Input for number of words is incorrect" << endl;
                return 0;
            }
            string ref_str = generate_reference_string(num);
            cout << "Your sentence is: " << ref_str << endl;
            string ans_str;
            auto start = chrono::high_resolution_clock::now();
            getline(cin, ans_str);
            auto end = chrono::high_resolution_clock::now();
            const chrono::duration<double> elapsed_time = end - start;
            float accuracy = compare_accuracy(ref_str, ans_str);
            cout << "Your accuracy is: " << accuracy * 100 << "%, in " << elapsed_time.count() << "s" << endl;
            cout << "Your calculated WPM is: " << getWPM(elapsed_time.count(), ref_str.length() / 5.0) << endl;
            string result;
            result.append(to_string(accuracy * 100));
            result.append(", ");
            result.append(to_string(getWPM(elapsed_time.count(), ref_str.length() / 5.0)));
            result.append("\n");
            write_to_file(result);
        }
    }
    else{
        cout << "Invalid argument: " << argv[1] << endl;
    }
} 


float compare_accuracy(string reference, string answer){
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
