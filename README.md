﻿# extract-fanfare-gcsim

Extract furina's dmgbonus% and frames from gcsim sample file.

## Table of Contents

- [Usage](#Usage)
- [Build](#Build)

## Usage
Needs a sample file from gcsim. Generate a sample in gcsim and download it. Place the sample.txt file in the same directory as the program and run it.
Program will generate output.txt in the same directory with 2 columns: time (s) | amount_of_fanfare. Check output.txt for reference.

## Build
Tested with g++.exe (Rev7, Built by MSYS2 project) 13.1.0
```bash
g++ -o main.exe main.cpp

