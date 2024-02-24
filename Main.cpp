#include <iostream>
#include <ostream>
#include <vector>
#include <string>
#include <limits>
#include <fstream>

// This variable is needed for the creation of a new task
std::string newTask;

// Home dir and path to the file
const char* homeDir = getenv("HOME");
std::string filePath = std::string(homeDir) + "/.config/tasks.txt";

void createNewTask() {

	// Get the name of the task
	std::cout << "Task name: ";

	std::cin.ignore();
	std::getline(std::cin, newTask);


	// Get the current number of lines in the file
	std::ifstream tasksFileReadonly(filePath);
	if (!tasksFileReadonly.is_open()) {

        std::cerr << "Error opening the file: " << filePath << std::endl;
        return; // Return an error code
    }

	int lineCount = 0;
	std::string line;

	while (std::getline(tasksFileReadonly, line)) {
		
		lineCount++;
	}

	tasksFileReadonly.close();

	
	// Open the file for writing
	std::ofstream tasksFile(filePath, std::ios::app);


	// Write to the file
	if (tasksFile.is_open()) {

		tasksFile << lineCount << ". " << newTask << "\n";
		tasksFile.close();
	} else {

		std::cout << "Error opening the file: " << filePath << std::endl;
		return; // Return an error code
	}
}

// THE REMOVE TASK FUNCTION IS IN PROGRESS NOW
void removeTask() {
    int orderToRemove;
    std::cout << "Task order number (list tasks to see the number): ";
    std::cin >> orderToRemove;

    std::ifstream tasksFileReadonly(filePath);
    if (!tasksFileReadonly.is_open()) {
        std::cerr << "Error opening the file: " << filePath << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;

    // Read all lines from the file into the lines vector
    while (std::getline(tasksFileReadonly, line)) {
        lines.push_back(line);
    }

    tasksFileReadonly.close();

	// Check if the specified order is valid
    if (orderToRemove > 0 && orderToRemove <= lines.size()) {
        // Remove the task with the specified order from the lines vector
        lines.erase(lines.begin() + orderToRemove);

        // Update the order for the remaining tasks in the lines vector
        for (int i = orderToRemove; i < lines.size(); ++i) {
            // Extract the order from each line and update it
            size_t pos = lines[i].find(".");
            if (pos != std::string::npos) {
                lines[i].replace(0, pos, std::to_string(i));
            }
        }

		//for (int i = orderToRemove; i < lines.size(); ++i)

        // Open the file for writing
        std::ofstream tasksFile(filePath);

        // Write the updated lines back to the file
        for (const auto& updatedLine : lines) {
            tasksFile << updatedLine << "\n";
        }

        tasksFile.close();

        std::cout << "Task was successfully removed.";
    } else {
        std::cout << "Please enter a valid task number!\n";
    }
}


void listAllTasks() {

	// Open the file for reading
	std::ifstream tasksFileReadonly(filePath);


	// Check if it was opened correctly
	if (!tasksFileReadonly.is_open()) {
	
		std::cerr << "Error opening the file: " << filePath << std::endl;
		return;
	}


	// List the contents of the file
	std::string line;

	while (std::getline(tasksFileReadonly, line)) {
	
		std::cout << line << "\n";
	}


	// Finally close the file
	tasksFileReadonly.close();
}

int main() {

	// The start of the program
	#ifdef _WIN32
	system("cls");
	#else
	system("clear");
	#endif
	std::string version = "v1.0.1";
	std::string name = "STBTL - SIMPLE TERMINAL-BASED TODO LIST";
	std::cout << "+==========================================|  " << name << "  " << version << " |==========================================+";


	// The loop of the program
	while (true) {

		// Firstly, let's list the actions you can do with this program
		std::cout << "\nThe Actions You can do:\n";
		std::cout << "1. New Task\n";
		std::cout << "2. Mark Task As Done (This simply removes the task entirely)\n";
		std::cout << "3. List All Tasks\n";
		std::cout << "4. Quit\n\n";
		
		
		// Let's find out what did the user choose to do
		char choice;
		
		std::cout << "$ ";
		std::cin >> choice;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Please enter a number between 1 to 4!";
			continue;
		}
		

		// The functions created before will now run based on the choice
		switch (choice) {
			
			case '1': 
				createNewTask();
				break;
			case '2': 
				// In progress
				removeTask();
				break;
			case '3': 
				listAllTasks();
				break;
			case '4': 
				// This just closes the program
				return 0;
			default:
				// If the user types a wrong number
				std::cout << "Please enter a number between 1 to 4!";
				break;
		}
	}
}
