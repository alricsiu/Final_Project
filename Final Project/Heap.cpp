//NAME: APRIL MARIE JONES
//CLASS: CIS22C, GARBACEA
//DATE: June 19, 2014
//COMPILER: MICROSOFT VISUAL STUDIO 2010 EXPRESS AND WINDOWS XP
//TITLE: TEAM PROJECT, TEAM #13, HEAP FOR SEARCHING OF MOBILE APPS DATA
#include "Heap.h"
#include <iostream>

//*********************************************************************************************************************
//Constructor: Allocates for a new maxHeap array and initializes the count
//*********************************************************************************************************************
Heap::Heap()
{
    size = MAXSIZE;
	maxHeap = new Data[size];			//allocate for a new array
	count = 0;								//initialize the count to zero
}
Heap::Heap(int size)
{
    this->size = size;
	maxHeap = new Data[this->size];			//allocate for a new array
	count = 0;								//initialize the count to zero
}

//*********************************************************************************************************************
//Destructor: Deletes the maxheap array.
//*********************************************************************************************************************
Heap::~Heap(void)
{
	delete [] maxHeap;
}

//*********************************************************************************************************************
//Insert: inserts the data of the mobile app into the heap and organizes it to a maxheap by the value of the frequency.  
//If it is successful in inserting it will return true, otherwise it will return false.
//*********************************************************************************************************************
bool Heap::insert(int newData)
{
	int parentIndex;							//the index of the parent for the new element
	Data temp1, temp2;							//temporary Data structs for swapping
    Data buffer;
    buffer.num = newData;
	maxHeap[count] = buffer;					//set the newData to be the last leaf on the heap
	int newIndex = count;						//initialize the new index to be the current count in the heap
	bool inPlace = false;						//a flag to see if the data is in the right place
	bool isDuplicate = false;					//a flag to see if a duplicate number is already in the heap
	
	if ( count >= size )						//if the count is greater than or equal to the maxsize, do not insert to the heap
	{
//		cout << "The heap is full and the new data cannot be added.";
        reHeap();
		return false;							//return before inserting
	}

	for (int d = 0; d <= count && isDuplicate == false; d++)	//traverse the heap to see if the number has already been inserted
	{
		if( maxHeap[d].num == maxHeap[newIndex].num )	//compare unique keys
		{
			if ( maxHeap[d].frequency > 0 )				
			{
				maxHeap[d].frequency++;					//if the number is in the heap already, increment that element's frequency
				isDuplicate = true;
				
				//move the existing data to the correct index
				while ( (d > 0) && !inPlace )			//while the index has not found its place yet
				{
					parentIndex = (d - 1) / 2;			//to find the parent index, start will this index number
					if ( maxHeap[d].frequency < maxHeap[parentIndex].frequency )	//compare the unique keys
						inPlace = true;
					else
					{
						temp1 = maxHeap[d];				//set the temp Data structs and swap elements parentIndex and the index
						temp2 = maxHeap[parentIndex];
						maxHeap[parentIndex] = temp1;
						maxHeap[d] = temp2;
						d = parentIndex;				//reset the index to be tested thru the loop again
					}//end else
				}//end while
			}//end if
		}//end if
	}//end for
	
	if(maxHeap[newIndex].frequency == 0 && isDuplicate == false)	//if the number is not in the heap yet, increment the frequency
	{
		maxHeap[newIndex].frequency++;
		
		//move the new data to the correct index
		while ( (newIndex > 0) && !inPlace )			//while the new index has not found its place yet
		{
			parentIndex = (newIndex - 1) / 2;			//to find the parent index, start will this index number
			if ( maxHeap[newIndex].frequency < maxHeap[parentIndex].frequency )	//compare the unique keys
				inPlace = true;
			else
			{
				temp1 = maxHeap[newIndex];				//set the temp Data structs and swap elements parentIndex and newIndex
				temp2 = maxHeap[parentIndex];
				maxHeap[parentIndex] = temp1;
				maxHeap[newIndex] = temp2;
				newIndex = parentIndex;					//reset the newIndex to be tested thru the loop again
			}//end else
		}//end while
	}//end if
	
	count++;											//increment the count for the heap
	return true;
}

//*********************************************************************************************************************
//displayHeap: It will display how many searches have been done.  It will aslo display the unique key and 
//search frequency of each element of the heap.
//*********************************************************************************************************************
void Heap::displayHeap() const
{
	cout << "\nThere have been " << count << " search(es) thus far.\nThese are the content(s) of the maxheap array :\n";
	for (int j = 0; j < count; j++)
	{
		cout << "index " << j << ": " << maxHeap[j].num;
		if (maxHeap[j].frequency > 0)
			cout << " has been searched for " << (maxHeap[j].frequency) << " time(s).\n";
		else
			cout << endl;
	}
}

void Heap::reHeap()
{
    
    Data *remaxHeap = new Data[size*2];
    cout<<"reheaped";
    size = size*2;
    
    for(int i = 0; i<size;i++)
    {
        remaxHeap[i] = maxHeap[i];
    }
    
 	maxHeap = remaxHeap;			//allocate for a new array
    
}

//*********************************************************************************************************************
//displayTop:  It will display the unique key and frequency of element at the top of the heap.
//*********************************************************************************************************************
void Heap::displayTop() const
{
    if(count == 0)
    {
        cout<<"\n\tPlease first perform a search."<<endl;
    }
    else
    {
	cout << "\n\tThe most frequently searched Unique Key is " << maxHeap[0].num
		<< ".\n\tIt has been searched for " << maxHeap[0].frequency << " time(s).\n";
    }
}