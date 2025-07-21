#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"

std::vector<std::string> words = {" Apple", " Banana", " Carrot", " Mango", " Apricot", " Pear", " Strawberry", " Blueberry", " Raspberry", " Orange", " Grapefruit", " Peach", " Nectarine", " Lime", " Pineapple", " Guava", " Watermelon", " Kiwi", " Cantaloupe"};

std::string generate_reference_quote(){
    httplib::SSLClient api("api.kanye.rest");

    /* api.set_follow_location(true);
    api.enable_server_certificate_verification(false); */

    auto response = api.Get("/");

    if(response && response->status == 200){
        /* std::cout << "API succesfully called" << std::endl; */
        nlohmann::json output = nlohmann::json::parse(response->body);
        return output["quote"];
    } else {
        /* std::cout << response->status << std::endl;
        std::cout << "API call failed" << std::endl; */
        return "";
    }
}

std::string generate_reference_string_api(int num){
    srand(time(0));
    std::string query = "/word?number=";
    if(num < 0){
        num = (rand() % 5) + 1;
    }
    query.append(std::to_string(num));
    
    httplib::SSLClient api("random-word-api.herokuapp.com");

    auto response = api.Get(query);
    if(response && response->status == 200){
        nlohmann::json output = nlohmann::json::parse(response->body);
        std::string return_string;
        for(std::string s : output){
            return_string.append(s);
            return_string.append(" ");
        }
        return return_string.substr(0, return_string.size() - 1);
    } else {
        std::cout << "Call failed" << std::endl;
        return "";
    }
} 

/* std::string generate_reference_string(){
    srand(time(0));

    int length = (rand() % 5) + 1;

    std::string ref_string = "";

    for(int i = 0; i < length; i++){
        int remove_index = rand() % words.size();
        ref_string.append(words.at(remove_index));
        words.erase(words.begin() + remove_index);
    }

    return ref_string.substr(1);
} */

std::string generate_reference_string(int num){
    srand(time(0));

    std::string ref_string = "";

    if(num < 0){
        num = (rand() % 5) + 1;
    }

    for(int i = 0; i < num; i++){
        int remove_index = rand() % words.size();
        ref_string.append(words.at(remove_index));
        words.erase(words.begin() + remove_index);
    }

    return ref_string.substr(1);
}

/* int main(){
    cout << generate_reference_string() << endl;
} */