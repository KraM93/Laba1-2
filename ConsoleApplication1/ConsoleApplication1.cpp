#include <iostream>
#include <string>

class DateTime {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:
    // Первый конструктор
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0) {
        this->year = year;
        this->month = month;
        this->day = day;
        this->hour = hour;
        this->minute = minute;
        this->second = second;
    }

    // Второй конструктор
    DateTime(const std::string& isoFormat) {
        std::string yearStr = isoFormat.substr(0, 4);
        std::string monthStr = isoFormat.substr(4, 2);
        std::string dayStr = isoFormat.substr(6, 2);
        std::string hourStr = isoFormat.substr(9, 2);
        std::string minuteStr = isoFormat.substr(11, 2);
        std::string secondStr = isoFormat.substr(13, 2);

        this->year = std::stoi(yearStr);
        this->month = std::stoi(monthStr);
        this->day = std::stoi(dayStr);
        this->hour = std::stoi(hourStr);
        this->minute = std::stoi(minuteStr);
        this->second = std::stoi(secondStr);
    }

    // Методы для доступа к значениям даты и времени

    int getYear() const {
        return year;
    }

    int getMonth() const {
        return month;
    }

    int getDay() const {
        return day;
    }

    int getHour() const {
        return hour;
    }

    int getMinute() const {
        return minute;
    }

    int getSecond() const {
        return second;
    }

    // Методы форматирования даты и времени

    std::string formatDate() const {
        return std::to_string(year) + padZero(month) + padZero(day);
    }

    std::string formatTime() const {
        return padZero(hour) + padZero(minute) + padZero(second);
    }

    std::string formatDateTime() const {
        return formatDate() + "T" + formatTime();
    }

    // Перегрузка операторов сравнения

    bool operator>(const DateTime& other) const {
        if (year > other.year)
            return true;
        else if (year < other.year)
            return false;

        if (month > other.month)
            return true;
        else if (month < other.month)
            return false;

        if (day > other.day)
            return true;
        else if (day < other.day)
            return false;

        if (hour > other.hour)
            return true;
        else if (hour < other.hour)
            return false;

        if (minute > other.minute)
            return true;
        else if (minute < other.minute)
            return false;

        return second > other.second;
    }

    bool operator<(const DateTime& other) const {
        return other > *this;
    }

    bool operator==(const DateTime& other) const {
        return year == other.year && month == other.month && day == other.day &&
            hour == other.hour && minute == other.minute && second == other.second;
    }

    // Перегрузка операторов сложения и вычитания

    DateTime operator+(int seconds) const {
        DateTime result(*this);
        result.addSeconds(seconds);
        return result;
    }

    DateTime operator-(int seconds) const {
        return *this + (-seconds);
    }

private:
    // Вспомогательная функция для добавления ведущего нуля
    std::string padZero(int number) const {
        if (number < 10)
            return "0" + std::to_string(number);
        else
            return std::to_string(number);
    }

    // Вспомогательная функция для добавления секунд
    void addSeconds(int seconds) {
        int totalSeconds = hour * 3600 + minute * 60 + second;
        totalSeconds += seconds;

        hour = totalSeconds / 3600;
        minute = (totalSeconds % 3600) / 60;
        second = totalSeconds % 60;
    }
};

int main() {
    setlocale(LC_ALL, "RUS");
    DateTime dt1(2023, 6, 10, 12, 30, 0);
    DateTime dt2("20230610T123000");

    std::cout << "Год: " << dt1.getYear() << std::endl;
    std::cout << "Месяц: " << dt1.getMonth() << std::endl;
    std::cout << "День: " << dt1.getDay() << std::endl;
    std::cout << "Часов: " << dt1.getHour() << std::endl;
    std::cout << "Минут: " << dt1.getMinute() << std::endl;
    std::cout << "Секунд: " << dt1.getSecond() << std::endl;

    std::cout << "Дата: " << dt1.formatDate() << std::endl;
    std::cout << "Время: " << dt1.formatTime() << std::endl;
    std::cout << "Дата и время: " << dt1.formatDateTime() << std::endl;

    std::cout << "dt1 > dt2: " << (dt1 > dt2) << std::endl;
    std::cout << "dt1 < dt2: " << (dt1 < dt2) << std::endl;
    std::cout << "dt1 == dt2: " << (dt1 == dt2) << std::endl;

    DateTime dt3 = dt1 + 3600;  // Добавил 1 час (3600 секунд)
    std::cout << "dt1 + 1 час: " << dt3.formatDateTime() << std::endl;

    DateTime dt4 = dt1 - 1800;  // Вычел 30 минут (1800 секунд)
    std::cout << "dt1 - 30 минут: " << dt4.formatDateTime() << std::endl;

    return 0;
}
