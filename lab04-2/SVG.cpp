#include "svg.h"

void svg_begin(double width, double height)
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}

void svg_text(double left, double baseline, string text)
{

    cout << "<text x='" << left << "' y='" << baseline << "'>" << text << "</text>" << endl;

}
void svg_rect(double x, double y, double wid, double heig, string stroke = "red", string fill = "white")
{

    cout << "<rect x='" << x << "' y='" << y << "' width='" << wid << "' height='" << heig << "' stroke='" << stroke << "' fill='" << fill << "'/>" << endl;

};

void svg_end()
{
    cout << "</svg>\n";
}

void show_histogram_svg(const vector<size_t>& bins, size_t bin_count, bool flag, const string& address)
{
    CURLcode res;
    CURL *curl = curl_easy_init();
    if (curl) {
        double total;
        curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
        res = curl_easy_perform(curl);
    if(CURLE_OK == res) {
        res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total);
    if(CURLE_OK == res) {
      printf("Time: %.1f", total);
    }
  }
  /* always cleanup */
  curl_easy_cleanup(curl);
}

    DWORD info = GetVersion();
    DWORD mask = 0b00000000'00000000'11111111'11111111;
    DWORD version = info & mask;
    mask = 0x000000ff;
    DWORD platform = info >> 16;
    DWORD version_major = version & mask;
    DWORD version_minor = version >> 8;
    DWORD build;

    if ((info & 0x80000000) == 0)
    {
        build = platform;
        //   printf("Windows v%u.%u (build %u)\n", version_major, version_minor, build);

    }
    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = sizeof(computer_name);
    GetComputerNameA(computer_name, &size);
    //  printf("Computer name: %s\n", computer_name);

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;

    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);


    size_t max_count = 0;
    for (size_t count : bins)
    {
        if (count > max_count)
        {
            max_count = count;
        }
    }

    const bool scaling_needed = (max_count * BLOCK_WIDTH) > (IMAGE_WIDTH - TEXT_WIDTH);
    const double scaling_factor = (double)((IMAGE_WIDTH - TEXT_WIDTH)) / (double)((max_count * BLOCK_WIDTH));

    if (scaling_needed)
    {

        double top = 0;

        for (size_t i = 0; i < bin_count; i++)
        {
            const double bin_width = double(BLOCK_WIDTH * bins[i] * scaling_factor);
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));

            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);

            top += BIN_HEIGHT;
        }

        if(flag == true)
        {
            cout << "<text x='" << TEXT_LEFT << "' y='" << top + TEXT_BASELINE << "'>" << "Windows v" << version_major << "." << version_minor << " (build " << build << ")" << "</text>" << endl;
            cout << "<text x='" << TEXT_LEFT << "' y='" << top + 20 + TEXT_BASELINE << "'>" << "Computer name: " << computer_name << "</text>" << endl;
        }
        else
        {
            cout << "<text x='" << TEXT_LEFT << "' y='" << top + TEXT_BASELINE << "'>" << "Windows v" << version_major << "." << version_minor << " (build " << build << ")" << "</text>" << endl;
            cout << "<text x='" << TEXT_LEFT << "' y='" << top + 20 + TEXT_BASELINE << "'>" << "Computer name: " << computer_name << "</text>" << endl;
            curl_global_init(CURL_GLOBAL_ALL);
            CURL *curl = curl_easy_init();
            if(curl)
            {
                CURLcode res;
                double total;
                curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
                res = curl_easy_perform(curl);
                if(CURLE_OK == res)
                {
                    res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total);
                    if(CURLE_OK == res)
                    {

                       cerr << total;

                    }
                }
                curl_easy_cleanup(curl);
            }

        }
    }

    else
    {

        double top = 0;

        for (size_t i = 0; i < bin_count; i++)
        {
            const double bin_width = BLOCK_WIDTH * bins[i];
            svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bins[i]));

            svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);

            top += BIN_HEIGHT;
        }

        if(flag == true)
        {
            cout << "<text x='" << TEXT_LEFT << "' y='" << top + TEXT_BASELINE << "'>" << "Windows v" << version_major << "." << version_minor << " (build " << build << ")" << "</text>" << endl;
            cout << "<text x='" << TEXT_LEFT << "' y='" << top + 20 + TEXT_BASELINE << "'>" << "Computer name: " << computer_name << "</text>" << endl;
        }
        else
        {
            cout << "<text x='" << TEXT_LEFT << "' y='" << top + TEXT_BASELINE << "'>" << "Windows v" << version_major << "." << version_minor << " (build " << build << ")" << "</text>" << endl;
            cout << "<text x='" << TEXT_LEFT << "' y='" << top + 20 + TEXT_BASELINE << "'>" << "Computer name: " << computer_name << "</text>" << endl;
            curl_global_init(CURL_GLOBAL_ALL);
            CURL *curl = curl_easy_init();
            if(curl)
            {
                CURLcode res;
                double total;
                curl_easy_setopt(curl, CURLOPT_URL, address.c_str());
                res = curl_easy_perform(curl);
                if(CURLE_OK == res)
                {
                    res = curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &total);
                    if(CURLE_OK == res)
                    {
                        cerr << total;

                    }
                }
                curl_easy_cleanup(curl);
            }

        }
    }


    svg_end();

}
