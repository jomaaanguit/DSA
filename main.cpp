#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cctype>
#include <algorithm>
#include <ctime>

bool isValidTime(const std::string& time) {
    std::regex timePattern(R"(^(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])$)");
    return std::regex_match(time, timePattern);
}

std::string getValidTimeInput(const std::string& fieldName) {
    std::string input;
    std::cout << "Enter " << fieldName << " (HH:MM): ";
    std::getline(std::cin >> std::ws, input);

    while (!isValidTime(input)) {
        std::cout << "Invalid " << fieldName << ". Enter " << fieldName << " (HH:MM): ";
        std::getline(std::cin >> std::ws, input);
    }

    return input;
}

bool isValidEntryDate(const std::string& entryDate) {
    std::regex datePattern(R"(^\d{4}-\d{2}-\d{2}$)"); //(R"(^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/(19|20)\d\d$)")

    if (!std::regex_match(entryDate, datePattern)) {
        return false;
    }

    int year = std::stoi(entryDate.substr(0, 4));
    int month = std::stoi(entryDate.substr(5, 2));
    int day = std::stoi(entryDate.substr(8, 2));

    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;

    std::time_t time = std::mktime(&tm);

    if (time == -1) {
        return false;
    }

    std::tm validatedTime;
    if (localtime_s(&validatedTime, &time) != 0) {
        return false;
    }

    char buffer[80];
    if (std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &validatedTime) == 0) {
        return false;
    }

    return validatedTime.tm_year == (year - 1900) && validatedTime.tm_mon == (month - 1) && validatedTime.tm_mday == day;
}


