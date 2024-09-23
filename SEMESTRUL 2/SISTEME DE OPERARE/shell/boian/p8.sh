#!/bin/bash

cat df.fake| awk ' NR > 1 && ($3 <1000 || $5+0 > 80) {print $6}'
