#include "Stats.h"

// Calculate mean (average) of floating-point values
double calculateMean(const Vector<float>& data)
{
    double sum =0.0;  // Initialize sum
    // Iterate through all rec
    for (int i =0; i <data.size(); ++i){
        sum +=data[i];  // Add each value to sum
    }
    return sum /data.size();  // Return average (sum divided by count)
}

// Sample standard deviation (n-1 in denominator)
double calculateStdDev(const Vector<float>& data)
{
    double mean = calculateMean(data);
    double sumSquaredDiffs = 0.0; // Initialize sum of squared differences

    // Calculate sum of squared differences from mean
    for (int i =0; i <data.size(); ++i){
        double diff = data[i] - mean;  // Difference from mean
        sumSquaredDiffs +=diff *diff;  // Square and add to sum
    }
    // Return square root of variance (using n-1 for sample standard deviation)
    return std::sqrt(sumSquaredDiffs/ (data.size() - 1));
}

double calculateSpcc(const Vector<float>& x, const Vector<float>& y){
    int n = x.size();
    if(n!=y.size() || n<2){
        return 0.0;
    }

    // Calculate means
    double meanX = calculateMean(x);
    double meanY = calculateMean(y);

    // Calculate the three sums needed for Pearson formula
    double sumProducts = 0.0;    // sum(xi - meanX)(yi - meanY)
    double sumSquaresX = 0.0;    // sum(xi - meanX)
    double sumSquaresY = 0.0;    // sum(yi - meanY)

    for (int i = 0; i < n; ++i) {
        double diffX = x[i] - meanX;
        double diffY = y[i] - meanY;

        sumProducts += diffX * diffY;
        sumSquaresX += diffX * diffX;
        sumSquaresY += diffY * diffY;
    }

    // Calculate Pearson Correlation Coefficient
    double correlation = sumProducts / (std::sqrt(sumSquaresX) * std::sqrt(sumSquaresY));

    return correlation;
}

double madValue(const Vector<float>& data){
    if(data.size()==0){
        return 0.0;
    }
    // (mu) - mean of the datase
    double mu = calculateMean(data);
    double sumAbsoluteDeviations = 0.0;

    // sum|xi - mu| - sum of absolute deviations from mean
    for (int i = 0; i < data.size(); ++i) {
        sumAbsoluteDeviations += std::abs(data[i] - mu);
    }

    // MAD = (sum|xi - mu|) / n
    return sumAbsoluteDeviations / data.size();
}


