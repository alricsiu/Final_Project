//NAME: APRIL MARIE JONES
//CLASS: CIS22C, GARBACEA
//DATE: June 19, 2014
//COMPILER: MICROSOFT VISUAL STUDIO 2010 EXPRESS AND WINDOWS XP
//TITLE: TEAM PROJECT, TEAM #13, HEAP FOR SEARCHING OF MOBILE APPS DATA
#pragma once
using namespace std;

#ifndef Final_Heap_h
#define  Final_Heap_h

class Heap
{
    struct Data
    {
        int num=0;
        int frequency=0;
    };
    
private:
	Data *maxHeap;						//an array of Apps that will be a max heap
	int count;							//the number of elements in the heap
	static const int MAXSIZE = 31;		//the maximum size allowed for the heap
	
public:
	Heap(void);
	~Heap(void);

    bool insert(int key);
	void displayHeap() const;
	void displayTop() const;
};

#endif
/*
	bool remove();
	void heapCreate();
	void heapRebuild(int index);
	bool isALeaf(int index);
	*/