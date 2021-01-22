# Signal Processing
Project for the MATH-458 course.

## Requirements
It is necessary to have `cmake` to compile the code via the `CMakeLists.txt` file. `jupyter-notebook` is also necessary
to visualize the plots of the outputted data from the codebase, as well as the libraries `matplotlib`, `pandas`, and 
`numpy`  for generating the plots.

## User Guide
In order to set up the project, first clone the repository and then run the following commands:

```
cd signal-processing
git submodule add https://github.com/adamstark/AudioFile.git
git submodule add https://github.com/google/googletest.git
git submodule init
mkdir build
cd build && cmake ..
make
```

The from the build directory run the file as follows:

```
./test_signal_processor
./run_signal_processor
```

You will be prompted to input a number of parameters. Note that `window_average` is an integer representing the moving 
average window that will be used for the time domain averaging, `average_mode` is a string which determines the type of 
averaging that will be applied (the two options are "moving_average" and "exponential_moving_average")

Second set of parameters for the Fourier filtered signal. First, a number (as a `percentage`) must be entered 
indicating which part of the signal we consider to be the main and which part to be noise. After that you should enter 
a `filename`  and type of signal to be saved (`label`) (```Signal```, ```Frequency```, ```CleanSignal```, ```CleanFrequency``` ).

Once you have run this, you can run open the jupyter notebook `plots.ipynb` to visualize the results (note that there
are already plots present which we have generated from our own test runs).

## Repository Structure
The repository is structured as follows:

`BaseSignalProcessor.hpp/cpp`

Base class from which the FourierTransform and TimeSignalProcessor classes are derived. Contains custom constructor 
that sets the time signal to a member variable, as well as saving functionality which are used in both derived classes.

`FourierTransform.hpp/cpp`

Header and source file containing the FourierTransform class. It contains methods to perform the Fast Fourier Transform,
which are subdivided into further smaller functions, the inverse Fourier Transform, and perform filtering in the Fourier
domain.

`TimeSignalProcessor.hpp/cpp`

Header and source file containing the signal processor class which works with time domain signals. It contains methods
to perform noise removal (either via the moving average or exponential moving average), and generate intensity 
histograms.

### tests.cpp
All the tests performed on the above classes containing into the tests/test.cpp:

- Tests for FourierTransform class - ```fft_1```, ```fft_2```, ```inverse_fft_1```, ```inverse_fft_2``` and 
```fft_filter```
- Tests for TimeSignalProcessor class - ```remove_noise``` and ```histogram_testing```.

## Limitations & Future Improvements
Currently the code is not set up to deal with signals whose length is not a power of 2 (due to the specific
implementation of the FFT). Furthermore it is only set up to work with mono channel signals.

## External Libraries
AudioFile [[1]](https://github.com/adamstark/AudioFile.git) - used for loading in wav files.

GoogleTest [[2]](https://github.com/google/googletest.git) - testing suite.