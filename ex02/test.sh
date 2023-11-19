#!/bin/bash

NUM_COUNT=$(( RANDOM % 50 + 1 ))
MAX=50
MIN=1

RANDOM_NUMS=()
while (( ${#RANDOM_NUMS[@]} < NUM_COUNT ))
do
  R=$(( RANDOM % (MAX - MIN + 1) + MIN))
  if ! [[ ${RANDOM_NUMS[*]} =~ $R ]]
  then
    RANDOM_NUMS+=($R)
  fi
done

./PMergeMe ${RANDOM_NUMS[@]}