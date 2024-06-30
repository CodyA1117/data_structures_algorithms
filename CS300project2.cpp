#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits> // Include this header for std::numeric_limits

// Class to store course information
class Course {
public:
    std::string courseNumber; // course number
    std::string courseName;   // course name
    std::vector<std::string> prerequisites; // list of prerequisites

    // Constructor
    Course() {}

    // Parameterized constructor
    Course(std::string number, std::string name, std::vector<std::string> prereqs) {
        courseNumber = number;
        courseName = name;
        prerequisites = prereqs;
    }
};

// Function to load courses from a file
void loadCourses(std::unordered_map<std::string, Course>& courses, const std::string& filename) {
    std::ifstream file(filename); // open file
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string line;

    // Read each line from the file
    while (getline(file, line)) {
        std::cout << "Reading line: " << line << std::endl; // debug print
        std::stringstream ss(line);
        std::string courseNumber, courseName, prereq;
        std::vector<std::string> prerequisites;

        getline(ss, courseNumber, ','); // get course number
        getline(ss, courseName, ',');   // get course name

        // Get all prerequisites
        while (getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);
        }

        // Create a course object and add it to the hash table
        Course course(courseNumber, courseName, prerequisites);
        courses[courseNumber] = course;
    }

    file.close(); // close file

    // Debug print to validate loaded courses
    std::cout << "Loaded courses:" << std::endl;
    for (const auto& pair : courses) {
        std::cout << pair.second.courseNumber << ", " << pair.second.courseName << std::endl;
        if (!pair.second.prerequisites.empty()) {
            std::cout << "Prerequisites: ";
            for (const auto& prereq : pair.second.prerequisites) {
                std::cout << prereq << " ";
            }
            std::cout << std::endl;
        }
    }
}

// Function to print course information
void printCourse(const Course& course) {
    std::cout << course.courseNumber << ", " << course.courseName << std::endl;
    if (!course.prerequisites.empty()) {
        std::cout << "Prerequisites: ";
        for (const auto& prereq : course.prerequisites) {
            std::cout << prereq << " ";
        }
        std::cout << std::endl;
    } else {
        std::cout << "No prerequisites" << std::endl;
    }
}

// Function to print all courses in alphanumeric order
void printCourseList(const std::unordered_map<std::string, Course>& courses) {
    std::vector<std::string> courseNumbers;

    // Collect all course numbers
    for (const auto& pair : courses) {
        courseNumbers.push_back(pair.first);
    }

    // Sort course numbers
    std::sort(courseNumbers.begin(), courseNumbers.end());

    // Print sorted courses
    for (const auto& courseNumber : courseNumbers) {
        const Course& course = courses.at(courseNumber);
        std::cout << course.courseNumber << ", " << course.courseName << std::endl;
    }
}

int main() {
    std::unordered_map<std::string, Course> courses;
    int choice;
    std::string filename = "ClassesABCU.csv"; // Set the default file name
    std::string courseNumber;

    std::cout << "Welcome to the course planner." << std::endl;

    // Menu loop
    while (true) {
        std::cout << "1. Load Data Structure." << std::endl;
        std::cout << "2. Print Course List." << std::endl;
        std::cout << "3. Print Course." << std::endl;
        std::cout << "9. Exit" << std::endl;
        std::cout << "What would you like to do? ";
        std::cin >> choice;

        // Prevent infinite loop caused by invalid input
        if (std::cin.fail()) {
            std::cin.clear(); // clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "Invalid input. Please enter a number between 1 and 9." << std::endl;
            continue;
        }

        switch (choice) {
        case 1:
            loadCourses(courses, filename); // Load courses from file
            break;
        case 2:
            std::cout << "Here is a sample schedule:" << std::endl;
            printCourseList(courses); // Print course list
            break;
        case 3:
            std::cout << "What course do you want to know about? ";
            std::cin >> courseNumber;
            if (courses.find(courseNumber) != courses.end()) {
                printCourse(courses[courseNumber]); // Print course info
            } else {
                std::cout << "Course not found" << std::endl;
            }
            break;
        case 9:
            std::cout << "Thank you for using the course planner!" << std::endl;
            return 0; // Exit program
        default:
            std::cout << choice << " is not a valid option." << std::endl;
        }
    }

    return 0;
}
