#include "histogram.h"
#include "svg.h"
#include <windows.h>
using namespace std;

int main()
{
    DWORD info = GetVersion();
    printf("numberW = %u\n", info);
    printf("numberW = %08x\n", info);

    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;

    mask = 0x000000ff;
    DWORD platform = info >> 16;

    DWORD version_major = version & mask;
    DWORD version_minor = version >> 8;

    printf("version_major = %u\n", version_major);
    printf("version_minor = %u\n", version_minor);

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
