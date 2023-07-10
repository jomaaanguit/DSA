#include <iostream>
#include <fstream>
#include <string>
#include <limits>

struct Node {
    std::string pcn;
    std::string last_name;
    std::string given_name;
    std::string middle_name;
    std::string birthdate;
    std::string sex;
    std::string marital_status;
    std::string blood_type;
    std::string nationality;
    std::string date_of_issue;
    std::string email_address;
    std::string home_address;
    std::string tag;
    Node* next = nullptr;
};

class Profile {
    Node* head = nullptr;
    Node* tail = nullptr;
    std::string filename = "profiles.txt";

public:
    Profile() {
        loadProfilesFromFile();
    }

    void loadProfilesFromFile() {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string line;
            Node* current = nullptr;

            while (std::getline(file, line)) {
                if (line.find("PCN: ") == 0) {
                    current = new Node;
                    current->pcn = line.substr(5);
                    std::getline(file, current->last_name);
                    std::getline(file, current->given_name);
                    std::getline(file, current->middle_name);
                    std::getline(file, current->birthdate);
                    std::getline(file, current->sex);
                    std::getline(file, current->marital_status);
                    std::getline(file, current->blood_type);
                    std::getline(file, current->nationality);
                    std::getline(file, current->date_of_issue);
                    std::getline(file, current->email_address);
                    std::getline(file, current->home_address);
                    std::getline(file, current->tag);

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
            std::cout << "Failed to open file!" << std::endl;
        }
    }

 void updateProfilesFile() {
    std::ofstream file(filename);
    if (file.is_open()) {
        Node* current = head;
        while (current != nullptr) {
            file << "PCN: " << current->pcn << std::endl;
            file << current->last_name << std::endl;
            file << current->given_name << std::endl;
            file << current->middle_name << std::endl;
            file << current->birthdate << std::endl;
            file << current->sex << std::endl;
            file << current->marital_status << std::endl;
            file << current->blood_type << std::endl;
            file << current->nationality << std::endl;
            file << current->date_of_issue << std::endl;
            file << current->email_address << std::endl;
            file << current->home_address << std::endl;
            file << current->tag << std::endl;
            file << std::endl;
            current = current->next;
        }
        file.close();
    } else {
        std::cout << "Failed to open file!" << std::endl;
    }
}


    void add_profile() {
        Node* new_profile = new Node;

        std::cout << "Enter PCN (Ex. xxxx-xxxx-xxxx-xxxx): ";
        std::getline(std::cin >> std::ws, new_profile->pcn);
        std::cout << "Enter Last Name: ";
        std::getline(std::cin >> std::ws, new_profile->last_name);
        std::cout << "Enter Given Name: ";
        std::getline(std::cin >> std::ws, new_profile->given_name);
        std::cout << "Enter Middle Name: ";
        std::getline(std::cin >> std::ws, new_profile->middle_name);
        std::cout << "Enter Birthdate (Ex. mm/dd/yyyy): ";
        std::getline(std::cin >> std::ws, new_profile->birthdate);
        std::cout << "Enter Sex (Ex. Male/Female): ";
        std::getline(std::cin >> std::ws, new_profile->sex);
        std::cout << "Enter Marital Status (Ex. Single/Married): ";
        std::getline(std::cin >> std::ws, new_profile->marital_status);
        std::cout << "Enter Blood Type (Ex. O+): ";
        std::getline(std::cin >> std::ws, new_profile->blood_type);
        std::cout << "Enter Nationality (Ex. Filipino): ";
        std::getline(std::cin >> std::ws, new_profile->nationality);
        std::cout << "Enter Date of Issue: ";
        std::getline(std::cin >> std::ws, new_profile->date_of_issue);
        std::cout << "Enter Email Address (Ex. juandelacruz@gmail.com): ";
        std::getline(std::cin >> std::ws, new_profile->email_address);
        std::cout << "Enter Home Address: ";
        std::getline(std::cin >> std::ws, new_profile->home_address);
        std::cout << "Enter Tag (Positive or Negative): ";
        std::getline(std::cin >> std::ws, new_profile->tag);

        new_profile->next = nullptr;

        if (head == nullptr) {
            head = new_profile;
            tail = new_profile;
        } else {
            tail->next = new_profile;
            tail = new_profile;
        }

        std::ofstream file(filename, std::ios::app);
        if (file.is_open()) {
            file << "PCN: " << new_profile->pcn << std::endl;
            file << "Last Name: " << new_profile->last_name << std::endl;
            file << "Given Name: " << new_profile->given_name << std::endl;
            file << "Middle Name: " << new_profile->middle_name << std::endl;
            file << "Birthdate: " << new_profile->birthdate << std::endl;
            file << "Sex: " << new_profile->sex << std::endl;
            file << "Marital Status: " << new_profile->marital_status << std::endl;
            file << "Blood Type: " << new_profile->blood_type << std::endl;
            file << "Nationality: " << new_profile->nationality << std::endl;
            file << "Date of Issue: " << new_profile->date_of_issue << std::endl;
            file << "Email Address: " << new_profile->email_address << std::endl;
            file << "Home Address: " << new_profile->home_address << std::endl;
            file << "Tag: " << new_profile->tag << std::endl;
            file << std::endl;
            file.close();
        } else {
            std::cout << "Failed to open file!" << std::endl;
        }
    }

    void delete_profile() {
        std::string pcn;
        std::cout << "Enter the PCN of the profile you want to delete: ";
        std::cin >> pcn;
        std::cout << std::endl; 

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
                std::cout << "The profile with PCN: " << pcn << " is successfully deleted" << std::endl << std::endl;
                break;
            }

            previous = current;
            current = current->next;
        }

