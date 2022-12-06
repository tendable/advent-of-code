#pragma once

#define TOP_N 3

void insertCalories(long calories, long* topCalories, size_t numberOfItems);
void printResult(long* topCalories, size_t numberOfItems);
void shift(long* array, size_t fromIndex, size_t untilIndex);