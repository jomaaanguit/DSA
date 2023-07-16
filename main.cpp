#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <regex>
#include <cctype>
#include <algorithm>
#include <ctime>

bool isValidPCN(const std::string& pcn) {
    std::regex pcnPattern(R"(\d{4}-\d{4}-\d{4}-\d{4})");
    return std::regex_match(pcn, pcnPattern);
}

std::string getValidPCNInput() {
    std::string input;
    std::cout << "Enter PCN (xxxx-xxxx-xxxx-xxxx): ";
    std::getline(std::cin >> std::ws, input);

    while (!isValidPCN(input)) {
        std::cout << "Invalid PCN format. Enter PCN: ";
        std::getline(std::cin >> std::ws, input);
    }

    return input;
} 

bool isValidName(const std::string& name) {
    bool capitalLetterExpected = true;

    for (char c : name) {
        if (std::isspace(c)) {
            capitalLetterExpected = true;
        }
        else if (capitalLetterExpected && std::isalpha(c)) {
            if (!std::isupper(c)) {
                return false;
            }
            capitalLetterExpected = false;
        }
        else if (!capitalLetterExpected && std::isalpha(c)) {
            if (!std::islower(c)) {
                return false;
            }
        }
        else {
            return false;
        }
    }

    return !name.empty();
}

std::string getValidNameInput(const std::string& fieldName) {
    std::string input;
    std::cout << "Enter " << fieldName << ": ";
    std::getline(std::cin >> std::ws, input);

    while (!isValidName(input)) {
        std::cout << "Invalid " << fieldName << ". Enter " << fieldName << ": ";
        std::getline(std::cin >> std::ws, input);
    }

    return input;
}

bool isValidDate(const std::string& birthdate) {
    std::regex birthdatePattern(R"(^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/(19|20)\d\d$)");
    return std::regex_match(birthdate, birthdatePattern);
}

std::string getValidDateInput(const std::string& fieldName) {
    std::string input;
    std::cout << "Enter " << fieldName << " (mm/dd/yyyy): ";
    std::getline(std::cin >> std::ws, input);

    while (!isValidDate(input)) {
        std::cout << "Invalid " << fieldName << ". Enter " << fieldName;
        std::getline(std::cin >> std::ws, input);
    }

    return input;
}

bool isValidBloodType(const std::string& bloodType) {
    std::regex bloodTypePattern(R"(^(A|B|AB|O)[+-]$)");
    return std::regex_match(bloodType, bloodTypePattern);
}

std::string getValidBloodTypeInput() {
    std::string input;
    std::cout << "Enter Blood Type (Ex. O+): ";
    std::getline(std::cin >> std::ws, input);

    while (!isValidBloodType(input)) {
        std::cout << "Invalid Blood Type. Enter Blood Type (Ex. O+): ";
        std::getline(std::cin >> std::ws, input);
    }

    return input;
}

bool isValidEmailAddress(const std::string& emailAddress) {
    std::regex emailPattern(R"(^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}$)");
    return std::regex_match(emailAddress, emailPattern);
}

std::string getValidEmailAddressInput() {
    std::string input;
    std::cout << "Enter Email Address (Ex. example@mail.com): ";
    std::getline(std::cin >> std::ws, input);

    while (!isValidEmailAddress(input)) {
        std::cout << "Invalid Email Address. Enter Email Address: ";
        std::getline(std::cin >> std::ws, input);
    }

    return input;
}

template <typename Validator>
std::string getInput(const std::string& prompt, const std::string& errorMessage, Validator validator) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin >> std::ws, input);

    while (!validator(input)) {
        std::cout << errorMessage;
        std::getline(std::cin >> std::ws, input);
    }

    return input;
}

bool isValidTag(const std::string& tag) {
    std::string uppercaseTag = tag;
    std::transform(uppercaseTag.begin(), uppercaseTag.end(), uppercaseTag.begin(), [](unsigned char c) {
        return std::toupper(c);
        });

    return uppercaseTag == "POSITIVE" || uppercaseTag == "NEGATIVE";
}

bool isValidSex(const std::string& sex) {
    std::string uppercaseSex = sex;
    std::transform(uppercaseSex.begin(), uppercaseSex.end(), uppercaseSex.begin(), [](unsigned char c) {
        return std::toupper(c);
        });

    return uppercaseSex == "MALE" || uppercaseSex == "FEMALE";
}

