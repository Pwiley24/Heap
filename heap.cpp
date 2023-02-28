#include <fstream>
#include <iostream>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

void add(int number, int index, int (&heap)[102]);
void swapNums(int &p, int &c, int (&heap)[102]);
void print(int (&hash)[102], int current, int depth);


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
    }
   
    if(heap[102] != NULL){//all slots filled
      print(heap, 1, 0);
    }
  }
  return 0;
}


void add(int number, int index, int (&heap)[102]){
  //add number to the next open index
  //check its parent
  //if greater, swap
  //if less done
  heap[index] = number;
  int parIndex = floor(index/2);

  while(heap[parIndex] < number &&
	parIndex != 0){ //parent is less - must be swapped
    swapNums(parIndex, index, heap);
  }
  
}

void swapNums(int &p, int &c, int (&heap)[102]){
  //switch the parent and child
  int hold;
  hold = heap[p];
  heap[p] = heap[c];
  heap[c] = hold;
}





void print(int (&hash)[102], int current, int depth){
  if((current*2 +1) != NULL){
    print(hash, (current*2 +1), (depth + 1));
  }
  for(int i = 0; i < depth; i++){
    cout << '\t';
  }
  cout << current << endl;

  if((current*2) != NULL){
    print(hash, (current*2), (depth +1));
  }
}

/*
Heap Index:
parent = index/2 (floor)
left child = index*2
right child = index*2+1


 */
