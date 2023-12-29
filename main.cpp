#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <regex>
#include <sstream>
#include <ctime>
#include <unistd.h>
#include <iomanip>

using namespace std;

// Define data structures for tasks, appointments, and notes
struct Task {
    string title;
    string description;
    string deadline;
    int priority;
    bool completed;
    string creationDate; 
};

struct Appointment {
    string title;
    string date;
    string time;
    string notes;
};

struct Note {
    string category;
    string text;
};

// Declare vectors to store tasks, appointments, and notes
vector<Task> tasks;
vector<Appointment> appointments;
vector<Note> notes;

// Define the command to clear the console based on the operating system
// For Windows, use "cls"; for other operating systems, use "clear"
const string CLEAR_COMMAND = "clear";

// Function prototypes
void saveData();
void loadData();
void showWelcomeMessage();
void showTaskMenu();
void showAppointmentMenu();
void clearConsole();
void showNoteMenu();
void search(const string& keyword);
bool isValidDateFormat(const string& date);
bool isValidTimeFormat(const string& time);
bool compareByDeadline(const Task& task1, const Task& task2);
bool compareByCreationDate(const Task& task1, const Task& task2);
bool compareByPriority(const Task& task1, const Task& task2);
void viewDailyAppointments(const string& date);
void viewWeeklyAppointments(const string& startDate);
void viewMonthlyAppointments(const string& month, const string& year);



