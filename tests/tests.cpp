#include <iostream>
#include <cmath>
#include "gtest/gtest.h"

#include "FourierTransform.hpp"
#include "SignalProcessor.hpp"

// https://developer.ibm.com/technologies/systems/articles/au-googletestingframework/

double square_root(const double a){
    return std::sqrt(a);
};

TEST (SquareRootTest, PositiveNos) {
    EXPECT_EQ (18.0, square_root(324.0));
    EXPECT_EQ (25.4, square_root(645.16));
    EXPECT_EQ (50.3321, square_root(2533.310224));
}

TEST (SquareRootTest, ZeroAndNegativeNos) {
    ASSERT_EQ (0.0, square_root(0.0));
    ASSERT_EQ (-1, square_root(-22.0));
}

TEST (FourierTransform, butterfly){
    return;
}

TEST (FourierTransform, backwards){
    return;
}

TEST (FourierTransform, reposition){
    return;
}

TEST (FourierTransform, fft){
    // Compare output with that of built in fft class
    return;
}

TEST (FourierTransform, inverse_fft){
    // Compare inverse output with that of built in fft class
    return;
}

TEST (FourierTransform, fft_filter){
    // Construct simple sum of sine waves and add noise terms
    return;
}

int main(int argc, char* argv[]){
	//make tests
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
