#include <stdio.h>
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  int echo = 0;                                // controls echoing, 0: echo off, 1: echo on
  if(argc > 1 && strcmp("-echo",argv[1])==0) { // turn echoing on via -echo command line option
    echo=1;
  }
printf("BST Demo\n");
printf("Commands:\n");
printf("  print:          shows contents of the tree in reverse sorted order\n");
printf("  clear:          eliminates all elements from the tree\n");
printf("  quit:           exit the program\n");
printf("  add <name>:     inserts the given string into the tree, duplicates ignored\n");
printf("  find <name>:    prints FOUND if the name is in the tree, NOT FOUND otherwise\n");
printf("  preorder:       prints contents of the tree in pre-order which is how it will be saved\n");
printf("  save <file>:    writes the contents of the tree in pre-order to the given file\n");
printf("  load <file>:    clears the current tree and loads the one in the given file\n");
char cmd[128];
bst_t *tree = malloc(sizeof(bst_t));
int *success = malloc(sizeof(int));
bst_init(tree);

while(1){
  printf("BST> ");                 // print prompt
  *success = fscanf(stdin,"%s",cmd); // read a command
  if(*success==EOF){                 // check for end of input
    printf("\n");                   // found end of input
    break;                          // break from loop
  }

  if( strcmp("quit", cmd)==0 ){     // check for exit command
    if(echo){
      printf("quit\n");
    }
    break;                          // break from loop
  }

  else if( strcmp("add", cmd)==0 ){ // insertion
    fscanf(stdin,"%s",cmd);            // read string to insert
    if(echo){
      printf("add %s\n",cmd);
    }

    *success = bst_insert(tree, cmd); // call list function
    if(!*success){                      // check for success
      printf("insert failed\n");
    }
  }


  else if( strcmp("clear", cmd)==0 ){   // clear command
    if(echo){
      printf("clear\n");
    }
    bst_clear(tree);
  }

  else if( strcmp("print", cmd)==0 ){   // print command
    if(echo){
      printf("print\n");
    }
    bst_print_revorder(tree);
  }



  else if(strcmp("find", cmd)==0) {    // find command
    if(echo){
      printf("find ");
    }

    fscanf(stdin,"%s",cmd);
    printf("%s\n",cmd);

    int i = bst_find(tree, cmd);
    if(i==1){
      printf("FOUND \n" );
    }else if (i!=1){
      printf("NOT FOUND\n");
    }
  }

  else if (strcmp("preorder",cmd)==0){
    if(echo){
      printf("preorder\n");
    }
    bst_print_preorder(tree);
  }

  else if (strcmp("load",cmd)==0){
    if(echo){
      printf("load ");
    }

      fscanf(stdin, "%s",cmd);
      //printf("%s\n",cmd);
      bst_load(tree, cmd);
      printf("reached here");
    }

else if(strcmp("save",cmd)==0){    // save command
    if(echo){
      printf("save ");
    }
    fscanf(stdin,"%s",cmd);
    printf("%s\n",cmd);
    bst_save(tree,cmd);

  }
  else{                                 // unknown command
      if(echo){
        printf("%s\n",cmd);
      }
      printf("unknown command '%s'\n",cmd);
    }




}
  return 0;
}
