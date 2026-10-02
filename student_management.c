#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILE_NAME "students.dat"

typedef struct {
    int id;
    char name[50];
    float marks;
    float gpa;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

float calculateGPA(float marks) {
    if (marks >= 80)
        return 4.00;
    else if (marks >= 75)
        return 3.75;
    else if (marks >= 70)
        return 3.50;
    else if (marks >= 65)
        return 3.25;
    else if (marks >= 60)
        return 3.00;
    else if (marks >= 55)
        return 2.75;
    else if (marks >= 50)
        return 2.50;
    else
        return 0.00;
}

void saveStudents() {
    FILE *file = fopen(FILE_NAME, "wb");

    if (file == NULL) {
        printf("\nError: Could not save data.\n");
        return;
    }

    fwrite(&studentCount, sizeof(int), 1, file);
    fwrite(students, sizeof(Student), studentCount, file);

    fclose(file);
}

void loadStudents() {
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return;

    fread(&studentCount, sizeof(int), 1, file);
    fread(students, sizeof(Student), studentCount, file);

    fclose(file);
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("\nStudent limit reached!\n");
        return;
    }

    Student s;

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    if (s.marks < 0 || s.marks > 100) {
        printf("Invalid marks!\n");
        return;
    }

    s.gpa = calculateGPA(s.marks);

    students[studentCount] = s;
    studentCount++;

    saveStudents();

    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    if (studentCount == 0) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    printf("%-8s %-25s %-10s %-8s\n",
           "ID", "Name", "Marks", "GPA");

    printf("-----------------------------------------------\n");

    for (int i = 0; i < studentCount; i++) {
        printf("%-8d %-25s %-10.2f %-8.2f\n",
               students[i].id,
               students[i].name,
               students[i].marks,
               students[i].gpa);
    }
}

void searchStudent() {
    int id;
    int found = 0;

    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {

        if (students[i].id == id) {

            printf("\nStudent Found!\n");
            printf("ID    : %d\n", students[i].id);
            printf("Name  : %s\n", students[i].name);
            printf("Marks : %.2f\n", students[i].marks);
            printf("GPA   : %.2f\n", students[i].gpa);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found.\n");
}

void updateStudent() {
    int id;
    int found = 0;

    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {

        if (students[i].id == id) {

            printf("Enter new name: ");
            scanf(" %[^\n]", students[i].name);

            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);

            if (students[i].marks < 0 ||
                students[i].marks > 100) {

                printf("Invalid marks!\n");
                return;
            }

            students[i].gpa =
                calculateGPA(students[i].marks);

            saveStudents();

            printf("\nStudent updated successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found.\n");
}

void deleteStudent() {
    int id;
    int found = 0;

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {

        if (students[i].id == id) {

            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }

            studentCount--;

            saveStudents();

            printf("\nStudent deleted successfully!\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found.\n");
}

int main() {

    int choice;

    loadStudents();

    while (1) {

        printf("\n\n====================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");

        printf("------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\nThank you for using the system!\n");
                return 0;

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }

    return 0;
}
