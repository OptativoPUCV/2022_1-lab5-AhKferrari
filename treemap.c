#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

  TreeMap * nuevo = (TreeMap *)malloc(sizeof(TreeMap));
  nuevo->root = NULL;
  nuevo->current = NULL;
  nuevo->lower_than = lower_than;
  return nuevo;
  
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {

  if(tree == NULL)return;
  
  TreeNode * aux = tree->root;
  TreeNode * padre = NULL;

  while(aux){
    padre = aux;
    if(tree->lower_than(key, aux->pair->key) == 1)
    aux = aux->left;
    
   
    else{
      (tree->lower_than( aux->pair->key, key) == 1);
    aux = aux->right;
    }
    //return; 
  }

  TreeNode * nodo = createTreeNode(key,value);
  if(tree->lower_than(key, aux->pair->key) == 1)
    padre->left = nodo;
  else
    (tree->lower_than( aux->pair->key, key) == 1);
    padre->right = nodo;
}

TreeNode * minimum(TreeNode * x){

  
 TreeNode * aux = x;
  while(aux->left != NULL){
    aux = aux->left;
  }
  return aux;
  
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  if(tree->root != NULL){
    TreeNode * aux = tree->root;
    while(aux){
      tree->current = aux;
      if(is_equal(tree,key,aux->pair->key)) return aux->pair;
      if (tree->lower_than (key, aux->pair->key) == 1){
        aux = aux->left;
       }
      if (tree->lower_than (aux->pair->key, key) == 1)  
        aux = aux->right;
    }
}  
  else{ 
    return NULL;
  }
  return NULL;
}

  


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
