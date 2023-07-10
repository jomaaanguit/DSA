#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

struct Node {
    string pcn;
    string last_name;
    string given_name;
    string middle_name;
    string birthdate;
    string sex;
    string marital_status;
    string blood_type;
    string nationality;
    string date_of_issue;
    string email_address;
    string home_address;
    string tag;
    Node* next = nullptr;
};

class Profile {
    Node* head = nullptr;
    Node* tail = nullptr;
    string filename = "profiles.txt";

public:
    Profile() {
        loadProfilesFromFile();
    }

    void loadProfilesFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            Node* current = nullptr;

            while (getline(file, line)) {
                if (line.find("PCN: ") == 0) {
                    current = new Node;
                    current->pcn = line.substr(5);
                    getline(file, current->last_name);
                    getline(file, current->given_name);
                    getline(file, current->middle_name);
                    getline(file, current->birthdate);
                    getline(file, current->sex);
                    getline(file, current->marital_status);
                    getline(file, current->blood_type);
                    getline(file, current->nationality);
                    getline(file, current->date_of_issue);
                    getline(file, current->email_address);
                    getline(file, current->home_address);
                    getline(file, current->tag);

                    current->next = nullptr;

                    if (head == nullptr) {
                        head = current;
                        tail = current;
                    } else {
                        tail->next = current;
                        tail = current;
                    }
                }
            }

            file.close();
        } else {
            cout << "Failed to open file!" << endl;
        }
    }

 void updateProfilesFile() {
    ofstream file(filename);
    if (file.is_open()) {
        Node* current = head;
        while (current != nullptr) {
            file << "PCN: " << current->pcn << endl;
            file << current->last_name << endl;
            file << current->given_name << endl;
            file << current->middle_name << endl;
            file << current->birthdate << endl;
            file << current->sex << endl;
            file << current->marital_status << endl;
            file << current->blood_type << endl;
            file << current->nationality << endl;
            file << current->date_of_issue << endl;
            file << current->email_address << endl;
            file << current->home_address << endl;
            file << current->tag << endl;
            file << endl;
            current = current->next;
        }
        file.close();
    } else {
        cout << "Failed to open file!" << endl;
    }
}


    void add_profile() {
        Node* new_profile = new Node;

        cout << "Enter PCN (Ex. xxxx-xxxx-xxxx-xxxx): ";
        getline(cin >> ws, new_profile->pcn);
        cout << "Enter Last Name: ";
        getline(cin >> ws, new_profile->last_name);
        cout << "Enter Given Name: ";
        getline(cin >> ws, new_profile->given_name);
        cout << "Enter Middle Name: ";
        getline(cin >> ws, new_profile->middle_name);
        cout << "Enter Birthdate (Ex. mm/dd/yyyy): ";
        getline(cin >> ws, new_profile->birthdate);
        cout << "Enter Sex (Ex. Male/Female): ";
        getline(cin >> ws, new_profile->sex);
        cout << "Enter Marital Status (Ex. Single/Married): ";
        getline(cin >> ws, new_profile->marital_status);
        cout << "Enter Blood Type (Ex. O+): ";
        getline(cin >> ws, new_profile->blood_type);
        cout << "Enter Nationality (Ex. Filipino): ";
        getline(cin >> ws, new_profile->nationality);
        cout << "Enter Date of Issue: ";
        getline(cin >> ws, new_profile->date_of_issue);
        cout << "Enter Email Address (Ex. juandelacruz@gmail.com): ";
        getline(cin >> ws, new_profile->email_address);
        cout << "Enter Home Address: ";
        getline(cin >> ws, new_profile->home_address);
        cout << "Enter Tag (Positive or Negative): ";
        getline(cin >> ws, new_profile->tag);

        new_profile->next = nullptr;

        if (head == nullptr) {
            head = new_profile;
            tail = new_profile;
        } else {
            tail->next = new_profile;
            tail = new_profile;
        }

        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << "PCN: " << new_profile->pcn << endl;
            file << "Last Name: " << new_profile->last_name << endl;
            file << "Given Name: " << new_profile->given_name << endl;
            file << "Middle Name: " << new_profile->middle_name << endl;
            file << "Birthdate: " << new_profile->birthdate << endl;
            file << "Sex: " << new_profile->sex << endl;
            file << "Marital Status: " << new_profile->marital_status << endl;
            file << "Blood Type: " << new_profile->blood_type << endl;
            file << "Nationality: " << new_profile->nationality << endl;
            file << "Date of Issue: " << new_profile->date_of_issue << endl;
            file << "Email Address: " << new_profile->email_address << endl;
            file << "Home Address: " << new_profile->home_address << endl;
            file << "Tag: " << new_profile->tag << endl;
            file << endl;
            file.close();
        } else {
            cout << "Failed to open file!" << endl;
        }
    }

    void delete_profile() {
        string pcn;
        cout << "Enter the PCN of the profile you want to delete: ";
        cin >> pcn;

        Node* current = head;
        Node* previous = nullptr;
        bool found = false;

        while (current != nullptr) {
            if (current->pcn == pcn) {
                found = true;

                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }

                if (current == tail) {
                    tail = previous;
                }

                delete current;
                cout << "The profile with PCN: " << pcn << " is successfully deleted" << endl << endl;
                break;
            }

            previous = current;
            current = current->next;
        }

        if (!found) {
            cout << "The profile with PCN: " << pcn << " does not exist" << endl << endl;
        }        updateProfilesFile();
    }

