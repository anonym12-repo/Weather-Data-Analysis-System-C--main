#include "DateUtils.h"

// Convert month number to month name
std::string getMonthName(int month){
    // Array of month names (index 0 is empty string for 1-based months)
    static const std::string months[] = {"", "January", "February", "March", "April", "May", "June",
                                 "July", "August", "September", "October", "November", "December"};
    if (month >= 1 && month <= 12) {
        return months[month];  // Return month name if valid
    }
    return "Unknown";  // Return "Unknown" for invalid month numbers
}

// Implementation of comparison operators as free functions
bool operator<(const Date& lhs, const Date& rhs){
    // Year -> Month -> Day hierarchy for chronological ordering
    if (lhs.GetYear() != rhs.GetYear()){
        return lhs.GetYear() < rhs.GetYear();
    }
    if (lhs.GetMonth() != rhs.GetMonth()){
        return lhs.GetMonth() < rhs.GetMonth();
    }
    return lhs.GetDay() < rhs.GetDay();
}

bool operator==(const Date& lhs, const Date& rhs){
    return (lhs.GetDay() == rhs.GetDay()) &&
           (lhs.GetMonth() == rhs.GetMonth()) &&
           (lhs.GetYear() == rhs.GetYear());
}

bool operator<=(const Date& lhs, const Date& rhs){
    return (lhs < rhs) || (lhs == rhs);
}

bool operator>(const Date& lhs, const Date& rhs){
    return rhs < lhs;
}

bool operator>=(const Date& lhs, const Date& rhs){
    return !(lhs < rhs);
}

bool operator!=(const Date& lhs, const Date& rhs){
    return !(lhs == rhs);
}

bool operator==(const MyTime& lhs, const MyTime& rhs){
    return (lhs.GetHours() == rhs.GetHours()) &&
           (lhs.GetMins() == rhs.GetMins());
}

// Output operator implementation
std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.GetDay() << "/" << date.GetMonth() << "/" << date.GetYear();
    return os;
}


