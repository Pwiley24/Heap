#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

void add(int number, int index, int (&heap)[100]);
void swapNums(int &p, int &c, int (&heap)[100]);
void print(int (&hash)[100]);


int main(){
  int heap[100]; //initial my heap
  char command[10];
  int index;
  bool running;

  
  //initialize all heap values to NULL:
  for(int i = 0; i < 100; i++){
    heap[i] = NULL;
  }

  while(running){
  
    cout << "Enter a command:" << endl;
    cin.get(command, 10);
    cin.ignore(10, '\n');

    if(strcmp(command, "ADD") == 0){ //Adding something to heap
      //check if it's a file or number:
      cout << "Adding a FILE or NUMBER?" << endl;
      cin.get(command, 10);
      cin.ignore(10, '\n');
      if(strcmp(command, "FILE") == 0){//adding a file
	//create a vector of ints
	//read in file and add to vector
	//iterate through vector and add to heap
	char fileName[50];
	cout << "What is the name of the file?" << endl;
	cin.get(file, 50);
	cin.ignore(50, '\n');
	
	vector<int> fileNums;
	ifstream file(fileName);
	
      
      }else if(strcmp(command, "NUMBER") == 0){ //adding number
	int number;
	cout << "Enter a number:" << endl;
	cin >> number;
	cin.ignore(10, '\n');
		
	//find index number:
	for(int i = 0; i < 100; i++){//find next open spot
	  if(heap[i] == NULL &&
	     i != 0){
	    index = i; //don't include 0
	    break;
	  }
	}
	cout << "index: " << index << endl;
	add(number, index, heap);
      }
    }
    if(heap[100] != NULL){//all slots filled
      print(heap);
    }
  }
  return 0;
}


void add(int number, int index, int (&heap)[100]){
  //add number to the next open index
  //check its parent
  //if greater, swap
  //if less done
  heap[index] = number;
  int parIndex = floor(index/2);
  cout << "parIndex: " << parIndex << endl;

  while(heap[parIndex] < number &&
	parIndex != 0){ //parent is less - must be swapped
    swapNums(parIndex, index, heap);
  }
  
}

void swapNums(int &p, int &c, int (&heap)[100]){
  //switch the parent and child
  int hold;
  hold = heap[p];
  heap[p] = heap[c];
  heap[c] = hold;
}



void print(int (&hash)[100]){
  for(int i = 0; i < 100; i++){
    cout << hash[i] << endl;
  }
}

/*
Heap Index:
parent = index/2 (floor)
left child = index*2
right child = index*2+1


 */
