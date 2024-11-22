#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>


// Function to handle the response data from cURL
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *data) {
    char **response_ptr = (char **)data;

    size_t total_size = size * nmemb;
    char *temp = realloc(*response_ptr, strlen(*response_ptr) + total_size + 1);

    if (temp == NULL) {
        fprintf(stderr, "Failed to reallocate memory for response.\n");
        return 0;
    }

    *response_ptr = temp;
    strncat(*response_ptr, (char *)ptr, total_size);

    return total_size;
}

// Function to fetch weather data
void get_weather(const char *city, const char *api_key) {
    CURL *curl;
    CURLcode res;

    // Allocate memory for the URL
    size_t url_size = 512;
    char *url = malloc(url_size);
    if (url == NULL) {
        fprintf(stderr, "Failed to allocate memory for URL.\n");
        return;
    }

    // Construct the URL for OpenWeatherMap API
    snprintf(url, url_size, "http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric", city, api_key);
    printf("%s",url);
    // Allocate memory for the response
    char *response = malloc(1);
    if (response == NULL) {
        fprintf(stderr, "Failed to allocate memory for response.\n");
        free(url);
        return;
    }
    response[0] = '\0'; // Initialize to an empty string

    // Initialize cURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Set up cURL options
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // Perform the request
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
        } else {
            // Print raw response data
            printf("Raw Response Data:\n%s\n", response);

            // Parse the JSON response using cJSON
            cJSON *json = cJSON_Parse(response);
            if (json == NULL) {
                fprintf(stderr, "Error parsing JSON response\n");
            } else {
                // Extract temperature from the "main" object
                cJSON *main = cJSON_GetObjectItemCaseSensitive(json, "main");
                if (main != NULL) {
                    cJSON *temp = cJSON_GetObjectItemCaseSensitive(main, "temp");
                    if (temp != NULL) {
                        printf("Processed Data: Current temperature in %s: %.2f°C\n", city, temp->valuedouble);
                    } else {
                        printf("Temperature data not found in the 'main' object.\n");
                    }
                } else {
                    printf("Main object not found in the response.\n");
                    cJSON *message = cJSON_GetObjectItemCaseSensitive(json, "message");
                    if (message != NULL) {
                        printf("API error message: %s\n", message->valuestring);
                    }
                }
                cJSON_Delete(json);
            }
        }

        // Clean up cURL
        curl_easy_cleanup(curl);
    }

    // Free allocated memory
    free(url);
    free(response);

    curl_global_cleanup();
}

int main() {
    char city[20];  // Change to your desired city
    const char *api_key = "572f7ccfe2c582a830dfddb06e0f2236"; // Replace with your OpenWeatherMap API key
    while (1) {
        printf("Enter a city (or press Enter to exit): ");
        if (!fgets(city, sizeof(city), stdin)) {
            break; // Exit on input failure
        }

        // Remove newline character if it exists
        city[strcspn(city, "\n")] = '\0';

        if (strlen(city) == 0) {
            break; // Exit if the user enters an empty city name
        }

        get_weather(city, api_key);
    }
    
    return 0;
}

