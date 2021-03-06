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
  
  if(node->left != NULL && node->right == NULL){  // nodo es hijo izq y tiene un hijo izq
    if(is_equal(tree, node->parent->left, node)){
      if(node->left != NULL){
        node->parent->left = node->left;
        node->left->parent = node->parent;
        node=NULL;
        return;}}
        //free(node);
      

    if(is_equal(tree, node->parent->right, node)){  // nodo es hijo der y tiene un hijo izq
     if(node->left != NULL){
        node->parent->right = node->left;
        node->left->parent = node->parent;
        node=NULL;
        return;}}
        //free(node);
      
  }

  if(node->left == NULL && node->right != NULL){ // nodo es hijo der y tiene un hijo der
    if(is_equal(tree, node->parent->right, node)){
     if(node->right != NULL){
        node->parent->right = node->right;
        node->right->parent = node->parent;
        node=NULL; 
        return;}}
        //free(node);
      
    if(is_equal(tree, node->parent->left, node)){  //nodo es hijo izq y tiene hijo der
      if(node->right != NULL){
        node->parent->left = node->right;
        node->right->parent = node->parent;
        node=NULL; 
        return;}}
        //free(node);
  
  }
    if(node->left !=NULL && node->right != NULL){
      TreeNode * mini = minimum(node->right);
      node->pair->key = mini->pair->key; 
      node->pair->value = mini->pair->value; 
      node = NULL;
      removeNode(tree, mini);
      return;
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
    
  tree->current = tree->root;
  TreeNode * ubNode = NULL;

  while(tree->current != NULL){

    if(is_equal(tree,tree->current->pair->key, key))
      return tree->current->pair;
    if(tree->lower_than(tree->current->pair->key, key)){ 
      tree->current = tree->current->right;
    }else{
      ubNode = tree->current;
      tree->current = tree->current->left;
      }
    if(ubNode == NULL && tree->current == NULL) return NULL;
    }
    return ubNode->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode * aux = tree->root;
  while(aux->left != NULL){
    aux = aux->left;
  }
  return aux->pair;
}

Pair * nextTreeMap(TreeMap * tree) {

  if(tree->current->right != NULL){
    tree->current = minimum(tree->current->right);
    return tree->current->pair;
  }
  
  while(tree->current->parent != NULL && tree->current == tree->current->parent->right){
    tree->current = tree->current->parent;
  }
  if(tree->current->parent != NULL){
    tree->current = tree->current->parent;
    return tree->current->pair;
  }
  return NULL;
}
