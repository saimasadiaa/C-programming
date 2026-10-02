#include <stdio.h>

int main() {
    float marks;
    char grade;

    printf("===== Student Grade Calculator =====\n");

    printf("Enter your marks (0-100): ");
    scanf("%f", &marks);

    if (marks < 0 || marks > 100) {
        printf("Invalid marks! Please enter a value between 0 and 100.\n");
    }
    else if (marks >= 80) {
        grade = 'A';
    }
    else if (marks >= 70) {
        grade = 'B';
    }
    else if (marks >= 60) {
        grade = 'C';
    }
    else if (marks >= 50) {
        grade = 'D';
    }
    else {
        grade = 'F';
    }

    if (marks >= 0 && marks <= 100) {
        printf("Marks: %.2f\n", marks);
        printf("Grade: %c\n", grade);
    }

    return 0;
}
