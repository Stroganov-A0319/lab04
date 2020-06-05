#include "histogram.h"
#include "SVG.h"
using namespace std;

int main()
{
    const char* name = "Commander Shepard";
    int year = 2154;
    printf("%s was born in %d.\n", name, year);
    // Commander Shepard was born in 2154.

    printf("n = %08x\n", 0x1234567); // 01234567

    return 0;

    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;

    cerr << "Enter numbers: ";
    const auto numbers = input_numbers(number_count);

    size_t bin_count;
    cerr << "Enter column count: ";
    cin >> bin_count;

    double min;
    double max;
    find_minmax(numbers,min,max);

    auto bins = make_histogram(numbers, bin_count, min, max);

    show_histogram_svg(bins, bin_count);

    return 0;
}
