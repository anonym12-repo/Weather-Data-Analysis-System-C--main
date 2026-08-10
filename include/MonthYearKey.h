// MonthYearKey.h
#ifndef MONTHYEARKEY_H
#define MONTHYEARKEY_H

/**
 * @class MonthYearKey
 * @brief Represents a (year, month) pair for use as Map key
 */

 struct MonthYearKey {

    /** @brief The year component */
    int year;

    /** @brief The month component (1–12) */
    int month;

    /**
     * @brief Constructs a MonthYearKey with the given year and month
     * @param y The year value
     * @param m The month value (1–12)
     * @pre y > 0, m between 1 and 12
     * @post Creates a valid MonthYearKey object
     */
    MonthYearKey(int y, int m);
};

    /**
     * @brief Less-than comparison operator
     *
     * Enables sorting of MonthYearKey objects (used in Maps and BSTs).
     * Compares by year first, then month if years are equal.
     *
     * @param other The other MonthYearKey to compare with
     * @return True if this key is earlier than the other
     */
bool operator<(const MonthYearKey& lhs, const MonthYearKey& rhs);
    /**
     * @brief Equality comparison operator
     *
     * Checks whether both keys represent the same (year, month) pair.
     *
     * @param other The other MonthYearKey to compare with
     * @return True if both year and month are equal
     */
bool operator==(const MonthYearKey& lhs, const MonthYearKey& rhs);

#endif // MONTHYEARKEY_H
