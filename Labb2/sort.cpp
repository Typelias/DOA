#include "sort.h"

template<typename Iter>
int* part(Iter lo, Iter hi)
{
	Iter Left = lo-1;
	Iter Right = hi;

	int piv = *(hi);
	while(true)
	{
		while(*++Left< piv);
		while(piv < *--Right) if(Right == lo) break;

		if(Left >= Right)
			break;
		std::swap(*Left, *Right);
		
		
	}
	std::swap(*Left,*hi);
	return &*Left;
}


template<typename Iter>
void q(Iter lo, Iter hi)
{
	int* p;
	if (lo < hi)
	{
		p = part(lo, hi);
		q(&*lo, &*p - 1);
		q(&*p + 1, &*hi);
	}
	
}

template<typename Iter>
Iter part2(Iter low, Iter Pivot, Iter high)
{
	Iter lo = &*(low-1);
	Iter hi = &*high;
	int pivot = *Pivot;
	while(true)
	{
		while(*++lo< pivot);
		while(pivot <*--hi) if(&*hi==&*low) break;
		if(lo >= hi)
			break;
		std::swap(*hi,*lo);
		
		
	}
	std::swap(*&*high,*lo);
	return &*lo;
}

template<typename Iter>
Iter median(Iter lo, Iter hi)
{
	Iter piv = hi-1;
	if(*hi > *lo)
		std::swap(*hi,*lo);
	if(*piv < *lo)
		std::swap(*lo, *piv);
	if(*piv> *hi)
		std::swap(*hi,*piv);
	
	std::swap(*piv,*(hi-1));

	return &*hi;
}

template<typename Iter>
void q2(Iter lo, Iter hi)
{
	int* pivot;
	int* index;
	if(lo < hi)
	{
		pivot = median(&*lo, &*hi);
		index = part2(&*lo, pivot, &*hi);
		q2(&*lo, &*index -1);
		q2(&*index+1, &*hi);
	}
}

sorting::sorting(int size, bool print, int samp, std::string prefix)
:Samp(samp), N(size),doPrint(print), prefix(prefix)
{

    this->createData(size);
}

sorting::sorting(std::vector<int> input,bool print, int samp, std::string prefix)
:Samp(samp),doPrint(print), N(input.size()), prefix(prefix)
{
    this->data = input;
}

void sorting::createData(int size)
{
    srand(time(NULL));
    this->data.clear();
    for(int i = 0; i < size; i++)
    {
        this->data.push_back(rand()% INT_MAX + INT_MIN);
    }
}

void sorting::print(std::string method, Time time, bool printTimes)
{
    std::cout << method << "\n";
	std::cout << "N\tT[ms]\t\tStdev[ms]\tSampels\n";
	std::cout << time.N << "\t" << time.mean << "\t\t" << time.stdev << "\t\t" << time.sampels << "\n";
	std::cout << "Printing to file\n";
	std::string filename = this->prefix + method + ".txt";
	std::ofstream out;
	out.open(filename,std::ofstream::app);
	out << time.N << "\t" << time.mean << "\t" << time.stdev << "\t" << time.sampels << "\n";
	out.close();

	filename = "[Data]"+filename;
	std::ofstream out;
	out.open(filename,std::ostream::app);
	out << time.N << " " << time.mean << "\n";

	if(printTimes)
		for(auto &c : time.times)
			std::cout << c << " ";
	std::cout << "\n";
}

void sorting::insertionSort()
{
	for(int x = 0; x < this->Samp; x++)
	{
		auto arr = this->data;
		auto start = std::chrono::high_resolution_clock::now();
		int i, key, j;
		for(i = 1; i < arr.size();i++)
		{
			key = arr[i];
			j = i -1;

			while(j>=0 && arr[j]>key)
			{
				arr[j+1] = arr[j];
				j = j -1;
			}

			arr[j + 1] = key;
			
		}
		auto stop = std::chrono::high_resolution_clock::now();
		if(!std::is_sorted(arr.begin(),arr.end()))
		{
			std::cout << "Not sorted\n";
			break;
		}
		std::chrono::duration<double, std::milli> time = stop - start;
		this->insertion.times.push_back(time.count());
	}
	this->insertion.N = this->N;
	this->insertion.mean = std::accumulate(this->insertion.times.begin(),this->insertion.times.end(),0.0)/this->insertion.times.size();
	this->insertion.sampels = Samp;
	double sq_sum = std::inner_product(this->insertion.times.begin(), this->insertion.times.end(), this->insertion.times.begin(), 0.0);
	this->insertion.stdev = std::sqrt(sq_sum / this->insertion.times.size() - this->insertion.mean * this->insertion.mean);
	this->print("Inserton Sort",this->insertion,this->doPrint);
}

