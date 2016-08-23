/***********************************************************
* Author:		Andrew Sparkes
* Lab Number:	CST 211 Lab 2
* Filename:		main.cpp
* Date Created:	4-19-12
* Modifications:	4-24-12 Fixed bug in stooge sort, quicksort, tweaks
*
* Overview:
*	This program demos a handful of popular sort algorithms. 
*	It makes a vector, Array and native array of ints to 
*	use to sort. Each data struct is reset to original before 
*	calling the next sort.
*
* Input:
*	A single commandline parameter representing length of 
*	array to sort. Used as length for vector, Array, native 
*	array.
*
* Output:
*	Output is primarily written to a file, but basic console 
*	output is also enabled.
************************************************************/
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;
#include <vector>
using std::vector;
#include "Array.h"
#include "Timer.h"
#include <time.h>
#include <crtdbg.h>
#define _CRTDBG_MAP_ALLOC

template <class container>
void bubbleSort(container& a, int length);

template <class container>
void flaggedBubbleSort(container& a, int length);

template <class container>
void selectionSort(container& a, int length);

template <class container>
void insertionSort(container& a, int length);

template <class container>
void binaryInsertionSort(container& a, int length);

template <class T, class container>
void shellSort(container& a, int length);

template <class container>
void heapSort(container& a, int length);

template <class T>
void mergeSort(vector<T>& a, int length);

template <class T>
void merge(vector<T> const& left, int len_left, vector<T> const& right, int len_right, vector<T>& combined);

template <class T>
void mergeSort(Array<T>& a, int length);

template <class T>
void merge(Array<T> const& left, int len_left, Array<T> const& right, int len_right, Array<T>& combined);

template <class T>
void mergeSort(T* a, int length);

template <class T>
void merge(T* const& left, int len_left, T* const& right, int len_right, T* combined);

template <class container, class T>
void quickSort(container& a, int length);

template <class container, class T>
void quickSort(container& a, int left, int right);

template <class container>
void gnomeSort(container& a, int length);

template <class container>
void shakerSort(container& a, int length);

template <class container>
void oddEvenSort(container& a, int length);

template <class container>
void stoogeSort(container& a, int length);

template <class container>
void stoogeSort(container& a, int low, int high);

template <class container>
void combSort(container& a, int length);

int RNG(int n);

template <class T>
void Swap(T& a, T& b);

template <class container>
void Print(container const& a, int length);

template <class T>
void ResetArrays(vector<T> orig, vector<T>& a, Array<T>& b, T* c);

template <class T>
void demoSort(void (*sortFunc)(T& a, int length), const char* sortName, T& a, int length, ofstream& fout);

