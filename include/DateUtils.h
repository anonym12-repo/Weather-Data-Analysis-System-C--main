
#ifndef DATEUTILITIES_H
#define DATEUTILITIES_H

#include "Date.h"
#include "MyTime.h"
#include <iostream>
#include <string>

/**
 * @brief Free function comparison operators for Date class
 *
 * These operators allow Date objects to be compared without
 * modifying the original Date class, following good design principles.
 */

std::string getMonthName(int month);
// Less than operator for chronological ordering
bool operator<(const Date& lhs, const Date& rhs);

// Equality operator
bool operator==(const Date& lhs, const Date& rhs);

// Less than or equal operator
bool operator<=(const Date& lhs, const Date& rhs);

// Greater than operator
bool operator>(const Date& lhs, const Date& rhs);

// Greater than or equal operator
bool operator>=(const Date& lhs, const Date& rhs);

// Not equal operator
bool operator!=(const Date& lhs, const Date& rhs);

bool operator==(const MyTime& lhs, const MyTime& rhs);

std::ostream& operator<<(std::ostream& os, const Date& date);


#endif // DATEUTILITIES_H


