// ParsingCsvDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class StudentRecord {
private:
/*string name,
         birthdate,
         sex,
         maritalstatus,
         bloodtype,
         nationality, 
         dateofissue,
         category,
         email,
         address;*/
public:
    StudentRecord(
        string name,
        string birthdate,
        string sex,
        string maritalstatus,
        string bloodtype,
        string nationality, 
        string dateofissue,
        string category,
        string email,
        string address
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
        cout << "    Name:           " << Name << endl;
        cout << "    Birthdate:      " << Birthdate  << endl;
        cout << "    Sex:            " << Sex  << endl;
        cout << "    Marital Status: " << Maritalstatus  << endl;
        cout << "    Blood Type:     " << Bloodtype  << endl;
        cout << "    Nationality:    " << Nationality  << endl;
        cout << "    Date of Issue:  " << Dateofissue  << endl;
        cout << "    Category:       " << Category  << endl;
        cout << "    Email:          " << Email  << endl;
        cout << "    Address:        " << Address  << endl << endl;

    }

    string Name, 
            Birthdate,
            Sex,
            Maritalstatus,
            Bloodtype, 
            Nationality,
            Dateofissue,
            Category, 
            Email, 
            Address;
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
    inputFile.open("C:\\Users\\Admin\\Desktop\\CS\\C++\\data.csv");
    string line = "";

    vector<StudentRecord> students;
    while (getline(inputFile, line)) {

        stringstream inputString(line);

        //StudentId, Last Name, FirstName, Age, Phone Number, GPA
        string name, 
                birthdate,
                sex,
                maritalstatus,
                bloodtype, 
                nationality,
                dateofissue,
                category, 
                email, 
                address;

        getline(inputString, name, ',');
        getline(inputString, birthdate, ',');
        getline(inputString, sex, ',');
        getline(inputString, maritalstatus, ',');
        //age = atoi(tempString.c_str());
        getline(inputString, bloodtype, ',');
        getline(inputString, nationality, ',');
        getline(inputString, dateofissue, ',');
        // gpa = atof(tempString.c_str());
        getline(inputString, category, ',');
        getline(inputString, email, ',');
        getline(inputString, address, ',');
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