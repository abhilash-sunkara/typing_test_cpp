using namespace std;

#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iostream>

vector<string> words = {" Apple", " Banana", " Carrot", " Mango", " Apricot", " Pear", " Strawberry", " Blueberry", " Raspberry", " Orange", " Grapefruit", " Peach", " Nectarine", " Lime", " Pineapple", " Guava", " Watermelon", " Kiwi", " Cantaloupe"};

string generate_reference_string(){
    srand(time(0));

    int length = (rand() % 5) + 1;

    string ref_string = "";

    for(int i = 0; i < length; i++){
        int remove_index = rand() % words.size();
        ref_string.append(words.at(remove_index));
        words.erase(words.begin() + remove_index);
    }

    return ref_string.substr(1);
}

/* int main(){
    cout << generate_reference_string() << endl;
} */