#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deltas.h"

// prototype for print_graph() function
void print_graph(int *data, int len, int max_height);
int main(int argc, char *argv[]){
//so argv[] is the characters after your initial call!! NOW I know cus'this lab taught me
  char *max_height = argv[3];
  char *format = argv[1];
  char *fname= argv[2];

  int data_len = -1;
  int *data_vals = NULL;
//if its found that text integers are input, then runs read text dektas and prints graph according to output.
  if( strcmp("text", format)==0 ){
    data_vals = read_text_deltas(fname, &data_len);
    printf("Reading text format\n");
    print_graph(data_vals, data_len, atoi(max_height));
  }

  //reads stdin, calls read int deltas and prints graph accordingto read int deltas output
  if( strcmp("int", format)==0 ){
    printf("Reading binary int format\n");
    data_vals = read_int_deltas(fname, &data_len);
    print_graph(data_vals, data_len, atoi(max_height));
  }
free(data_vals);
return 0;
}
