/*
 Name: Kevin Qian
 Lab: COEN 12 - Project 4
 Time: T 2:15 - 5:00
 Summary: This program implements a radix sort algorithm to sort a collection of given non-negative integers.
 */

#include<stdlib.h>
#include<stdio.h> 
#include"deque.h"
#include<stdbool.h>
#include<assert.h>
#include<math.h>
// r is the base number of unique digits, also known as the radix
#define r 10
int main(void)
{
	int input; 	
	int max=0;

	DEQUE *list = createDeque();
	DEQUE *array[r];
	while(scanf("%d", &input)==1)
	{	
		if(input<0)
		{
            //makes sure input is a non-negative integer
			printf("%d is not a non-negative integer\n", input);
			break;
		}
		else
		{
            //Adds integer into main deque and updates the largest input number
		 	addLast(list, input);
			if (input > max)
			    max = input;
		}
		
	}
	for(int i=0; i<r; i++)
	{
		array[i] = createDeque(); //Creating an array of deques
	}
	int iterations = ceil(log(max+1)/log(r)); //algorithm to determine number of iterations for radix sort
	int totalNums = numItems(list); 
	int temp;
	int div=1; // used to change digit in number in main deque
	int index;
	for(int i =0; i<iterations; i++) //goes through loop of sorting deques
	{
		while(totalNums-- >0)
		{
			temp = removeFirst(list);
			index =((temp/div)%10);	
			addLast(array[index],temp); //adds to specific digit deque
		}

		for (int j=0; j<r; j++)
		{
            //makes sure deque is not empty and adds sorted items to main deque
			while(numItems(array[j])!=0)
				addLast(list,removeFirst(array[j]));
		}
        //to help move to next digit placement
		div = div*10; 
	}
    
    //Prints out sorted main deque after radix sort
	while (numItems(list)>0)
	{
		printf("%d\n", removeFirst(list));
	}
    
    //Destroy deque and list 
	for(int i=0;i<r;i++)
	{
		destroyDeque(array[i]);
	}
	
	destroyDeque(list); 
}	