int main(int argc, char* argv[]){
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	if(argc != 2){
		cout << "Lab2 requires a commandline parameter indicating the requested number of elements in the arrays to be sorted." << endl;
		system("pause");
	}else{
		Timer globalTimer; // used to track whole script execution duration
		globalTimer.Start();

		// prepare file for output
		ofstream outputFile;
		outputFile.open("output.txt", std::ios::out); // will overwrite previous contents
		if(!outputFile.is_open()){
			// error opening file for output
			return -1;
		}

		int length = atoi(argv[1]);
		cout << "Generating a random array of integers of length " << length << endl << endl;
		outputFile << "Generating a random array of integers of length " << length << endl << endl;
		
		Timer timer; // used for merge sort below


		// initialize all our array datatypes
		vector<int> a;
		a.reserve(length);
		Array<int> b(length, 0);
		int* c = new int[length];

		// populate the arrays with random data
		int random_num = 0;
		for(int i=0; i<length; ++i){
			random_num = RNG(100000); // elements will be in bound below by 0 (inclusive) and 100000 above (exclusive)
			a.push_back(random_num);
			b[i] = random_num;
			c[i] = random_num;
		}

		vector<int> orig = a; // copying the vector to be used to reset the vector, Array, native array in ResetArrays() later
		
		demoSort(&bubbleSort<vector<int>>, "Bubble Sort Vector", a, length, outputFile);
		demoSort(&bubbleSort<Array<int>>, "Bubble Sort Array", b, length, outputFile);
		demoSort(&bubbleSort<int*>, "Bubble Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);
		
		demoSort(&flaggedBubbleSort<vector<int>>, "Flagged Bubble Sort Vector", a, length, outputFile);
		demoSort(&flaggedBubbleSort<Array<int>>, "Flagged Bubble Sort Array", b, length, outputFile);
		demoSort(&flaggedBubbleSort<int*>, "Flagged Bubble Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);
		
		demoSort(&selectionSort<vector<int>>, "Selection Sort Vector", a, length, outputFile);
		demoSort(&selectionSort<Array<int>>, "Selection Sort Array", b, length, outputFile);
		demoSort(&selectionSort<int*>, "Selection Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);
		
		demoSort(&insertionSort<vector<int>>, "Insertion Sort Vector", a, length, outputFile);
		demoSort(&insertionSort<Array<int>>, "Insertion Sort Array", b, length, outputFile);
		demoSort(&insertionSort<int*>, "Insertion Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);

		demoSort(&binaryInsertionSort<vector<int>>, "Binary Insertion Sort Vector", a, length, outputFile);
		demoSort(&binaryInsertionSort<Array<int>>, "Binary Insertion Sort Array", b, length, outputFile);
		demoSort(&binaryInsertionSort<int*>, "Binary Insertion Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);

		demoSort(&shellSort<int, vector<int>>, "Shell Sort Vector", a, length, outputFile);
		demoSort(&shellSort<int, Array<int>>, "Shell Sort Array", b, length, outputFile);
		demoSort(&shellSort<int, int*>, "Shell Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);

		demoSort(&heapSort<vector<int>>, "Heap Sort Vector", a, length, outputFile);
		demoSort(&heapSort<Array<int>>, "Heap Sort Array", b, length, outputFile);
		demoSort(&heapSort<int*>, "Heap Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);
		
		demoSort(&quickSort<vector<int>,int>, "Quick Sort Vector", a, length, outputFile);
		demoSort(&quickSort<Array<int>,int>, "Quick Sort Array", b, length, outputFile);
		demoSort(&quickSort<int*,int>, "Quick Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);

		demoSort(&gnomeSort<vector<int>>, "Gnome Sort Vector", a, length, outputFile);
		demoSort(&gnomeSort<Array<int>>, "Gnome Sort Array", b, length, outputFile);
		demoSort(&gnomeSort<int*>, "Gnome Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);

		demoSort(&shakerSort<vector<int>>, "Shaker Sort Vector", a, length, outputFile);
		demoSort(&shakerSort<Array<int>>, "Shaker Sort Array", b, length, outputFile);
		demoSort(&shakerSort<int*>, "Shaker Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);

		demoSort(&oddEvenSort<vector<int>>, "Odd-Even Sort Vector", a, length, outputFile);
		demoSort(&oddEvenSort<Array<int>>, "Odd-Even Sort Array", b, length, outputFile);
		demoSort(&oddEvenSort<int*>, "Odd-Even Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);
		
		demoSort(&combSort<vector<int>>, "Comb Sort Vector", a, length, outputFile);
		demoSort(&combSort<Array<int>>, "Comb Sort Array", b, length, outputFile);
		demoSort(&combSort<int*>, "Comb Sort Native Array", c, length, outputFile);

		ResetArrays(orig, a, b, c);

		// had to work mergeSort slightly differently, due to non-templated, but just overloaded
		timer.Start();
		mergeSort(a, length);
		timer.Stop();
		outputFile << "Merge Sort vector (" << timer.getTime() << " ms)" << endl;
		timer.Reset();
		for(int i=0; i < length; i+=1000){
			outputFile << a[i] << " ";
		}
		outputFile << endl << endl;

		timer.Start();
		mergeSort(b, length);
		timer.Stop();
		outputFile << "Merge Sort Array (" << timer.getTime() << " ms)" << endl;
		timer.Reset();
		for(int i=0; i < length; i+=1000){
			outputFile << b[i] << " ";
		}
		outputFile << endl << endl;

		timer.Start();
		mergeSort(c, length);
		timer.Stop();
		outputFile << "Merge Sort Native Array (" << timer.getTime() << " ms)" << endl;
		timer.Reset();
		for(int i=0; i < length; i+=1000){
			outputFile << c[i] << " ";
		}
		outputFile << endl << endl;

		
		ResetArrays(orig, a, b, c);

		// stooge sort saved for last, because it is atrociously slow
		// slow enough where it did not sort 100k elements over ~7hours, where bubblesort was in the 30-60sec area for same data. temp removed
		//demoSort(&stoogeSort<vector<int>>, "Stooge Sort Vector", a, length, outputFile);
		//demoSort(&stoogeSort<Array<int>>, "Stooge Sort Array", b, length, outputFile);
		//demoSort(&stoogeSort<int*>, "Stooge Sort Native Array", c, length, outputFile);

		outputFile.close();

		delete [] c; // clean up the array itself as well

		globalTimer.Stop();
		cout << "All done in " << globalTimer.getTime() << " ms!" << endl;
		outputFile << "All done in " << globalTimer.getTime() << " ms!" << endl;

		system("pause");
	}
	return 0;
}

/**********************************************************************	
* Purpose: This function demos a sort, outputting a brief console message 
*	as well as writing each 1000th element to a file, and the time taken 
*	for the sort.
*
* Entry: sortFunc is a function pointer to the sort being demo'd
*		sortName is a string representing the name of the sort
*		a is the Array/vector/native array to be sorted
*		length is the length of the above Array/vector
*		fout is the file stream to output to
*
* Exit: The function leaves the Array/vector sorted, and a small summary 
*		written to console/file.
*
************************************************************************/
template <class T>
void demoSort(void (*sortFunc)(T& a, int length), const char* sortName, T& a, int length, ofstream& fout){
	Timer timer;
	cout << "Sorting via " << sortName << "..." << endl;

	timer.Start();
	sortFunc(a, length);
	timer.Stop();
	fout << sortName << " (" << timer.getTime() << " ms)" << endl;

	for(int i=0; i < length; i+=1000){
		fout << a[i] << " ";
	}
	fout << endl << endl;
	cout << "Done in " << timer.getTime() << " ms." << endl << endl;
}

/**********************************************************************	
* Purpose: This function resets the vector, Array, native array back to 
*		the original data values, so later sorts do not have an advantage
*
* Entry: orig is a vector used to copy values from
*		a is the vector
*		b is the Array
*		c is the native array
*
* Exit: This function sets a,b,c to the same values as orig.
*
************************************************************************/
template <class T>
void ResetArrays(vector<T> orig, vector<T>& a, Array<T>& b, T* c){
	// use the first vector passed in as a prototype to make all the others
	// vector used simply because it's simplest
	for(unsigned i=0; i<orig.size(); ++i){
		a[i] = b[i] = c[i] = orig[i];
	}
}

/**********************************************************************	
* Purpose: Short helper function to print the passed in container's data
*		(used for debug purposes)
*
* Entry: a is the vector/Array
*		length is how many elements in a
*
* Exit: Prints vector/Array to console, space delimited
*
************************************************************************/
template <class container>
void Print(container const& a, int length){
	for(int i=0; i<length; ++i){
		cout << a[i] << " ";
	}
	cout << endl;
}

/**********************************************************************	
* Purpose: Bubble sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void bubbleSort(container& a, int length){
	for(int j = 0; j < length; ++j){
		for(int i = 0; i < length-1; ++i){
			if(a[i] > a[i+1]){
				Swap(a[i], a[i+1]);
			}
		}
	}
}

/**********************************************************************	
* Purpose: Flagged bubble sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void flaggedBubbleSort(container& a, int length){
	bool sorted = false;
	for(int j = 0; j < length && !sorted; ++j){
		sorted = true;
		for(int i = 0; i < length-1; ++i){
			if(a[i] > a[i+1]){
				sorted = false;
				Swap(a[i], a[i+1]);
			}
		}
	}
}

/**********************************************************************	
* Purpose: Selection sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void selectionSort(container& a, int length){
	int i_max = 0;
	for(int i = length-1; i >= 0; --i){
		// i is the index of the last element of the subarray
		// now, finding the largest element in the index range [0, i]
		i_max = 0; // resetting the max for each subarray
		for(int j = 0; j <= i; ++j){
			if(a[j] > a[i_max]){
				// a[j] is larger than the current max, steal its index for later
				i_max = j;
			}
		}
		Swap(a[i], a[i_max]); // swap the max entry into the last element of the subarray
	}
}

/**********************************************************************	
* Purpose: Insertion sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void insertionSort(container& a, int length){
	int index = -1;
	for(int i = 1; i < length; ++i){
		// sort each subarray from element 0 til element i
		index = i;
		while(index > 0 && a[index-1] > a[index]){
			Swap(a[index], a[index-1]);
			index--;
		}
		
	}
}

/**********************************************************************	
* Purpose: Shell sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*		note: T is the type held by container. i.e. a call to sort a 
*		vector<int> would be shellSort<vector<int>, int>(a, len)
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class T, class container>
void shellSort(container& a, int length){
	// first, determine each step that will be needed
	// steps used were taken from Data Structures and Algorithms in C++ by Adam Drozdek:
	// h_1 = 1; h_{i+1} = 3*h_i + 1
	vector<int> steps;
	for(int h=1; h < length; h=3*h+1){
		steps.push_back(h);
	}

	// variables used in the below loop
	int k;
	T tmp;
	for(vector<int>::reverse_iterator h = steps.rbegin(); h != steps.rend(); ++h){
		for(int hCnt = (*h); hCnt < 2*(*h); ++hCnt){
			// insertion sort
			for(int j = hCnt; j < length; j += (*h)){
				tmp = a[j];
				for(k = j; k >= *h && a[k - *h] > tmp; k -= *h){
					a[k] = a[k - *h];
				}
				a[k] = tmp;
			}
		}
	}
}

/**********************************************************************	
* Purpose: Heap sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void heapSort(container& a, int length){
	// first, heapify the array
	int start = (length-2)/2;
	while(start >= 0){
		heapSiftDown(a, start, length-1);
		--start;
	}

	// now, sort the heap
	while(length-1 > 0){
		Swap(a[length-1], a[0]);
		--length;
		heapSiftDown(a, 0, length-1);
	}
}

/**********************************************************************	
* Purpose: Helper function for heap sort, this function represents the 
*		sifting down the heap portion of the algorithm
*
* Entry: a, the vector/Array to be sorted
*		start, starting index
*		end, end index
*
* Exit: The heap has been sifted for all points below start to end
*
************************************************************************/
template <class container>
void heapSiftDown(container& a, int start, int end){
	int root = start;
	int child = -1;
	int swap = -1;

	while(2*root + 1 <= end){
		child = 2*root+1;
		swap = root;

		if(a[swap] < a[child]){
			swap = child;
		}
		if(child+1 <= end && a[swap] < a[child+1]){
			swap = child+1;
		}
		if(swap != root){
			Swap(a[root], a[swap]);
			root = swap;
		}else{
			return;
		}
	}
}

/**********************************************************************	
* Purpose: Merge sort (and it's helper function merge(), and both 
*		overloaded for all 3 data types)
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class T>
void mergeSort(vector<T>& a, int length){
	if(length != 1){
		// find the midpoint and split the array into halves
		// note: due to / default behavior, if odd length, right will contain 1 more element than left
		vector<T>::iterator middle = a.begin() + length/2;

		vector<T> left(a.begin(), middle);
		vector<T> right(middle, a.end());

		// merge sort each subarray
		mergeSort(left, left.size());
		mergeSort(right, right.size());

		// and finally, merge the two arrays back into a single array
		merge(left, left.size(), right, right.size(), a);
	}else{
		// a 1 element array is sorted
	}
}

template <class T>
void merge(vector<T> const& left, int len_left, vector<T> const& right, int len_right, vector<T>& combined){
	int i_left = 0;
	int i_right = 0;

	// because combined is the whole array being passed in, and all its data is already represented in left, right, zero it out so push_back doesn't push too many things to it
	combined.clear();

	while(i_left < len_left && i_right < len_right){
		if(left[i_left] < right[i_right]){
			combined.push_back(left[i_left]);
			++i_left;
		}else{
			combined.push_back(right[i_right]);
			++i_right;
		}
	}

	// if there are any remaining values (i.e. left and right were diff size), push them to the combined array
	while(i_left < len_left){
		combined.push_back(left[i_left]);
		++i_left;
	}

	while(i_right < len_right){
		combined.push_back(right[i_right]);
		++i_right;
	}
}

template <class T>
void mergeSort(Array<T>& a, int length){
	if(length != 1){
		// find the midpoint and split the array into halves
		// note: due to / default behavior, if odd length, right will contain 1 more element than left
		int middle = length/2;

		Array<T> left(middle, 0);
		Array<T> right(length-middle, 0);
		for(int i=0; i<middle; ++i){
			left[i] = a[i]; 
		}
		for(int i = middle; i<length; ++i){
			right[i-middle] = a[i];
		}

		// merge sort each subarray
		mergeSort(left, middle);
		mergeSort(right, length-middle);

		// and finally, merge the two arrays back into a single array
		merge(left, middle, right, length-middle, a);
	}else{
		// a 1 element array is sorted
	}
}

template <class T>
void merge(Array<T> const& left, int len_left, Array<T> const& right, int len_right, Array<T>& combined){
	int i_left = 0;
	int i_right = 0;
	int index = 0;


	while(i_left < len_left && i_right < len_right){
		if(left[i_left] < right[i_right]){
			combined[index++] = left[i_left];
			++i_left;
		}else{
			combined[index++] = right[i_right];
			++i_right;
		}
	}

	// if there are any remaining values (i.e. left and right were diff size), push them to the combined array
	while(i_left < len_left){
		combined[index++] = left[i_left];
		++i_left;
	}

	while(i_right < len_right){
		combined[index++] = right[i_right];
		++i_right;
	}
}

template <class T>
void mergeSort(T* a, int length){
	if(length != 1){
		// find the midpoint and split the array into halves
		// note: due to / default behavior, if odd length, right will contain 1 more element than left
		int middle = length/2;

		T* left = new T[middle];
		T* right = new T[length-middle];
		for(int i=0; i<middle; ++i){
			left[i] = a[i]; 
		}
		for(int i = middle; i<length; ++i){
			right[i-middle] = a[i];
		}

		// merge sort each subarray
		mergeSort(left, middle);
		mergeSort(right, length-middle);

		// and finally, merge the two arrays back into a single array
		merge(left, middle, right, length-middle, a);

		//clean up
		delete [] left;
		delete [] right;
	}else{
		// a 1 element array is sorted
	}
}

template <class T>
void merge(T* const& left, int len_left, T* const& right, int len_right, T* combined){
	int i_left = 0;
	int i_right = 0;
	int index = 0;

	while(i_left < len_left && i_right < len_right){
		if(left[i_left] < right[i_right]){
			combined[index++] = left[i_left];
			++i_left;
		}else{
			combined[index++] = right[i_right];
			++i_right;
		}
	}

	// if there are any remaining values (i.e. left and right were diff size), push them to the combined array
	while(i_left < len_left){
		combined[index++] = left[i_left];
		++i_left;
	}

	while(i_right < len_right){
		combined[index++] = right[i_right];
		++i_right;
	}
}

/**********************************************************************	
* Purpose: Quick sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container, class T>
void quickSort(container& a, int length){
	quickSort<container, T>(a, 0, length-1);
}

/**********************************************************************	
* Purpose: Recursive function for quick sort, quicksorts a from left 
*		index to right index
*
* Entry: a, the vector/Array to be sorted
*		left, left index
*		right, right index
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container, class T>
void quickSort(container& a, int left, int right){
	int i = left;
	int j = right;
	T pivot = a[(left + right)/2];

	while(i <= j){
		// finding a value larger than the pivot, below the pivot
		while(a[i] < pivot){
			i++;
		}
		// finding a value less than the pivot, above the pivot
		while(a[j] > pivot){
			j--;
		}

		// if the larger value is below the smaller, swap them and "zoom" in via i, j
		if(i <= j){
			Swap(a[i], a[j]);
			++i;
			--j;
		}
	}

	// if there are remaining elements on either side of the pivot, perform a recursive quickSort on each as well
	if(left < j)
		quickSort<container, T>(a, left, j);
	if(i < right)
		quickSort<container, T>(a, i, right);
}

/**********************************************************************	
* Purpose: Gnome sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void gnomeSort(container& a, int length){
	for(int i=1; i<length; ){
		if(a[i] >= a[i-1]){
			++i;
		}else{
			Swap(a[i], a[i-1]);
			if(i > 1){
				--i;
			}else{
				++i;
			}
		}
	}
}

/**********************************************************************	
* Purpose: Shaker sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void shakerSort(container& a, int length){
	int begin = -1;
	int end = length-2;

	bool swapped = true;
	while(swapped){
		swapped = false;

		++begin;

		for(int i = begin; i <= end; ++i){
			if(a[i] > a[i+1]){
				Swap(a[i], a[i+1]);
				swapped = true;
			}
		}
		if(!swapped){
			return;
		}
		--end;
		for(int i = end; i >= begin; --i){
			if(a[i] > a[i+1]){
				Swap(a[i], a[i+1]);
				swapped = true;
			}
		}
	}
}

/**********************************************************************	
* Purpose: Odd-Even sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void oddEvenSort(container& a, int length){
	bool sorted = false;
	while(!sorted){
		sorted = true;
		for(int i=1; i<length-1; i += 2){
			if(a[i] > a[i+1]){
				Swap(a[i],a[i+1]);
				sorted = false;
			}
		}
		for(int i = 0; i<length-1; i+=2){
			if(a[i] > a[i+1]){
				Swap(a[i], a[i+1]);
				sorted = false;
			}
		}
	}
}

/**********************************************************************	
* Purpose: Stooge sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void stoogeSort(container& a, int length){
	stoogeSort(a, 0, length-1);
}

/**********************************************************************	
* Purpose: Recursive stooge sort
*
* Entry: a, the vector/Array to be sorted
*		low, lower index
*		high, higher index
*
* Exit: Performs a step of the stooge sort on a[low], a[high]
*
************************************************************************/
template <class container>
void stoogeSort(container& a, int low, int high){
	if(a[low] > a[high]){
		Swap(a[high], a[low]);
	}

	if(high - low  > 1){
		int tmp = (high - low + 1) / 3;
		stoogeSort(a, low, high-tmp);
		stoogeSort(a, low+tmp, high);
		stoogeSort(a, low, high-tmp);
	}
}

/**********************************************************************	
* Purpose: Binary insertion sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void binaryInsertionSort(container& a, int length){
	int index = -1, left = 0, right = -1;
	for(int i = 0; i < length; ++i){
		// binary search for where to put element i
		left = 0;
		right = i;

		while(left < right){
			index = (left+right) / 2;
			if(a[i]  >= a[index]){
				left = index + 1;
			}else{
				right = index;
			}
		}
		for (int j=i; j>left;--j){
			Swap(a[j-1], a[j]);
		}
	}
}

/**********************************************************************	
* Purpose: Comb sort
*
* Entry: a, the vector/Array to be sorted
*		length, how long a is
*
* Exit: The container a is sorted!
*
************************************************************************/
template <class container>
void combSort(container& a, int length){
	int gap = length;
	bool swapped = false;

	while(gap > 1 || swapped){
		if(gap > 1){
			gap = (int)((double)gap / 1.247330950103979); // refer to wikipedia article for comb sort for explanation of constant
		}else{
			gap = 1; // 1 is smallest gap
		}

		swapped = false;

		for(int i = 0; gap+i < length; ++i){
			if(a[i] > a[i+gap]){
				Swap(a[i], a[i+gap]);
				swapped = true;
			}
		}
	}
}

/**********************************************************************	
* Purpose: Helper function to generate random numbers in range [0,n)
*		Will seed rand() with time(0) if needed.
*
* Entry: n, upper bound for random integer
*
* Exit: Returns random number
*
************************************************************************/
int RNG(int n){
	static bool seeded = false;
	if(!seeded){	
		seeded = true;
		srand(static_cast<unsigned>(time(0)));
	}
	return rand()%n;
}

/**********************************************************************	
* Purpose: Little helper function to swap two elements
*
* Entry: a, first element
*		b, second element
*
* Exit: The elements are swapped
*
************************************************************************/
template <class T>
void Swap(T& a, T& b){
	T c = b;
	b = a;
	a = c;
}