#!/bin/bash

gcc json.c api.c learning.c -o w -lcurl -ljson
./w
