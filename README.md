# Signal Processing

Project for the MATH-458 course.

## Requirements
It is necessary to have `cmake` to make the executable and `python` (in particular Python 3) with the `matplotlib` 
and `numpy` libraries for generating the plots.

## User Guide
In order to set up the project, it is necessary to 'make' the `CmakeLists.txt` files. The run the file as follows:

```
./run_exe window_average average_mode num_fourier_coeffs
```

Note that `window_average` is an integer representing the moving average window that will be used for the time domain 
averaging, `average_mode` is a string which determines the type of averaging that will be applied (the two options are
"moving_average" and "exponential_moving_average"), and `num_fourier_coeffs` represents the number of Fourier 
coefficients that will be used for the filtering in the Fourier domain (i.e. we consider the ones with the largest
magnitude for reconstructing the signal in the time domain).

Once you have run this, run the following in the command line to generate the plots:

```
python plots.py
```

This will generate as output 4 different files: `original_signal.png`, `time_processed_signal.png`, 
`intensity_histogram.png`, and `fourier_filtered_signal.png`.

## Repository Structure



## Limitations & Future Improvements
Currently the code is not set up to deal with signals whose length is not a power of 2 (due to the specific
implementation of the FFT). Furthermore it is only set up to work with mono signals.