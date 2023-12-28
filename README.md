# Personal-Organizer

```markdown
# Personal Organizer

Personal Organizer is a simple command-line application to help you manage tasks, appointments, and personal notes, providing an organized approach to your daily life.

## Features

- **Task Management:** Add, view, mark as completed, and edit tasks with deadlines and priorities.
- **Appointment Scheduler:** Schedule and view appointments with date, time, and notes.
- **Personal Notes:** Organize your thoughts and ideas with categorized notes.
- **Search:** Quickly find items by entering keywords.

## Getting Started

1. **Clone the repository:**

   ```bash
   git clone <repository-url>
   ```

2. **Build the program:**

   - **Linux:**
     ```bash
     cd PersonalOrganizer
     make
     ```

   - **macOS:**
     ```bash
     cd PersonalOrganizer
     clang++ -std=c++11 -o personal_organizer main.cpp
     ```

3. **Run the program:**

   ```bash
   ./personal_organizer
   ```

4. **Follow the on-screen instructions to navigate and use the application.**

## Usage

- **Main Menu:**

  Navigate among tasks, appointments, notes, and perform searches.

- **Task Management:**

  - **Add a Task:**
    Enter title, description, deadline, and priority.

  - **View Tasks:**
    View all tasks or filter by completion status.

  - **Mark Task as Completed:**
    Mark a task as completed.

  - **Edit Task:**
    Modify the details of an existing task.

  - **Sort Tasks:**
    Sort tasks by deadline, creation date, or priority.

- **Appointment Scheduler:**

  - **Schedule Appointments:**
    Enter title, date, time, and notes for appointments.

  - **View Appointments:**
    - **Upcoming Appointments:**
      View all upcoming appointments.
    - **Daily Appointments:**
      View appointments for a specific date.
    - **Weekly Appointments:**
      View appointments for a specific week.
    - **Monthly Appointments:**
      View appointments for a specific month.

- **Personal Notes:**

  - **Add Notes:**
    Categorize and store personal notes.

- **Search:**

  Enter keywords to search for tasks, appointments, and notes.

- **Exit:**

  Exit the program correctly to save your data.

## Dependencies

- C++11 or later
- [CMake](https://cmake.org/) (for building)

## Building on Linux and macOS

- **Linux:**
  - Ensure you have a C++ compiler installed (e.g., `g++`).
  - Navigate to the project directory: `cd PersonalOrganizer`.
  - Build the program: `make`.

- **macOS:**
  - Ensure you have Xcode Command Line Tools installed.
  - Navigate to the project directory: `cd PersonalOrganizer`.
  - Build the program: `clang++ -std=c++11 -o personal_organizer main.cpp`.

## Contributing

Contributions are welcome! Feel free to open issues and pull requests.


```
