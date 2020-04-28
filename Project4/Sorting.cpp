#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <ostream>
#include <fstream>

using namespace std;

int comparisons =0;

void insertionSort(int* arr, int size) {
   if(size > 1){
    for(int i = 1; i < size; ++i){
      int j = i - 1;
      int key = arr[i];
      while(j > 0 && arr[j] > key){
		comparisons++;
        arr[j+1] = arr[j];
        j--;
      }
	  if(arr[j] <= key){
		comparisons++;
	  }
	  
      arr[j+1] = key;
    }
  }
}

void merge(int arr[], int min, int max, int mid){
	//sorts two halves of a given array segment
	//precondition: both low to mid and mid+1 to max are sorted
	//postcondition: low to high have been sorted in the given array
	
	int z,y,x;
	int temp[max - min + 1];
	x = min;
	y = mid + 1;
	z = 0;

	//sort each half into temp
	while(x <= mid || y <= max){
		if(x > mid){//no more values in first half
			temp[z] = arr[y];
			z++;
			y++;
		}else if( y > max){//no more values in second half
			temp[z] = arr[x];
			z++;
			x++;
		}else if( arr[x] < arr[y]){//lower index is less than upper index
			comparisons++;
			temp[z] = arr[x];
			z++;
			x++;
		}else{//higher index less than lower index
			comparisons++;
			temp[z] = arr[y];
			z++;
			y++;
		}
	}
	//input temp into the area designated under min -> max
	for(int w=min; w <= max; w++){
		arr[w] = temp[w - min];
	}
	
}

void mergeSort(int arr[], int min, int max){
	//sort given array by divide and conquer and merging
	//precondition: arr points to an array and sorted section is known
	//postcondtion: array is sorted
  int mid = (min + max)/2;
  if((max - min) > 1){
	//create a mid point to divide the array into two separate calls
	//recursive calls via divide and conquer (two halves)
	mergeSort(arr, min, mid);
	mergeSort(arr, mid+1, max);
	//call to merge the current data sorted by the recursive calls
  }
  merge(arr, min, max, mid);
}




//heap stuff
void heapify(int arr[], int n, int i) {
	int temp;
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < n && arr[l] > arr[largest]){
		comparisons++;
		largest = l;
	}
	if (r < n && arr[r] > arr[largest]){
		comparisons++;
		largest = r;	
	}
	if (largest != i) {
		temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		heapify(arr, n, largest);
	}
}

void heapSort(int arr[], int n) {
   int temp;
   for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);
   for (int i = n - 1; i >= 0; i--) {
      temp = arr[0];
      arr[0] = arr[i];
      arr[i] = temp;
      heapify(arr, i, 0);
   }
}

// https://www.geeksforgeeks.org/quicksort-using-random-pivoting/
/* This function takes last element as pivot, places 
  the pivot element at its correct position in sorted 
  array, and places all smaller (smaller than pivot) 
  to left of pivot and all greater elements to right 
  of pivot 
*/ 
int partition(int arr[], int low, int high) 
{ 
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element 
  
    for (int j = low; j <= high - 1; j++) { 
  
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) { 
			comparisons++;
            i++; // increment index of smaller element 
            swap(arr[i], arr[j]); 
        } 
    } 
    swap(arr[i + 1], arr[high]); 
    return (i + 1); 
} 
  
// Generates Random Pivot, swaps pivot with 
// end element and calls the partition function 
int partition_r(int arr[], int low, int high) 
{ 
    // Generate a random number in between 
    // low .. high 
    srand(time(NULL)); 
    int random = low + rand() % (high - low); 
  
    // Swap A[random] with A[high] 
    swap(arr[random], arr[high]); 
  
    return partition(arr, low, high); 
} 
  
/* The main function that implements QuickSort 
arr[] --> Array to be sorted, 
low --> Starting index, 
high --> Ending index */
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) { 
		comparisons++;
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition_r(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 
  
/* Function to print an array */
void printArray(int arr[], int size) 
{ 
    int i; 
    for (i=0; i < size; i++) 
        printf("%d ", arr[i]); 
    printf("\n"); 
}
///end quicksort code



//  https://www.geeksforgeeks.org/radix-sort/
//start radix code
// A utility function to get maximum value in arr[] 
int getMax(int arr[], int n) 
{ 
    int mx = arr[0]; 
    for (int i = 1; i < n; i++) 
        if (arr[i] > mx) 
            mx = arr[i]; 
    return mx; 
} 
  
// A function to do counting sort of arr[] according to 
// the digit represented by exp. 
void countSort(int arr[], int n, int exp) 
{ 
    int output[n]; // output array 
    int i, count[10] = {0}; 
  
    // Store count of occurrences in count[] 
    for (i = 0; i < n; i++) 
        count[ (arr[i]/exp)%10 ]++; 
  
    // Change count[i] so that count[i] now contains actual 
    //  position of this digit in output[] 
    for (i = 1; i < 10; i++) 
        count[i] += count[i - 1]; 
  
    // Build the output array 
    for (i = n - 1; i >= 0; i--) 
    { 
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
        count[ (arr[i]/exp)%10 ]--; 
    } 
  
    // Copy the output array to arr[], so that arr[] now 
    // contains sorted numbers according to current digit 
    for (i = 0; i < n; i++) 
        arr[i] = output[i]; 
} 
  
// The main function to that sorts arr[] of size n using  
// Radix Sort 
void radixSort(int arr[], int n) 
{ 
    // Find the maximum number to know number of digits 
    int m = getMax(arr, n); 
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m/exp > 0; exp *= 10) 
        countSort(arr, n, exp); 
} 



int main(int argc, char** argv){
	int value;
	int sortArry[9999];
	ifstream inFile;
	inFile.open(argv[1]);
	if (!inFile)
    {
        cout << "\nError opening file.\n";
        return 13;
    }
	
	int i = 0;
	while(inFile >>value){
		sortArry[i] = value;
		i++;
	}
	//the array should be filled now
	
	for(int i=0;i<=9999;i++){
		cout << sortArry[i] << endl;
	}
	
	
	bool userInput = false;
	while(!userInput){
		cout << "(i)insertion-sort	(m)merge-sort	(h)heap-sort	(q)quick-sort	(b)bonus-sort\n";
		cout << "Enter the algorithm: ";
		string choice;
		cin >> choice;
		//cout << choice << "\n";//checking if read corectly
		if(choice=="i"){
			insertionSort(sortArry, 10000);
			printArray(sortArry, 10000);
			cout << "#Insertion-sort comparions: " << comparisons << endl;
			return 0;
		}
		else if(choice=="m"){
			mergeSort(sortArry, 0, 9999);
			printArray(sortArry, 10000);
			cout << "#Merge-sort comparions: " << comparisons << endl;
			return 0;
		}
		else if(choice=="h"){
			heapSort(sortArry, 9999);
			for(int i=0;i<9999;i++){
				cout << sortArry[i] << endl;
			}
			cout << "#Heap-sort comparisons: " << comparisons << endl;
			return 0;
		}
		else if(choice=="q"){
			quickSort(sortArry,0,9999);
			printArray(sortArry,10000);
			cout << "#Quick-sort comparisons: " << comparisons << endl;
			return 0;
		}
		else if(choice=="b"){
			//int n = sizeof(sortArry)/sizeof(sortArry[0]);
			radixSort(sortArry, 10000);
			printArray(sortArry,10000);
			return 0;
		}
		else if(choice=="quit"){
			return 0;
		}
		else{
			cout << "ERR: unrecognized user input try again\n";
		}	
	}
		
}