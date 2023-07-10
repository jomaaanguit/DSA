// ParsingCsvDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <std::string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class StudentRecord {
private:  
    std::string Name, 
         Birthdate,
         Sex,
         Maritalstatus,
         Bloodtype, 
         Nationality,
         Dateofissue,
         Category, 
         Email, 
         Address;
public:
    StudentRecord(
        std::string name,
        std::string birthdate,
        std::string sex,
        std::string maritalstatus,
        std::string bloodtype,
        std::string nationality, 
        std::string dateofissue,
        std::string category,
        std::string email,
        std::string address
    ) {
        Name = name;
        Birthdate = birthdate;
        Sex = sex;
        Maritalstatus = maritalstatus;
        Bloodtype = bloodtype;
        Nationality = nationality;
        Dateofissue = dateofissue;
        Category = category; 
        Email = email;
        Address = address;
    }

    void display() {    
        std::cout << "    Name:           " << Name << std::endl;
        std::cout << "    Birthdate:      " << Birthdate  << std::endl;
        std::cout << "    Sex:            " << Sex  << std::endl;
        std::cout << "    Marital Status: " << Maritalstatus  << std::endl;
        std::cout << "    Blood Type:     " << Bloodtype  << std::endl;
        std::cout << "    Nationality:    " << Nationality  << std::endl;
        std::cout << "    Date of Issue:  " << Dateofissue  << std::endl;
        std::cout << "    Category:       " << Category  << std::endl;
        std::cout << "    Email:          " << Email  << std::endl;
        std::cout << "    Address:        " << Address  << std::endl << std::endl;

    }
};

void displayStudents(vector<StudentRecord>& students) {

    
    for (auto student : students) {
        student.display();
    }
}

int main()
{
    ifstream inputFile;
    //inputFile.open("C:\\temp\\student-records.csv");
    inputFile.open("C:\\Users\\Admin\\Desktop\\CS\\Final_Project\\DSA\\data.csv");
    std::string line = "";

    vector<StudentRecord> students;
    while (std::getline(inputFile, line)) {

        std::stringstream inputstd::string(line);

        //StudentId, Last Name, FirstName, Age, Phone Number, GPA
        std::string name, 
                birthdate,
                sex,
                maritalstatus,
                bloodtype, 
                nationality,
                dateofissue,
                category, 
                email, 
                address;

        std::getline(inputstd::string, name, ',');
        std::getline(inputstd::string, birthdate, ',');
        std::getline(inputstd::string, sex, ',');
        std::getline(inputstd::string, maritalstatus, ',');
        //age = atoi(tempstd::string.c_str());
        std::getline(inputstd::string, bloodtype, ',');
        std::getline(inputstd::string, nationality, ',');
        std::getline(inputstd::string, dateofissue, ',');
        // gpa = atof(tempstd::string.c_str());
        std::getline(inputstd::string, category, ',');
        std::getline(inputstd::string, email, ',');
        std::getline(inputstd::string, address, ',');
        StudentRecord student(
                name, 
                birthdate,
                sex,
                maritalstatus,
                bloodtype, 
                nationality,
                dateofissue,
                category, 
                email, 
                address);
        students.push_back(student);
        line = "";
    }

    displayStudents(students);
}