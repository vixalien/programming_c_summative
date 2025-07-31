# Summative C Projects

This repository contains several C programming projects, each located in its own subdirectory. Each project demonstrates different aspects of C programming, including shell implementation, file management, function dispatching, and web scraping.

## Directory Structure

- `2_menu_shell/` — Mini shell implementation (`minishell`)
- `3_student_management_system/` — Student management system (`student_management`)
- `4_dispatcher/` — Dynamic function dispatcher for file operations (`dispatcher`)
- `5_scraper/` — Multithreaded web scraper using libcurl and pthreads (`scraper`)

## Building All Projects

A single `Makefile` is provided in the `summative/` directory to build all projects at once.

### Prerequisites

- GCC (or compatible C compiler)
- `make`
- For the scraper: `libcurl` and `pthread` development libraries (e.g., `libcurl4-openssl-dev` on Debian/Ubuntu)

### Build Everything

From the `summative/` directory, run:

```sh
make
```

This will build all four projects and place the binaries in their respective subdirectories.

### Clean All Binaries

To remove all compiled binaries:

```sh
make clean
```

## Building Individual Projects

You can also build each project separately:

- Mini Shell:
  ```sh
  make menu_shell
  ```
- Student Management System:
  ```sh
  make student_management
  ```
- Dispatcher:
  ```sh
  make dispatcher
  ```
- Scraper:
  ```sh
  make scraper
  ```

## Running the Programs

Navigate to the corresponding subdirectory and run the binary:

### 1. Mini Shell

```sh
cd 2_menu_shell
./minishell
```

A simple shell supporting basic commands, pipes, redirection, and background execution.

### 2. Student Management System

```sh
cd 3_student_management_system
./student_management
```

Menu-driven system to add, view, search, update, and delete student records (stored in `students.dat`).

### 3. Dispatcher

```sh
cd 4_dispatcher
./dispatcher
```

Menu-driven utility to perform various operations on `data.txt` (add text, count lines/chars, change case, etc.).

### 4. Scraper

```sh
cd 5_scraper
./scraper
```

Multithreaded web scraper that fetches five predefined URLs and saves their HTML content as `output_1.html`, `output_2.html`, etc.

## Notes

- The scraper requires internet access and the `libcurl` and `pthread` libraries.
- The student management system stores data in a binary file (`students.dat`) in its directory.
- All programs are written in standard C and should compile on any Unix-like system with the required libraries.

## License

This repository is for educational purposes.

---
