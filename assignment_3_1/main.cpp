#include <SQLiteCpp/SQLiteCpp.h>
#include <iostream>
#include <string>
#include <limits>

using namespace std;

void fjernError() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

class SchoolDatabase {
public:
    SchoolDatabase() : db("school.sqlite", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE) {
        db.exec("CREATE TABLE IF NOT EXISTS students (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, email TEXT, year INTEGER)");
    }

    void displayMenu() {
        while (true) {
            cout << "1. Read all students\n";
            cout << "2. Get student by id\n";
            cout << "3. Add student\n";
            cout << "4. Edit student\n";
            cout << "5. Remove student\n";
            cout << "6. Search\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
                case 1:
                    readAllStudents();
                    break;
                case 2:
                    getStudentById();
                    break;
                case 3:
                    addStudent();
                    break;
                case 4:
                    updateStudentDetails();
                    break;
                case 5:
                    removeStudent();
                    break;
                case 6:
                    searchStudents();
                    break;
                case 7:
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    }

private:
    SQLite::Database db;

    void readAllStudents() {
        SQLite::Statement query(db, "SELECT * FROM students");
        bool found = false;
        while (query.executeStep()) {
            found = true;
            cout << "id: " << query.getColumn(0) << ", name: " << query.getColumn(1)
                 << ", email: " << query.getColumn(2) << ", year: " << query.getColumn(3) << endl;
        }
        if (!found) {
            cout << "No students found\n";
        }
    }

    void getStudentById() {
        cout << "Enter student id: ";
        int id;
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer

        SQLite::Statement query(db, "SELECT * FROM students WHERE id = ?");
        query.bind(1, id);
        if (query.executeStep()) {
            cout << "id: " << query.getColumn(0) << ", name: " << query.getColumn(1)
                 << ", email: " << query.getColumn(2) << ", year: " << query.getColumn(3) << endl;
        } else {
            cout << "Student not found\n";
        }
    }

    void addStudent() {
        string name, email;
        int year;
        cout << "Enter name: ";
        getline(cin, name);
        cout << "Enter email: ";
        getline(cin, email);
        cout << "Enter year: ";
        cin >> year;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear the input buffer after reading year

        SQLite::Statement query(db, "INSERT INTO students (name, email, year) VALUES (?, ?, ?)");
        query.bind(1, name);
        query.bind(2, email);
        query.bind(3, year);
        query.exec();

        long long lastId = db.getLastInsertRowid();
        cout << "Added student: id: " << lastId << ", name: " << name << ", email: " << email << ", year: " << year << endl;
    }


    void updateStudentDetails() {
        int studentId;
        string studentName, studentEmail;
        int studentYear;

        cout << "Enter student ID to update: ";
        cin >> studentId;
        fjernError(); // Clear any input errors.

        // Check for student existence
        SQLite::Statement checkIfExists(db, "SELECT COUNT(*) FROM students WHERE id = ?");
        checkIfExists.bind(1, studentId);
        checkIfExists.executeStep();

        if (checkIfExists.getColumn(0).getInt() == 0) {
            cout << "Student not found\n";
            return;
        }

        // Collect new student details
        cout << "New name: ";
        getline(cin, studentName);
        cout << "New email: ";
        getline(cin, studentEmail);
        cout << "New academic year: ";
        cin >> studentYear;
        fjernError(); // Clear cin state again.

        // Update the student's information
        SQLite::Statement updateStudent(db, "UPDATE students SET name = ?, email = ?, year = ? WHERE id = ?");
        updateStudent.bind(1, studentName);
        updateStudent.bind(2, studentEmail);
        updateStudent.bind(3, studentYear);
        updateStudent.bind(4, studentId);
        updateStudent.exec();

        if (db.getChanges() > 0) {
            cout << "Student was edited successfully\n";
        } else {
            cout << "Student not found\n";
        }
    }


    void removeStudent() {
        cout << "Enter student id: ";
        int id;
        cin >> id;

        SQLite::Statement query(db, "DELETE FROM students WHERE id = ?");
        query.bind(1, id);

        if (query.exec() > 0) {
            cout << "Student was removed successfully\n";
        } else {
            cout << "Student not found\n";
        }
    }

    void searchStudents() {
        string searchInput;
        cout << "Enter search query (name): ";
        getline(cin, searchInput);

        SQLite::Statement query(db, "SELECT * FROM students WHERE name LIKE ?");
        query.bind(1, searchInput);

        bool found = false;
        while (query.executeStep()) {
            found = true;
            cout << "id: " << query.getColumn(0) << ", name: " << query.getColumn(1)
                 << ", email: " << query.getColumn(2) << ", year: " << query.getColumn(3) << endl;
        }
        if (!found) {
            cout << "No students found matching the search criteria\n";
        }
    }
};
int main() {
    try {
        SchoolDatabase db;
        db.displayMenu();
    } catch (const std::exception& e) {
        cerr << "An error occurred: " << e.what() << endl;
    }
    return 0;
}