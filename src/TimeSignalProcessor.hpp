//
// Created by Maximo Cravero and Sergei Kliavinek.
//

#include <cmath>
#include <vector>
#include <algorithm>

#include "BaseSignalProcessor.hpp"
#include "../AudioFile/AudioFile.h"

using namespace std;

#ifndef SIGNAL_PROCESSING_SIGNALPROCESSER_H
#define SIGNAL_PROCESSING_SIGNALPROCESSER_H

/** Class for signal preprocessing (noise removing and histogram building).
 * \param mSignal: original signal
 * \param mNoiseRemovedSignal: processed signal
 */

class TimeSignalProcessor : public BaseSignalProcessor {
public:
    // constructors and destructors
    TimeSignalProcessor(){};
    TimeSignalProcessor(const AudioFile<double>& signal) : BaseSignalProcessor(signal){};
    ~TimeSignalProcessor() {};

    // noise removal method
    void RemoveNoise(int window, const string& flag, double m = 0.5);
};


#endif //SIGNAL_PROCESSING_SIGNALPROCESSER_H
