#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"
#include <sys/stat.h>
int *read_text_deltas(char *fname, int *len){
  FILE *file;
  file = fopen(fname, "r");
//checks if file is null
    if(file == NULL){
      *len = -1;
      return NULL;
      fclose(file);
    }

  //this loop counts the number of ints in the file and adds them to the int count
  int count = 0;

    while(fscanf(file, "%*d")!=EOF){
      count++;
    }
    *len = count;
  rewind(file);
  //this checks if the file is a ridiculous size.
    if(count <=0){
	fclose(file);
      *len = -1;
      return NULL;
    }
  //Declares intArray (array that we will eventually return) along with helper int y and mallocs memory.
  int *intArray;
  intArray = malloc(*len*sizeof(int));
  int y;
  //this for(if/else) loop adds the deltas to intArray and does the "delta"-ing math with y.
    for(int x = 0; x<count; x++){
      if(x == 0){
        fscanf(file, "%d", &intArray[x]);
      }
      else{
        y = intArray[x-1];
        fscanf(file, "%d", &intArray[x]);
        y = intArray[x] + y;
        intArray[x] = y;
      }
      }
    //this gets rid of memory leaks  and ends the program.
    fclose(file);
    *len = count;
    return intArray;
    free(intArray);
}

int *read_int_deltas(char *fname, int *len){

//checks for null files, returns -1.
struct stat sb;
 // unix system call to determine size of named file
  int result = stat(fname, &sb);
  // if something went wrong or bail if file is too small
    if(result==-1 || sb.st_size < sizeof(int)){
      *len = -1;
    //  free(len);
      return NULL;
    }



//makes ptr file, and derefs len make it the size/sizeof(int).
*len = sb.st_size;
*len = *len/sizeof(int);
FILE *file;
file = fopen(fname, "r");
//creates the ptr to the array that we'll be storing our deltas in
int *intArray;
intArray = malloc(*len*sizeof(int));

//for loop that adds ints to intarray while computing deltas.
  for(int x = 0; x<*len; x++){
    if(x == 0){
      fread(&intArray[x], sizeof(int), 1, file);
    }else{
      int y = intArray[x-1];
      fread(&intArray[x], sizeof(int), 1, file);
      y = intArray[x] + y;
      intArray[x] = y;
    }
}

//prevents memory leaks
fclose(file);
return intArray;
free(intArray);
}
