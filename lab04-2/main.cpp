#include "histogram.h"
#include <iostream>
#include "svg.h"
#include <sstream>
#include <string>

using namespace std;

vector<double> input_numbers(istream& in, size_t count);
Input read_input(istream& in, bool prompt);
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx);
Input download(const string& address);

int main(int argc, char* argv[])
{

    Input input;
    if (argc > 1)
    {
        input = download(argv[1]);
        const auto bins = make_histogram(input);
        show_histogram_svg(bins, input.bin_count, false, argv[1]);
    }
    else
    {
        input = read_input(cin, true);
        const auto bins = make_histogram(input);
        show_histogram_svg(bins, input.bin_count, false, argv[1]);
    }
    return 0;
}

Input read_input(istream& in, bool prompt)
{
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

size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx)
{
    size_t data_size = item_size * item_count;
    stringstream* buffer = reinterpret_cast<stringstream*>(ctx);
    (*buffer).write(reinterpret_cast<const char*>(items), data_size);

    return data_size;
}

Input download(const string& address)
{
    stringstream buffer;
    curl_global_init(CURL_GLOBAL_ALL);
    CURL *curl = curl_easy_init();

    if(curl)
    {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        res = curl_easy_perform(curl);
        if (res)
        {
            cerr << curl_easy_strerror(res) << endl;
            exit(1);
        }
    }
    curl_easy_cleanup(curl);

    return read_input(buffer, false);
}



vector<double> input_numbers(istream& in, size_t count)
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++)
    {
        in >> result[i];
    }
    return result;
}