        if (!found) {
            std::cout << "The profile with PCN: " << pcn << " does not exist" << std::endl << std::endl;
        }        updateProfilesFile();
    }

void display() {
    Node* current = head;

    if (current == nullptr) {
        std::cout << "No profile found..." << std::endl << std::endl;
        return;
    }

    while (current != nullptr) {
        std::cout << "PCN: " << current->pcn << std::endl;
        std::cout << "Last Name: " << current->last_name << std::endl;
        std::cout << "Given Name: " << current->given_name << std::endl;
        std::cout << "Middle Name: " << current->middle_name << std::endl;
        std::cout << "Birthdate: " << current->birthdate << std::endl;
        std::cout << "Sex: " << current->sex << std::endl;
        std::cout << "Marital Status: " << current->marital_status << std::endl;
        std::cout << "Blood Type: " << current->blood_type << std::endl;
        std::cout << "Nationality: " << current->nationality << std::endl;
        std::cout << "Date of Issue: " << current->date_of_issue << std::endl;
        std::cout << "Email Address: " << current->email_address << std::endl;
        std::cout << "Home Address: " << current->home_address << std::endl;
        std::cout << "Tag: " << current->tag << std::endl;
        std::cout << std::endl;
        current = current->next;
    }
}


    void search() {
        std::string pcn;
        std::cout << "Enter the PCN of the profile you want to search: ";
        std::cin >> pcn;
        std::cout << std::endl;

        Node* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->pcn == pcn) {
                found = true;
                std::cout << "PCN: " << current->pcn << std::endl;
                std::cout << "Full name: " << current->last_name << ", " << current->given_name << " " << current->middle_name << std::endl;
                std::cout << "Birthdate: " << current->birthdate << std::endl;
                std::cout << "Sex: " << current->sex << std::endl;
                std::cout << "Marital Status: " << current->marital_status << std::endl;
                std::cout << "Blood Type: " << current->blood_type << std::endl;
                std::cout << "Nationality: " << current->nationality << std::endl;
                std::cout << "Date of Issue: " << current->date_of_issue << std::endl;
                std::cout << "Email Address: " << current->email_address << std::endl;
                std::cout << "Tag: " << current->tag << std::endl;
                std::cout << std::endl;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "The profile with PCN: " << pcn << " does not exist" << std::endl << std::endl;
        }
    }
};

int main() {
    Profile profile;
    int choice;

    do {
        system("cls");
        std::cout << "PROFILE ADD/DELETE/DISPLAY/SEARCH" << std::endl << std::endl;
        std::cout << "[1] ADD PROFILE" << std::endl;
        std::cout << "[2] DELETE PROFILE" << std::endl;
        std::cout << "[3] DISPLAY ALL PROFILES" << std::endl;
        std::cout << "[4] SEARCH PROFILE" << std::endl;
        std::cout << "[5] EXIT PROGRAM" << std::endl << std::endl;
        std::cout << "ENTER CHOICE (1-5): ";
        std::cin >> choice;

        while (choice < 1 || choice > 5) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ENTER CHOICE (1-5): ";
            std::cin >> choice;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

    std::cout << "Exiting Program..." << std::endl << std::endl;
    return 0;
}
