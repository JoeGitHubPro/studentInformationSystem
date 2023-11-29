#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// Function to add a new student
void addStudent() {
	try {
		string ID, Name, Address;

		cout << "Enter Student ID: ";
		cin >> ID;

		cout << "Enter Student Name: ";
		cin >> Name;

		cout << "Enter Student Address: ";
		cin >> Address;

		// Read existing student data from the file
		ifstream file("Students.txt");
		string content((istreambuf_iterator<char>(file)), (istreambuf_iterator<char>()));
		file.close();

		// Check if the entered student ID already exists
		if (ID.empty() || Name.empty() || Address.empty()) {
			cout << "Please enter valid input" << endl;
			return;
		}
		else {
			if (content.find(ID + " \t ") != string::npos) {
				cout << "This student already exists" << endl;
			}
			else {
				// Append the new student data to the file
				ofstream outFile("Students.txt", ios::app);
				outFile << ID + " \t " + Name + " \t " + Address << endl;
				outFile.close();

				cout << "The student has been added successfully" << endl;
			}
		}
	}
	catch (exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}
}

// Function to display information for a specific student
void displayStudent() {
	try {
		string ID;

		cout << "Enter Student ID: ";
		cin >> ID;

		if (!ID.empty()) {
			// Read student data from the file
			ifstream file("Students.txt");
			string line;
			bool found = false;

			// Search for the entered student ID
			do {
				getline(file, line);

				if (!file.fail()) {
					istringstream iss(line);
					string data[3];
					for (int i = 0; i < 3; ++i) {
						iss >> data[i];
					}

					// Display information if the student ID is found
					if (data[0] == ID) {
						cout << "Student ID: " << data[0] << endl;
						cout << "Student Name: " << data[1] << endl;
						cout << "Student Address: " << data[2] << endl;
						found = true;
						break;
					}
				}
				else {
					cout << "This Student ID does not exist" << endl;
					break;
				}

			} while (!file.eof());

			file.close();

			// Display a message if the student is not found
			if (!found) {
				cout << "Student not found" << endl;
			}
		}
		else {
			cout << "Please enter Student ID" << endl;
		}
	}
	catch (exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}
}

// Function to display information for all students
void showAllStudents() {
	try {
		// Read all student data from the file and display it
		ifstream file("Students.txt");
		string line;

		while (getline(file, line)) {
			istringstream iss(line);
			string data[3];
			for (int i = 0; i < 3; ++i) {
				iss >> data[i];
			}

			cout << "Student ID: " << data[0] << endl;
			cout << "Student Name: " << data[1] << endl;
			cout << "Student Address: " << data[2] << endl;
			cout << "-------------------------" << endl;
		}

		file.close();
	}
	catch (exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}
}

// Function to delete a specific student
void deleteStudent() {
	try {
		string ID;

		cout << "Enter Student ID to delete: ";
		cin >> ID;

		if (!ID.empty()) {
			// Open input and output files
			ifstream inFile("Students.txt");
			ofstream outFile("temp.txt");

			string line;
			bool found = false;

			// Iterate through each line in the file
			while (getline(inFile, line)) {
				istringstream iss(line);
				string data[3];
				for (int i = 0; i < 3; ++i) {
					iss >> data[i];
				}

				// Check if the current line has the specified student ID
				if (data[0] == ID) {
					found = true;
				}
				else {
					// Write lines (except the one to be deleted) to the temporary file
					outFile << line << endl;
				}
			}

			// Close files
			inFile.close();
			outFile.close();

			// Remove the original file and rename the temporary file
			remove("Students.txt");
			rename("temp.txt", "Students.txt");

			// Display a message based on whether the student was found and deleted
			if (found) {
				cout << "Student with ID " << ID << " deleted successfully" << endl;
			}
			else {
				cout << "Student not found" << endl;
			}
		}
		else {
			cout << "Please enter Student ID" << endl;
		}
	}
	catch (exception& ex) {
		cout << "Error: " << ex.what() << endl;
	}
}

// Main function
int main() {

	cout << "What opereation nedded" << endl;
	cout << "1-Add Student\n2-Display Student\n3-Show All Students\n4-Delete Student" << endl;

	int input;
	cin >> input;

	switch (input)
	{
	case 1:
		addStudent();
		break;
	case 2:
		displayStudent();
		break;
	case 3:
		showAllStudents();
		break;
	case 4:
		deleteStudent();
		break;

	default:
		break;
	}

	return 0;
}
