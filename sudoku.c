#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
   int i, j, k, p;
   int visto[10];

   for(i = 0; i < 9; i++)
   {
      for(k = 0; k < 10; k++)
      {
         visto[k] = 0;   
      }
      for(j = 0; j < 9; j++)
      {
         int num = n->sudo[i][j];
         if(num != 0)
         {
            if(visto[num] == 1)
            {
               return 0;
            }
            visto[num] = 1;
         }
      }
   }

   for(j = 0; j < 9; j++)
   {
      for(k = 0; k < 10; k++)
      {
         visto[k] = 0;
      }
      for(i = 0; i < 9; i++)
      {
         int num = n->sudo[i][j];
         if(num != 0)
         {
            if(visto[num] == 1) return 0;
            visto[num] = 1;
         }
      }
   }

   for (k = 0; k < 9; k++) 
   {
      // Inicializar el arreglo de vistos en 0
      for (i = 0; i < 10; i++) 
      {
         visto[i] = 0;
      }
      for (p = 0; p < 9; p++) 
      {
         int row = 3 * (k / 3) + (p / 3);
         int col = 3 * (k % 3) + (p % 3);
         int num = n->sudo[row][col];
         if (num != 0) 
         {
            if (visto[num] == 1) 
            {
               return 0; // Número repetido en la submatriz
            }
            visto[num] = 1;
         }
      }
   }
   return 1;
}



List* get_adj_nodes(Node* n)
{
   List* list=createList();
   for(int i = 0; i < 9; i++)
   {
      for(int j = 0; j < 9; j++)
      {
         if(n->sudo[i][j] == 0)
         {
            for(int x = 1; x < 10; x++)
            {
               Node * new = copy(n);
               new->sudo[i][j] = x;
               if(is_valid(new) == 1)
               {
                  pushBack(list, new);
               }
            }
            return list;
         }
      }
   }
   return list;
}


int is_final(Node* n)
{
   int i, j;
   for(i = 0; i < 9; i++)
      for(j = 0; j < 9; j++)
         if(n->sudo[i][j] == 0) return 0;
   return 1;
}

Node* DFS(Node* initial, int* cont)
{
   Stack * S = createStack();
   push(S, initial);
   while(get_size(S) != 0)
   {
      Node* ini = top(S);
      pop(S);
      if(is_final(ini) == 1) return ini;
      List * adj = get_adj_nodes(ini);
      Node * adjun = first(adj);
      while(adjun)
      {
         push(S, adjun);
         adj = next(adj);
      }   
      free(ini);
      (*cont)++;
   }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/