#include "histogram.h"
#include "svg.h"
#include <iostream>
using namespace std;

int main()
{
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    if (number_count == 0) {
        cerr << "ERROR: Empty vector";
    } else {

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(cin, number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    double min;
    double max;
    find_minmax(numbers,min,max);

    auto bins = make_histogram(numbers, bin_count, min, max);

    show_histogram_svg(bins, bin_count);
    }
    return 0;
}
