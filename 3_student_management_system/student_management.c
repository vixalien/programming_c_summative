#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"

typedef struct {
  int id;
  char name[50];
  int age;
  char course[50];
  float grade;
} Student;

void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void menu();

int main() {
  menu();
  return 0;
}

void menu() {
  int choice;
  do {
    printf("\n=== Student Management System ===\n");
    printf("1. Add Student\n");
    printf("2. View All Students\n");
    printf("3. Search Student\n");
    printf("4. Update Student\n");
    printf("5. Delete Student\n");
    printf("6. Exit\n");
    printf("Enter your choice: \n");
    fflush(stdout);
    scanf("%d", &choice);
    getchar(); // Clear newline from buffer

    switch (choice) {
    case 1:
      addStudent();
      break;
    case 2:
      viewStudents();
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
      printf("Exiting...\n");
      break;
    default:
      printf("Invalid choice. Try again.\n");
    }
  } while (choice != 6);
}

void addStudent() {
  printf("\n=======================================================\n");
  printf("                  Adding a Student\n");
  printf("=======================================================\n");

  FILE *file = fopen(FILENAME, "ab");
  if (!file) {
    perror("Unable to open file\n");
    return;
  }

  Student s;
  printf("Enter student ID: \n");
  fflush(stdout);
  scanf("%d", &s.id);
  getchar();
  printf("Enter student name: \n");
  fflush(stdout);
  fgets(s.name, sizeof(s.name), stdin);
  s.name[strcspn(s.name, "\n")] = 0;
  printf("Enter age: \n");
  fflush(stdout);
  scanf("%d", &s.age);
  getchar();
  printf("Enter course: \n");
  fflush(stdout);
  fgets(s.course, sizeof(s.course), stdin);
  s.course[strcspn(s.course, "\n")] = 0;
  printf("Enter grade: \n");
  fflush(stdout);
  scanf("%f", &s.grade);

  fwrite(&s, sizeof(Student), 1, file);
  fclose(file);
  printf("Student added successfully.\n");
}

void viewStudents() {
  printf("\n=======================================================\n");
  printf("                Viewing All Students\n");
  printf("=======================================================\n");

  FILE *file = fopen(FILENAME, "rb");
  if (!file) {
    perror("Unable to open file\n");
    return;
  }

  Student s;
  printf("\n%-5s %-20s %-5s %-20s %-6s\n", "ID", "Name", "Age", "Course",
         "Grade");
  printf("-------------------------------------------------------------\n");
  while (fread(&s, sizeof(Student), 1, file)) {
    printf("%-5d %-20s %-5d %-20s %-6.2f\n", s.id, s.name, s.age, s.course,
           s.grade);
  }
  fclose(file);
}

void searchStudent() {
  printf("\n=======================================================\n");
  printf("                 Searching a Student\n");
  printf("=======================================================\n");

  FILE *file = fopen(FILENAME, "rb");
  if (!file) {
    perror("Unable to open file\n");
    return;
  }

  int id, found = 0;
  printf("Enter student ID to search: \n");
  fflush(stdout);
  scanf("%d", &id);

  Student s;
  while (fread(&s, sizeof(Student), 1, file)) {
    if (s.id == id) {
      printf("\nStudent found:\n");
      printf("ID: %d\nName: %s\nAge: %d\nCourse: %s\nGrade: %.2f\n", s.id,
             s.name, s.age, s.course, s.grade);
      found = 1;
      break;
    }
  }
  if (!found)
    printf("Student not found.\n");

  fclose(file);
}

void updateStudent() {
  printf("\n=======================================================\n");
  printf("                 Updating a Student\n");
  printf("=======================================================\n");

  FILE *file = fopen(FILENAME, "rb+");
  if (!file) {
    perror("Unable to open file\n");
    return;
  }

  int id, found = 0;
  printf("Enter student ID to update: \n");
  fflush(stdout);
  scanf("%d", &id);
  Student s;

  while (fread(&s, sizeof(Student), 1, file)) {
    if (s.id == id) {
      fseek(file, -sizeof(Student), SEEK_CUR); // Move pointer back

      printf("Enter new name: \n");
      fflush(stdout);
      getchar();
      fgets(s.name, sizeof(s.name), stdin);
      s.name[strcspn(s.name, "\n")] = 0;
      printf("Enter new age: \n");
      fflush(stdout);
      scanf("%d", &s.age);
      getchar();
      printf("Enter new course: \n");
      fflush(stdout);
      fgets(s.course, sizeof(s.course), stdin);
      s.course[strcspn(s.course, "\n")] = 0;
      printf("Enter new grade: \n");
      fflush(stdout);
      scanf("%f", &s.grade);

      fwrite(&s, sizeof(Student), 1, file);
      printf("Student record updated successfully.\n");
      found = 1;
      break;
    }
  }

  if (!found)
    printf("Student not found.\n");

  fclose(file);
}

void deleteStudent() {
  printf("\n=======================================================\n");
  printf("                 Deleting a Student\n");
  printf("=======================================================\n");

  FILE *file = fopen(FILENAME, "rb");
  FILE *temp = fopen("temp.dat", "wb");
  if (!file || !temp) {
    perror("Unable to open file\n");
    return;
  }

  int id, found = 0;
  printf("Enter student ID to delete: \n");
  fflush(stdout);
  scanf("%d", &id);

  Student s;
  while (fread(&s, sizeof(Student), 1, file)) {
    if (s.id == id) {
      found = 1;
      continue; // Skip writing this student
    }
    fwrite(&s, sizeof(Student), 1, temp);
  }

  fclose(file);
  fclose(temp);
  remove(FILENAME);
  rename("temp.dat", FILENAME);

  if (found)
    printf("Student deleted successfully.\n");
  else
    printf("Student not found.\n");
}
