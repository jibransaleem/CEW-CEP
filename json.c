#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
#include "json.h"

void json(char* response,const char* city){
  cJSON *json = cJSON_Parse(response);
  FILE* processed_data = fopen("processed_data.txt","a");
  if (json == NULL){
    printf("Error parsing JSON response\n");
    exit(1);
  }
  else{
     cJSON *main = cJSON_GetObjectItemCaseSensitive(json, "main");
     if (main == NULL){
        printf("Main object not found in the response.\n");
        exit(1);
     }
     cJSON *temp = cJSON_GetObjectItemCaseSensitive(main, "temp");
     if (temp == NULL) {
        printf("Temperature data not found!\n");
        exit(1);
     } 
     printf("%s \nCurrent temperature : %.2f°C\n", city, temp->valuedouble);
     fprintf(processed_data,"%s \nCurrent temperature : %.2f°C\n", city, temp->valuedouble);
     cJSON *feels_like = cJSON_GetObjectItemCaseSensitive(main,"feels_like");
     if (feels_like == NULL){
        printf("feels like data not found!\n");
     }
     printf("feels like : %.2f°C\n",feels_like->valuedouble);
     fprintf(processed_data,"feels like : %.2f°C\n",feels_like->valuedouble);
     cJSON *humidity = cJSON_GetObjectItemCaseSensitive(main,"humidity");
     if (feels_like == NULL){
        printf("humidity data not found!\n");
     }
     printf("Humidity : %d\n",humidity->valueint);
     fprintf(processed_data,"Humidity : %d\ntrick\n",humidity->valueint);
     cJSON_Delete(json);
     fclose(processed_data);    
  }
}
