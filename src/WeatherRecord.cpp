#include "WeatherRecord.h"


// Default constructor
WeatherRecord::WeatherRecord()
:date(0,0,0), t_time(0,0), speed(0.0), temperature(0.0), solarRadiation(0.0)
{}

// parameterized constructor
WeatherRecord::WeatherRecord(const Date& d, const MyTime& t, float s, float temp, float sr)
:date(d), t_time(t), speed(s), temperature(temp), solarRadiation(sr)
{}

// Get date object
const Date& WeatherRecord::GetDate() const
{
    return date;  // Return date member
}

// Get time object
const MyTime& WeatherRecord::GetTime() const
{
    return t_time;  // Return time member
}

// Get wind speed value
float WeatherRecord::GetSpeed() const{
    return speed;  // Return speed member
}

// Get temperature value
float WeatherRecord::GetTemp() const{
    return temperature;  // Return temperature member
}

// Get solar radiation value
float WeatherRecord::GetSolarRad() const{
    return solarRadiation;  // Return solar radiation member
}

