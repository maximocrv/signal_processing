//
// Created by Maximo Cravero and Sergei Kliavinek.
//

#include <vector>
#include <complex>

#include "AudioFile/AudioFile.h"
#include "src/TimeSignalProcessor.hpp"
#include "src/FourierTransform.hpp"

typedef std::complex<double> comp;

int main(int argc, char* argv[]){
    // loading in audiofile
    AudioFile<double> audioFile;
    audioFile.load("../CantinaBand3.wav");

    // defining variables for time signal processing
    string average_mode;
    int window_size;
    int num_bins;

    cout << "Select an averaging mode for the time filtered signal: ";
    cin >> average_mode;
    cout << "\nWindow size for the moving average filter: ";
    cin >> window_size;
    cout << "\nNumber of bins for the histogram: ";
    cin >> num_bins;

    // time domain processing
    TimeSignalProcessor time_signal(audioFile);
    time_signal.RemoveNoise(window_size, average_mode, 0.5);
    time_signal.GenerateHistogram(num_bins);

    const string& original_signal_file = "../output_data/original_signal.dat";
    const string& noise_removed_signal_file = "../output_data/noise_removed_signal.dat";
    const string& intensity_histogram_file = "../output_data/intensity_histogram.dat";

    // saving time domain files
    time_signal.SaveHistogram(intensity_histogram_file);
    time_signal.SaveTimeSignal(original_signal_file, "raw_signal");
    time_signal.SaveTimeSignal(noise_removed_signal_file, "filtered_signal");

    // frequency domain processing and saving files
    // first we truncate the signal so it's a power of 2
    std::vector<double> raw_signal = time_signal.getTimeSignal();
    auto* signal_cut = new std::vector<double>;
    *signal_cut = std::vector<double>(raw_signal.begin(), raw_signal.begin() + pow(2, 14));

    FourierTransform fourier_instance;
    float percentage;
    string filename;
    string label;
    cout << "Write the percentage for the FFT_Filter, filename and name of saving parameter:\n";
    cout << "Percentage (as %):";
    cin >> percentage;
    cout << "\nFilename: ";
    cin >> filename;
    cout << "\nLabel of saving parameter:\n";
    cin >> label;

    auto* random = new vector<comp>;
    fourier_instance.FFTFilter(*signal_cut, percentage, *random);
    //fourier_instance.FastFourierTransform(*signal_cut, *random);
    //fourier_instance.InverseFourierTransform(*signal_cut, *random);

    const string& filtered_fourier_file = "../output_data/filtered_fourier_file.dat";
    // saving frequency domain files
    fourier_instance.SaveFile(filename, label);

}
