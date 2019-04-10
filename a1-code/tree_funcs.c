#include <string.h>
#include "tree.h"
// Initialize the given tree to have a null root and have size 0.
void bst_init(bst_t *tree){
    tree->root = NULL;

    //tree->size = malloc(sizeof(int));
    tree->size = 0;
}


int bst_insert(bst_t *tree, char name[]){
// Inserts given name into a binary search tree. Uses an ITERATIVE
// (loopy) approach to insertion which starts a pointer at the root of
// the tree and changes its location until the correct insertion point
// is located. Returns 1 if a new node is created and 0 if a duplicate
// name is found in the tree already in which case the name is not
// added.
if(tree->root == NULL){
  //make new node here, root isn't Initialized yet
  node_t *newnode = malloc(sizeof(node_t));
  strcpy(newnode->name, name);
  newnode->left = NULL;
  newnode->right = NULL;
  tree->root = newnode;
  tree->size+=1;
  return 1;
  free(newnode);
}
//if the charactert has already been iserted, fails
 if(bst_find(tree, name)==1){
   return 0;
 }
  node_t *insert = malloc(sizeof(node_t));
  insert = tree->root;
  while(1){
    //new node, nothing further right and nothing smaller.
    if(insert->right==NULL&&strcmp(insert->name,name)<0){
      node_t *new = malloc(sizeof(node_t));
      strcpy(new->name,name);
      new->left = NULL;
      new->right = NULL;
      insert->right = new;
    //  printf("->right->name = %s\n",insert->right->name);
      tree->size++;
    //  printf("%d\n",tree->size);

      return 1;
      free(new);
    }
    else if(insert->left==NULL && strcmp(insert->name,name)>0){
      node_t *new = malloc(sizeof(node_t));
      strcpy(new->name,name);
      //printf("added %s to new's name!\n", name);
      new->left = NULL;
      new->right = NULL;
      insert->left = new;
    //  printf("insert->left->name = %s\n",insert->left->name);
      tree->size++;
    //  printf("%d\n",tree->size);
    //
      return 1;
      free(new);
    }

     if(strcmp(insert->name, name)>0){
         insert = insert->left;
         //printf("\n\nnreached here(left)!!!\n\n");
     }
     else if(strcmp(insert->name,name)<0){
     insert = insert->right;
      //printf("\n\nreached here(right)!!\n\n");
   }
}
}


int bst_find(bst_t *tree, char name[]){
// Determines whether name is present or not in the tree using binary
// search. Returns 1 if name is present and 0 otherwise. Uses an
// ITERATIVE (loopy) approach which starts a pointer at the root of
// the tree and changes it until the search name is found or
// determined to not be in the tree.
node_t *node =  malloc(sizeof(node_t));
node = tree->root;
while(node!=NULL){
  //if node is found
  if(strcmp(name,node->name)==0){

  return 1;
  free(node);
  }
  //go left
  else if(strcmp(name,node->name)<0){
      node = node->left;
  }
//go right
  else if(strcmp(name,node->name)>0){
    node = node->right;
  }
}

free(node);
return 0;

}

void bst_clear(bst_t *tree){
// Eliminate all nodes in the tree setting its contents empty. Uses
// recursive node_remove_all() function to free memory for all nodes.
node_t *cur = malloc(sizeof(node_t));
//this function does all the work
node_remove_all(cur);
tree->root = NULL;
tree->size = 0;
return;
free(cur);
}

void node_remove_all(node_t *cur){
// Recursive helper function which visits all nodes in a tree and
// frees the memory associated with them. This requires a post-order
// traversal: visit left tree, visit right tree, then free the cur
//frees node, nothing left after it.
if(cur->left == NULL){
  node_t *freeit = cur;
  cur = cur->left;
  free(freeit);
}
//frees node, noting after it
  else if (cur->right == NULL){
    node_t *freeit = cur;
    cur = cur->right;
    free(freeit);
  }
  //go left
  else if(cur->left != NULL){
    node_remove_all(cur->left);
  }
  //go right
  else if (cur->right != NULL){
    node_remove_all(cur->right);
  }

}


void bst_print_revorder(bst_t *tree){
// Prints the elements of the tree in reverse order at differing
// levels of indentation which shows all elements and their structure
// in the tree. Visually the tree can be rotated clockwise to see its
// structure.

node_t *node = malloc(sizeof(node_t));
printf("%s", node->name);
//if empty
if(tree->root==NULL){
  return;
}
//creates pointer for helper function
node = tree->root;
node_print_revorder(node, 0);

}

void node_print_revorder(node_t *cur, int indent){
// Recursive helper function which prints all elements in the tree
// rooted at cur in reverse order: traverses right subtree, prints cur
// node, traverses left tree. Parameter 'indent' indicates how far to
// indent (2 spaces per indent level)

//reached end, stop
      if(cur==NULL){
        return;
      }
      //go right, adds to index
     node_print_revorder(cur->right,indent+1);
     for(int x = indent; x>0; x--){
       printf("  ");
     }
     printf("%s\n",cur->name);
     // go left, also adds to index
     node_print_revorder(cur->left, indent+1);


}

void bst_print_preorder(bst_t *tree){
  // Print all the data in the tree in pre-order with indentation
  // corresponding to the depth of the tree. Makes use of
  // node_write_preorder() for this.
  node_t *node = malloc(sizeof(node_t));
  node = tree->root;
  //treee is emptyyy
  if(tree->root==NULL){
    return;
  }
  //calls helper
  node_write_preorder(node, stdout, 0);
  return;
}

void bst_save(bst_t *tree, char *fname){
// Saves the tree by opening the named file, writing the tree to it in
// pre-order with node_write_preorder(), then closing the file.
node_t *node = malloc(sizeof(node_t));
node = tree->root;
FILE *f;
f = fopen(fname,"w");

//calls helper after file has been opened
node_write_preorder(node, f,0);
}


void node_write_preorder(node_t *cur, FILE *out, int depth){
// Recursive helper function which writes/prints the tree in pre-order
// to the given open file handle. The parameter depth gives how far to
// indent node data, 2 spaces per unit depth. Depth increases by 1 on
// each recursive call. The function prints the cur node data,
// traverses the left tree, then traverses the right tree.
//if reached end
  if(cur==NULL){
        return;
  }
  for( int x =depth; x>0; x--){
    fprintf(out,"  ");
  }
    fprintf(out,"%s\n", cur->name);
//go left, then right
      node_write_preorder(cur->left,out,depth+1);
      node_write_preorder(cur->right,out,depth+1);
return;
free(cur);
fclose(out);
}

int bst_load(bst_t *tree, char *fname ){
  int count;
  count= 0;
  bst_clear(tree);
  FILE *open;
//opens a file and checks for NULL
  open = fopen(fname,"r");
  if(open==NULL){
    return 0;
    fclose(open);
  }
//counts length of file
  while(fscanf(open,"%*d")!=EOF){
    count+=1;
  }
  //malloc's array and adds to loadArray, prints loadArray
    char *loadArray = malloc(count*sizeof(char));
    rewind(open);
    for(int i = 0; i<count; i++){
      fscanf(open, "%s", loadArray);
      printf(" %s\n",&loadArray[i]);
    }
return 1;
  fclose(open);


}
