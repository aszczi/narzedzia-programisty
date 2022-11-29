#include <stdio.h>
#include <time.h>

#include <curl/curl.h>

static size_t data_handler(void *data, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    return realsize;
}

double measure_get()
{
    CURL *curl;
    CURLcode res;

    double trip_time;
    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://google.com");
        /* we tell libcurl to follow redirection */
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        /* discard output instead of printing to stdout*/
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, data_handler);
        /* Perform the request, res will get the return code */
        clock_t start = clock();
        res = curl_easy_perform(curl);
        clock_t end = clock();
        trip_time = (double)(end - start) / CLOCKS_PER_SEC;
        /* Check for errors */
        if (res != CURLE_OK)
        {
            printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return -1.0;
        }
        /* always cleanup */
        curl_easy_cleanup(curl);
    }
    return trip_time;
}