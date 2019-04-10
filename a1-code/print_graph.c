
#include <stdio.h>
#include <math.h>
void printHeader(int len);
void bottomAxisNum(int len);
void main_body (int *data, int len, int max_height);
void print_graph(int *data, int len, int max_height);
int getLength(char *fname, int *len);
int min;
int max;
int range;
float units_per_height;

// Prints a graph of the values in data which is an array of integers
// that has len elements. The max_height argument is the height in
// character rows that the maximum number data[] should be.  A sample
// graph is as follows:
//
// length: 50
// min: 13
// max: 996
// range: 983
// max_height: 10
// units_per_height: 98.30
//      +----+----+----+----+----+----+----+----+----+----
// 996 |                X
// 897 |       X        X X            X
// 799 |  X    X X   X  X X    X       X                X
// 701 |  XX   X X   X  XXX    X      XX   XXX    X   X XX
// 602 |  XX   X X  XX  XXX X  X      XX  XXXX    XX  X XX
// 504 |  XX   XXX  XX  XXX XX X      XXX XXXX XX XX  X XX
// 406 |  XX X XXX XXXX XXX XX X  XXX XXX XXXXXXXXXX  X XX
// 307 | XXX X XXX XXXXXXXXXXX X XXXX XXXXXXXXXXXXXXX X XX
// 209 | XXX XXXXXXXXXXXXXXXXX XXXXXX XXXXXXXXXXXXXXXXX XX
// 111 | XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  13 |XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//      +----+----+----+----+----+----+----+----+----+----
//      0    5    10   15   20   25   30   35   40   45
//called here so c doesnt cry
 void compute_vals(int *data, int len, int max_height);

 //my main print function that calls all helper functions
 void print_graph(int *data, int len, int max_height){

compute_vals(data,len, max_height);
printf("length: %d\nmin: %d\nmax: %d\nrange: %d\nmax_height: %d\nunits_per_height: %.2f\n",len, min, max,range,max_height, units_per_height );
printHeader(len);
main_body(data, len, max_height);
bottomAxisNum(len);


 }

 //helper function that creates the top and bottom lines of print_graph_data
void printHeader(int len){
 printf("     "); //just the first five spaces, ya know
 for(int x = 0; x<len; x++){
  if(x%5 != 0){
    printf("-");
  }
  else{
    printf("+");
  }
 }
 printf("\n"); // this enters so the next line is below
}

//helper function that calls printHeader to make a line and numbers below.
void bottomAxisNum(int len){
  printHeader(len);
  printf("     ");
  for(int x = 0; x < len; x++){
    if(x%5 == 0){
      printf("%-5d", x);
    }
  }
  printf("\n"); // this enters so the next line is below
}

void compute_vals(int *data, int len, int max_height){
  //this determines the minimum and maximum values.
  //min is used to compute the int cutoff (i cutoff)
  //max is used to compute units_per_height
    min = data[0];
    max = data[0];
  for(int x = 1; x< len; x++){
    if(data[x]> max){
      max = data[x];
    }else if(data[x]< min){
      min = data[x];
    }
  }
  range = max-min;

  //computing units_per_height
  units_per_height = (float)range/(float)(max_height);

}

//function that creates the main body of our graph.
void main_body (int *data, int len, int max_height){
//finally writing out the data on the inside!
//the first for loop only checks if it should be
for(int x = max_height; x>=0; x--){
  int icutoff = (int)(min + x * units_per_height);

  //the second for loop goes through to check if the array
  //meets the cutoff req. for an x.
  printf("%3d |", icutoff);
// place is the last place in the array that we looped through.
  for(int y = 0; y<len; y++){
    if(data[y]<icutoff){
      printf(" ");
    }else{
      printf("X");
    }
  }
  printf("\n");
}
}
