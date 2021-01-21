//
// Created by Maximo Cravero on 22/11/2020.
//

// TODO: Include exceptions, function overloading.
// TODO: include exception catching!!
// Function declarations
//void ReadFile(std::string fileName);fileName
// Function definitions

#include <iostream>
#include <fstream>
#include <vector>
#include <complex>

typedef std::complex<double> comp;

#include "AudioFile/AudioFile.h"
#include "src/TimeSignalProcessor.hpp"
#include "src/FourierTransform.hpp"

// Flow
// Read in audio signal
// Process signal in time domain (i.e. do a moving average/ exponential moving average, make histogram bins)
// Return output into a file, use gnuplot to make:
// histogram plot of intensities
// plot of original signal
// plot of moving averaged/ exponential signal
// process signal in frequency domain, save output into file. Transform back to time domain, save the file
// plot of fourier domain filtered signal
// take as input the number of fourier coefficients to use

// include a check for whether the command line arguments are valid?...

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
    time_signal.SaveFile(noise_removed_signal_file, "filtered_signal");

    // frequency domain processing and saving files
    // first we truncate the signal so it's a power of 2
    std::vector<double> raw_signal = time_signal.getTimeSignal();
    auto* signal_cut = new std::vector<double>;
    *signal_cut = std::vector<double>(raw_signal.begin(), raw_signal.begin() + pow(2, 14));

    // need your help to get it to work here but you get the idea
    FourierTransform fourier_instance;
    auto* random = new vector<comp>;
    fourier_instance.FFTFilter(*signal_cut,90, *random);
    //fourier_instance.FastFourierTransform(*signal_cut, *random);
    //fourier_instance.InverseFourierTransform(*signal_cut, *random);
    fourier_instance.SaveFile("signal.dat", "signal");


//    MISCELLANEOUS. DON'T DELETE FOR NOW.
//    auto test = fourier_instance.getFTSignal();
//    fourier_instance.FastFourierTransform(*signal_cut, false);
//    int window = 10;
//    int channel = 0;
//    int numSamples = audioFile.getNumSamplesPerChannel();
//    auto* sampleList = new double[numSamples];
//
//    for (int i=0; i < numSamples; i++){
//        sampleList[i] = audioFile.samples[channel][i];
//        //std::cout << sampleList[i] << "\n";
//    }
//    audioFile.printSummary();

}
