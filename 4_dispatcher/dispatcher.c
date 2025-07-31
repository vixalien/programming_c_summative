#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void (*FunctionHandler)(const char *filename);

// Utility to read entire file into buffer
char *readFile(const char *filename) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Unable to open file\n");
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = malloc(size + 1);
  if (!buffer) {
    fclose(file);
    printf("Memory allocation failed.\n");
    return NULL;
  }

  fread(buffer, 1, size, file);
  buffer[size] = '\0';
  fclose(file);
  return buffer;
}

void addText(const char *filename) {
  printf("\n=======================================================\n");
  printf("                  Add Text to File\n");
  printf("=======================================================\n");

  FILE *file = fopen(filename, "a");
  if (!file) {
    perror("Unable to open file\n");
    return;
  }

  char *text = malloc(1024);
  if (!text) {
    printf("Memory allocation failed.\n");
    fclose(file);
    return;
  }

  printf("Enter text to add: \n");
  fflush(stdout);
  fgets(text, 1024, stdin);
  fprintf(file, "%s", text);

  free(text);
  fclose(file);
  printf("Text added successfully.\n");
}

void countLines(const char *filename) {
  printf("\n=======================================================\n");
  printf("                Count Number of Lines\n");
  printf("=======================================================\n");

  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Unable to open file\n");
    return;
  }

  int count = 0;
  char ch;
  while ((ch = fgetc(file)) != EOF)
    if (ch == '\n')
      count++;

  fclose(file);
  printf("Total lines: %d\n", count);
}

void countChars(const char *filename) {
  printf("\n=======================================================\n");
  printf("              Count Number of Characters\n");
  printf("=======================================================\n");

  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("Unable to open file\n");
    return;
  }

  int count = 0;
  char ch;
  while ((ch = fgetc(file)) != EOF)
    count++;

  fclose(file);
  printf("Total characters: %d\n", count);
}

void toUppercase(const char *filename) {
  printf("\n=======================================================\n");
  printf("             Convert File to UPPERCASE\n");
  printf("=======================================================\n");

  char *buffer = readFile(filename);
  if (!buffer)
    return;

  for (int i = 0; buffer[i]; i++)
    buffer[i] = toupper(buffer[i]);

  FILE *file = fopen(filename, "w");
  if (!file) {
    perror("Unable to open file\n");
    free(buffer);
    return;
  }

  fputs(buffer, file);
  fclose(file);
  free(buffer);
  printf("File converted to uppercase.\n");
}

void toLowercase(const char *filename) {
  printf("\n=======================================================\n");
  printf("             Convert File to lowercase\n");
  printf("=======================================================\n");

  char *buffer = readFile(filename);
  if (!buffer)
    return;

  for (int i = 0; buffer[i]; i++)
    buffer[i] = tolower(buffer[i]);

  FILE *file = fopen(filename, "w");
  if (!file) {
    perror("Unable to open file\n");
    free(buffer);
    return;
  }

  fputs(buffer, file);
  fclose(file);
  free(buffer);
  printf("File converted to lowercase.\n");
}

int main() {
  const char *filename = "data.txt";
  FunctionHandler handlers[] = {addText, countLines, countChars, toUppercase,
                                toLowercase};

  int choice;
  do {
    printf("\n=======================================================\n");
    printf("          Dynamic Function Dispatcher Menu\n");
    printf("=======================================================\n");
    printf("1. Add Text to File\n");
    printf("2. Count Lines in File\n");
    printf("3. Count Characters in File\n");
    printf("4. Convert to Uppercase\n");
    printf("5. Convert to Lowercase\n");
    printf("6. Exit\n");
    printf("Enter your choice: \n");
    fflush(stdout);
    scanf("%d", &choice);
    getchar(); // Clear buffer

    if (choice >= 1 && choice <= 5) {
      handlers[choice - 1](filename);
    } else if (choice != 6) {
      printf("Invalid choice. Try again.\n");
    }

  } while (choice != 6);

  printf("Exiting program.\n");
  return 0;
}
