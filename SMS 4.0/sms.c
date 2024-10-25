#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/ioctl.h>
#include <unistd.h>
#endif


#define MAX_STUDENTS 100
#define MAX_COURSES 10
#define CENTER_WIDTH 40

typedef struct {
    char name[50];
    char email[50];
    char id[10];
    float gpa;
    int attendance;
    int enrolledCourses;
} Student;

typedef struct {
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
void adminLogin();
void centerPrint(const char *text);
void goBackMenu();

// Function to get the terminal width
int getTerminalWidth() {
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        return columns;
    } else {
        return 80;  // Default width if retrieval fails
    }
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
#endif
}

// Function to print text centered in the terminal
void centerPrint(const char *text) {
    int len = strlen(text);
    int terminalWidth = getTerminalWidth();
    int spaces = (terminalWidth - len) / 2;
    for (int i = 0; i < spaces; i++) {
        printf(" ");
    }
    printf("%s\n", text);
}

void welcomePage() {
    system("clear || cls");
    centerPrint("\n");
    centerPrint("\n");
    centerPrint("==== Welcome to Student Management System! ====");
    centerPrint("\n");
    centerPrint("by _ovee_\n");
    centerPrint("\n");
    centerPrint("\n");
    centerPrint("\n");
    centerPrint("\n");
    centerPrint("Press any key to continue...");
    getchar();
    mainMenu();
}

void mainMenu() {
    int choice;
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== Student Management System ===\n");
    printf("\n");
    printf("1. Admin Panel\n");
    printf("\n");
    printf("2. Student Panel\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("Choose an option: ");
    scanf("%d", &choice);
    getchar(); // Clear newline buffer

    switch (choice) {
        case 1:
            adminLogin();
            break;
        case 2:
            studentPanel();
            break;
        default:
            printf("Invalid choice. Try again.");
            mainMenu();
    }
}

void goBackMenu() {
    printf("\n");
    printf("\n");
    printf("\nPress any key to go back...");
    getchar();
    getchar();
}

void adminLogin() {
    char username[50], password[50];
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("===Admin Login===\n");
    printf("\n");
    printf("[Enter default admin username and password to login....]\n");
    printf("\n");
    printf("Username: ");
    scanf("%s", username);
    printf("\n");
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) {
        adminPanel();
    } else {
        printf("\n");
        printf("\n");
        printf("\n");
        centerPrint("Invalid credentials. Try again.");
        goBackMenu();
        adminLogin();
    }
}

void adminPanel() {
    int choice;
    do {
        system("clear || cls");
        printf("\n");
        printf("\n");
        printf("=== Admin Panel ===");
        printf("\n");
        printf("\n");
        printf("1. Register Student\n");
        printf("2. Enroll in Course\n");
        printf("3. Update Grades\n");
        printf("4. View GPA\n");
        printf("5. Mark Attendance\n");
        printf("6. Generate Reports\n");
        printf("8. Sort Students\n");
        printf("9. View Students\n");
        printf("10. Log out\n");
        printf("\n");
        printf("\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
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
                viewGPA();
                break;
            case 5:
                markAttendance();
                break;
            case 6:
                generateReports();
                break;
            case 8:
                sortStudents();
                break;
            case 9:
                viewStudents();
                break;
            case 10:
                mainMenu();
                break;
            default:
                printf("\n");
                printf("\n");
                printf("\n");
                printf("Invalid choice!! Try again.");
                goBackMenu();
        }
    } while (choice != 10);
}

