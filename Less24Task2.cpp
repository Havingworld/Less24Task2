#include <iostream>
#include <map>
#include <ctime>
#include <iomanip>
#include <string>
#include <vector>
#pragma warning(disable : 4996)

struct BirthDate {
    int year;
    int month;
    int day;
};

int getDaysUntilBirthday(struct BirthDate birthday) {
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    int currentYear = localTime->tm_year;
    int currentMonth = localTime->tm_mon + 1;
    int currentDay = localTime->tm_mday;

    int targetYear = currentYear;
    int targetMonth = birthday.month;
    int targetDay = birthday.day;

    if (targetMonth < currentMonth || (targetMonth == currentMonth && targetDay < currentDay)) {
        targetYear++;
    }

    std::tm target{};
    target.tm_year = { targetYear};
    target.tm_mon = { targetMonth - 1 };
    target.tm_mday = { targetDay };
    target.tm_hour = { 0 };
    target.tm_min = { 0 };
    target.tm_sec = { 0 };

    std::time_t targetTime = std::mktime(&target);
    return ((targetTime - now) / (static_cast<long long>(24) * 3600));
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

    //находим ближайшие дени рождения
    std::map<int, std::vector<std::string>> nearestBirthdays;
    for (auto& it : birthdays) {
        int daysUntil = getDaysUntilBirthday(it.second); 
        if (daysUntil >= 0) {
            nearestBirthdays[daysUntil].push_back(it.first);
        }
    }
  
    if(nearestBirthdays.empty()) {
        std::cout << "No birthdays today." << std::endl;
    }
    else if (nearestBirthdays.begin()->first == 0) {
        auto it_nearBirt = nearestBirthdays.begin();
        for (auto cNames : it_nearBirt->second) {
            std::cout << "Happy birthday, " << cNames << "!" << std::endl;
        }
    }
    else {
        auto it_nearBirt = nearestBirthdays.begin();
        for (auto cNames : it_nearBirt->second) {
            auto itf = birthdays.find(cNames)->second;
            std::cout << cNames << "'s birthday is in " << it_nearBirt->first
                << " days (" << itf.month << "/" << itf.day << ")" << std::endl;
        }
    }

    return 0;
}
