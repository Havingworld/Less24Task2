#include <iostream>
#include <map>
#include <ctime>
#include <iomanip>
#include <string>
#pragma warning(disable : 4996)

struct BirthDate {
    int year;
    int month;
    int day;
};

int getDaysUntilBirthday(struct BirthDate birthday) {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    int currentYear = localTime->tm_year + 1900;
    int currentMonth = localTime->tm_mon + 1;
    int currentDay = localTime->tm_mday;

    int targetYear = birthday.year;
    int targetMonth = birthday.month;
    int targetDay = birthday.day;

    if (targetMonth < currentMonth || (targetMonth == currentMonth && targetDay < currentDay)) {
        targetYear++;
    }

    std::tm target{};
    target.tm_year = { targetYear - 1900 };
    target.tm_mon = { targetMonth - 1 };
    target.tm_mday = { targetDay };
    target.tm_hour = { 0 };
    target.tm_min = { 0 };
    target.tm_sec = { 0 };

    std::time_t targetTime = std::mktime(&target);
    return ((targetTime - now) / (24 * 3600));
}

int main() {
    std::map<std::string, BirthDate> birthdays;
    std::string name{""};
    
    while (name != "end") {
        std::cout << "Enter friend's name or 'end' to stop: ";
        std::cin >> name;
        if (name == "end")  break;

        BirthDate birthday;
        std::cout << "Enter birthday (YYYY MM DD): ";
        std::cin >> birthday.year >> birthday.month >> birthday.day;
        birthdays[name] = birthday;
    }

    //std::time_t now = std::time(nullptr);
    //std::tm* localTime = std::localtime(&now);
    //int currentMonth = localTime->tm_mon + 1;
    //int currentDay = localTime->tm_mday;
    
    //находим ближайшие дени рождения
    std::map<int, std::string> nearestBirthdays;
    for (auto& it : birthdays) {
        int daysUntil = getDaysUntilBirthday(it.second); 
        if (daysUntil >= 0) {
            nearestBirthdays[daysUntil] = it.first;
        }
    }

    bool hasBirthdayToday = false;
    for (auto& it : nearestBirthdays) {
        if (it.first == 0) {
            std::cout << "Happy birthday, " << it.second << "!" << std::endl;
            hasBirthdayToday = true;
        }
        else {
            auto itf = birthdays.find(it.second)->second;
            std::cout << it.second << "'s birthday is in " << it.first 
                << " days (" << std::setw(2) << std::setfill('0') 
                << itf.month << "/" << std::setw(2) << std::setfill('0') << itf.day << ")" << std::endl;
        }
    }

    if (!hasBirthdayToday) {
        std::cout << "No birthdays today." << std::endl;
    }

    return 0;
}