std::string getValidEntryDateInput(const std::string& fieldName) {
    std::string input;
    std::cout << "Enter " << fieldName << " (YYYY-MM-DD): ";
    std::getline(std::cin >> std::ws, input);

    while (!isValidEntryDate(input)) {
        std::cout << "Invalid " << fieldName << ". Enter " << fieldName << " (YYYY-MM-DD): ";
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
    std::regex birthdatePattern(R"(^\d{4}-\d{2}-\d{2}$)");   // (R"(^(0[1-9]|1[0-2])/(0[1-9]|[12][0-9]|3[01])/(19|20)\d\d$)");
    return std::regex_match(birthdate, birthdatePattern);
}

std::string getValidDateInput(const std::string& fieldName) {
    std::string input;
    std::cout << "Enter " << fieldName << " (YYYY-MM-DD): ";
    std::getline(std::cin >> std::ws, input);

    while (!isValidDate(input)) {
        std::cout << "Invalid " << fieldName << ". Enter " << fieldName << ": ";
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
    std::string entry_date;
    std::string entry_time;
    std::string exit_time;
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
                    std::getline(file, current->entry_date);
                    std::getline(file, current->entry_time);
                    std::getline(file, current->exit_time);
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
                file << current->entry_date << std::endl;
                file << current->entry_time << std::endl;
                file << current->exit_time << std::endl;
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

    bool isDuplicatePCN(const std::string& pcn) {
        Node* current = head;
        while (current != nullptr) {
            if (current->pcn == pcn) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    bool isValidPCN(const std::string& pcn) {
        std::regex pcnPattern(R"(\d{4}-\d{4}-\d{4}-\d{4})");
        return std::regex_match(pcn, pcnPattern);
    }

    std::string getValidPCNInput(int n = 1) {
        std::string input;
        std::cout << "Enter PCN (xxxx-xxxx-xxxx-xxxx): ";
        std::getline(std::cin >> std::ws, input);

        if (n == 1)
        {
            while (!isValidPCN(input) || isDuplicatePCN(input)) {
                if (!isValidPCN(input)) {
                    std::cout << "Invalid PCN format. Enter PCN: ";
                }
                else {
                    std::cout << "PCN already exists. Enter PCN: ";
                }
                std::getline(std::cin >> std::ws, input);
            }

            return input;

        }
        else
        {
            while (!isValidPCN(input)) {
                std::cout << "Invalid PCN format. Enter PCN: ";
                std::getline(std::cin >> std::ws, input);
            }

            return input;
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
        new_profile->entry_date = getValidEntryDateInput("Entry Date");
        new_profile->entry_time = getValidTimeInput("Entry Time");
        new_profile->exit_time = getValidTimeInput("Exit Time");
        new_profile->tag = "Negative"; // Assign default value "NEGATIVE" to tag

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
            file << new_profile->last_name << std::endl;
            file << new_profile->given_name << std::endl;
            file << new_profile->middle_name << std::endl;
            file << new_profile->birthdate << std::endl;
            file << new_profile->sex << std::endl;
            file << new_profile->marital_status << std::endl;
            file << new_profile->blood_type << std::endl;
            file << new_profile->nationality << std::endl;
            file << new_profile->date_of_issue << std::endl;
            file << new_profile->email_address << std::endl;
            file << new_profile->home_address << std::endl;
            file << new_profile->entry_date << std::endl;
            file << new_profile->entry_time << std::endl;
            file << new_profile->exit_time << std::endl;
            file << new_profile->tag << std::endl;
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
        }
        updateProfilesFile();
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

    void updatePCN() {
        std::string oldPCN = getValidPCNInput(2);
        /*std::cout << "Enter the PCN you want to change: ";
        std::getline(std::cin >> std::ws, oldPCN);*/

        Node* current = head;
        bool found = false;

        while (current != nullptr) {
            if (current->pcn == oldPCN) {
                found = true;
                std::string newPCN = getValidPCNInput(2);/*
                std::cout << "Enter the updated PCN: ";
                std::getline(std::cin >> std::ws, newPCN);*/
                current->pcn = newPCN;
                std::cout << "PCN is successfully updated." << std::endl;
                break;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "The entered PCN does not exist. Please try again." << std::endl;
        }
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
            std::cout << "Entry Date: " << current->entry_date << std::endl;
            std::cout << "Entry Time: " << current->entry_time << std::endl;
            std::cout << "Exit Time: " << current->exit_time << std::endl;
            std::cout << "Tag: " << current->tag << std::endl;
            std::cout << std::endl;
            current = current->next;
        }
    }

    void displayPositive() {
        Node* current = head;
        bool positiveFound = false;  // Flag to track if any positive profiles are found

        while (current != nullptr) {
            if (current->tag == "Positive") {
                positiveFound = true;

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
                std::cout << "Entry Date: " << current->entry_date << std::endl;
                std::cout << "Entry Time: " << current->entry_time << std::endl;
                std::cout << "Exit Time: " << current->exit_time << std::endl;
                std::cout << "Tag: " << current->tag << std::endl;
                std::cout << std::endl;
            }

            current = current->next;
        }

        if (!positiveFound) {
            std::cout << "No profiles with a tag of 'Positive' found." << std::endl;
        }
    }

    void displayNegative() {
        Node* current = head;
        bool negativeFound = false;  // Flag to track if any negative profiles are found

        while (current != nullptr) {
            if (current->tag == "Negative") {
                negativeFound = true;

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
                std::cout << "Entry Date: " << current->entry_date << std::endl;
                std::cout << "Entry Time: " << current->entry_time << std::endl;
                std::cout << "Exit Time: " << current->exit_time << std::endl;
                std::cout << "Tag: " << current->tag << std::endl;
                std::cout << std::endl;
            }

            current = current->next;
        }

        if (!negativeFound) {
            std::cout << "No profiles with a tag of 'Negative' found." << std::endl;
        }
    }

    void displayCloseContacts() {
        std::string pcn = getValidPCNInput(2);
        /*std::cout << "Enter PCN: ";
        std::getline(std::cin >> std::ws, pcn);
        std::cout << std::endl;*/

        Node* current = head;
        Node* enteredProfile = nullptr;
        bool found = false;
        bool closeContactsFound = false;  // Flag to track if any close contacts are found

        // Find the entered PCN profile
        while (current != nullptr) {
            if (current->pcn == pcn) {
                enteredProfile = current;
                found = true;
                break;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "The profile with PCN: " << pcn << " does not exist" << std::endl << std::endl;
            return;
        }

        if (enteredProfile->tag == "Positive") {
            std::cout << "Close Contacts of PCN: " << pcn << std::endl;
            std::cout << "Entry Date: " << enteredProfile->entry_date << std::endl;
            std::cout << "Entry Time: " << enteredProfile->entry_time << std::endl;
            std::cout << "Exit Time: " << enteredProfile->exit_time << std::endl;

            std::cout << "Close Contacts:" << std::endl;
            current = head;

            while (current != nullptr) {
                if (current != enteredProfile) {
                    // Check if the entry date, entry time, and exit time overlap with the entered PCN
                    if (current->entry_date == enteredProfile->entry_date &&
                        ((current->entry_time >= enteredProfile->entry_time && current->entry_time < enteredProfile->exit_time) ||
                            (current->exit_time > enteredProfile->entry_time && current->exit_time <= enteredProfile->exit_time) ||
                            (current->entry_time <= enteredProfile->entry_time && current->exit_time >= enteredProfile->exit_time))) {
                        std::cout << "PCN: " << current->pcn << std::endl;
                        // Output other details of the close contact profile
                        // ...
                        closeContactsFound = true;
                    }
                }
                current = current->next;
            }

            if (!closeContactsFound) {
                std::cout << "No Close Contacts Found!" << std::endl;
            }
        }
        else if (enteredProfile->tag == "Negative") {
            std::cout << "The profile with PCN: " << pcn << " is marked as negative." << std::endl;
            //std::cout << "Please enter a PCN with the 'Positive' tag to display close contacts." << std::endl;
            //displayCloseContacts();  // Recursively call the function to take input again
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
                std::cout << "Home Address: " << current->home_address << std::endl;
                std::cout << "Entry Date: " << current->entry_date << std::endl;
                std::cout << "Entry Time: " << current->entry_time << std::endl;
                std::cout << "Exit Time: " << current->exit_time << std::endl;
                std::cout << "Tag: " << current->tag << std::endl;
                std::cout << std::endl;
                break;
            }
            current = current->next;
        }

        if (!found) {
            std::cout << "The profile with PCN: " << pcn << " does not exist" << std::endl << std::endl;
        }
    }
};

int main() {
    Profile profileSystem;
    int choice{};

    do {
        system("cls");
        std::cout << "NID TRACER" << std::endl;
        std::cout << "A National ID-Based Contact Tracing System" << std::endl;
        std::cout << "1. Add Profile" << std::endl;
        std::cout << "2. Delete Profile" << std::endl;
        std::cout << "3. Update" << std::endl;
        std::cout << "4. Display" << std::endl;
        std::cout << "5. Search Profile" << std::endl;
        std::cout << "0. Exit" << std::endl << std::endl;
        std::cout << "Enter your choice: ";

        while (!(std::cin >> choice) || choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 0)
        {
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "Enter your choice: ";
            
            /*if (std::cin >> choice)
                break;*/
        }
        std::cout << std::endl;

        system("cls");

        switch (choice) {
        case 1:
        {
            profileSystem.add_profile();
            break;
        }
        case 2:
        {
            profileSystem.delete_profile();
            system("pause");
            break;
        }
        case 3: {

            std::cout << "1. Update PCN" << std::endl;
            std::cout << "2. Update Tag" << std::endl << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            while (choice != 1 && choice != 2)
            {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "Enter your choice: ";
                std::cin >> choice;
            }

            if (choice == 1)
            {
                profileSystem.updatePCN();
                system("pause");
            }
            else if (choice == 2)
            {
                std::string pcn = profileSystem.getValidPCNInput(2), tag = getValidNameInput("Enter Tag: ");
                /*std::cout << "Enter PCN: ";
                std::getline(std::cin >> std::ws, pcn);
                std::cout << "Enter Tag: ";
                std::getline(std::cin >> std::ws, tag);*/
                profileSystem.update_tag(pcn, tag);
                system("pause");

            }
            break;
        }
        case 4:
        {
            std::cout << "1. Display All Profiles" << std::endl;
            std::cout << "2. Display All Positive Profiles" << std::endl;
            std::cout << "3. Display All Negative Profiles" << std::endl;
            std::cout << "4. Display Close Contacts of PCN:" << std::endl << std::endl;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            while (choice != 1 && choice != 2 && choice != 3 && choice != 4)
            {
                std::cin.clear();
                std::cin.ignore(100, '\n');
                std::cout << "Enter your choice: ";
                std::cin >> choice;
            }

            std::cout << std::endl;

            if (choice == 1)
            {
                profileSystem.display();
                system("pause");
            }
            else if (choice == 2)
            {
                std::cout << "Displaying All Positive Profiles..." << std::endl << std::endl;
                profileSystem.displayPositive();
                system("pause");
            }
            else if (choice == 3)
            {
                std::cout << "Displaying All Negative Profiles..." << std::endl << std::endl;
                profileSystem.displayNegative();
                system("pause");
            }
            else if (choice == 4)
            {
                std::cout << "Close Contacts ";
                profileSystem.displayCloseContacts();
                system("pause");
            }
            break;
        }
        case 5:
        {
            profileSystem.search();
            system("pause");
            break;
        }
        case 0:
            std::cout << "Exiting..." << std::endl;
            break;
        }

        std::cout << std::endl;

    } while (choice != 0);

    return 0;
}