bool isValidMaritalStatus(const std::string& maritalStatus) {
    std::string uppercaseStatus = maritalStatus;
    std::transform(uppercaseStatus.begin(), uppercaseStatus.end(), uppercaseStatus.begin(), [](unsigned char c) {
        return std::toupper(c);
        });

    return uppercaseStatus == "SINGLE" || uppercaseStatus == "MARRIED" ||
        uppercaseStatus == "SEPARATED" || uppercaseStatus == "WIDOWED";
}


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
                    }
                    else {
                        tail->next = current;
                        tail = current;
                    }
                }
            }

            file.close();
        }
        else {
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
        }
        else {
            std::cout << "Failed to open file!" << std::endl;
        }
    }

    void add_profile() {
        Node* new_profile = new Node;

        new_profile->pcn = getValidPCNInput();
        new_profile->last_name = getValidNameInput("Last Name");
        new_profile->given_name = getValidNameInput("Given Name");
        new_profile->middle_name = getValidNameInput("Middle Name");
        new_profile->birthdate = getValidDateInput("Birthdate");
        new_profile->sex = getInput("Enter Sex (Ex. Male/Female): ", "Invalid Sex. Enter Sex: ", isValidSex);
        new_profile->marital_status = getInput("Enter Marital Status (Ex. Single/Married/Separated/Widowed): ", "Invalid Marital Status. Enter Marital Status: ", isValidMaritalStatus);
        new_profile->blood_type = getValidBloodTypeInput();
        new_profile->nationality = getValidNameInput("Nationality (Ex. Filipino)");
        new_profile->date_of_issue = getValidDateInput("Date of Issue");
        new_profile->email_address = getValidEmailAddressInput();
        std::cout << "Enter Home Address: ";
        std::getline(std::cin >> std::ws, new_profile->home_address);
        new_profile->tag = getInput("Enter Tag (Positive/Negative): ", "Invalid Tag. Enter Tag: ", isValidTag);

        new_profile->next = nullptr;

        if (head == nullptr) {
            head = new_profile;
            tail = new_profile;
        }
        else {
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
        }
        else {
            std::cout << "Failed to open file!" << std::endl;
        }
    }

    void delete_profile() {
        std::string pcn;
        std::cout << "Enter the PCN of the profile you want to delete: ";
        std::getline(std::cin >> std::ws, pcn);
        std::cout << std::endl;

        Node* current = head;
        Node* previous = nullptr;
        bool found = false;

        while (current != nullptr) {
            if (current->pcn == pcn) {
                found = true;

                if (previous == nullptr) {
                    head = current->next;
                }
                else {
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
    void update_tag(const std::string& pcn, const std::string& tag) {
        std::fstream file(filename, std::ios::in | std::ios::out);
        if (file.is_open()) {
            std::string line;
            bool profileFound = false;

            if (!isValidPCN(pcn)) {
                std::cout << "Invalid PCN format. Update failed." << std::endl;
                return;
            }

            if (!isValidTag(tag)) {
                std::cout << "Invalid tag. Update failed." << std::endl;
                return;
            }

            while (std::getline(file, line)) {
                if (line.find("PCN: " + pcn) != std::string::npos) {
                    // Found the matching PCN, update the tag
                    profileFound = true;
                    file.seekp(file.tellg()); // Move write position to the current line
                    file << "Tag: " << tag << std::endl;
                    std::cout << "Tag updated successfully!" << std::endl;
                    break;
                }
            }

            if (!profileFound) {
                std::cout << "Profile with PCN " << pcn << " not found." << std::endl;
            }

            file.close();
        }
        else {
            std::cout << "Failed to open file!" << std::endl;
        }

        // Update the profiles in memory and save to file
        Node* current = head;
        while (current != nullptr) {
            if (current->pcn == pcn) {
                current->tag = tag;
                break;
            }
            current = current->next;
        }

        updateProfilesFile();
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
        std::getline(std::cin >> std::ws, pcn);
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
        std::cout << "[3] UPDATE PROFILE TAG" << std::endl;
        std::cout << "[4] DISPLAY ALL PROFILES" << std::endl;
       std::cout << "[5] DISPLAY CLOSE CONTACTS OF A POSITIVE CASE" << std::endl;
        std::cout << "[6] SEARCH PROFILE" << std::endl;
        std::cout << "[7] EXIT PROGRAM" << std::endl << std::endl;
        std::cout << "ENTER CHOICE (1-7): ";
        std::cin >> choice;

        while (choice < 1 || choice > 7) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "ENTER CHOICE (1-7): ";
            std::cin >> choice;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        system("cls");

        if (choice == 1) {
            profile.add_profile();
        }
        else if (choice == 2) {
            profile.delete_profile();
        }  
        
        else if (choice == 3) {
            std::string pcn;
            std::cout << "Enter the PCN of the profile you want to update: ";
            std::getline(std::cin >> std::ws, pcn);
            std::cout << std::endl;

            std::string tag;
            std::cout << "Enter the new tag (Positive/Negative): ";
            std::getline(std::cin >> std::ws, tag);
            std::cout << std::endl;

            profile.update_tag(pcn, tag);
        }
       
        else if (choice == 4) {
            profile.display();
        }

        /*else if (choice == 5) {
   std::string positivePCN;
   std::cout << "Enter the PCN of the positive profile: ";
   std::getline(std::cin >> std::ws, positivePCN);

   Node* current = profile.getHead();
   while (current != nullptr) {
       if (current->pcn == positivePCN && current->tag == "Positive") {
           profile.displayCloseContacts(current);
           break;
       }
       current = current->next;
   }
   if (current == nullptr) {
       std::cout << "Positive profile not found!\n";
   }
}*/

  
        else if (choice == 6) {
            profile.search();
        }

        profile.updateProfilesFile();

        system("pause");
    } while (choice != 7);

    std::cout << "Exiting Program..." << std::endl << std::endl;
    return 0;
}
