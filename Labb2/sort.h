#pragma once
#include <algorithm>
#include <vector>
#include <time.h>
#include <iostream>
#include <chrono>
#include <numeric>
#include <cmath>
#include <fstream>


#define INT_MAX std::numeric_limits<int>::max()
#define INT_MIN std::numeric_limits<int>::min()

struct Time
{
    int N;
    std::vector<double> times;
    float stdev;
    int sampels;
    double mean;
};



class sorting
{
public:
    sorting(int size, bool print, int samp, std::string prefix);
    sorting(std::vector<int> input,bool print, int samp, std::string prefix);
    void createData(int size);
    void insertionSort();
    void selectionSort();
	void quickSort();
	void medianQuickSort();
    void standardSort();
    void printData();
private:
	bool doPrint;
    int Samp;
    int N;
    std::string prefix;
    std::vector<int> data;
    void print(std::string method, Time time, bool printTimes);

    Time insertion;
    Time selection;
    Time quick;
    Time medianQuick;
    Time standard;

};