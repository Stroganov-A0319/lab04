#include "histogram.h"
#include "svg.h"
#include <iostream>
using namespace std;

Input read_input(istream& in, bool prompt) {
    Input data;

    if(prompt)
    {
        cerr << "Enter number count: ";
    }
    size_t number_count;
    in >> number_count;

    if(prompt)
    {
        cerr << "Enter numbers: ";
    }
    data.numbers = input_numbers(in, number_count);

    if(prompt)
    {
        cerr << "Enter column count: ";
    }
    in >> data.bin_count;

    return data;
}
int main()
{
    Input input = read_input(cin, true);
    vector<size_t> bins = make_histogram(input);
    show_histogram_svg(bins, input.bin_count);
    return 0;
}
