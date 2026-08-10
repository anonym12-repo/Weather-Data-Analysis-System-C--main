#include "Date.h"

// Default constructor -initialize all fields to 0
Date::Date()
:day(1),month(1),year(0000)
{}

// Parameterized constructor - initialize with specific values
Date::Date(int d, int m, int y)
:day(d), month(m), year(y)  // Member initializer list for direct initialization
{}

// Set day with validation (1-31 range)
void  Date::SetDay(int d){
    if(d>=1 && d<=31){  // Validate day is within reasonable calendar range
        day=d;
    } // Only set if valid
}

// Set month with validation (1-12 range)
void  Date::SetMonth(int m){
    if(m>=1 && m<=12){  // Validate month is within calendar range
        month=m;       // Only set if valid
    }
}

// Set year (no validation for basic implementation)
void  Date::SetYear(int y){
    year=y;  // Set year directly
}

// Get day value
int Date::GetDay() const{
    return day;  // Return current day value
}

// Get month value
int Date::GetMonth() const{
    return month;  // Return current month value
}

// Get year value
int Date::GetYear() const{
    return year;  // Return current year value
}