void display() {
    Node* current = head;
    while (current != nullptr) {
        cout << "PCN: " << current->pcn << endl;
        cout << "Last Name: " << current->last_name << endl;
        cout << "Given Name: " << current->given_name << endl;
        cout << "Middle Name: " << current->middle_name << endl;
        cout << "Birthdate: " << current->birthdate << endl;
        cout << "Sex: " << current->sex << endl;
        cout << "Marital Status: " << current->marital_status << endl;
        cout << "Blood Type: " << current->blood_type << endl;
        cout << "Nationality: " << current->nationality << endl;
        cout << "Date of Issue: " << current->date_of_issue << endl;
        cout << "Email Address: " << current->email_address << endl;
        cout << "Home Address: " << current->home_address << endl;
        cout << "Tag: " << current->tag << endl;
        cout << endl;
        current = current->next;
    }
}


    void search() {
        string pcn;
        cout << "Enter the PCN of the profile you want to search: ";
        cin >> pcn;
        cout << endl;

        Node* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->pcn == pcn) {
                found = true;
                cout << "PCN: " << current->pcn << endl;
                cout << "Full name: " << current->last_name << ", " << current->given_name << " " << current->middle_name << endl;
                cout << "Birthdate: " << current->birthdate << endl;
                cout << "Sex: " << current->sex << endl;
                cout << "Marital Status: " << current->marital_status << endl;
                cout << "Blood Type: " << current->blood_type << endl;
                cout << "Nationality: " << current->nationality << endl;
                cout << "Date of Issue: " << current->date_of_issue << endl;
                cout << "Email Address: " << current->email_address << endl;
                cout << "Tag: " << current->tag << endl;
                cout << endl;
            }
            current = current->next;
        }

        if (!found) {
            cout << "The profile with PCN: " << pcn << " does not exist" << endl << endl;
        }
    }
};

int main() {
    Profile profile;
    int choice;

    do {
        system("cls");
        cout << "PROFILE ADD/DELETE/DISPLAY/SEARCH" << endl << endl;
        cout << "[1] ADD PROFILE" << endl;
        cout << "[2] DELETE PROFILE" << endl;
        cout << "[3] DISPLAY ALL PROFILES" << endl;
        cout << "[4] SEARCH PROFILE" << endl;
        cout << "[5] EXIT PROGRAM" << endl << endl;
        cout << "ENTER CHOICE (1-5): ";
        cin >> choice;

        while (choice < 1 || choice > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ENTER CHOICE (1-5): ";
            cin >> choice;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        system("cls");

        if (choice == 1) {
            profile.add_profile();
        } else if (choice == 2) {
            profile.delete_profile();
        } else if (choice == 3) {
            profile.display();
        } else if (choice == 4) {
            profile.search();
        }

        profile.updateProfilesFile();

        system("pause");
    } while (choice != 5);

    cout << "Exiting Program..." << endl << endl;
    return 0;
}