int main() {

    //First show a welcome message
    showWelcomeMessage();

    //load data form the data.txt file
    loadData();

    int choice;
    do {

        //clear console to keep the interface consistent
        clearConsole();
        cout << "\033[1;32m==== Personal Organizer ====\033[0m" << endl;
        cout << "1. Task Management" << endl;
        cout << "2. Appointment Scheduler" << endl;
        cout << "3. Personal Notes" << endl;
        cout << "4. Search" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        string keyword;

        switch (choice) {
            case 1:
                // clear the console and show the new menu
                clearConsole();
                showTaskMenu();
                break;
            case 2:
                // clear the console and show the new menu
                clearConsole();
                showAppointmentMenu();
                break;
            case 3:
                // clear the console and show the new menu
                clearConsole();
                showNoteMenu();
                break;
            case 4:
                cout << "Enter keyword to search: ";
                cin >> keyword;
                search(keyword);
                break;
            case 0:
                saveData();
                cout << "Exiting the program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 0);

    return 0;
}

// Function to clear the console
void clearConsole() {
    
    system(CLEAR_COMMAND.c_str());
}

// Function to display the welcome message
void showWelcomeMessage() {
    clearConsole();

    cout << "***********************************************" << endl;
    cout << "*           Welcome to Your Organizer          *" << endl;
    cout << "***********************************************" << endl;
    cout << "\033[1;32m";
    cout << "██╗   ██╗  ███████╗  ███████╗ ████████╗ ███████╗\n";
    cout << "██║   ██║  ██╔════╝  ██╔════╝    ██╔══╝ ██╔════╝\n";
    cout << "██║   ██║  ██████║   ███████║    ██║    ██║     \n";
    cout << "██║   ██║  ██║           ║██║    ██║    ██║     \n";
    cout << "████████║  ███████║  ███████║    ██║    ███████ \n";
    cout << "╚═══════╝  ╚══════╝  ╚══════╝   ╚══╝    ╚══════╝\n";
    cout << "\033[0m";
    cout << "***********************************************" << endl;
    cout << "             Organize Your Life Effortlessly    " << endl;
    cout << "***********************************************" << endl;
    cout << "               Getting Started                 " << endl;
    cout << "***********************************************" << endl;
    cout << "1. Navigate among tasks, appointments, and notes." << endl;
    cout << "2. Search for items by entering keywords." << endl;
    cout << "3. Enjoy an organized and efficient daily life!" << endl;
    cout << "4. EXIT THE PROGRAM CORRECTLY TO SAVE YOUR DATA." << endl;
    cout << "***********************************************" << endl;
    cout << "Initializing...";

    // Simulate loading with a delay
    for (int i = 0; i < 8; ++i) {
        sleep(1);
        cout << ".";
        cout.flush();
    }

    cout << endl << "Initialization complete!" << endl;
    cout << "***********************************************" << endl;
    cout << endl;
}

// Function to validate date format (dd/mm/yyyy) and check if it's a valid date
bool isValidDateFormat(const string& date) {

    //First check the date format
    const regex dateRegex("\\d{2}/\\d{2}/\\d{4}");

    if (!regex_match(date, dateRegex)) {
        cout << "Invalid date format. Use dd/mm/yyyy." << endl;
        return false;
    }

    //check if it is a valida date 
    tm tm_date = {};
    istringstream ss(date);
    ss >> get_time(&tm_date, "%d/%m/%Y");

    if (ss.fail()) {
        cout << "Invalid date. Please enter a valid date." << endl;
        return false;
    }

    return true;
}

// Function to validate time format (HH:mm) and check if it's a valid time
bool isValidTimeFormat(const string& time) {

    //First check the time format
    const regex timeRegex("\\d{2}:\\d{2}");

    if (!regex_match(time, timeRegex)) {
        cout << "Invalid time format. Use HH:mm." << endl;
        return false;
    }

    int hours = stoi(time.substr(0, 2));
    int minutes = stoi(time.substr(3, 2));

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
        cout << "Invalid time. Hours should be in the range 0-23, and minutes should be in the range 0-59." << endl;
        return false;
    }

    return true;
}

// Function to compare tasks based on deadline
bool compareByDeadline(const Task& task1, const Task& task2) {
    return task1.deadline < task2.deadline;
}

// Function to compare tasks based on creation date
bool compareByCreationDate(const Task& task1, const Task& task2) {
    return task1.creationDate < task2.creationDate;
}

// Function to compare tasks based on priority
bool compareByPriority(const Task& task1, const Task& task2) {
    return task1.priority < task2.priority;
}

// Function to view appointments for a specific date
void viewDailyAppointments(const string& date) {
    clearConsole();
    cout << "\033[1;32m==== Appointments for " << date << " ====\033[0m" << endl;

    for (size_t i = 0; i < appointments.size(); ++i) {
        const Appointment& appointment = appointments[i];
        if (appointment.date == date) {
            cout << "Index: " << i << endl; 
            cout << "Title: " << appointment.title << endl;
            cout << "Time: " << appointment.time << endl;
            cout << "Notes: " << appointment.notes << endl;
            cout << "\033[1;33m------------------------\033[0m" << endl;
        }
    }

    cout << "View complete." << endl;
    cout << "\033[1;32m - When you are ready: PRESS ENTER\033[0m" << endl;
    cin.ignore();  // Pause to allow the user to read the results
    cin.get();
}

// Function to view appointments for a specific week
void viewWeeklyAppointments(const string& startDate) {
    clearConsole();
    cout << "\033[1;32m==== Appointments for the Week Starting on " << startDate << " ====\033[0m" << endl;

    // Convert the start date to tm structure for manipulation
    tm tm_startDate = {};
    istringstream ss(startDate);
    ss >> get_time(&tm_startDate, "%d/%m/%Y");

    // Calculate the end date of the week
    tm tm_endDate = tm_startDate;
    tm_endDate.tm_mday += 7; // Add 7 days to get the end date of the week
    mktime(&tm_endDate);

    for (size_t i = 0; i < appointments.size(); ++i) {
        const Appointment& appointment = appointments[i];
        // Convert the appointment date to tm structure for comparison
        tm tm_appointmentDate = {};
        istringstream ss(appointment.date);
        ss >> get_time(&tm_appointmentDate, "%d/%m/%Y");

        // Check if the appointment date is within the week
        if (difftime(mktime(&tm_appointmentDate), mktime(&tm_startDate)) >= 0 &&
            difftime(mktime(&tm_appointmentDate), mktime(&tm_endDate)) < 0) {
            cout << "Index: " << i << endl; 
            cout << "Title: " << appointment.title << endl;
            cout << "Date: " << appointment.date << endl;
            cout << "Time: " << appointment.time << endl;
            cout << "Notes: " << appointment.notes << endl;
            cout << "\033[1;33m------------------------\033[0m" << endl;
        }
    }

    cout << "View complete." << endl;
    cout << "\033[1;32m - When you are ready: PRESS ENTER\033[0m" << endl;
    cin.ignore();
    cin.get();
}

// Function to view appointments for a specific month
void viewMonthlyAppointments(const string& month, const string& year) {
    clearConsole();
    cout << "\033[1;32m==== Appointments for " << month << " " << year << " ====\033[0m" << endl;

    int targetMonth, targetYear;
    stringstream(month) >> targetMonth;
    stringstream(year) >> targetYear;

    //check appointments among all registers
    for (size_t i = 0; i < appointments.size(); ++i) {
        const Appointment& appointment = appointments[i];
        tm tm_appointmentDate = {};
        istringstream ss(appointment.date);
        ss >> get_time(&tm_appointmentDate, "%d/%m/%Y");

        // Check if the appointment date is within the specified month and year
        if (tm_appointmentDate.tm_mon + 1 == targetMonth &&  // tm_mon is 0-indexed
            tm_appointmentDate.tm_year + 1900 == targetYear) {  // tm_year is years since 1900
            cout << "Index: " << i << endl; 
            cout << "Title: " << appointment.title << endl;
            cout << "Date: " << appointment.date << endl;
            cout << "Time: " << appointment.time << endl;
            cout << "Notes: " << appointment.notes << endl;
            cout << "\033[1;33m------------------------\033[0m" << endl;
        }
    }

    cout << "View complete." << endl;
    cout << "\033[1;32m - When you are ready: PRESS ENTER\033[0m" << endl;
    cin.ignore();
    cin.get();
}


void saveData() {
    ofstream file("data.txt");
    //we use names labels such as TASK, APPOINTMENT and NOTE to save all data
    if (file.is_open()) {
        for (const Task& task : tasks) {
            file << "TASK\n" << task.title << "\n" << task.description << "\n" << task.deadline << "\n"
                 << task.creationDate << "\n" << task.priority << "\n" << task.completed << "\n" ;
        }

        for (const Appointment& appointment : appointments) {
            file << "APPOINTMENT\n" << appointment.title << "\n" << appointment.date << "\n"
                 << appointment.time << "\n" << appointment.notes << "\n";
        }

        for (const Note& note : notes) {
            file << "NOTE\n" << note.category << "\n" << note.text << "\n";
        }

        file.close();
    } else {
        cerr << "Error: Unable to save data to file." << endl;
    }
}

void loadData() {
    ifstream file("data.txt");
    if (file.is_open()) {
        string type;
        // read the data file into a string array and save it in the vector
        while (file >> type) {
            if (type == "TASK") {
                Task task;
                file.ignore(); // Ignore the newline character
                getline(file, task.title);
                getline(file, task.description);
                getline(file, task.deadline);
                getline(file, task.creationDate);
                file >> task.priority;
                file >> task.completed;
                tasks.push_back(task);
            } else if (type == "APPOINTMENT") {
                Appointment appointment;
                file.ignore(); // Ignore the newline character
                getline(file, appointment.title);
                getline(file, appointment.date);
                getline(file, appointment.time);
                getline(file, appointment.notes);
                appointments.push_back(appointment);
            } else if (type == "NOTE") {
                Note note;
                file.ignore(); // Ignore the newline character
                getline(file, note.category);
                getline(file, note.text);
                notes.push_back(note);
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to load data from file." << endl;
    }
}

void showTaskMenu() {
    int choice;
    do {
        cout << "\033[1;32m==== Task Management ====\033[0m" << endl;
        cout << "1. Add new task" << endl;
        cout << "2. List all tasks" << endl;
        cout << "3. Delete a task" << endl;
        cout << "4. Edit a task" << endl;
        cout << "5. Mark a task as completed" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                clearConsole();
                Task newTask;
                cout << "Enter task title: ";
                cin.ignore();
                getline(cin, newTask.title);
                cout << "Enter task description: ";
                getline(cin, newTask.description);

                // Validate and get the deadline until a valid date is entered
                do {
                    cout << "Enter task deadline (dd/mm/yyyy): ";
                    cin >> newTask.deadline;
                } while (!isValidDateFormat(newTask.deadline));

                cout << "Enter task priority (1-5): ";
                cin >> newTask.priority;

                // Automatically set the creation date to the current date
                time_t now = time(0);
                tm* currentDate = localtime(&now);
                char buffer[11];
                strftime(buffer, sizeof(buffer), "%d/%m/%Y", currentDate);
                newTask.creationDate = buffer;

                newTask.completed = false;
                tasks.push_back(newTask);
                cout << "Task added successfully!" << endl;
                break;
            }
            case 2: {
                clearConsole();
                cout << "\033[1;33m==== List of Tasks ====\033[0m" << endl;

                // Sorting menu
                int sortChoice;
                cout << "Sort by:" << endl;
                cout << "1. Deadline" << endl;
                cout << "2. Creation Date" << endl;
                cout << "3. Priority" << endl;
                cout << "Enter your choice (0 to skip sorting): ";
                cin >> sortChoice;
                cout << "\033[1;33m------------------------\033[0m" << endl;

                // Sorting logic
                switch (sortChoice) {
                    case 1:
                        sort(tasks.begin(), tasks.end(), compareByDeadline);
                        break;
                    case 2:
                        sort(tasks.begin(), tasks.end(), compareByCreationDate);
                        break;
                    case 3:
                        sort(tasks.begin(), tasks.end(), compareByPriority);
                        break;
                    case 0:
                        break;
                    default:
                        cout << "Invalid choice. Skipping sorting." << endl;
                        break;
                }

                // Display sorted tasks
                for (size_t i = 0; i < tasks.size(); ++i) {
                    const Task& task = tasks[i];
                    cout << "Index: " << i << endl;
                    cout << "Title: " << task.title << endl;
                    cout << "Description: " << task.description << endl;
                    cout << "Deadline (dd/mm/yyyy): " << task.deadline << endl;
                    cout << "Priority: " << task.priority << endl;
                    cout << "Creation Date: " << task.creationDate << endl;
                    cout << "Completed: " << (task.completed ? "\033[1;32mYes\033[0m" : "\033[1;31mNo\033[0m") << endl;
                    cout << "\033[1;33m------------------------\033[0m" << endl;
                }

                break;
            }

            case 3: {
                clearConsole();
                int index;
                cout << "Enter the index of the task to delete: ";
                cin >> index;
                if (index >= 0 && index < tasks.size()) {
                    tasks.erase(tasks.begin() + index);
                    cout << "Task deleted successfully!" << endl;
                } else {
                    cout << "Invalid index. No task deleted." << endl;
                }
                break;
            }
            case 4: {
                int index;
                cout << "Enter the index of the task to edit: ";
                cin >> index;
                if (index >= 0 && index < tasks.size()) {
                    Task& task = tasks[index];
                    cout << "Enter new task title: ";
                    cin.ignore();
                    getline(cin, task.title);
                    cout << "Enter new task description: ";
                    getline(cin, task.description);

                    // Validate and get the new deadline until a valid date is entered
                    do {
                        cout << "Enter new task deadline (dd/mm/yyyy): ";
                        cin >> task.deadline;
                    } while (!isValidDateFormat(task.deadline));

                    cout << "Enter new task priority (1-5): ";
                    cin >> task.priority;
                    cout << "Task edited successfully!" << endl;
                } else {
                    cout << "Invalid index. No task edited." << endl;
                }
                break;
            }
            case 5: {
                clearConsole();
                int index;
                cout << "Enter the index of the task to mark as completed: ";
                cin >> index;
                if (index >= 0 && index < tasks.size()) {
                    tasks[index].completed = true;
                    cout << "Task marked as completed!" << endl;
                } else {
                    cout << "Invalid index. No task marked as completed." << endl;
                }
                break;
            }
            case 0:
                cout << "Returning to the main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void showAppointmentMenu() {
    int choice;
    do {
        cout << "\033[1;32m==== Appointment Scheduler ====\033[0m" << endl;
        cout << "1. Add new appointment" << endl;
        cout << "2. View upcoming appointments" << endl;
        cout << "3. View appointments for a specific date" << endl;
        cout << "4. View appointments for a specific week" << endl;   
        cout << "5. View appointments for a specific month" << endl;
        cout << "6. Edit an appointment" << endl;
        cout << "7. Delete an appointment" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                clearConsole();
                Appointment newAppointment;
                cout << "Enter appointment title: ";
                cin.ignore();
                getline(cin, newAppointment.title);
                do {
                    cout << "Enter appointment date (dd/mm/yyyy): ";
                    cin >> newAppointment.date;
                } while (!isValidDateFormat(newAppointment.date));

                do {
                    cout << "Enter appointment time (HH:mm): ";
                    cin >> newAppointment.time;
                } while (!isValidTimeFormat(newAppointment.time));

                cout << "Enter appointment notes: ";
                cin.ignore();
                getline(cin, newAppointment.notes);
                appointments.push_back(newAppointment);
                cout << "Appointment added successfully!" << endl;
                break;
            }
            case 2: {
                clearConsole();
                cout << "\033[1;33m==== Upcoming Appointments ====\033[0m" << endl;
                
                // Iterate through appointments with an index
                for (size_t i = 0; i < appointments.size(); ++i) {
                    const Appointment& appointment = appointments[i];
                    cout << "Index: " << i << endl;  
                    cout << "Title: " << appointment.title << endl;
                    cout << "Date (dd/mm/yyyy): " << appointment.date << endl;
                    cout << "Time: " << appointment.time << endl;
                    cout << "Notes: " << appointment.notes << endl;
                    cout << "\033[1;33m------------------------\033[0m" << endl;
                }
                
                // Optionally, you can print a message if there are no appointments
                if (appointments.empty()) {
                    cout << "No upcoming appointments." << endl;
                }
                
                break;
            }
            case 3: {
                clearConsole();
                string date;
                do {
                    cout << "Enter date (dd/mm/yyyy): ";
                    cin >> date;
                } while (!isValidDateFormat(date));
                viewDailyAppointments(date);
                break;
            }
            case 4: {
                clearConsole();
                string startDate;
                do {
                    cout << "Enter start date of the week (dd/mm/yyyy): ";
                    cin >> startDate;
                } while (!isValidDateFormat(startDate));
                viewWeeklyAppointments(startDate);
                break;
            }
            case 5: {
                clearConsole();
                string month, year;
                do {
                    cout << "Enter the month (mm): ";
                    cin >> month;
                    cout << "Enter the year (yyyy): ";
                    cin >> year;
                } while (!isValidDateFormat("01/" + month + "/" + year));
                viewMonthlyAppointments(month, year);
                break;
            }
            case 6: {
                int index;
                cout << "Enter the index of the appointment to edit: ";
                cin >> index;
                if (index >= 0 && index < appointments.size()) {
                    Appointment& appointment = appointments[index];
                    cout << "Enter new appointment title: ";
                    cin.ignore();
                    getline(cin, appointment.title);
                    do {
                        cout << "Enter appointment date (dd/mm/yyyy): ";
                        cin >> appointment.date;
                    } while (!isValidDateFormat(appointment.date));
                    cout << "Enter new appointment time: ";
                    cin >> appointment.time;
                    cout << "Enter new appointment notes: ";
                    cin.ignore();
                    getline(cin, appointment.notes);
                    cout << "Appointment edited successfully!" << endl;
                } else {
                    cout << "Invalid index. No appointment edited." << endl;
                }
                break;
            }
            case 7: {
                clearConsole();
                int index;
                cout << "Enter the index of the appointment to delete: ";
                cin >> index;
                if (index >= 0 && index < appointments.size()) {
                    appointments.erase(appointments.begin() + index);
                    cout << "Appointment deleted successfully!" << endl;
                } else {
                    cout << "Invalid index. No appointment deleted." << endl;
                }
                break;
            }
            case 0:
                cout << "Returning to the main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void showNoteMenu() {
    int choice;
    do {
        cout << "\033[1;32m==== Personal Notes ====\033[0m" << endl;
        cout << "1. Create a new note" << endl;
        cout << "2. List all notes" << endl;  
        cout << "3. Edit a note" << endl;
        cout << "4. Delete a note" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                clearConsole();
                Note newNote;
                cout << "Enter note category: ";
                cin.ignore();
                getline(cin, newNote.category);
                cout << "Enter note text: ";
                getline(cin, newNote.text);
                notes.push_back(newNote);
                cout << "Note created successfully!" << endl;
                break;
            }
            case 2: {
                clearConsole();
                cout << "\033[1;33m==== List of Notes ====\033[0m" << endl; 
                for (size_t i = 0; i < notes.size(); ++i) {
                    const Note& note = notes[i];
                    cout << "Index: " << i << endl;
                    cout << "Category: " << note.category << endl;
                    cout << "Text: " << note.text << endl;
                    cout << "\033[1;33m------------------------\033[0m" << endl;
                }
                break;
            }
            case 3: {
                int index;
                cout << "Enter the index of the note to edit: ";
                cin >> index;
                if (index >= 0 && index < notes.size()) {
                    Note& note = notes[index];
                    cout << "Enter new note category: ";
                    cin.ignore();
                    getline(cin, note.category);
                    cout << "Enter new note text: ";
                    getline(cin, note.text);
                    cout << "Note edited successfully!" << endl;
                } else {
                    cout << "Invalid index. No note edited." << endl;
                }
                break;
            }
            case 4: {
                clearConsole();
                int index;
                cout << "Enter the index of the note to delete: ";
                cin >> index;
                if (index >= 0 && index < notes.size()) {
                    notes.erase(notes.begin() + index);
                    cout << "Note deleted successfully!" << endl;
                } else {
                    cout << "Invalid index. No note deleted." << endl;
                }
                break;
            }
            case 0:
                cout << "Returning to the main menu." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);
}

void search(const string& keyword) {
    clearConsole();
    cout << "\033[1;32m==== Search Results ====\033[0m" << endl;

    // Search through tasks
    cout << "\033[1;33mTasks:\033[0m" << endl;
    for (const Task& task : tasks) {
        if (task.title.find(keyword) != string::npos || task.description.find(keyword) != string::npos) {
            cout << "Title: " << task.title << endl;
            cout << "Description: " << task.description << endl;
            cout << "Deadline: " << task.deadline << endl;
            cout << "Priority: " << task.priority << endl;
            cout << "Completed: " << (task.completed ? "Yes" : "No") << endl;
            cout << "\033[1;33m------------------------\033[0m" << endl;
        }
    }

    // Search through appointments
    cout << "\033[1;33mAppointments:\033[0m" << endl;
    for (const Appointment& appointment : appointments) {
        if (appointment.title.find(keyword) != string::npos || appointment.notes.find(keyword) != string::npos) {
            cout << "Title: " << appointment.title << endl;
            cout << "Date: " << appointment.date << endl;
            cout << "Time: " << appointment.time << endl;
            cout << "Notes: " << appointment.notes << endl;
            cout << "\033[1;33m------------------------\033[0m" << endl;
        }
    }

    // Search through notes
    cout << "\033[1;33mNotes:\033[0m" << endl;
    for (const Note& note : notes) {
        if (note.category.find(keyword) != string::npos || note.text.find(keyword) != string::npos) {
            cout << "Category: " << note.category << endl;
            cout << "Text: " << note.text << endl;
            cout << "\033[1;33m------------------------\033[0m" << endl;
        }
    }

    cout << "Search complete." << endl;
    cout << "\033[1;32m - When you are ready: PRESS ENTER\033[0m" << endl;
    cin.ignore();  // Pause to allow the user to read the results
    cin.get();
}

