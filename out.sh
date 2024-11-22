#!/bin/bash
gcc json.c api.c learning.c -o w -lcurl -lcjson
OUTPUT_DIR="output_files"
mkdir -p "$OUTPUT_DIR"

PROGRAM="./w"  
RUN_COUNT=7  

TIMESTAMP=$(date +"%Y-%m-%d;%H:%M:%S")
OUTPUT_FILE="$OUTPUT_DIR/output_$TIMESTAMP.txt"

echo "Running the program and saving output to $OUTPUT_FILE..."
$PROGRAM > "$OUTPUT_FILE" 2>&1

FILE_COUNT=$(ls "$OUTPUT_DIR" | wc -l)

if (( FILE_COUNT > RUN_COUNT )); then
    OLDEST_FILE=$(ls -t "$OUTPUT_DIR" | tail -1)
    echo "Removing the oldest output file: $OLDEST_FILE"
    rm "$OUTPUT_DIR/$OLDEST_FILE"
fi

echo "Done. Current output files:"
ls "$OUTPUT_DIR"