void registerStudent() {
    if (totalStudents >= MAX_STUDENTS) {
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
    scanf("%s", students[totalStudents].name);
    printf("\n");
    printf("Enter student email: ");
    scanf("%s", students[totalStudents].email);
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", students[totalStudents].id);
    students[totalStudents].gpa = 0.0;
    students[totalStudents].attendance = 0;
    students[totalStudents].enrolledCourses = 0;
    totalStudents++;
    printf("\n");
    printf("\n");
    printf("Student registered successfully!");
    goBackMenu();
}

void enrollCourse() {
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== Enroll in Course ===\n");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    printf("\n");
    for (int i = 0; i < totalStudents; i++) {
        if (strcmp(students[i].id, studentID) == 0) {
            printf("Enter course name to enroll: ");
            char courseName[50];
            scanf("%s", courseName);
            strcpy(courses[students[i].enrolledCourses].name, courseName);
            students[i].enrolledCourses++;
            printf("\n");
            printf("\n");
            printf("Student enrolled in course successfully!");
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("Student not found!");
    goBackMenu();
}

void updateGrades() {
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== Update Grades ===");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    for (int i = 0; i < totalStudents; i++) {
        if (strcmp(students[i].id, studentID) == 0) {
            printf("Enter new GPA: ");
            scanf("%f", &students[i].gpa);
            printf("\n");
            printf("\n");
            printf("GPA updated successfully!");
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("Student not found!");
    goBackMenu();
}

void viewGPA() {
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== View GPA ===");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    for (int i = 0; i < totalStudents; i++) {
        if (strcmp(students[i].id, studentID) == 0) {
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

void markAttendance() {
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== Mark Attendance ===");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    printf("\n");
    for (int i = 0; i < totalStudents; i++) {
        if (strcmp(students[i].id, studentID) == 0) {
            printf("Enter attendance (number of days): ");
            scanf("%d", &students[i].attendance);
            printf("\n");
            printf("\n");
            printf("Attendance updated successfully!");
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("Student not found!");
    goBackMenu();
}

void generateReports() {
    system("clear || cls");
    char studentID[10];
    printf("\n");
    printf("\n");
    printf("=== Generate Reports ===\n");
    printf("\n");
    printf("Enter student ID: ");
    scanf("%s", studentID);
    printf("\n");
    for (int i = 0; i < totalStudents; i++) {
        if (strcmp(students[i].id, studentID) == 0) {
            printf("=== Student Report ===\n");
            printf("Name: %s\n", students[i].name);
            printf("Email: %s\n", students[i].email);
            printf("GPA: %.2f\n", students[i].gpa);
            printf("Attendance: %d days\n", students[i].attendance);
            goBackMenu();
            return;
        }
    }
    printf("\n");
    printf("\n");
    printf("Student not found!");
    goBackMenu();
}

void sortStudents() {
    system("clear || cls");
    int choice;
    printf("\n");
    printf("\n");
    printf("=== Sort Students ===");
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

    if (choice == 1) {
        sortByGPA();
    } else if (choice == 2) {
        sortByName();
    } else {
        printf("\n");
        printf("\n");
        printf("Invalid choice!");
    }
    goBackMenu();
}

void sortByGPA() {
    for (int i = 0; i < totalStudents - 1; i++) {
        for (int j = i + 1; j < totalStudents; j++) {
            if (students[i].gpa < students[j].gpa) {
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
    printf("-------------------------------\n");
    for (int i = 0; i < totalStudents; i++) {
        printf("%-30s %.2f\n", students[i].name, students[i].gpa);
    }
}

void sortByName() {
    for (int i = 0; i < totalStudents - 1; i++) {
        for (int j = i + 1; j < totalStudents; j++) {
            if (strcmp(students[i].name, students[j].name) > 0) {
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
    printf("-------------------------------\n");
    for (int i = 0; i < totalStudents; i++) {
        printf("%-30s %.2f\n", students[i].name, students[i].gpa);
    }
}


void viewStudents() {
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== View Students ===\n");
    printf("\n");
    for (int i = 0; i < totalStudents; i++) {
        printf("Name: %s, GPA: %.2f\n", students[i].name, students[i].gpa);
    }
    goBackMenu();
}

void studentPanel() {
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

    for (int i = 0; i < totalStudents; i++) {
        if (strcmp(students[i].email, email) == 0 && strcmp(students[i].id, id) == 0) {
            int choice;
            do {
                system("clear || cls");
                printf("\n");
                printf("\n");
                printf("=== Student Panel ===");
                printf("\n");
                printf("\n");
                printf("1. View Info");
                printf("\n");
                printf("2. View GPA");
                printf("\n");
                printf("3. View Attendance");
                printf("\n");
                printf("4. Generate Reports");
                printf("\n");
                printf("5. Exit");
                printf("\n");
                printf("\n");
                printf("Choose an option: ");
                scanf("%d", &choice);

                switch (choice) {
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
                        generateReports();
                        break;
                    case 5:
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
}

void viewStudentInfo(int studentIndex) {
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== Student Info ===\n");
    printf("\n");
    printf("Name: %s\n", students[studentIndex].name);
    printf("Email: %s\n", students[studentIndex].email);
    printf("ID: %s\n", students[studentIndex].id);
    printf("Enrolled Courses: %d\n", students[studentIndex].enrolledCourses);
    goBackMenu();
}

void viewStudentGPA(int studentIndex) {
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== View GPA ===\n");
    printf("\n");
    printf("Your GPA: %.2f\n", students[studentIndex].gpa);
    goBackMenu();
}

void viewStudentAttendance(int studentIndex) {
    system("clear || cls");
    printf("\n");
    printf("\n");
    printf("=== View Attendance ===\n");
    printf("\n");
    printf("Your Attendance: %d days\n", students[studentIndex].attendance);
    goBackMenu();
}

int main() {
    welcomePage();
    return 0;
}
