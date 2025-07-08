using namespace std;

#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <chrono>
#include "string_generator.cpp"

float compare_accuracy(string, string);
float getWPM(float, float);
string generate_reference_string();


int main(int argc, char* argv[]){
    if(argc == 1){
        cout << "No parameters specified" << endl;
    }
    if(argc > 2 && !strcmp(argv[1], "echo")){
        cout << argv[2] << endl;
    }
    if(argc > 1 && !strcmp(argv[1], "timer")){
        auto start = chrono::system_clock::now();
        string str;
        cin >> str; 
        auto end = chrono::system_clock::now();
        const chrono::duration<double> time = end - start;
        cout << "Printed " << str << " in " << time.count() << "s.";
    }
    if(argc > 1 && !strcmp(argv[1], "accuracy")){
        cout << "Your word is: apple" << endl;
        string str;
        cin >> str;
        float accuracy = compare_accuracy("apple", str);
        cout << "Your accuracy is: " << accuracy * 100 << "%" << endl;
    }
    if(argc > 1 && !strcmp(argv[1], "run")){
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