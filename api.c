#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "api.h"

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
char* response(const char* city,const char* api){
  CURL* easy;
  CURLcode res;
  size_t url_size = 512;
  char* url = malloc(url_size);
  if (url == NULL){
    printf("Memory allocation failed for url!!");
    exit(1);
  }
  char* response = malloc(1);
  if (response == NULL){
    printf("Memory allocation failed for response!!");
    free(url);
    exit(1);
  }
  response[0] = '\0'; /*Did this b/c we used strncat function in code 
                      so, they will not behave  abnormally*/ 
  curl_global_init(CURL_GLOBAL_DEFAULT);
  easy = curl_easy_init();
  //printf("%s %s",city,api);
  snprintf(url,url_size,"http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric", city, api);
  
  if (easy){
    curl_easy_setopt(easy,CURLOPT_URL,url);
    curl_easy_setopt(easy,CURLOPT_WRITEFUNCTION,write_callback);
    curl_easy_setopt(easy,CURLOPT_WRITEDATA,&response);
  }
  res = curl_easy_perform(easy);
  if (res != CURLE_OK){
    fprintf(stderr, "cURL error: %s\n", curl_easy_strerror(res));
    free(url);
    free(response);
    curl_easy_cleanup(easy);
    curl_global_cleanup();
    exit(1);
  }
  free(url);
  
  curl_easy_cleanup(easy);
  curl_global_cleanup();
  return response;
}

