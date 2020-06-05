#include "histogram.h"
#include "svg.h"
#include <iostream>
using namespace std;

struct Input {
    vector<double> numbers;
    size_t bin_count;
};
Input read_input(istream& in) {
    Input data;
    cerr << "Enter number count: ";
    size_t number_count;
    in >> number_count;

    cerr << "Enter numbers: ";
    data.numbers = input_numbers(in, number_count);

    cerr << "Enter column count: ";
    in >> data.bin_count;

    return data;
}
int main()
{
    Input input = read_input(cin);

    double min;
    double max;
    find_minmax(input.numbers, min, max);

    const auto bins = make_histogram(input.numbers, input.bin_count, min, max);
    show_histogram_svg(bins, input.bin_count);
    return 0;
}
