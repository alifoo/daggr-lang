#include <iostream>
#include <string>
#include <curl/curl.h>

// libcurl calls this repeatedly as it receives chunks of data from the internet
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    // size * nmemb is the actual size of the data chunk in bytes
    size_t newLength = size * nmemb;

    try {
        // append new chunk of data to the end of our string 's'
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        // if we run out of memory, return 0 to tell curl to stop the transfer
        return 0;
    }
    return newLength;
}

int main() {
    CURL* curl;
    CURLcode res;

    std::string readBuffer;

    curl = curl_easy_init();

    if(curl) {
        // main way to configure your request
        // set destination url to fetch
        curl_easy_setopt(curl, CURLOPT_URL, "https://linguee-api.fly.dev/api/v2/translations?query=hallo&src=de&dst=pt&guess_direction=false&follow_corrections=never");

        // tell curl which function to call with each chunk of data
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);

        // tell curl where to send the data
        // this is passed as the 4th argument to WriteCallback
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        // starts the network transfer and blocks until it's done
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            std::cout << "Response: " << readBuffer << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}
