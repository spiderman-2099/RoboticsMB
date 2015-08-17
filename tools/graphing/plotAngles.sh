#!/bin/bash
feedgnuplot --lines --points --legend 0 "Pitch" --legend 1 "Roll" --title "Board Attitude" --stream --xlen 10 --ylabel "Angle"
