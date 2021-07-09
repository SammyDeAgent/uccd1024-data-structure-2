#ifndef BT_type
#define BT_type

#include	"BTNode.h"
#include	"Queue.h"


struct BST {

		int		count;
		BTNode	*root;

		// print operation for BST (same as BT)					
		void preOrderPrint2(BTNode *);	// recursive function for preOrderPrint()
		void inOrderPrint2(BTNode *);	// recursive function for inOrderPrint()
		void postOrderPrint2(BTNode *);	// recursive function for postOrderPrint()

		// sample operation (extra functions) - same as BT
		void countNode2(BTNode *, int &);		// recursive function for countNode()
		bool fGS2(type, BTNode *);				// recursive function for findGrandsons(): to find the grandfather
		void fGS3(BTNode *, int);				// recursive function for findGrandsons(): to find the grandsons after the grandfather has been found
		
		// basic functions for BST
		void insert2(BTNode *, BTNode *);		// recursive function for insert() of BST
		void case3(BTNode *);					// recursive function for remove()
		void case2(BTNode *, BTNode *);			// recursive function for remove()
		bool remove2(BTNode *, BTNode *, type);	// recursive function for remove()
		



		// basic functions for BST
		BST();
		bool empty();
		int size();
		bool insert (type);			// insert an item into a BST
		bool remove(type);			// remove an item from a BST
		
		// print operation for BST (same as BT)
		void preOrderPrint();			// print BST node in pre-order manner
		void inOrderPrint();			// print BST node in in-order manner
		void postOrderPrint();			// print BST node in post-order manner
		void topDownLevelTraversal();	// print BST level-by-level

		// sample operation (extra functions) - same as BT
		int countNode();			// count number of tree nodes
		bool findGrandsons(type);	// find the grandsons of an input father item
		
		//F(x) created for Assignment 2
		bool deepestNodes();						// used to find the deepest level nodes	
		void deepestNodes2(BTNode*, int, int);		// recursive function for deepest node search

		int depth(BTNode*, int, int&);				// used to find the depth of the tree
		int depth2(BTNode*, int, int&, type);		// recursive function for depth calculation
		
		bool display(int, int);						// display function in either ascending or descending, screen or file

		void Reverse_inOrderPrint();				// display function in descending for display screen	
		void Reverse_inOrderPrint2(BTNode*);		// recursive function for display function in descending for display screen
			
		void file_inOrderPrint();					// display function in ascending for file
		void file_inOrderPrint2(BTNode*, ostream&);	// recursive function for display function in ascending for file
			
		void file_Reverse_inOrderPrint();						// display function in descending for file
		void file_Reverse_inOrderPrint2(BTNode*, ostream&);		// recursive function for display function in descending for file

		bool CloneSubtree(BST, type);				// function for displaying the subtree of a given node as root
		bool searchNode(BTNode*&, type);			// search function for a tree
		void searchNode2(BTNode*, type, BTNode*&);	// recursive function for the search function for a tree
		void insertSub(BTNode*, Student);		    // function for inserting subtree into another tree
		
		bool printAncestor(type);					// function for printing the ancestor of a given node
		void UpNode(int, BTNode*, int);				// function for printing nodes that are the ancestor of the node
		void UpNode2(int, BTNode*, int, BTNode*);	// recursive function for function for printing nodes that are the ancestor of the node
		void searchNode3(BTNode*, type, bool&);		// search function for a tree given case of specific node as root point

		bool printSpiral();							// printing nodes in a spiral traversal
		void printSpiral2(BTNode*, int, bool);		// recursive function for printing nodes in a spiral traversal
};




#endif