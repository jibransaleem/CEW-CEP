#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "api.h"
#include "json.h"

int main() {
  char* city = "Karachi";
  const char* api = "572f7ccfe2c582a830dfddb06e0f2236";
  char* res;
  res = response(city,api);
  FILE* raw_f = fopen("raw_data.json","a");
  if (raw_f == NULL){
    printf("Error opening file for writing.\n");
    exit(1);
  }
  fprintf(raw_f,"%s\n",res);
  system("notify-send 'hogia ab soja'");
  json(res,city);
  free(res);
  return 0;
}