void sorting::selectionSort()
{
	for(int x = 0; x<this->Samp; x++)
	{
		auto vec = this->data;
		auto start = std::chrono::high_resolution_clock::now();
		int i, j;
		int n = vec.size();

		for(i=0; i<n-1; i++)
		{
			int min_index = i;

			for(j = i+1; j<n; j++)
			{
				if(vec[j] < vec[min_index]) min_index = j;
			}
			if(min_index != i)
			{
				std::swap(vec[min_index], vec[i]);
			}
		}
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time = stop - start;
		this->selection.times.push_back(time.count());
	}
	this->selection.N = this->N;
	this->selection.mean = std::accumulate(this->selection.times.begin(),this->selection.times.end(),0.0)/this->selection.times.size();
	this->selection.sampels = Samp;
	double sq_sum = std::inner_product(this->selection.times.begin(), this->selection.times.end(), this->selection.times.begin(), 0.0);
	this->selection.stdev = std::sqrt(sq_sum / this->selection.times.size() - this->selection.mean * this->selection.mean);
	this->print("Selection Sort",this->selection,this->doPrint);
}

void sorting::quickSort()
{
	for(int x = 0; x < this->Samp; x++)
	{
		auto vec = this->data;
		auto start = std::chrono::high_resolution_clock::now();
		q(vec.begin(), vec.end());
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time = stop - start;
		this->quick.times.push_back(time.count());
	}
	this->quick.N = this->N;
	this->quick.mean = std::accumulate(this->quick.times.begin(),this->quick.times.end(),0.0)/this->quick.times.size();
	this->quick.sampels = Samp;
	double sq_sum = std::inner_product(this->quick.times.begin(), this->quick.times.end(), this->quick.times.begin(), 0.0);
	this->quick.stdev = std::sqrt(sq_sum / this->quick.times.size() - this->quick.mean * this->quick.mean);
	this->print("Quicksort",this->quick,this->doPrint);
}

void sorting::medianQuickSort()
{
	for(int x = 0; x< this->Samp; x++)
	{
		auto vec = this->data;
		auto start = std::chrono::high_resolution_clock::now();
		q2(vec.begin(),vec.end());
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time = stop - start;
		this->medianQuick.times.push_back(time.count());
	}
	this->medianQuick.N = this->N;
	this->medianQuick.mean = std::accumulate(this->medianQuick.times.begin(),this->medianQuick.times.end(),0.0)/this->medianQuick.times.size();
	this->medianQuick.sampels = Samp;
	double sq_sum = std::inner_product(this->medianQuick.times.begin(), this->medianQuick.times.end(), this->medianQuick.times.begin(), 0.0);
	this->medianQuick.stdev = std::sqrt(sq_sum / this->medianQuick.times.size() - this->medianQuick.mean * this->medianQuick.mean);
	this->print("Median Quicksort",this->medianQuick,this->doPrint);
}

void sorting::standardSort()
{
	for(int x = 0; x < this->Samp; x++)
	{
		auto vec = this->data;
		auto start = std::chrono::high_resolution_clock::now();
		std::sort(vec.begin(),vec.end());
		auto stop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> time = stop - start;
		this->standard.times.push_back(time.count());
	}
	this->standard.N = this->N;
	this->standard.mean = std::accumulate(this->standard.times.begin(),this->standard.times.end(),0.0)/this->standard.times.size();
	this->standard.sampels = Samp;
	double sq_sum = std::inner_product(this->standard.times.begin(), this->standard.times.end(), this->standard.times.begin(), 0.0);
	this->standard.stdev = std::sqrt(sq_sum / this->standard.times.size() - this->standard.mean * this->standard.mean);
	this->print("std::sort",this->standard,this->doPrint);
}


void sorting::printData()
{
    for(auto &c : this->data)
        std::cout << c << "\t";
    std::cout << "\n";
}