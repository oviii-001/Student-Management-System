// STUDENT MANAGEMENT SYSTEM - SMS: A simple student management system using C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif

#define MAX_STUDENTS 500
#define MAX_COURSES 10
#define CENTER_WIDTH 40

typedef struct
{
    char name[50];
    char email[50];
    char id[10];
    char address[100];
    char department[50];
    float gpa;
    int attendance;
    int enrolledCourses;
    int totalCredits;
} Student;

typedef struct
{
    char name[50];
    int credits;
} Course;

Student students[MAX_STUDENTS];
Course courses[MAX_COURSES];
int totalStudents = 0;
int totalCourses = 0;

void welcomePage();
void mainMenu();
void adminPanel();
void studentPanel();
void registerStudent();
void enrollCourse();
void updateGrades();
void viewGPA();
void markAttendance();
void generateReports();
void sortStudents();
void sortByGPA();
void sortByName();
void viewStudents();
void viewStudentInfo(int studentIndex);
void viewStudentGPA(int studentIndex);
void viewStudentAttendance(int studentIndex);
void generateStudentReports(int studentIndex);
void adminLogin();
void centerPrint(const char *text);
void goBackMenu();
void loggingOut();
void saveStudentsToFile();
void loadStudentsFromFile();
void exitProgram();
void loadingScreen();

// Function to get the terminal width
int getTerminalWidth()
{
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        return columns;
    }
    else
    {
        return 80; // Default width if retrieval fails
    }
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}

// Function to print text centered in the terminal
void centerPrint(const char *text)
{
    int len = strlen(text);
    int terminalWidth = getTerminalWidth();
    int spaces = (terminalWidth - len) / 2;
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    printf("%s\n", text);
}

// Function to print text slowly
void slowPrint(const char *text, int delay)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        putchar(text[i]);
        fflush(stdout); // Force immediate output
        usleep(delay);  // Delay in microseconds
    }
}

// Function to print text centered and slowly
void centerSlowPrint(const char *text, int delay)
{
    int len = strlen(text);
    int terminalWidth = getTerminalWidth();
    int spaces = (terminalWidth - len) / 2;
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }
    slowPrint(text, delay);
    printf("\n"); // Add a newline after the text
}

void welcomePage()
{
    system("clear || cls");

    printf("\033[1;31m");  // Set text color to red
    printf("\t\t_____/\\\\\\\\\\\\\\\\\\\\\\___        __/\\\\\\\\____________/\\\\\\\\_        _____/\\\\\\\\\\\\\\\\\\\\\\___     \n");
    printf("\t\t ___/\\\\\\/////////\\\\\\_        _\\/\\\\\\\\\\\\________/\\\\\\\\\\\\_        ___/\\\\\\/////////\\\\\\_       \n");
    printf("\t\t  __\\//\\\\\\______\\///__        _\\/\\\\\\//\\\\\\____/\\\\\\//\\\\\\_        __\\//\\\\\\______\\///__      \n");
    printf("\t\t   ___\\////\\\\\\_________        _\\/\\\\\\\\///\\\\\\/\\\\\\/_\\/\\\\\\_        ___\\////\\\\\\_________     \n");
    printf("\t\t    ______\\////\\\\\\______        _\\/\\\\\\__\\///\\\\\\/___\\/\\\\\\_        ______\\////\\\\\\______    \n");
    printf("\t\t     _________\\////\\\\\\___        _\\/\\\\\\____\\///_____\\/\\\\\\_        _________\\////\\\\\\___   \n");
    printf("\t\t      __/\\\\\\______\\//\\\\\\__        _\\/\\\\\\_____________\\/\\\\\\_        __/\\\\\\______\\//\\\\\\__  \n");
    printf("\t\t       _\\///\\\\\\\\\\\\\\\\\\\\\\/___        _\\/\\\\\\_____________\\/\\\\\\_        _\\///\\\\\\\\\\\\\\\\\\\\\\/___ \n");
    printf("\t\t        ___\\///////////_____        _\\///______________\\///__        ___\\///////////_____\n");
    printf("\033[0m");  // Reset text color to default

    centerPrint("\n");
    centerPrint("\n");
    centerSlowPrint("\033[34m\033[48;5;153m\t\t==== Welcome to STUDENT MANAGEMENT SYSTEM! ====\033[0m", 10000);
    centerPrint("\n");
    centerSlowPrint("\033[1;32m\033[40m\t\t     _oveee_\033[0m", 10000);
    centerSlowPrint("\033[1;32m\033[40m\t\tby   _jakia_\033[0m", 10000);
    centerSlowPrint("\033[1;32m\033[40m\t\t     _israt_\033[0m", 10000);
    centerPrint("\n");
    centerPrint("\n");
    centerPrint("\n");
    centerPrint("\n");
    centerSlowPrint("\033[36m\tPress any key to continue...\033[0m", 10000);
    getchar();  // Wait for user input
    loadingScreen();
    mainMenu(); // Call main menu after the welcome page
}

