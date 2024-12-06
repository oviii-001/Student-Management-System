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
    centerPrint("\n");
    centerPrint("\n");
    centerSlowPrint("\033[1;91m\033[47m==== Welcome to STUDENT MANAGEMENT SYSTEM! ====\033[0m", 10000);
    centerPrint("\n");
    centerSlowPrint("\033[1;91m\033[40m     _oveee_\033[0m", 10000);
    centerSlowPrint("\033[1;91m\033[40mby   _jakia_\033[0m", 10000);
    centerSlowPrint("\033[1;91m\033[40m     _israt_\033[0m", 10000);
    centerPrint("\n");
    centerPrint("\n");
    centerPrint("\n");
    centerPrint("\n");
    centerSlowPrint("\033[32mPress any key to continue...\033[0m", 10000);
    getchar();  // Wait for user input
    mainMenu(); // Call main menu after the welcome page
}

void mainMenu()
{
    int choice;
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== Student Management System ===\n");
    printf("\n");
    printf("1. Administrative Panel\n");
    printf("\n");
    printf("2. Student Panel\n");
    printf("\n");
    printf("3. Exit\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Choose an option: ");
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
        printf("Invalid choice. Try again.");
        mainMenu();
    }
}

void goBackMenu()
{
    printf("\n");
    printf("\n");
    printf("\nPress any key to go back...");
    getchar();
    getchar();
}

void adminLogin()
{
    char username[50], password[50];
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== Admin Login ===\n");
    printf("\n");
    printf("[Enter default admin username and password to login....]\n");
    printf("\n");
    printf("Username: ");
    scanf("%s", username);
    printf("\n");
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0)
    {
        printf("\n");
        const char *message = "Logged in successfully!\n";
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
        printf("Invalid credentials. Try again.");
        goBackMenu();
        adminLogin();
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
        printf("=== Administrative Panel ===");
        printf("\n");
        printf("\n");
        printf("1. Register Student\n");
        printf("2. Enroll in Course\n");
        printf("3. Update Grades\n");
        printf("4. Mark Attendance\n");
        printf("5. Generate Reports\n");
        printf("6. View GPA of specific student\n");
        printf("7. View GPA of all students\n");
        printf("8. View Students\n");
        printf("9. Log out\n");
        printf("\n");
        printf("\n");
        printf("Choose an option: ");
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
            printf("Invalid choice!! Try again.");
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
        printf("Student limit reached!");
        goBackMenu();
        return;
    }
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== Register Student ===\n");
    printf("\n");
    printf("Enter student name: ");
    while ((getchar()) != '\n'); // Flush leftover newline characters
    fgets(students[totalStudents].name, sizeof(students[totalStudents].name), stdin);
    students[totalStudents].name[strcspn(students[totalStudents].name, "\n")] = '\0'; // Remove newline character

    printf("\nEnter student email: ");
    fgets(students[totalStudents].email, sizeof(students[totalStudents].email), stdin);
    students[totalStudents].email[strcspn(students[totalStudents].email, "\n")] = '\0'; // Remove newline character

    printf("\nEnter student address: ");
    fgets(students[totalStudents].address, sizeof(students[totalStudents].address), stdin);
    students[totalStudents].address[strcspn(students[totalStudents].address, "\n")] = '\0'; // Remove newline character

    printf("\nEnter student ID: ");
    fgets(students[totalStudents].id, sizeof(students[totalStudents].id), stdin);
    students[totalStudents].id[strcspn(students[totalStudents].id, "\n")] = '\0'; // Remove newline character

    printf("\nEnter student department : ");
    fgets(students[totalStudents].department, sizeof(students[totalStudents].department), stdin);
    students[totalStudents].department[strcspn(students[totalStudents].department, "\n")] = '\0'; // Remove newline character

    students[totalStudents].gpa = 0.0;
    students[totalStudents].attendance = 0;
    students[totalStudents].enrolledCourses = 0;
    students[totalStudents].totalCredits = 0;
    totalStudents++;
    printf("\n");
    printf("\n");
    slowPrint("Student registered successfully!", 10000);
    saveStudentsToFile();
    goBackMenu();
}

void enrollCourse()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== Enroll in Course ===\n");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    printf("\n");
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("Enter course code to enroll: ");
            char courseName[50];
            scanf("%s", courseName);
            printf("\n");
            int courseCredits;
            printf("Enter course credits: ");
            scanf("%d", &courseCredits);
            strcpy(courses[students[i].enrolledCourses].name, courseName);
            courses[students[i].enrolledCourses].credits = courseCredits;
            students[i].totalCredits += courseCredits;
            students[i].enrolledCourses++;

            printf("\n");
            printf("\n");
            printf("Student enrolled in course %s successfully! Total credit is %d.", courseName, students[i].totalCredits);
            saveStudentsToFile();
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("Student not found!");
    goBackMenu();
}

void updateGrades()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== Update Grades ===");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("Enter new GPA: ");
            scanf("%f", &students[i].gpa);
            printf("\n");
            printf("\n");
            slowPrint("GPA updated successfully!", 10000);
            saveStudentsToFile();
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("Student not found!");
    goBackMenu();
}

void viewGPA()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== View GPA of specific student ===");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("GPA of %s: %.2f\n", students[i].name, students[i].gpa);
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("Student not found!");
    goBackMenu();
}

void markAttendance()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== Mark Attendance ===");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    printf("\n");
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("Enter attendance (number of days): ");
            scanf("%d", &students[i].attendance);
            printf("\n");
            printf("\n");
            slowPrint("Attendance updated successfully!", 10000);
            saveStudentsToFile();
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("Student not found!");
    goBackMenu();
}

