//
// Created by Maximo Cravero on 27/11/2020.
//

#include <cmath>
#include <numeric>
#include <algorithm>
#include "TimeSignalProcessor.hpp"

using namespace std;

/** Function for different types of noise removing:
 *        - moving_average: simple average of signal over a window
 *        - exponential_average: averaging, what use mixing with previous value in signal
 * \param window: averaging size
 * \param flag: type of Noise removing
 * \param m: mixing parameter
 */

void TimeSignalProcessor::RemoveNoise(int window, const string& flag, double m) {
    try {
        if ((flag != "moving_average") && ((flag != "exponential_average"))) {
            throw -1;
        }
    }
    catch (int a) {
            cerr << "Please input a valid flag ('moving_average', 'exponential_average')" << "\n";
    }
    if (flag == "moving_average") {
        try {
            if (window<=1) {
                throw -1;
            }
        }
        catch (int a) {
                cerr << "Window can't be smaller than 1. Increase it.";
        }

        double avg = accumulate(mTimeSignal.begin(), mTimeSignal.begin() + window - 1, 0.0) / (double) window;
        mFilteredTimeSignal.push_back(avg);

        for (int i = window; i < mTimeSignal.size(); i++) {
            avg -= mTimeSignal[i - window] / window;
            avg += mTimeSignal[i] / window;
            mFilteredTimeSignal.push_back(avg);
        }
    } else if (flag == "exponential_average") {

        try {
            if ((m > 1) || (m < 0)) {
                throw -1;
            }
        }
        catch (int a) {
            cerr << "Mixing factor should be between 0 and 1. Change it.";
        }
        mFilteredTimeSignal.push_back(mTimeSignal[0]);

        for (int i = 1; i < mTimeSignal.size(); i++) {
            double EMA = m * mTimeSignal[i] + (1 - m) * mFilteredTimeSignal[i - 1];
            mFilteredTimeSignal.push_back(EMA);
        }
    }
}
