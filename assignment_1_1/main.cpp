#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Student
{
private:
    static int nextStudentId;
    int student_id;
    string name;
    string email;

public:
    Student(string name, string email)
    {
        this->name = name;
        this->email = email;
        this->student_id = nextStudentId;
        nextStudentId++;
    }
    string getName()
    {
        return name;
    }
    string getEmail()
    {
        return email;
    }
    int getId()
    {
        return student_id;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setEmail(string email)
    {
        this->email = email;
    }
    void show()
    {
        cout << "Student ID: " << student_id << ", ";
        cout << "Name: " << name << ", ";
        cout << "Email: " << email << endl;
    }
};
// Initialize the static variable
int Student::nextStudentId = 1;

class Test
{
private:
    static int nextTestId;
    int test_id;
    string course_name;
    string test_name;
    string date;

public:
    Test(string course_name, string test_name, string date)
    {
        this->course_name = course_name;
        this->test_name = test_name;
        this->date = date;
        this->test_id = nextTestId;
        nextTestId++;
    }
    string getCourseName()
    {
        return course_name;
    }
    string getTestName()
    {
        return test_name;
    }
    string getDate()
    {
        return date;
    }
    int getId()
    {
        return test_id;
    }
    void setTestName(string test_name)
    {
        this->test_name = test_name;
    }
    void setDate(string date)
    {
        this->date = date;
    }
    void setCourseName(string course_name)
    {
        this->course_name = course_name;
    }
    void show()
    {
        cout << "Test ID: " << test_id << ", ";
        cout << "Course Name: " << course_name << ", ";
        cout << "Test Name: " << test_name << ", ";
        cout << "Date: " << date << endl;
    }
};

// Initialize the static variable
int Test::nextTestId = 1;

class TestResult
{
private:
    int student_id;
    int test_id;
    int score;

public:
    TestResult(int student_id, int test_id, int score)
    {
        this->student_id = student_id;
        this->test_id = test_id;
        this->score = score;
    }
    int getStudentId()
    {
        return student_id;
    }
    int getTestId()
    {
        return test_id;
    }
    int getScore()
    {
        return score;
    }
    void setScore(int score)
    {
        this->score = score;
    }
    void show()
    {
        cout << "Student ID: " << student_id << ", ";
        cout << "Test ID: " << test_id << ", ";
        cout << "Grade: " << score << endl;
    }
};

class School
{
private:
    vector<Student> students;
    vector<Test> tests;
    vector<TestResult> testResults;

public:
    void addStudent()
    {
        string name, email;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter student email: ";
        getline(cin, email);
        Student student(name, email);
        students.push_back(student);
        // cout << "Student added successfully" << endl;
    }
    void editStudent()
    {
        if (students.empty())
        {
            cout << "No students to edit." << endl;
            return;
        }
        int id;
        // print all students name and id
        for (int i = 0; i < students.size(); i++)
        {
            cout << i + 1 << "-> ";
            students[i].show();
        }
        cout << "Enter student id to edit or " << students.size() + 1 << " to return: ";
        cin >> id;
        if (id >= students.size() + 1)
        {
            return;
        }
        string name, email;
        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter student email: ";
        getline(cin, email);
        students[id - 1].setName(name);
        students[id - 1].setEmail(email);
        cout << "Student updated successfully" << endl;
    }
    void deleteStudent()
    {
        if (students.empty())
        {
            cout << "No students to delete" << endl;
            return;
        }
        int id;
        // print all students name and id
        for (int i = 0; i < students.size(); i++)
        {
            cout << i + 1 << "-> ";
            students[i].show();
        }
        cout << "Enter student id to delete or " << students.size() + 1 << " to return: ";
        cin >> id;
        if (id >= students.size() + 1)
        {
            return;
        }
        students.erase(students.begin() + id - 1);
        // delete all test results for this student
        for (int i = 0; i < testResults.size(); i++)
        {
            if (testResults[i].getStudentId() == id)
            {
                testResults.erase(testResults.begin() + i);
                i--;
            }
        }
        cout << "Student deleted successfully" << endl;
    }
    void addTest()
    {
        string course_name, test_name, date;
        cout << "Enter course name: ";
        cin.ignore();
        getline(cin, course_name);
        cout << "Enter test name: ";
        getline(cin, test_name);
        cout << "Enter test date: ";
        getline(cin, date);
        Test test(course_name, test_name, date);
        tests.push_back(test);
        cout << "Test added successfully" << endl;
    }
    void editTest()
    {
        if (tests.empty())
        {
            cout << "No tests to edit" << endl;
            return;
        }
        int id;
        // print all tests name and id
        for (int i = 0; i < tests.size(); i++)
        {
            cout << i + 1 << "-> ";
            tests[i].show();
        }
        cout << "Enter test id to edit or " << tests.size() + 1 << " to return: ";
        cin >> id;
        if (id >= tests.size() + 1)
        {
            return;
        }
        string course_name, test_name, date;
        cout << "Enter course name: ";
        cin.ignore();
        getline(cin, course_name);
        cout << "Enter test name: ";
        getline(cin, test_name);
        cout << "Enter test date: ";
        getline(cin, date);
        tests[id - 1].setCourseName(course_name);
        tests[id - 1].setTestName(test_name);
        tests[id - 1].setDate(date);
        cout << "Test updated successfully" << endl;
    }
    void deleteTest()
    {
        if (tests.empty())
        {
            cout << "No tests to delete" << endl;
            return;
        }
        int id;
        // print all tests name and id
        for (int i = 0; i < tests.size(); i++)
        {
            cout << i + 1 << "-> ";
            tests[i].show();
        }
        cout << "Enter test id to delete or " << tests.size() + 1 << " to return: ";
        cin >> id;
        if (id >= tests.size() + 1)
        {
            return;
        }
        tests.erase(tests.begin() + id - 1);
        // delete all test results for this test
        for (int i = 0; i < testResults.size(); i++)
        {
            if (testResults[i].getTestId() == id)
            {
                testResults.erase(testResults.begin() + i);
                i--;
            }
        }
        cout << "Test deleted successfully" << endl;
    }
    void addTestResult()
    {
        if (students.empty() || tests.empty())
        {
            cout << "No students or tests to add result" << endl;
            return;
        }
        int student_id, test_id, score;
        // print all students name and id
        for (int i = 0; i < students.size(); i++)
        {
            cout << i + 1 << "-> ";
            students[i].show();
        }
        cout << "Enter student id: ";
        cin >> student_id;
        if (student_id < 1 || student_id > students.size())
        {
            cout << "Invalid student id" << endl;
            return;
        }
        // print all tests name and id
        for (int i = 0; i < tests.size(); i++)
        {
            cout << i + 1 << "-> ";
            tests[i].show();
        }
        cout << "Enter test id: ";
        cin >> test_id;
        if (test_id < 1 || test_id > tests.size())
        {
            cout << "Invalid test id" << endl;
            return;
        }
        cout << "Enter score: ";
        cin >> score;
        TestResult testResult(student_id, test_id, score);
        testResults.push_back(testResult);
        cout << "Test result added successfully" << endl;
    }
    void editTestResult()
    {
        if (testResults.empty())
        {
            cout << "No test results to edit" << endl;
            return;
        }
        int student_id, test_id, score;
        bool isFound = false;
        // print all students
        for (int i = 0; i < students.size(); i++)
        {
            cout << i + 1 << "-> ";
            students[i].show();
        }
        cout << "Enter student id to edit or " << students.size() + 1 << " to return: ";
        cin >> student_id;

        if (student_id < 1 || student_id > students.size())
        {
            cout << "Invalid student id" << endl;
            return;
        }

        // print all tests for this student
        for (int i = 0; i < testResults.size(); i++)
        {
            if (testResults[i].getStudentId() == student_id)
            {
                cout << i + 1 << "-> ";
                testResults[i].show();
                isFound = true;
            }
        }


        if (!isFound)
        {
            cout << "No test results for this student" << endl;
            return;
        }

        cout << "Enter test id to edit:";
        cin >> test_id;

        // search for the test result to edit for this student
        for (int i = 0; i < testResults.size(); i++)
        {
            if (testResults[i].getStudentId() == student_id && testResults[i].getTestId() == test_id)
            {
                cout << "Enter new score: ";
                cin >> score;
                testResults[i].setScore(score);
                cout << "Test result updated successfully" << endl;
                return;
            }
        }

        cout << "Invalid test id for this student" << endl;
    }
    void deleteTestResult()
    {
        if (testResults.empty())
        {
            cout << "No test results to delete" << endl;
            return;
        }
        int student_id, test_id;
        bool isFound = false;
        // print all students
        for (int i = 0; i < students.size(); i++)
        {
            cout << i + 1 << "-> ";
            students[i].show();
        }
        cout << "Enter student id to delete or " << students.size() + 1 << " to return: ";
        cin >> student_id;

        if (student_id < 1 || student_id > students.size())
        {
            cout << "Invalid student id" << endl;
            return;
        }

        // print all test results for this student
        for (int i = 0; i < testResults.size(); i++)
        {
            if (testResults[i].getStudentId() == student_id)
            {
                cout << i + 1 << "-> ";
                testResults[i].show();
                isFound = true;
            }
        }
        if(!isFound){
            cout << "No results found for this student" << endl;
        }

        cout << "Enter test id to delete:";
        cin >> test_id;

        for(int i = 0; i < testResults.size(); i++){
            if(testResults[i].getStudentId() == student_id && testResults[i].getTestId() == test_id){
                // remove it
                testResults.erase(testResults.begin() + i);
                cout << "Test result deleted successfully" << endl;
                return;
            }
        }

        cout << "Invalid test id for this student" << endl;
    }

    void show_all()
    {
        cout << "Students details:" << endl;
        if (students.empty())
        {
            cout << "No students to show" << endl;
        }
        else
        {
            for (int i = 0; i < students.size(); i++)
            {
                cout << "student id = " << students[i].getId() << ", ";
                cout << "name = " << students[i].getName() << ", ";
                cout << "email = " << students[i].getEmail() << endl;
            }
        }

        cout << "Tests details:" << endl;
        if (tests.empty())
        {
            cout << "No tests to show" << endl;
        }
        else
        {
            for (int i = 0; i < tests.size(); i++)
            {
                cout << "test id = " << tests[i].getId() << ", ";
                cout << "course name = " << tests[i].getCourseName() << ", ";
                cout << "test name = " << tests[i].getTestName() << ", ";
                cout << "date = " << tests[i].getDate() << endl;
            }
        }

        cout << "Test results details:" << endl;
        if (testResults.empty())
        {
            cout << "No test results to show" << endl;
        }
        else
        {
            for (int i = 0; i < testResults.size(); i++)
            {
                cout << "student id = " << testResults[i].getStudentId() << ", ";
                cout << "course name = " << tests[testResults[i].getTestId() - 1].getCourseName() << ", ";
                cout << "test id = " << testResults[i].getTestId() << ", ";
                cout << "test name = " << tests[testResults[i].getTestId() - 1].getTestName() << ", ";
                cout << "grade = " << testResults[i].getScore() << endl;
            }
        }
    }
};

int main()
{
    School school;
    int choice;

    // freopen("test_file_in.txt", "r", stdin);
    // freopen("test_file_out.txt", "w", stdout);

    while (1)
    {
        cout << "1. Add student" << endl;
        cout << "2. Edit student" << endl;
        cout << "3. Remove student" << endl;
        cout << "4. Add test" << endl;
        cout << "5. Edit test" << endl;
        cout << "6. Remove test" << endl;
        cout << "7. Add test result" << endl;
        cout << "8. Edit test result" << endl;
        cout << "9. Remove test result" << endl;
        cout << "10. Show all info" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                school.addStudent();
                break;
            case 2:
                school.editStudent();
                break;
            case 3:
                school.deleteStudent();
                break;
            case 4:
                school.addTest();
                break;
            case 5:
                school.editTest();
                break;
            case 6:
                school.deleteTest();
                break;
            case 7:
                school.addTestResult();
                break;
            case 8:
                school.editTestResult();
                break;
            case 9:
                school.deleteTestResult();
                break;
            case 10:
                school.show_all();
                break;
            case 11:
                exit(0);
            default:
                cout << "Invalid choice" << endl;
        }
    }
    return 0;
}