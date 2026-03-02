
// ProjectTwo.cpp 
// ABCU Course Advising Program
// Created by: Bianca Bennett
// SNHU CS-300-10460
// February 2026

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Define Course object
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Binary Search Tree Node structure
struct Node {
    Course course;
    Node* left;
    Node* right;

    Node(Course c) {
        course = c;
        left = nullptr;
        right = nullptr;
    }
};

// Binary Search Tree structure
struct BinarySearchTree {
    Node* root;

    BinarySearchTree() {
        root = nullptr;
    }
};

// Input normalization to trim whitespace and convert to uppercase
// so that user input will match stored course IDs
string Trim(string str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == string::npos) {
        return "";
    }
    return str.substr(start, end - start + 1);
}

string ToUpper(string str) {
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

string NormalizeCourseID(string id) {
    return ToUpper(Trim(id));
}

// Function to insert a course into the BST
Node* Insert(Node * node, Course course) {
    // Base case: empty spot found
    if (node == nullptr) {
        return new Node(course);
    }

    // Recursive insertion
    if (course.courseNumber < node->course.courseNumber) {
        node->left = Insert(node->left, course);
    }
    else if (course.courseNumber > node->course.courseNumber) {
        node->right = Insert(node->right, course);
    }

    return node;
}

// Function to search for a course in the BST
Node* Search(Node * node, string courseNumber) {
    if (node == nullptr) {
        return nullptr;
    }

    if (courseNumber == node->course.courseNumber) {
        return node;
    }
    else if (courseNumber < node->course.courseNumber) {
        return Search(node->left, courseNumber);
    }
    else {
        return Search(node->right, courseNumber);
    }
}

// Print all courses in sorted order (uses in-order traversal)
void InOrderTraversal(Node * node) {
    if (node == nullptr) {
        return;
    }

    InOrderTraversal(node->left);
    cout << node->course.courseNumber << ", " << node->course.courseTitle << endl;
    InOrderTraversal(node->right);
}

void PrintSortedCourses_BST(BinarySearchTree & courseTree) {
    cout << endl;
    cout << "Here is a sample schedule:" << endl;
    cout << endl;
    InOrderTraversal(courseTree.root);
    cout << endl;
}

// Destructor using post-order traversal
void DestroyTree(Node * node) {
    if (node == nullptr) {
        return;
    }

    // Delete left subtree
    DestroyTree(node->left);

    // Delete right subtree
    DestroyTree(node->right);

    // Delete current node
    delete node;
}

// Wrapper function to destroy the entire tree
void DestroyBST(BinarySearchTree & courseTree) {
    DestroyTree(courseTree.root);
    courseTree.root = nullptr;
}

// Function to load courses from file and store in binary search tree
void LoadCourses_BST(string fileName, BinarySearchTree & courseTree) {
    vector<string> courseNumbers;
    vector<Course> allCourses;

    // Open file using fileName
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Error: File unable to open" << endl;
        return;
    }

    string line;
    int lineNumber = 0;

    while (getline(file, line)) {
        lineNumber++;

        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (Trim(line).empty()) {
            continue;
        }

        // Separate line into parts using commas
        vector<string> lineParts;
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            lineParts.push_back(Trim(token));
        }

        if (lineParts.size() < 2 || lineParts[0].empty() || lineParts[1].empty()) {
            cout << "Error: Invalid format" << endl;
            continue;
        }

        // Create new Course object
        Course course;
        course.courseNumber = NormalizeCourseID(lineParts[0]);
        course.courseTitle = lineParts[1];

        // Store prerequisites if they exist
        for (int i = 2; i < (int)lineParts.size(); i++) {
            string prereq = NormalizeCourseID(lineParts[i]);
            if (!prereq.empty()) {
                course.prerequisites.push_back(prereq);
            }
        }

        courseNumbers.push_back(course.courseNumber);
        allCourses.push_back(course);
    }

    file.close();

    // Validate prerequisites exist
    for (int i = 0; i < (int)allCourses.size(); i++) {
        for (int j = 0; j < (int)allCourses[i].prerequisites.size(); j++) {
            string prereq = allCourses[i].prerequisites[j];
            bool found = false;

            for (int k = 0; k < (int)courseNumbers.size(); k++) {
                if (courseNumbers[k] == prereq) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Error: Prerequisite " << prereq
                    << " doesn't exist for course " << allCourses[i].courseNumber << endl;
            }
        }
    }

    // Insert all courses into BST
    for (int i = 0; i < (int)allCourses.size(); i++) {
        courseTree.root = Insert(courseTree.root, allCourses[i]);
    }

    cout << "Data loaded successfully. " << allCourses.size() << " courses loaded." << endl;
}

// Search and print course info modified for use of binary search tree
void SearchCourse_BST(BinarySearchTree & courseTree, string rawInput) {
    string searchCourseNumber = NormalizeCourseID(rawInput);

    if (searchCourseNumber.empty()) {
        cout << "Error: No course number entered. Please try again." << endl;
        return;
    }

    Node* result = Search(courseTree.root, searchCourseNumber);

    if (result == nullptr) {
        cout << "Course " << searchCourseNumber << " not found" << endl;
        return;
    }

    Course course = result->course;
    cout << endl;
    cout << course.courseNumber << ", " << course.courseTitle << endl;
    cout << "Prerequisites: ";

    if (course.prerequisites.empty()) {
        cout << "None" << endl;
    }
    else {
        for (int i = 0; i < (int)course.prerequisites.size(); i++) {
            cout << course.prerequisites[i];

            if (i < (int)course.prerequisites.size() - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }

    cout << endl;
}

// Menu control function
void RunMenu_BST() {
    // Create BinarySearchTree
    BinarySearchTree courseTree;
    bool coursesLoaded = false;
    string inputLine;
    int choice = 0;

    cout << "Welcome to the course planner." << endl;

    while (true) {
        cout << endl;
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        getline(cin, inputLine);
        inputLine = Trim(inputLine);

        // Reject input that contains anything other than digits
        bool validInteger = !inputLine.empty();
        for (int i = 0; i < (int)inputLine.size(); i++) {
            if (!isdigit(inputLine[i])) {
                validInteger = false;
                break;
            }
        }

        if (!validInteger) {
            cout << inputLine << " is not a valid option." << endl;
            continue;
        }

        choice = stoi(inputLine);

        if (choice == 1) {
            // Prompt for file name and load data
            string fileName;
            cout << "Enter file name: ";
            getline(cin, fileName);
            fileName = Trim(fileName);

            if (fileName.empty()) {
                cout << "Error: No file name entered. Please try again." << endl;
            }
            else {
                LoadCourses_BST(fileName, courseTree);
                if (courseTree.root != nullptr) {
                    coursesLoaded = true;
                }
            }
        }
        else if (choice == 2) {
            if (coursesLoaded) {
                PrintSortedCourses_BST(courseTree);
            }
            else {
                cout << "Load data first (Choice 1)" << endl;
            }
        }
        else if (choice == 3) {
            if (coursesLoaded) {
                string searchCourseNumber;
                cout << "What course do you want to know about? ";
                getline(cin, searchCourseNumber);
                SearchCourse_BST(courseTree, searchCourseNumber);
            }
            else {
                cout << "Load data first (Choice 1)" << endl;
            }
        }
        else if (choice == 9) {
            cout << "Thank you for using the course planner!" << endl;
            // Clean up memory before exit
            if (courseTree.root != nullptr) {
                DestroyBST(courseTree);
            }
            break;
        }
        else {
            cout << choice << " is not a valid option." << endl;
        }
    }
}

// Main menu program
int main() {
    RunMenu_BST();
    return 0;
}
