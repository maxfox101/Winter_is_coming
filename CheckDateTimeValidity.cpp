#include <array>
#include <stdexcept>
#include <string>

using namespace std;

struct DateTime {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
};

class DateTimeValidator {
private:
    static constexpr int MIN_YEAR = 1;
    static constexpr int MAX_YEAR = 9999;
    static constexpr int MIN_MONTH = 1;
    static constexpr int MAX_MONTH = 12;
    static constexpr int MIN_HOUR = 0;
    static constexpr int MAX_HOUR = 23;
    static constexpr int MIN_MINUTE = 0;
    static constexpr int MAX_MINUTE = 59;
    static constexpr int MIN_SECOND = 0;
    static constexpr int MAX_SECOND = 59;
    
    static bool isLeapYear(int year) {
        return (year % 4 == 0) && !(year % 100 == 0 && year % 400 != 0);
    }
    
    static int getDaysInMonth(int month, int year) {
        const array<int, 12> month_lengths = {
            31, 28 + isLeapYear(year), 31, 30, 31, 30, 
            31, 31, 30, 31, 30, 31
        };
        return month_lengths[month - 1];
    }
    
    static void validateRange(int value, int min, int max, const string& field_name) {
        if (value < min) {
            throw domain_error(field_name + " is too small"s);
        }
        if (value > max) {
            throw domain_error(field_name + " is too big"s);
        }
    }

public:
    static void Validate(const DateTime& dt) {
        validateRange(dt.year, MIN_YEAR, MAX_YEAR, "year"s);
        validateRange(dt.month, MIN_MONTH, MAX_MONTH, "month"s);
        validateRange(dt.hour, MIN_HOUR, MAX_HOUR, "hour"s);
        validateRange(dt.minute, MIN_MINUTE, MAX_MINUTE, "minute"s);
        validateRange(dt.second, MIN_SECOND, MAX_SECOND, "second"s);
        
        // Проверка дня с учетом количества дней в месяце
        validateRange(dt.day, 1, getDaysInMonth(dt.month, dt.year), "day"s);
    }
};

void CheckDateTimeValidity(const DateTime& dt) {
    DateTimeValidator::Validate(dt);
} 
