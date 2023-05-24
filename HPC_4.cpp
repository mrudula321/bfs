#include <iostream>
#include <omp.h>
#include <cstdlib>
#define N 10000
using namespace std;

void swap(int * xp, int * yp) {

	 int temp = * xp;
	 * xp = * yp;
	 * yp = temp;
}
void bubbleSort(int arr[], int n) {
	 
	 int i, j;
	 for (i = 0; i < n - 1; i++) {
	 
		for (j = 0; j < n - i - 1; j++) {
		
			if (arr[j] > arr[j + 1])
				
				swap( & arr[j], & arr[j + 1]);
		}
	 }
}


void parallelBubbleSort(int arr[], int n) {
 
	int i, j;
	for (i = 0; i < n - 1; i++) {
	
		#pragma omp parallel for
	
		for (j = 0; j < n - i - 1; j++) {

		if (arr[j] > arr[j + 1])
			
			swap( & arr[j], & arr[j + 1]);
		}
	}
}

void merge(int arr[],int start,int mid,int end){

    int ele1 = mid-start+1;
    int ele2 = end-mid;

    int arr1[ele1],arr2[ele2];

    int i=0,j=0,k=start;

    for(;i<ele1;i++){

        arr1[i] = arr[start+i];
    }

    for(;j<ele2;j++){

        arr2[j] = arr[mid+1+j];
    }


    i=0;
    j=0;

    while(i<ele1 && j<ele2){

        if(arr1[i]<arr2[j]){

            arr[k] =  arr1[i];
            i++;
        }else{

            arr[k] = arr2[j];
            j++;
        }

        k++;
    }

    while(i<ele1){

        arr[k++] = arr1[i++];
    }

    while(j<ele2){

        arr[k++] = arr2[j++];
    }

   
}



void mergeSort(int arr[],int start,int end){

    if(start<end){

        int mid = (start+end)/2;

        mergeSort(arr,start,mid);
        mergeSort(arr,mid+1,end);
        merge(arr,start,mid,end);
    }

}

void parallelMergeSort(int arr[], int start, int end) {

	if (start < end) {
 
	int mid = start + (end - start) / 2;
   	 
    	#pragma omp parallel sections num_threads(2) 
    	{

        	#pragma omp section
        	{
            	parallelMergeSort(arr,start,mid);   	 
        	}

        	#pragma omp section
        	{
            	parallelMergeSort(arr,mid+1,end);    
        	}
    	}

    	merge(arr,start,mid,end);    
    	
    }
  
    
   
   /*
	if(start<end){
    	
    	int mid=start+(end-start)/2;
   	 
        #pragma omp task
 
       parallelMergeSort(arr, mid + 1, end);
 
       #pragma omp taskwait

       merge(arr, start, mid, end);
    }
   
*/	


}


int main() {
 
 int arr[N];
 
 for (int i = 0; i < N; i++)
	arr[i] = rand() % N + 1;

 double start, end;

 start = omp_get_wtime();
 bubbleSort(arr, N);
 end = omp_get_wtime();
 
 cout << "Sequential bubble sort time: " << end - start << endl;
 
 for (int i = 0; i < N; i++)
	arr[i] = rand() % N + 1;
 
 start = omp_get_wtime();
 parallelBubbleSort(arr, N);
 end = omp_get_wtime();
 
 cout << "Parallel bubble sort time: " << end - start << endl;

 for (int i = 0; i < N; i++)
	arr[i] = rand() % N + 1;
 
 start = omp_get_wtime();
 mergeSort(arr, 0, N - 1);
 end = omp_get_wtime();
 
 cout << "Sequential merge sort time: " << end - start << endl;
 
 for (int i = 0; i < N; i++)
	arr[i] = rand() % N + 1;
 
 start = omp_get_wtime();
 parallelMergeSort(arr, 0, N - 1);
 end = omp_get_wtime();
 
 cout << "Parallel merge sort time: " << end - start << endl;
 
 return 0;
}
