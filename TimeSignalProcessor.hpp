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

#include "BaseSignalProcessor.hpp"

/** Class for signal preprocessing (noise removing and histogram building).
 * \param mSignal: original signal
 * \param mNoiseRemovedSignal: processed signal
 */

class TimeSignalProcessor : public BaseSignalProcessor {
public:
    // constructors and destructors
    TimeSignalProcessor(const AudioFile<double>& signal) : BaseSignalProcessor(signal){};
    ~TimeSignalProcessor() {};

    // set methods
    void RemoveNoise(int window, const string& flag, double m = 0.5);

    void GenerateHistogram(int n_bins, const string& filename);
};


#endif //SIGNAL_PROCESSING_SIGNALPROCESSER_H
