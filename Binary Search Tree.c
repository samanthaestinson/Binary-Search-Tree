// BST.C
// 
// Code for ELEC278 Lab 3.  

#include <stdlib.h>
#include <stdio.h>
#include "bst.h"


Node *initNode (Key k, void *v)
// Allocate memory for a new node and initialize fields.
// Returns pointer to node created.
{
	//creates a new tree node for the given data
	//acessed through a pointer *n, pointer to root node
	Node *n = malloc(sizeof(Node));
	// initialize node if memory obtained
	//
	if (n != NULL)	{
		n->key = k; //location
		n->value = v; //data
		//spliting the binary tree
		//filling left and right cells as NULL till filled up
		//initally set to NULL so empty
		n->leftChild = NULL;
		n->rightChild = NULL;
		}
	//returning the node
	return n;
}//initNode()


Tree *initTree(Key k, void *v)
// Set up a new tree. Allocates memory for the Tree structure, then
// calls initNode() to allocate first node.
{
	Tree* t = malloc(sizeof(Tree));
	if (t != NULL)
		t->root = initNode(k,v);
	return t;
}//initTree()

void printTreeExplanation (void)
// Prints hint to reader what to expect on screen
{
	static int done = 0;
	if (!done)	{
		printf ("First time explanation of tree display:\n");
		printf ("Every node is displayed as a comma-separated pair within brackets:");
		printf (" (kk,vv)\n");
		printf ("A tree starts with a { and ends with a }.  An empty tree will be {}\n");
		printf ("A tree with no children will be { (kk,vv),{},{} }\n");
		printf ("If either subtree is populated, it will be shown using the same ");
		printf ("technique\n============\n\n");
		done = 1;
		}
}//printTreeExplanation()


void printTree (Node* root)
// Print whole tree. We cannot make it look pretty graphically, so we add some
// characters to make it a little easier to understand.  We also don't really
// know what the value field is - it is declared to be a void pointer - so we
// treat it as though it points to an integer.
{
	// assume printTree magically know the types in the tree node
	printTreeExplanation();
	// start of this tree
	printf("{");
	// values in the root node (assuming value is pointing to an integer)
	printf("(%d,%d),", root->key, *(int*)root->value);
	
	// Now show left subtree or {} if there is no left subtree
	if (root->leftChild != NULL)	printTree(root->leftChild);
	else							printf("{}");
	// Marker between left and right subtrees		
	printf(",");
	// Now show right subtree or {} if there is no right subtree
	if (root->rightChild != NULL)	printTree(root->rightChild);
	else							printf("{}");
	// Close display of this tree with closing curly bracket	
	printf("}");
}//printTree()


Node *find (Key k, Node *root)
// Function locates node with key value equal to parameter k. Parameter
// root holds pointer to root node of tree. Function returns immediately
// if either root pointer is null, or the node that root points to has
// key value sought.  If neither of those conditions is true, then the
// function calls itself with a pointer to either the left or right
// subtree.
{
	// termination conditions - either true, search is ended
	if ((root == NULL) || (root->key == k))	return root;
	// search continues.  Since this is a search tree, we know that
	// every key in the right subtree is bigger than the key in the tree's
	// root, and every key in the left subtree is smaller than the key in
	// the tree's root.  That allows us to choose the appropriate subtree
	// to search.
	if (k > root->key)
		// Key value sought is larger than current node key, so search right
		// subtree
		return find(k,root->rightChild);
	else
		// Key value sought is smaller than current node key (the equal case
		// was handled as a termination condition in the first line), so
		// search left subtree
		return find(k,root->leftChild);	
}//find()



int insert(Key k, void *v, Node *root) //needs pointer/location and data
// Function inserts a new node into the tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.
{
	int result = 0;
	// this if statement can only be true with the first root (root of whole tree)
	if (root == NULL)	{ //empty tree
		Node *n = initNode(k,v);
		root = n;
		result = 1; 
		}
	
	/* already exists in tree ==> can't insert */
	if (root->key == k)
		result = 0;
	else if (k < root->key) {
		// key value less than key value in root node - try to insert into left
		// subtree, if it exists.
		if (root->leftChild != NULL)
			// there is a left subtree - insert it
			result = insert(k, v, root->leftChild);
		else {
			// new Node becomes the left subtree
			Node *n = initNode(k,v);
			root->leftChild = n;
			result = 1;
			}
	} else if (k > root->key) {			// test actually redundant
		// key is greater than this nodes key value, so value goes into right
		// subtree, if it exists
		if (root->rightChild != NULL)
			// there is a right subtree - insert new node
			result = insert(k,v,root->rightChild);
		else {
			// no right subtree - new node becomes right subtree
			Node*n = initNode(k,v);
			root->rightChild = n;
			result = 1;
			}
		}
	return result;	
}//insert()


