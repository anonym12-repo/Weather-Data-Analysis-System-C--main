// MonthYearKey.cpp
#include "MonthYearKey.h"

MonthYearKey::MonthYearKey(int y, int m)
:year(y), month(m) {}

bool operator<(const MonthYearKey& lhs, const MonthYearKey& rhs) {
    return (lhs.year < rhs.year) ||
           (lhs.year == rhs.year && lhs.month < rhs.month);
}

bool operator==(const MonthYearKey& lhs, const MonthYearKey& rhs) {
    return lhs.year == rhs.year && lhs.month == rhs.month;
}
