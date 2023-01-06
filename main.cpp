#include <iostream>
#include <string>
#include <vector>
#include <map>

// Data structures for storing information about students, lessons, and schedules

class Student {
public:
  std::string name;
  std::string email;
  std::string phone;
  std::string notes;
};

class Lesson {
public:
  std::string subject;
  int duration; // in minutes
  std::string location;
};

class Schedule {
public:
  std::map<std::string, std::vector<Lesson>> schedule;
};

// Functions for creating, modifying, and deleting entries in the data structures

void createStudent(std::vector<Student>& students) {
  std::cout << "Enter the name of the student: ";
  std::string name;
  std::cin >> name;

  std::cout << "Enter the email of the student: ";
  std::string email;
  std::cin >> email;

  std::cout << "Enter the phone number of the student: ";
  std::string phone;
  std::cin >> phone;

  std::cout << "Enter any notes about the student: ";
  std::string notes;
  std::cin.ignore();
  std::getline(std::cin, notes);

  students.emplace_back(Student{name, email, phone, notes});
  std::cout << "Student added successfully!" << std::endl;
}

void modifyStudent(std::vector<Student>& students) {
  std::cout << "Enter the name of the student to modify: ";
  std::string name;
  std::cin >> name;

  for (auto& student : students) {
    if (student.name == name) {
      std::cout << "Enter the new email of the student: ";
      std::cin >> student.email;

      std::cout << "Enter the new phone number of the student: ";
      std::cin >> student.phone;

      std::cout << "Enter any new notes about the student: ";
      std::cin.ignore();
      std::getline(std::cin, student.notes);

      std::cout << "Student modified successfully!" << std::endl;
      return;
    }
  }

  std::cout << "Error: student not found." << std::endl;
}

void deleteStudent(std::vector<Student>& students) {
  std::cout << "Enter the name of the student to delete: ";
  std::string name;
  std::cin >> name;

  for (int i = 0; i < students.size(); i++) {
    if (students[i].name == name) {
      students.erase(students.begin() + i);
      std::cout << "Student deleted successfully!" << std::endl;
      return;
    }
  }

  std::cout << "Error: student not found." << std::endl;
}

void createLesson(Schedule& schedule) {
  std::cout << "Enter the date of the lesson (DD/MM/YYYY): ";
  std::string date;
  std::cin >> date;

  std::cout << "Enter the subject of the lesson: ";
  std::string subject;
  std::cin >> subject;

  std::cout << "Enter the duration of the lesson (in minutes): ";
  int duration;
  std::cin >> duration;

  std::cout << "Enter the location of the lesson: ";
  std::string location;
  std::cin >> location;

  schedule.schedule[date].emplace_back(Lesson{subject, duration, location});
  std::cout << "Lesson added successfully!" << std::endl;
}

void modifyLesson(Schedule& schedule) {
  std::cout << "Enter the date of the lesson to modify (DD/MM/YYYY): ";
  std::string date;
  std::cin >> date;

  std::cout << "Enter the subject of the lesson to modify: ";
  std::string subject;
  std::cin >> subject;

  for (auto& dateLessons : schedule.schedule) {
    if (dateLessons.first != date) continue;
    for (auto& lesson : dateLessons.second) {
      if (lesson.subject == subject) {
        std::cout << "Enter the new duration of the lesson (in minutes): ";
        std::cin >> lesson.duration;

        std::cout << "Enter the new location of the lesson: ";
        std::cin >> lesson.location;

        std::cout << "Lesson modified successfully!" << std::endl;
        return;
      }
    }
  }

  std::cout << "Error: lesson not found." << std::endl;
}

void deleteLesson(Schedule& schedule) {
  std::cout << "Enter the date of the lesson to delete (DD/MM/YYYY): ";
  std::string date;
  std::cin >> date;

  std::cout << "Enter the subject of the lesson to delete: ";
  std::string subject;
  std::cin >> subject;

  for (auto& dateLessons : schedule.schedule) {
    if (dateLessons.first != date) continue;
    for (int i = 0; i < dateLessons.second.size(); i++) {
      if (dateLessons.second[i].subject == subject) {
        dateLessons.second.erase(dateLessons.second.begin() + i);
        std::cout << "Lesson deleted successfully!" << std::endl;
        return;
      }
    }
  }

  std::cout << "Error: lesson not found." << std::endl;
}

// User interface

int main() {
  std::vector<Student> students;
  Schedule schedule;

  while (true) {
    std::cout << "1. View students" << std::endl;
    std::cout << "2. Add student" << std::endl;
    std::cout << "3. Modify student" << std::endl;
    std::cout << "4. Delete student" << std::endl;
    std::cout << "5. View schedule" << std::endl;
    std::cout << "6. Add lesson" << std::endl;
    std::cout << "7. Modify lesson" << std::endl;
    std::cout << "8. Delete lesson" << std::endl;
    std::cout << "9. Quit" << std::endl;

    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;

    if (choice == 1) {
      for (const auto& student : students) {
        std::cout << student.name << std::endl;
      }
    } else if (choice == 2) {
      createStudent(students);
    } else if (choice == 3) {
      modifyStudent(students);
    } else if (choice == 4) {
      deleteStudent(students);
    } else if (choice == 5) {
      std::cout << "Enter the date of the schedule to view (DD/MM/YYYY): ";
      std::string date;
      std::cin >> date;
      if (schedule.schedule.count(date) == 0) {
        std::cout << "Error: no lessons scheduled for this date." << std::endl;
      } else {
        for (const auto& lesson : schedule.schedule[date]) {
          std::cout << lesson.subject << " " << lesson.duration << " " << lesson.location << std::endl;
        }
      }
    } else if (choice == 6) {
      createLesson(schedule);
    } else if (choice == 7) {
      modifyLesson(schedule);
    } else if (choice == 8) {
      deleteLesson(schedule);
    } else if (choice == 9) {
      break;
    } else {
      std::cout << "Invalid choice." << std::endl;
    }
  }

  return 0;
}