int intmax(int a, int b)
// YOU WILL USE THIS FUNCTION WHEN YOU IMPLEMENT HEIGHT() !!
// Useful function - returns the greater value of two integers.
// Called intmax, not max, because max already exists.
// It is a chance to see the conditional value in C - a value that is the
// first one (after the ?) if the condition is true, or the second one (after
// the :) if the condition is false.
{
	return (a>=b) ? a : b;
}//intmax()


int height(Node *root)
{
    if (root==NULL) //if root is empty then just return -1.
    {
        return -1;
    }
    
    int lheight=height(root->leftChild);
    int rheight=height(root->rightChild);
    
    
    return intmax(lheight,rheight)+1;
    
    //Use recursion to check the left child, then the right.
    //Once you hit the bottom of a branch (root==null from above)
    //then the formula will work its way back up adding one for every node.
    
}//height()


Node* findParentHelper (Key k, Node* root)
{
    if (root == NULL) { //empty if null
        printf("parent does not exist /n");
        return NULL;
	}
	//if the root isnt null and it equals the desired value for Left or Right
    if ((root->leftChild != NULL && root->leftChild->key == k) || (root->rightChild != NULL && root->rightChild->key == k)) {
		//returns the parent fo the node whose key is equaled to the target value k
		return root;
    }
    //if the target is greater than the root value then look more indepth by moving right bc its higher
    if (k > root->key ) {
        return findParentHelper(k, root->rightChild);
	}
	//if the target is less than the root value then look more indepth by moving left bc its lower
    if (k < root->key) {
        return findParentHelper(k, root->leftChild);
	}
    return root;
}


Node* findParent(Key k, Node* root)
{
	/* Deal with special special cases which could only happen for the root of the whole tree */
	if (root == NULL)
		return root;	
	/* real root doesn't have a parent so we make it the parent of itself */
	if (root->key == k) 
		return root;	
	/* root has no children */
	if (!(root->leftChild) && !(root->rightChild)) 
			return NULL;
	
	/* Deal with the cases where the root has at least one child */
	return findParentHelper(k, root);
}//findParent()


void delete (Node* p, Node *n)
{
    //if the rightchild is equal to the node
    if (p->rightChild == n ) {
		
		//if both are empty in the node for left and right then delete parent and free its memory
        if (n->rightChild == NULL && n->leftChild == NULL) {
            p->rightChild = NULL;
			free(n);
		
		//if the right isnt empty and the left is delete the right and free the memory
        }
        if (n->rightChild != NULL && n->leftChild == NULL) {
            p->rightChild = n->rightChild;
            free(n);
        }
		
		//if th left isnt empty and the right is, delete the left and free the memory
        if (n->leftChild != NULL && n->rightChild == NULL) {
            p->rightChild = n->leftChild;
            free(n);
        }
		
		//if the left isnt empty and the right isnt empty and 
        if(n->leftChild != NULL && n->rightChild != NULL) {
			//set a temporary pointer to node and store the value
            Node *temp = n->leftChild;
            Node *ptemp = n;
            //while the right isnt null
            while(temp->rightChild != NULL) {
				//set a temporary pointer to node and store the value
                ptemp = temp;
                temp = temp->rightChild;
            }
            n->key = temp->key;
            delete(ptemp,temp);
        }
    }
    if (p->leftChild == n) {
        
        if (n->rightChild == NULL && n->leftChild == NULL) {
            p->leftChild = NULL;
            free(n);
        }
        if (n->rightChild != NULL && n->leftChild == NULL) {
            
            p->leftChild = n->rightChild;
            free(n);
        }
        
        if (n->leftChild != NULL && n->rightChild == NULL) {
            p->leftChild= n->leftChild;
            free(n);
        }
        
        if(n->leftChild != NULL && n->rightChild != NULL) {
            Node *temp = n->leftChild;
            Node *ptemp = n;
            
            while(temp->rightChild != NULL) {
                ptemp = temp;
                temp = temp->rightChild;
            }
            n->key = temp->key;
            delete(ptemp,temp);
        }
        
        
    }
    
}//delete()


int withdraw(Key k, Node* root, Node* n)
// Withdraw does two things:
//	return a copy of the node with key k (and value v)
//	Delete the node with key k from the tree while ensuring the tree remains valid
{
	Node *p, *m;
	m = find(k, root);
	
	if (m) /* another way or writing if (m!==NULL) */
	{
		/* create a copy of the node with the same key and value*/
		n = initNode(m->key,m->value);
		p = findParent(k,root);
		/* now I can delete the node */
		delete(p,m);
		return 1;
	}
	
	return 0;	
}