void generateReports()
{
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== Generate Reports ===\n");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    printf("\n");
    for (int i = 0; i < totalStudents; i++)
    {
        if (strcmp(students[i].id, studentID) == 0)
        {
            printf("=================================\n");
            printf("         STUDENT REPORT          \n");
            printf("=================================\n");
            printf("Name             : %s\n", students[i].name);
            printf("ID               : %s\n", students[i].id);
            printf("Email            : %s\n", students[i].email);
            printf("Address          : %s\n", students[i].address);
            printf("Department       : %s\n", students[i].department);
            printf("Enrolled Courses : ");
            for (int j = 0; j < students[i].enrolledCourses; j++)
            {
                printf("%s", courses[j].name);
                if (j < students[i].enrolledCourses - 1)
                {
                    printf(", "); // Add a comma and space between courses
                }
            }
            printf("\n");
            printf("Total Credits    : %d\n", students[i].totalCredits);
            printf("GPA              : %.2f\n", students[i].gpa);
            printf("Attendance       : %d days\n", students[i].attendance);
            printf("=================================\n");

            goBackMenu();
            return;
        }
    }

    printf("\n");
    printf("\n");
    printf("Student not found!");
    goBackMenu();
}

void sortStudents()
{
    system("clear || cls");
    int choice;
    printf("\n");
    printf("\n");
    printf("=== View GPA of all students ===");
    printf("\n");
    printf("\n");
    printf("1. Sort by GPA");
    printf("\n");
    printf("2. Sort by Name");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Choose an option: ");
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
        printf("Invalid choice!");
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
    printf("Students sorted by GPA:");
    printf("\n");
    printf("%-30s %-10s\n", "Name", "GPA");
    printf("---------------------------------\n");
    for (int i = 0; i < totalStudents; i++)
    {
        printf("%-30s %.2f\n", students[i].name, students[i].gpa);
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
    printf("Students sorted by Name:");
    printf("\n");
    printf("%-30s %-10s\n", "Name", "GPA");
    printf("---------------------------------\n");
    for (int i = 0; i < totalStudents; i++)
    {
        printf("%-30s %.2f\n", students[i].name, students[i].gpa);
    }
}

void viewStudents()
{
    system("clear || cls");
    printf("\n");
    printf("=== View Students ===\n\n");
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
    printf("=== Student Panel ===\n");
    printf("\n");
    printf("Enter email: ");
    scanf("%s", email);
    printf("\n");
    printf("Enter ID: ");
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
                printf("=== Student Panel ===");
                printf("\n");
                printf("\n");
                printf("1. View Your Information");
                printf("\n");
                printf("2. View Your GPA");
                printf("\n");
                printf("3. View Your Attendance");
                printf("\n");
                printf("4. Generate Your Reports");
                printf("\n");
                printf("5. Log Out");
                printf("\n");
                printf("\n");
                printf("Choose an option: ");
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
                    printf("Invalid choice. Try again.");
                    goBackMenu();
                }
            } while (choice != 5);
        }
    }
    printf("\n");
    printf("\n");
    printf("Invalid credentials!");
    goBackMenu();
    studentPanel();
}

void viewStudentInfo(int studentIndex)
{
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== Your Student Information ===\n");
    printf("\n");
    printf("Name             : %s\n", students[studentIndex].name);
    printf("Email            : %s\n", students[studentIndex].email);
    printf("Address          : %s\n", students[studentIndex].address);
    printf("ID               : %s\n", students[studentIndex].id);
    printf("Department       : %s\n", students[studentIndex].department);
    printf("Enrolled Courses : ");
    for (int i = 0; i < students[studentIndex].enrolledCourses; i++)
    {
        printf("%s", courses[i].name);
        if (i < students[studentIndex].enrolledCourses - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
    printf("Total Credits    : %d\n", students[studentIndex].totalCredits);
    goBackMenu();
}

void viewStudentGPA(int studentIndex)
{
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== View Your GPA ===\n");
    printf("\n");
    printf("Your GPA: %.2f\n", students[studentIndex].gpa);
    goBackMenu();
}

void viewStudentAttendance(int studentIndex)
{
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== View Your Attendance ===\n");
    printf("\n");
    printf("Your Attendance: %d days\n", students[studentIndex].attendance);
    goBackMenu();
}

void generateStudentReports(int studentIndex)
{
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=================================\n");
    printf("         STUDENT REPORT          \n");
    printf("=================================\n");
    printf("Name             : %s\n", students[studentIndex].name);
    printf("Email            : %s\n", students[studentIndex].email);
    printf("Address          : %s\n", students[studentIndex].address);
    printf("Id               : %s\n", students[studentIndex].id);
    printf("Department       : %s\n", students[studentIndex].department);
    printf("Enrolled courses : ");
    for (int j = 0; j < students[studentIndex].enrolledCourses; j++)
    {
        printf("%s", courses[j].name);
        if(j < students[studentIndex].enrolledCourses - 1)
        {
            printf(", ");
        }
    }
    printf("\n");
    printf("Total credits    : %d\n", students[studentIndex].totalCredits);
    printf("GPA              : %.2f\n", students[studentIndex].gpa);
    printf("Attendance       : %d days\n", students[studentIndex].attendance);
    goBackMenu();
}

void loggingOut(){
    system("clear || cls");
    printf("=== Student Management System ===\n");
    printf("\n");
    printf("\n");
    slowPrint("Logging out...............", 200000);
}

void saveStudentsToFile() {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("\nError: Could not open file for writing!\n");
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
        centerSlowPrint("Exiting the program....\n", 200000);
        printf("\n");
        centerSlowPrint("Thank you for using our system!\n", 200000);
        printf("\n");
        system("clear || cls");
        exit(0);
}

int main()
{
    loadStudentsFromFile();
    welcomePage();
    return 0;
}
