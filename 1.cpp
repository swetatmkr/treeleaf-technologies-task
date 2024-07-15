#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <sstream>

using namespace std;

struct Student {
    int id;
    string name;
    string date_birth;
    int roll_no;
    string department;
    string address;
};

// Function to read the CSV file
vector<Student> readCSV(const string &filename) {
    vector<Student> students;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Student student;
        string word;

        getline(ss, word, ','); student.id = stoi(word);
        getline(ss, student.name, ',');
        getline(ss, student.date_birth, ',');
        getline(ss, word, ','); student.roll_no = stoi(word);
        getline(ss, student.department, ',');
        getline(ss, student.address, ',');

        students.push_back(student);
    }
    return students;
}

// Function to write the CSV file
void writeCSV(const string &filename, const vector<Student> &students) {
    ofstream file(filename);
    for (const auto &student : students) {
        file << student.id << ","
             << student.name << ","
             << student.date_birth << ","
             << student.roll_no << ","
             << student.department << ","
             << student.address << "\n";
    }
}

// Function to calculate age from date of birth
int calculateAge(const string &date_birth) {
    int year, month, day;
    sscanf(date_birth.c_str(), "%d-%d-%d", &year, &month, &day);
    time_t t = time(0);
    tm *now = localtime(&t);
    int age = (now->tm_year + 1900) - year;
    if ((now->tm_mon + 1 < month) || ((now->tm_mon + 1 == month) && (now->tm_mday < day))) {
        age--;
    }
    return age;
}

int main() {
    string inputFile = "students.csv";
    vector<Student> students = readCSV(inputFile);

    // Sort by name
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.name < b.name;
    });
    writeCSV("students_sorted_by_name.csv", students);

    // Sort by age
    sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return calculateAge(a.date_birth) < calculateAge(b.date_birth);
    });
    writeCSV("students_sorted_by_age.csv", students);

    return 0;
}
