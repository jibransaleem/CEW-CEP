# Weather Alert System - CEP Complex Engineering Project

This project is a Weather Alert System developed as part of a CEP Complex Engineering Project. The application fetches real-time weather data using APIs, processes the responses, and provides critical weather alerts. The system is implemented in C, leveraging powerful libraries and tools for robust functionality and automation.

Key Features:

API Integration:
    Uses the libcurl library to fetch real-time weather data from external APIs.
    Efficient and secure HTTP requests.
    
Handles API responses seamlessly.
    JSON Response Handling:
    Employs the c-json library to parse and extract meaningful data from API responses.

Linux Automation:
    Designed to run on Linux systems, utilizing shell scripts and cron jobs for automation.
    Scheduled updates to fetch and display weather alerts periodically.

Dependencies:
    libcurl: For HTTP communication with APIs.
    cJSON: For handling JSON data.
    Linux environment: Required for automation scripts and task scheduling.

For Automation Purpose:
    This application automates for a week and saves all the files in out_files folder.After seven days, the oldest file will be deleted.
    For this automation be accessed user is needed to write the following command in his *crontab editor*.

    '0 0 * * * /path/to/your/out.sh'
