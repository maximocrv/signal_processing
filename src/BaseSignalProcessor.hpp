//
// Created by Maximo Cravero on 19/01/2021.
//

#include <cmath>
#include <vector>
#include <algorithm>
#include <complex>
#include "../AudioFile/AudioFile.h"

using namespace std;
typedef complex<double> comp;

#ifndef SIGNAL_PROCESSING_BASESIGNALPROCESSOR_HPP
#define SIGNAL_PROCESSING_BASESIGNALPROCESSOR_HPP

class BaseSignalProcessor {
public:
    // constructors and destructors
    BaseSignalProcessor() {};
    BaseSignalProcessor(const AudioFile<double>& signal);
    virtual ~BaseSignalProcessor();

    // Set methods
    template<typename T>
    void SetTimeSignal(const T& signal);

    // Get methods
    vector<double> getTimeSignal() {return mTimeSignal; };
    vector<double> getFilteredTimeSignal() {return mFilteredTimeSignal; };
    vector< pair<double, pair<double, double> > > getHistogram() {return mHistogram; };

    // Generate the intensity histogram of the processed signal
    void GenerateHistogram(int n_bins);

    // Save the signals into an output file
    void SaveFile(const string& file_name, const string& signal_name);
    void SaveHistogram(const string& file_name);

protected:
    vector<double> mTimeSignal;
    vector<double> mFilteredTimeSignal;
    vector< pair<double, pair<double, double> > > mHistogram;

};


#endif //SIGNAL_PROCESSING_BASESIGNALPROCESSOR_HPP
