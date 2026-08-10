#include <iostream>
#include <iomanip> // Required for std::setw, std::setfill, std::left

#include "MyTime.h"

// Default constructor
MyTime::MyTime()
:hours(0), minutes(0) {}

// Parameterized constructor
MyTime::MyTime(int hr, int min)
:hours(hr), minutes(min)
{}

int MyTime::GetHours() const{
    return hours;
}

int MyTime::GetMins() const{
    return minutes;
}

bool MyTime::SetHours(int hr){
    if(hr >= 0 && hr <= 23){  // Fixed: use parameter 'hr', not 'hour'
        hours = hr;
        return true;
    }else{
        return false;
    }
}

bool MyTime::SetMins(int min){
    if(min >= 0 && min <= 59){  // Fixed: use parameter 'min', not 'minus'
        minutes = min;
        return true;
    }else{
        return false;
    }
}