void mainMenu()
{
    int choice;
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== Student Management System ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\t   1. Administrative Panel\n");
    printf("\n");
    printf("\t\t\t\t\t   2. Student Panel\n");
    printf("\n");
    printf("\t\t\t\t\t   3. Exit\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[36mChoose an option:\033[0m ");
    scanf("%d", &choice);
    getchar(); // Clear newline buffer

    switch (choice)
    {
    case 1:
        adminLogin();
        break;
    case 2:
        studentPanel();
        break;
    case 3:
        exitProgram();
        break;
    default:
        printf("\t\t\t\t\t\033[1;31mInvalid choice. Try again.\033[0m");
        mainMenu();
    }
}

void goBackMenu()
{
    printf("\n");
    printf("\n");
    printf("\n\t\t\t\t\t\033[36mPress any key to go back...\033[0m");
    getchar();
    getchar();
}

void adminLogin()
{
    char username[50], password[50];
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\t\033[34m\033[48;5;153m=== Admin Login ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t[Enter default admin username and password to login....]\n");
    printf("\n");
    printf("\t\t\t\t\t   Username: ");
    scanf("%s", username);
    printf("\n");
    printf("\t\t\t\t\t   Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
    {
        printf("\n");
        const char *message = "\t\t\t\t\t\033[1;32mLogged in successfully!\033[0m\n";
        for (int i = 0; message[i] != '\0'; i++)
        {
            printf("%c", message[i]);
            fflush(stdout); // Ensure each character is printed immediately
            usleep(10000);  // Delay for 10 milliseconds
        }
        sleep(2); // Pause for 1 second before redirecting to adminPanel
        adminPanel();
    }
    else
    {
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\033[1;31mInvalid credentials!\033[0m");
        sleep(1);
        goBackMenu();
        mainMenu();
    }
}

void adminPanel()
{
    int choice;
    do
    {
        system("clear || cls");
        printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\033[34m\033[48;5;153m=== Administrative Panel ===\033[0m");
        printf("\n");
        printf("\n");
        printf("\t\t\t\t\t   1. Register Student\n");
        printf("\t\t\t\t\t   2. Enroll in Course\n");
        printf("\t\t\t\t\t   3. Update Grades\n");
        printf("\t\t\t\t\t   4. Mark Attendance\n");
        printf("\t\t\t\t\t   5. Generate Reports\n");
        printf("\t\t\t\t\t   6. View GPA of specific student\n");
        printf("\t\t\t\t\t   7. View GPA of all students\n");
        printf("\t\t\t\t\t   8. View Students\n");
        printf("\t\t\t\t\t   9. Log out\n");
        printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\033[36mChoose an option:\033[0m ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            registerStudent();
            break;
        case 2:
            enrollCourse();
            break;
        case 3:
            updateGrades();
            break;
        case 4:
            markAttendance();
            break;
        case 5:
            generateReports();
            break;
        case 6:
            viewGPA();
            break;
        case 7:
            sortStudents();
            break;
        case 8:
            viewStudents();
            break;
        case 9:
            loggingOut();
            mainMenu();
            break;
        default:
            printf("\n");
            printf("\n");
            printf("\n");
            printf("\t\t\t\t\t\033[1;31mInvalid choice! Try again.\033[0m");
            goBackMenu();
        }
    } while (choice != 9);
}

void registerStudent()
{
    if (totalStudents >= MAX_STUDENTS)
    {
        printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\033[1;31mStudent limit reached!\033[0m");
        goBackMenu();
        return;
    }
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\t\033[34m\033[48;5;153m=== Register Student ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\t Enter student name: ");
    while ((getchar()) != '\n'); // Flush leftover newline characters
    fgets(students[totalStudents].name, sizeof(students[totalStudents].name), stdin);
    students[totalStudents].name[strcspn(students[totalStudents].name, "\n")] = '\0'; // Remove newline character

    printf("\n\t\t\t\t\t Enter student email: ");
    fgets(students[totalStudents].email, sizeof(students[totalStudents].email), stdin);
    students[totalStudents].email[strcspn(students[totalStudents].email, "\n")] = '\0'; // Remove newline character

    printf("\n\t\t\t\t\t Enter student address: ");
    fgets(students[totalStudents].address, sizeof(students[totalStudents].address), stdin);
    students[totalStudents].address[strcspn(students[totalStudents].address, "\n")] = '\0'; // Remove newline character

    printf("\n\t\t\t\t\t Enter student ID: ");
    fgets(students[totalStudents].id, sizeof(students[totalStudents].id), stdin);
    students[totalStudents].id[strcspn(students[totalStudents].id, "\n")] = '\0'; // Remove newline character

    printf("\n\t\t\t\t\t Enter student department : ");
    fgets(students[totalStudents].department, sizeof(students[totalStudents].department), stdin);
    students[totalStudents].department[strcspn(students[totalStudents].department, "\n")] = '\0'; // Remove newline character

    students[totalStudents].gpa = 0.0;
    students[totalStudents].attendance = 0;
    students[totalStudents].enrolledCourses = 0;
    students[totalStudents].totalCredits = 0;
    totalStudents++;
    printf("\n");
    printf("\n");
    slowPrint("\t\t\t\t\t\033[1;32mStudent registered successfully!\033[0m", 10000);
    saveStudentsToFile();
    goBackMenu();
}

void enrollCourse()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== Enroll in Course ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\t Enter student ID: ");
    scanf("%s", studentID);
    printf("\n");
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("\t\t\t\t\t Enter course code to enroll: ");
            char courseName[50];
            scanf("%s", courseName);
            printf("\n");
            int courseCredits;
            printf("\t\t\t\t\t Enter course credits: ");
            scanf("%d", &courseCredits);
            strcpy(courses[students[i].enrolledCourses].name, courseName);
            courses[students[i].enrolledCourses].credits = courseCredits;
            students[i].totalCredits += courseCredits;
            students[i].enrolledCourses++;

            printf("\n");
            printf("\n");
            printf("\t\t\t\t\t\033[1;32mStudent enrolled in course \033[1;33m%s\033[0m \033[1;32msuccessfully! Total credit is \033[1;33m%d\033[0m\033[1;32m.\033[0m", courseName, students[i].totalCredits);
            saveStudentsToFile();
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[1;31mStudent not found!\033[0m");
    goBackMenu();
}

void updateGrades()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== Update Grades ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\tEnter student ID: ");
    printf("\n");
    printf("\n");
    scanf("%s", studentID);
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("\t\t\t\t\tEnter new GPA: ");
            scanf("%f", &students[i].gpa);
            printf("\n");
            printf("\n");
            slowPrint("\t\t\t\t\t\033[1;32mGPA updated successfully!\033[0m", 10000);
            saveStudentsToFile();
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[1;31mStudent not found!\033[0m");
    goBackMenu();
}

void viewGPA()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== View GPA of specific student ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\t   Enter student ID: ");
    printf("\n");
    printf("\n");
    printf("\n");
    scanf("%s", studentID);
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("\t\t\t\t\t   GPA of %s: %.2f\n", students[i].name, students[i].gpa);
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[1;31mStudent not found!\033[0m");
    goBackMenu();
}

void markAttendance()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== Mark Attendance ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\t   Enter student ID: ");
    scanf("%s", studentID);
    printf("\n");
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("\t\t\t\t\t   Enter attendance (number of days): ");
            scanf("%d", &students[i].attendance);
            printf("\n");
            printf("\n");
            slowPrint("\t\t\t\t\t\033[1;32mAttendance updated successfully!\033[0m", 10000);
            saveStudentsToFile();
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[1;31mStudent not found!\033[0m");
    goBackMenu();
}

void generateReports()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\t\033[34m\033[48;5;153m=== Generate Reports ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\tEnter student ID: ");
    scanf("%s", studentID);
    printf("\n");
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("\t\t\t\t\t======================================\n");
            printf("\t\t\t\t\t              STUDENT REPORT          \n");
            printf("\t\t\t\t\t======================================\n");
            printf("\t\t\t\t\tName             : %s\n", students[i].name);
            printf("\t\t\t\t\tID               : %s\n", students[i].id);
            printf("\t\t\t\t\tEmail            : %s\n", students[i].email);
            printf("\t\t\t\t\tAddress          : %s\n", students[i].address);
            printf("\t\t\t\t\tDepartment       : %s\n", students[i].department);
            printf("\t\t\t\t\tEnrolled Courses : ");
            for (int j = 0; j < students[i].enrolledCourses; j++)
            {
                printf("%s", courses[j].name);
                if (j < students[i].enrolledCourses - 1)
                {
                    printf(", "); // Add a comma and space between courses
                }
            }
            printf("\n");
            printf("\t\t\t\t\tTotal Credits    : %d\n", students[i].totalCredits);
            printf("\t\t\t\t\tGPA              : %.2f\n", students[i].gpa);
            printf("\t\t\t\t\tAttendance       : %d days\n", students[i].attendance);
            printf("\t\t\t\t\t======================================\n");

            goBackMenu();
            return;
        }
    }

    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[1;31mStudent not found!\033[0m");
    goBackMenu();
}

void sortStudents()
{
    system("clear || cls");
    int choice;
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== View GPA of all students ===\033[0m");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t   1. Sort by GPA");
    printf("\n");
    printf("\t\t\t\t\t   2. Sort by Name");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[36mChoose an option:\033[0m ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        sortByGPA();
    }
    else if (choice == 2)
    {
        sortByName();
    }
    else
    {
        printf("\n");
        printf("\n");
        printf("\t\t\t\t\t\033[1;31mInvalid choice!\033[0m");
    }
    goBackMenu();
}

void sortByGPA()
{
    for (int i = 0; i < totalStudents - 1; i++)
    {
        for (int j = i + 1; j < totalStudents; j++)
        {
            if (students[i].gpa < students[j].gpa)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\tStudents sorted by GPA:");
    printf("\n");
    printf("\t\t\t\t\t%-30s %-10s\n", "Name", "GPA");
    printf("\t\t\t\t\t-----------------------------------\n");
    for (int i = 0; i < totalStudents; i++)
    {
        printf("\t\t\t\t\t%-30s %.2f\n", students[i].name, students[i].gpa);
    }
}

void sortByName()
{
    for (int i = 0; i < totalStudents - 1; i++)
    {
        for (int j = i + 1; j < totalStudents; j++)
        {
            if (strcmp(students[i].name, students[j].name) > 0)
            {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\tStudents sorted by Name:");
    printf("\n");
    printf("\t\t\t\t\t%-30s %-10s\n", "Name", "GPA");
    printf("\t\t\t\t\t-----------------------------------\n");
    for (int i = 0; i < totalStudents; i++)
    {
        printf("\t\t\t\t\t%-30s %.2f\n", students[i].name, students[i].gpa);
    }
}

void viewStudents()
{
    system("clear || cls");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== View Students ===\033[0m\n\n");
    printf("List of Students:\n");
    printf("\n");

    // Table header with adjusted column widths
    printf("%-20s %-30s %-10s %-25s %-20s %-15s %-5s %-10s\n",
           "Name", "Email", "ID", "Department", "Enrolled Courses",
           "Total Credits", "GPA", "Attendance");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------\n");

    // Print student details with formatted alignment
    for (int i = 0; i < totalStudents; i++)
    {
        printf("%-20s %-30s %-10s %-25s %-20d %-15d %-5.2f %d days\n",
               students[i].name,
               students[i].email,
               students[i].id,
               students[i].department,
               students[i].enrolledCourses,
               students[i].totalCredits,
               students[i].gpa,
               students[i].attendance);
    }

    goBackMenu();
}

void studentPanel()
{
    char email[50], id[10];
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\t\033[34m\033[48;5;153m=== Student Panel ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\tEnter email: ");
    scanf("%s", email);
    printf("\n");
    printf("\t\t\t\t\tEnter ID: ");
    scanf("%s", id);

    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].email, email) == 0 && strcmp(students[i].id, id) == 0)
        {
            int choice;
            do
            {
                system("clear || cls");
                printf("\n");
                printf("\n");
                printf("\t\t\t\t\t  \033[34m\033[48;5;153m=== Student Panel ===\033[0m");
                printf("\n");
                printf("\n");
                printf("\t\t\t\t\t1. View Your Information");
                printf("\n");
                printf("\t\t\t\t\t2. View Your GPA");
                printf("\n");
                printf("\t\t\t\t\t3. View Your Attendance");
                printf("\n");
                printf("\t\t\t\t\t4. Generate Your Reports");
                printf("\n");
                printf("\t\t\t\t\t5. Log Out");
                printf("\n");
                printf("\n");
                printf("\t\t\t\t\t\033[36mChoose an option:\033[0m ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    viewStudentInfo(i);
                    break;
                case 2:
                    viewStudentGPA(i);
                    break;
                case 3:
                    viewStudentAttendance(i);
                    break;
                case 4:
                    generateStudentReports(i);
                    break;
                case 5:
                    loggingOut();
                    mainMenu();
                    break;
                default:
                    printf("\n");
                    printf("\n");
                    printf("\t\t\t\t\t\033[1;31mInvalid choice! Try again.\033[0m");
                    goBackMenu();
                }
            } while (choice != 5);
        }
    }
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[1;31mInvalid credentials!\033[0m");
    sleep(1);
    goBackMenu();
    mainMenu();
}

void viewStudentInfo(int studentIndex)
{
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== Your Student Information ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\tName             : %s\n", students[studentIndex].name);
    printf("\t\t\t\t\tEmail            : %s\n", students[studentIndex].email);
    printf("\t\t\t\t\tAddress          : %s\n", students[studentIndex].address);
    printf("\t\t\t\t\tID               : %s\n", students[studentIndex].id);
    printf("\t\t\t\t\tDepartment       : %s\n", students[studentIndex].department);
    printf("\t\t\t\t\tEnrolled Courses : ");
    for (int i = 0; i < students[studentIndex].enrolledCourses; i++)
    {
        printf("%s", courses[i].name);
        if (i < students[studentIndex].enrolledCourses - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
    printf("\t\t\t\t\tTotal Credits    : %d\n", students[studentIndex].totalCredits);
    goBackMenu();
}

void viewStudentGPA(int studentIndex)
{
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== View Your GPA ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\t  Your GPA: %.2f\n", students[studentIndex].gpa);
    goBackMenu();
}

void viewStudentAttendance(int studentIndex)
{
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== View Your Attendance ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\t Your Attendance: %d days\n", students[studentIndex].attendance);
    goBackMenu();
}

void generateStudentReports(int studentIndex)
{
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== Generate Your Report ===\033[0m\n");
    printf("\n");
    printf("\t\t\t\t\t======================================\n");
    printf("\t\t\t\t\t              STUDENT REPORT          \n");
    printf("\t\t\t\t\t======================================\n");
    printf("\t\t\t\t\tName             : %s\n", students[studentIndex].name);
    printf("\t\t\t\t\tEmail            : %s\n", students[studentIndex].email);
    printf("\t\t\t\t\tAddress          : %s\n", students[studentIndex].address);
    printf("\t\t\t\t\tId               : %s\n", students[studentIndex].id);
    printf("\t\t\t\t\tDepartment       : %s\n", students[studentIndex].department);
    printf("\t\t\t\t\tEnrolled courses : ");
    for (int j = 0; j < students[studentIndex].enrolledCourses; j++)
    {
        printf("%s", courses[j].name);
        if(j < students[studentIndex].enrolledCourses - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
    printf("\t\t\t\t\tTotal credits    : %d\n", students[studentIndex].totalCredits);
    printf("\t\t\t\t\tGPA              : %.2f\n", students[studentIndex].gpa);
    printf("\t\t\t\t\tAttendance       : %d days\n", students[studentIndex].attendance);
    printf("\t\t\t\t\t======================================\n");
    goBackMenu();
}

void loggingOut(){
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("\t\t\t\t\t\033[34m\033[48;5;153m=== Student Management System ===\033[0m\n");
    printf("\n");
    printf("\n");
    slowPrint("\t\t\t\t\t\033[1;31mLogging out...............\033[0m", 200000);
}

void saveStudentsToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("\n\t\t\t\t\t\033[1;31mError: Could not open file for writing!\033[0m\n");
        return;
    }

    // First, save the total number of students
    fprintf(file, "%d\n", totalStudents);

    // Save each student's data
    for (int i = 0; i < totalStudents; i++) {
        fprintf(file, "%s\n", students[i].name);
        fprintf(file, "%s\n", students[i].email);
        fprintf(file, "%s\n", students[i].id);
        fprintf(file, "%s\n", students[i].address);
        fprintf(file, "%s\n", students[i].department);
        fprintf(file, "%f\n", students[i].gpa);
        fprintf(file, "%d\n", students[i].attendance);
        fprintf(file, "%d\n", students[i].enrolledCourses);
        fprintf(file, "%d\n", students[i].totalCredits);

        // Save enrolled courses for this student
        for (int j = 0; j < students[i].enrolledCourses; j++) {
            fprintf(file, "%s\n", courses[j].name);
            fprintf(file, "%d\n", courses[j].credits);
        }
    }

    fclose(file);
}

void loadStudentsFromFile() {
    FILE *file = fopen("students.txt", "r");
    if (file == NULL) {
        // File might not exist on first run, so just return
        return;
    }

    // Reset total students before loading
    totalStudents = 0;
    totalCourses = 0;

    // Read total number of students
    if (fscanf(file, "%d\n", &totalStudents) != 1) {
        fclose(file);
        return;
    }

    // Load each student's data
    for (int i = 0; i < totalStudents; i++) {
        // Read student details
        fgets(students[i].name, sizeof(students[i].name), file);
        students[i].name[strcspn(students[i].name, "\n")] = '\0';

        fgets(students[i].email, sizeof(students[i].email), file);
        students[i].email[strcspn(students[i].email, "\n")] = '\0';

        fgets(students[i].id, sizeof(students[i].id), file);
        students[i].id[strcspn(students[i].id, "\n")] = '\0';

        fgets(students[i].address, sizeof(students[i].address), file);
        students[i].address[strcspn(students[i].address, "\n")] = '\0';

        fgets(students[i].department, sizeof(students[i].department), file);
        students[i].department[strcspn(students[i].department, "\n")] = '\0';

        fscanf(file, "%f\n", &students[i].gpa);
        fscanf(file, "%d\n", &students[i].attendance);
        fscanf(file, "%d\n", &students[i].enrolledCourses);
        fscanf(file, "%d\n", &students[i].totalCredits);

        // Load enrolled courses for this student
        for (int j = 0; j < students[i].enrolledCourses; j++) {
            fgets(courses[j].name, sizeof(courses[j].name), file);
            courses[j].name[strcspn(courses[j].name, "\n")] = '\0';
            
            fscanf(file, "%d\n", &courses[j].credits);
            
            // Update total courses if needed
            if (j >= totalCourses) {
                totalCourses = j + 1;
            }
        }
    }

    fclose(file);
}


void exitProgram(){
    system("clear || cls");
        printf("\n");
        printf("\n");
        printf("\n");
        printf("\n");
        centerSlowPrint("\033[1;31mExiting the program....\033[0m\n", 200000);
        printf("\n");
        centerSlowPrint("\033[1;33mThank you for using our system!\033[0m\n", 200000);
        printf("\n");
        system("clear || cls");
        exit(0);
}

void loadingScreen() {

    system("clear || cls");


    int total = 50;  // Total number of steps in the progress bar
    int i;

    // Get terminal dimensions (width and height)
    const char *cols = getenv("COLUMNS");
    const char *rows = getenv("LINES");
    int terminal_width = cols ? atoi(cols) : 80;  // Default to 80 columns if not set
    int terminal_height = rows ? atoi(rows) : 24;  // Default to 24 rows if not set

    // Calculate the padding to center the loading bar horizontally
    int progress_bar_width = total + 2;  // Width of the progress bar with spaces
    int horizontal_padding = (terminal_width - progress_bar_width) / 2;

    // Calculate the padding to center the loading screen vertically
    int vertical_padding = (terminal_height - 3) / 2;  // 3 lines for message, bar, and done

    // Print vertical padding
    for (i = 0; i < vertical_padding; i++) {
        printf("\n");
    }

    // Print horizontal padding and the message
    for (i = 0; i < horizontal_padding; i++) {
        printf(" ");
    }
    printf("\033[1;32mPlease wait while loading...\033[0m\n");

    // Print horizontal padding for the progress bar
    for (i = 0; i < horizontal_padding; i++) {
        printf(" ");
    }
    printf("\033[0;32m");  // Start of the loading bar with green color

    for (i = 0; i < total; i++) {
        // Print a progress bar with '#' for each step
        printf("\033[42m \033[0m");  // Green background for each step
        fflush(stdout);  // Ensure the output is printed immediately
        usleep(100000);  // Sleep for 0.1 second to create animation effect
    }

    // Print the remaining part of the progress bar and finish
    // printf("\n");

    // Print the final message
    for (i = 0; i < horizontal_padding; i++) {
        printf("");
    }
    printf("\033[0;32m Done!\033[0m\n");

    sleep(1);
}

int main()
{
    loadStudentsFromFile();
    welcomePage();
    return 0;
}
