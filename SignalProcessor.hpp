//
// Created by Maximo Cravero on 27/11/2020.
//

#include <cmath>
#include <vector>
#include <algorithm>
#include "AudioFile/AudioFile.h"

using namespace std;

#ifndef SIGNAL_PROCESSING_SIGNALPROCESSER_H
#define SIGNAL_PROCESSING_SIGNALPROCESSER_H

/** Class for signal preprocessing (noise removing and histogram building).
 * \param mSignal: original signal
 * \param mNoiseRemovedSignal: processed signal
 */

class SignalProcessor {
public:
    // constructors and destructors
    SignalProcessor();
    SignalProcessor(const AudioFile<double>& signal);
    ~SignalProcessor();

    // set methods
    template<typename T>
    void SetSignal(const T& signal);
    void RemoveNoise(int window, string flag, double m = 0.5);

    void GenerateHistogram(int n_bins);

    // get methods (const)
    // get
    vector<double> getRawSignal();
    void getNoiseRemovedSignal();

    // Signal.to_file(asjdlfkasjdf)

private:
    vector<double> mSignal;
    vector<double> mNoiseRemovedSignal;
};


#endif //SIGNAL_PROCESSING_SIGNALPROCESSER_H
