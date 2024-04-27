#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> split(string s, char del);
fstream openFile(string path);

int main() {

    string buf;
    int option = 0;
    int id,age;
    string name;

    do
    {

       cout << "Select one of the following options" << endl;
       cout << "0. Exit" << endl;
       cout << "1. Add person" << endl;
       cout << "2. Show people" << endl;

       cin >> option;

       switch (option) {
            case 0: 
                cout << "Bye!" << endl;
                break;

            case 1:
                    id = random();

                    cout << "Please write down your name: " << endl;
                    cin >> name;
                    cout << "Please write down your age : " << endl;
                    cin >> age;

                    try {
                        
                        auto file = openFile("people.txt");

                        file << to_string(id) + "," + name + "," + to_string(age) << endl;

                        file.close();

                        cout << "Person added successfully!" << endl;
                    } catch(const exception& e) {
                        cerr << e.what() << '\n';
                    }
                break;

            case 2: 

                try {

                    auto file = openFile("people.txt");

                    while(!file.eof()) {
                        getline(file, buf);

                        if(buf.empty()) {
                            continue;
                        }

                        const vector<string> data = split(buf, ',');

                        cout << 
                            "Id: " + data[0] + " | " +
                            "Name: " + data[1] + " | " + 
                            "Age: " + data[2] 
                        << endl;
                    }

                    file.close();
                } catch (const exception& e) {
                    cerr << e.what() << '\n';
                }

                break;
            
            default:
                cout << "Please select a valid option" << endl;
                break;
        }
        

    } while (option != 0);

}

vector<string> split(string s, char del) {

    vector<string> fields;
    string actual_field;

    for (string::size_type i = 0; i < s.size(); i++) {
        if(s[i] != ',') {
            actual_field.push_back(s[i]);

            if(i == s.size() - 1) {
                fields.push_back(actual_field);
            }

            continue;
        }

        fields.push_back(actual_field);
        actual_field = "";
    }

    return fields;
}

fstream openFile(string path) {
    return fstream(path, ios::in|ios::out|ios::app);
}