/**
 * Stats
 * statistical calculations on numeric data
 *
 * This class provides static methods for common statistical operations including
 * mean and standard deviation calculations.
 *
 * The class uses Bessel's correction (n-1 denominator) for standard deviation
 * calculations, making it appropriate for sample data rather than entire populations.
 *
 */
#ifndef STATS_H
#define STATS_H

#include <cmath>
#include "Vector.h"

            /**
             * @brief  Calculates the mean of a vector of float values
             *
             * Computes the arithmetic mean (average) of all values in the vector.
             * Returns 0.0 if the vector is empty to avoid division by zero.
             *
             * @param  data - Vector of float values to calculate mean from
             * @return double - The mean value of all elements in the vector
             * @pre Vector should contain valid numeric data
             * @post Returns 0.0 if vector is empty
             */
double calculateMean(const Vector<float>& data);


            /**
             * @brief  Calculates the sample standard deviation of a vector of float values
             *
             * Computes the sample standard deviation using Bessel's correction (n-1).
             * This is the unbiased estimator for the population standard deviation.
             * Returns 0.0 if the vector has less than 2 elements.
             *
             * @param  data - Vector of float values to calculate standard deviation from
             * @return double - The sample standard deviation of the vector elements
             * @pre Vector should contain at least 2 elements for meaningful results
             * @post Returns 0.0 if vector has less than 2 elements
             */
double calculateStdDev(const Vector<float>& data);


            /**
             * @brief Calculates the Pearson correlation coefficient between two datasets
             *
             * Uses the standard Pearson Product-Moment Correlation (PPMC) formula to
             * measure the linear relationship between two equally sized vectors.
             * A value close to 1 indicates strong positive correlation, close to -1
             * indicates strong negative correlation, and around 0 indicates no linear relation.
             *
             * @param x - First vector of float values
             * @param y - Second vector of float values (must be same size as x)
             * @return double - The Pearson correlation coefficient in the range [-1, 1]
             * @pre x.size() == y.size() and size > 1
             * @post Returns a valid correlation value if preconditions are met
             */
double calculateSpcc(const Vector<float>& x, const Vector<float>& y);

             /**
             * @brief Calculates the Mean Absolute Deviation (MAD) from the mean
             *
             * Computes the average of the absolute differences between each data value
             * and the mean of the dataset. This is a simple measure of dispersion that
             * is less sensitive to outliers than standard deviation.
             *
             * @param data - Vector of float values to calculate MAD from
             * @return double - The mean absolute deviation of the dataset
             * @pre data.size() > 0
             * @post Returns 0.0 if vector is empty (if handled by caller)
             */
double madValue(const Vector<float>& data);

#endif // STATS_H

