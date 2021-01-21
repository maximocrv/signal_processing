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
    AudioFile<double> audioFile;
    audioFile.load("CantinaBand3.wav");

    int window_size = 10000;
    std::string average_mode = "moving_average";
    int num_bins = 50;
    int num_fourier_coeffs = 10;

    // keep these for when we make the final executable and actually use command line inputs!
    // int window_size = atoi(argv[0]);
    // char* average_mode = argv[1];
    // int num_bins = atoi(argv[2]);
    // int num_fourier_coeffs = atoi(argv[3]);

    // following lines define the file names for the plotting
    const string& original_signal_file = "output_data/original_signal.dat";
    const string& noise_removed_signal_file = "output_data/noise_removed_signal.dat";
    const string& intensity_histogram_file = "output_data/intensity_histogram.dat";
    const string& filtered_fourier_file = "output_data/filtered_fourier_file.dat";

    // time domain processing and saving files
    TimeSignalProcessor time_signal(audioFile);
    time_signal.RemoveNoise(window_size, average_mode, 0.5);
    time_signal.GenerateHistogram(num_bins);

    time_signal.SaveHistogram(intensity_histogram_file);
    time_signal.SaveTimeSignal(original_signal_file, "raw_signal");
    time_signal.SaveTimeSignal(noise_removed_signal_file, "filtered_signal");

    // frequency domain processing and saving files
    // first we truncate the signal so it's a power of 2
    std::vector<double> raw_signal = time_signal.getTimeSignal();
    auto* signal_cut = new std::vector<double>;
    *signal_cut = std::vector<double>(raw_signal.begin(), raw_signal.begin() + pow(2, 14));

    FourierTransform fourier_instance;
    auto* random = new vector<comp>;
    fourier_instance.FFTFilter(*signal_cut,90, *random);
    //fourier_instance.FastFourierTransform(*signal_cut, *random);
    //fourier_instance.InverseFourierTransform(*signal_cut, *random);
    fourier_instance.SaveFile("output_data/signal.dat", "signal");

}
