#!/bin/bash

for i in {1..1000}; do
    for j in {1..1000}; do
        echo "${i} ${j}" >> test.txt
    done
done
