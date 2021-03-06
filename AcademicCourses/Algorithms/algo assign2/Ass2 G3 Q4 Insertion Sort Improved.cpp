#include<iostream>
using namespace std;

/*Question 4. Write an algorithm to implement the improved insertion sort where it takes the help of binary search to find the insertion place.
Test Case:
    int *a = new int[10];
    for(int i=0; i<10; i++)
        a[i]=20-i;
    cout<<"Initial Sequence:\n";
    for(int i=0; i<10; i++)
        cout<<a[i]<<" ";
    InsertionSort(a, 10);
    cout<<"\nSorted Sequence:\n";
    for(int i=0; i<10; i++)
        cout<<a[i]<<" ";
    cout<<"\n";
    delete[] a;
Output:
    Initial Sequence:
    20 19 18 17 16 15 14 13 12 11
    Sorted Sequence:
    11 12 13 14 15 16 17 18 19 20
Test Case:
    int *a = new int[10];
    for(int i=0; i<10; i++)
        a[i]=20+i;
    cout<<"Initial Sequence:\n";
    for(int i=0; i<10; i++)
        cout<<a[i]<<" ";
    InsertionSort(a, 10);
    cout<<"\nSorted Sequence:\n";
    for(int i=0; i<10; i++)
        cout<<a[i]<<" ";
    cout<<"\n";
    delete[] a;
Output:
    Initial Sequence:
    20 21 22 23 24 25 26 27 28 29
    Sorted Sequence:
    20 21 22 23 24 25 26 27 28 29	
*/
//a: is pointer to array
//ind: is index of a such that from 0 to a, list is already sorted
//item: new item for which insertion index would be returned
//returns index such that if item is inserted in a[index], from 0 to ind+1 will be sorted.
int findIndexInLnN(int *a, int ind, int item){
	int beg=0, end=ind, mid;
	while(beg!=end){
		mid = (beg+end)/2;
		if(a[mid] == item)
			return mid;
		else if(a[mid] < item)
			beg = (mid==ind)?ind:mid+1;
		else
			end = (mid!=0)?mid-1:0;
	}
	if(a[beg]<item)
		beg++;
	return beg;
}
void InsertionSort(int *a, int n){
	int item, pos;
	for(int i=1; i<n; i++){//0th index element already sorted, so i <- 1 to n-1
	    cout<<i<<" sorted are: ";
	    for(int z=0; z<i; z++)
            cout<<a[z]<<" ";
		item = a[i];
		pos = findIndexInLnN(a, i-1, item);
        cout<<". Inserting "<<item<<" at "<<pos<<"\n";
		for(int j=i; j>pos ; j--)
			a[j] = a[j-1];
		a[pos]=item;
	}
}