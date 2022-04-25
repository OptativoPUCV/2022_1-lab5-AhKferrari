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
  TreeNode * nodo = createTreeNode(key,value);

  while(aux!= NULL){
    padre = aux;
    if(tree->lower_than(key,aux->pair->key)){
      aux = aux->left;
      }else if(tree->lower_than(aux->pair->key,key)){
      aux = aux->right;
      }else{ 
        return;
      }
  }
  
  if(padre == NULL) {
    tree->root = nodo; }
  else if(tree->lower_than(nodo->pair->key, padre->pair->key)){
    nodo->parent = padre;
    padre->left = nodo;
    tree->current = nodo->left;
  }  
  else{
    nodo->parent = padre;
    padre->right = nodo;
    tree->current = nodo->right;
  }
  tree->current = nodo;
}

TreeNode * minimum(TreeNode * x){

  TreeNode * aux = x;
  while(aux->left != NULL){
    aux = aux->left;
  }
  return aux;
  
}


void removeNode(TreeMap * tree, TreeNode* node) {

  if (tree == NULL || tree->root == NULL) return;
  if (node->left == NULL && node->right == NULL) {
    if(node->parent->left == NULL) node->parent->right = NULL;
    else node->parent->left = NULL;
    return;
  }
  else if (node->left != NULL && node->right == NULL){
      node->parent->left = node->left;
      node->left = NULL;
      return;}

    if(node->left == NULL && node->right != NULL){
      node->parent->right = node->right;    
      node->right = NULL;
      return;}  
    
    
    else{
      node = minimum(node->right);
      removeNode(tree, minimum (node->right));
    }
  
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
