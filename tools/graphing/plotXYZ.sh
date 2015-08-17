#!/bin/bash
feedgnuplot --lines --points --legend 0 "X" --legend 1 "Y" --legend 2 "Z" --title "Accelerometer Data" --stream --xlen 10 --ylabel "Measurement"
