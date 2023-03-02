/*
 * This program creates a max heap to store up to 100 integers.
 * Author: Paige Wiley
 * Date: 3-2-23 
 */

#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

void add(int number, int index, int (&heap)[102]);
void swapNums(int &p, int &c, int (&heap)[102]);
void print(int (&hash)[102], int current, int depth);
void deleteRoot(int (&heap)[102]);
void deleteAll(int (&heap)[102]);
void swapDown(int (&heap)[102], int parent); 

int main(){
  int heap[102]; //initial my heap
  char command[10];
  int index = 0;
  bool running = true;

  
  //initialize all heap values to NULL:
  for(int i = 0; i < 102; i++){
    heap[i] = NULL;
  }

  while(running){
  
    cout << "Enter a command (ADD, DELETE, QUIT):" << endl;
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
	cin.get(fileName, 50);
	cin.ignore(50, '\n');
	
	vector<int> fileNums;
	
	ifstream file(fileName);
	if(file.is_open()){
	  int a;
	  while(file >> a){
	    fileNums.push_back(a);
	  }
	  file.close();
	}else{
	  cout << "File could not be opened!" << endl;
	}

	vector<int>::iterator ptr;
	for(ptr = fileNums.begin(); ptr < fileNums.end(); ptr++){
	  for(int i = 0; i < 102; i++){
	    if(heap[i] == NULL &&
	       i != 0){
	      index = i;
	      break;
	    }
	  }
	  add((*ptr), index, heap);
	}

      }else if(strcmp(command, "NUMBER") == 0){ //adding number
	int number;
	cout << "Enter a number:" << endl;
	cin >> number;
	cin.ignore(10, '\n');
		
	//find index number:
	for(int i = 0; i < 102; i++){//find next open spot
	  if(heap[i] == NULL &&
	     i != 0){
	    index = i; //don't include 0
	    break;
	  }
	}
	cout << "index: " << index << endl;
	add(number, index, heap);
      }

    }else if(strcmp(command, "DELETE") == 0){ //deleting numbers
      cout << "Delete ROOT or ALL?" << endl;
      cin.get(command, 10);
      cin.ignore(10, '\n');

      if(strcmp(command, "ROOT") == 0){ //deleting the root 
	deleteRoot(heap);
      }else if(strcmp(command, "ALL") == 0){ //deleting all
	deleteAll(heap);
      }
    }else if(strcmp(command, "QUIT") == 0){ //quit program
      running = false;
    }
   
    if(heap[102] != NULL){//all slots filled
      print(heap, 1, 0);
    }
  }
  return 0;
}


void deleteRoot(int (&heap)[102]){
  int lastIndex;
  for(int i = 1; i < 102; i++){
    if(heap[i] == NULL){ //reached end of heap
      lastIndex = i-1;
    }
  }
  cout << "Deleting... " << heap[1] << endl;
  //swap last index value with first
  heap[1] = heap[lastIndex];

  //check up tree
  swapDown(heap, 1);
}

void swapDown(int (&heap)[102], int parent){
  //find largest child
  int childIndex;
  bool left = false;
  if(heap[parent*2] > heap[parent*2 +1]){ //left is larger
    childIndex = parent*2;
    left = true;
  }else{ //right is larger
    childIndex = parent*2 +1;
  }

  //check if parent is larger
  if(heap[parent] < heap[childIndex]){ //parent needs to swap
    int hold;
    hold = heap[parent];
    heap[parent] = heap[childIndex];
    heap[childIndex] = hold;

    if(childIndex*2 < 102 &&
       childIndex*2 != NULL &&
       left == true){
      swapDown(heap, childIndex);
    }else if(childIndex*2+1 < 102 &&
	     childIndex*2+1 != NULL &&
	     left != true){ 
      swapDown(heap, childIndex);
    }
  }
}

void deleteAll(int (&heap)[102]){
  for(int i = 0; i < 102; i++){
    cout << "Deleting... " << heap[i] << endl;
    heap[i] = NULL;
  }
}

    

void add(int number, int index, int (&heap)[102]){
  //add number to the next open index
  //check its parent
  //if greater, swap
  //if less done
  heap[index] = number;
  int parIndex = floor(index/2);
  swapNums(parIndex, index, heap);
}

void swapNums(int &p, int &c, int (&heap)[102]){
  if(heap[p] < heap[c] &&
     heap[p] != 0){ //parent is less than child
    int hold;
    hold = heap[p]; //parent value
    heap[p] = heap[c]; //parent value equals the child
    heap[c] = hold; //child value equals the parent

    //find the parent of the new parent 
    int newP = floor(p/2);
    cout << "old parent " << p << endl;
    cout << "new parent " << newP << endl;
    if(heap[p] != 0){ //not at the first index
      cout << "recursion" << endl;
      swapNums(newP, p, heap);
    }
  }
}





void print(int (&hash)[102], int current, int depth){
  if(hash[current*2 +1] != NULL &&
     current < 50){
    print(hash, (current*2 +1), (depth + 1));
  }
  for(int i = 0; i < depth; i++){
    cout << '\t';
  }
  cout << hash[current] << endl;

  if(hash[current*2] != NULL &&
     current < 50){
    print(hash, (current*2), (depth +1));
  }
}



