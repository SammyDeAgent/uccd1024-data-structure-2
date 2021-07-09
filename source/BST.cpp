#include <iostream>
#include <fstream>
#include <algorithm>
#include "BST.h"


using namespace std;


BST::BST() {
	root = NULL;
	count = 0;
}

bool BST::printSpiral() {
	if (root == NULL)return false;
	int level = 0;
	int max = 0;
	depth(root, level, max);	//Finding the depth of the tree
	bool Toggle = false;		//Toggle used to flip travesal method
	cout << "\n\nPrinting Nodes in Spiral Traversal Mode: \n";
	for (int i = 0; i <= max; i++) {
		printSpiral2(root,i,Toggle);
		Toggle = !Toggle;		//Toggle flips like a RS-Latch for every iteration
	}
	return true;
}

void BST::printSpiral2(BTNode* cur, int i, bool Toggle) {
	if (cur == NULL)return;
	if (i == 0) cur->item.print(cout);
	else if (i >= 1) {
		if (Toggle == true) {	//LTR Traversal
			printSpiral2(cur->left, i - 1, Toggle);
			printSpiral2(cur->right, i - 1, Toggle);
		}
		else {					//RTL Traversal
			printSpiral2(cur->right, i - 1, Toggle);
			printSpiral2(cur->left, i - 1, Toggle);
		}
	}
}

bool BST::printAncestor(type item) {
	BTNode* SNode = NULL;
	if (root == NULL) return false;
	if (!searchNode(SNode, item)) {			//Finding the ancestor node location
		cout << "\n\nUnable to find requested Node!\n";
		return false;
	}
	if (SNode->item.id == root->item.id) {	//If node is a root, no ancestor
		cout << "\n\nAlert! There's no Ancestor for this Node.\n";
		return false;
	}
	int level = 0;
	int max = 0;
	level = depth2(root, level, max, item);	//Finding the specific node's depth
	cout << "\n\nThe Ancestor(s) for Node \"" << item.id << "\": \n";
	UpNode(level,SNode, 0);
	return true;
}

void BST::UpNode(int level, BTNode* SNode, int current) {
	if (root == NULL) return;
	UpNode2(level, SNode, current, root);
}

void BST::UpNode2(int level, BTNode* SNode, int current,BTNode* cur) {
	BTNode* temp = NULL;
	if (cur == NULL) {
		current--;
		return;
	}
	bool DS= false;							//Boolean logic for if this pathway can lead to the specific node
	searchNode3(cur, SNode->item, DS);
	if ( DS == true && current < level) {	//A Ancestor must have a higher level that the node and have the pathway conencted
		cur->item.print(cout);
	}
	UpNode2(level, SNode, current + 1, cur->left);
	UpNode2(level, SNode, current + 1, cur->right);
}

void BST::searchNode3(BTNode* cur, type item, bool& DS) {
	if (cur == NULL) return;
	if (item.id == cur->item.id) {	//Searching if the pathway to node is available
		DS = true;
		return;
	}
	searchNode3(cur->left, item, DS);
	searchNode3(cur->right, item, DS);
	return;
}

bool BST::CloneSubtree(BST t1, type item) {
	BTNode* SNode = NULL;
	Student subtree;
	if (t1.size() == 0) {
		cout << "\n\nAlert! The tree is empty.\n";
		return false;
	}
	if (!t1.searchNode(SNode, item)) {
		cout << "\n\nUnable to find requested Node!\n";					//Searchs for the node
		return false;
	}	
	else insertSub(SNode, subtree);										//Inserts the subtree to a new tree
	return true;
}

void BST::insertSub(BTNode* cur, Student subtree) {
	if (cur == NULL) return;

	strcpy_s(subtree.name, sizeof(subtree.name), cur->item.name);
	subtree.id = cur->item.id;
	strcpy_s(subtree.address, sizeof(subtree.address), cur->item.address);
	strcpy_s(subtree.DOB, sizeof(subtree.DOB), cur->item.DOB);
	strcpy_s(subtree.phone_no, sizeof(subtree.phone_no), cur->item.phone_no);
	strcpy_s(subtree.course, sizeof(subtree.course), cur->item.course);
	subtree.cgpa = cur->item.cgpa;
	insert(subtree);

	insertSub(cur->left, subtree);
	insertSub(cur->right, subtree);
}

bool BST::searchNode(BTNode*& SNode,type item) {
	if (root == NULL) return false;
	searchNode2(root, item, SNode);
	if (SNode != NULL) {
		return true;
	}
	return false;
}

void BST::searchNode2(BTNode* cur, type item,BTNode*& SNode) {
	if (cur == NULL) return;
	if (item.id == cur->item.id) {	//If matching, then node is found
		SNode = cur;
		return;
	}
	searchNode2(cur->right, item, SNode);
	searchNode2(cur->left, item, SNode);
	return;
	
}

bool BST::display(int order, int source) {
	if (root == NULL) return false;
	if (source == 1) {			//Print to Display Screen
		if (order == 1) {		//ASCE
			cout << "\n\nDisplaying Student Details via Ascending Order:\n";
			inOrderPrint();
		}
		else if (order == 2) {	//DESC
			cout << "\n\nDisplaying Student Details via Descending Order:\n";
			Reverse_inOrderPrint();
		}
	}
	else if (source == 2) {		//Print to File
		if (order == 1) {		//ASCE
			file_inOrderPrint();
			cout << "\nStudent Details has been saved to \"student-info.txt\" File via Ascending Order. \n";
		}
		else if (order == 2) {	//DESC
			file_Reverse_inOrderPrint();
			cout << "\nStudent Details has been saved to \"student-info.txt\" File via Descending Order. \n";
		}
	}
	return true;
}

void BST::Reverse_inOrderPrint() {
	if (root == NULL) return;
	else Reverse_inOrderPrint2(root);
	cout << endl;
}

void BST::Reverse_inOrderPrint2(BTNode* cur) {
	if (cur == NULL) return;
	Reverse_inOrderPrint2(cur->right);
	cur->item.print(cout);
	Reverse_inOrderPrint2(cur->left);
}

void BST::file_inOrderPrint() {
	if (root == NULL) return;
	else {
		ofstream out;
		out.open("student-info.txt");
		file_inOrderPrint2(root, out);
		out.close();
	}
	cout << endl;
}

void BST::file_inOrderPrint2(BTNode* cur, ostream &out) {
	if (cur == NULL) return;
	file_inOrderPrint2(cur->left, out);
	cur->item.print(out);
	file_inOrderPrint2(cur->right, out);
}

void BST::file_Reverse_inOrderPrint() {
	if (root == NULL) return;
	else {
		ofstream out;
		out.open("student-info.txt");
		file_Reverse_inOrderPrint2(root, out);
		out.close();
	}
	cout << endl;
}

void BST::file_Reverse_inOrderPrint2(BTNode* cur, ostream &out) {
	if (cur == NULL) return;
	file_Reverse_inOrderPrint2(cur->right, out);
	cur->item.print(out);
	file_Reverse_inOrderPrint2(cur->left, out);
}

bool BST::deepestNodes() {
	if (root == NULL) return false;
	else {
		int level = 0;
		int max = 0;
		level = depth(root, level, max);
		cout << "\n\nDeepest Node(s) for selected tree at Level " << level << ": \n";
		int current = 0;
		deepestNodes2(root, level, current);	//Prints deepest node after the depth function where level is equal to maximum depth
	}
	return true;
}

void BST::deepestNodes2(BTNode *cur,int level, int current) {
	if (cur == NULL) {
		current--;
		return;
	}
	if (current == level) {
		cur->item.print(cout);
		return;
	}
	deepestNodes2(cur->left, level, current + 1);
	deepestNodes2(cur->right, level, current+1);
}

int BST::depth(BTNode* cur, int level, int& max) {
	if (cur == NULL) {
		return level--;
	}
	if (level > max) max = level;	//Solving for maximum depth here only
	depth(cur->left, level+1, max);
	depth(cur->right, level+1, max);
	return max;
}

int BST::depth2(BTNode* cur, int level, int& max,type item) {
	if (cur == NULL) {
		return level--;
	}
	if (level > max && cur->item.id == item.id) max = level;	//Solving for maximum depth for the specific node point
	depth2(cur->left, level + 1, max, item);
	depth2(cur->right, level + 1, max, item);
	return max;
}

/////////////////////////////////////////////////////////////////////////////////////

bool BST::empty() {
	if (count == 0) return true;
	return false;
}


int BST::size() {
	return count;
}


void BST::preOrderPrint() {
	if (root == NULL) return;// handle special case
	else preOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::preOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	cur->item.print(cout);
	preOrderPrint2(cur->left);
	preOrderPrint2(cur->right);
}


void BST::inOrderPrint() {
	if (root == NULL) return;// handle special case
	else inOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::inOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	inOrderPrint2(cur->left);
	cur->item.print(cout);
	inOrderPrint2(cur->right);
}


void BST::postOrderPrint() {
	if (root == NULL) return;// handle special case
	else postOrderPrint2(root);// do normal process
	cout << endl;
}


void BST::postOrderPrint2(BTNode *cur) {
	if (cur == NULL) return;
	postOrderPrint2(cur->left);
	postOrderPrint2(cur->right);
	cur->item.print(cout);
}



int BST::countNode() {
	int	counter = 0;
	if (root == NULL) return 0;
	countNode2(root, counter);
	return counter;
}


void BST::countNode2(BTNode *cur, int &count) {
	if (cur == NULL) return;
	countNode2(cur->left, count);
	countNode2(cur->right, count);
	count++;
}


bool BST::findGrandsons(type grandFather) {
	if (root == NULL) return false;
	return (fGS2(grandFather, root));
}


bool BST::fGS2(type grandFather, BTNode *cur) {
	if (cur == NULL) return false;
	//if (cur->item == grandFather) {
	if (cur->item.compare2(grandFather)){

		fGS3(cur, 0);// do another TT to find grandsons
		return true;
	}
	if (fGS2(grandFather, cur->left)) return true;
	return fGS2(grandFather, cur->right);
}


void BST::fGS3(BTNode *cur, int level) {
	if (cur == NULL) return;
	if (level == 2) {
		cur->item.print(cout);
		return;  // No need to search downward
	}
	fGS3(cur->left, level + 1);
	fGS3(cur->right, level + 1);
}



void BST::topDownLevelTraversal() {
	BTNode			*cur;
	Queue		    q;


	if (empty()) return; 	// special case
	q.enqueue(root);	// Step 1: enqueue the first node
	while (!q.empty()) { 	// Step 2: do 2 operations inside
		q.dequeue(cur);
		if (cur != NULL) {
			cur->item.print(cout);

			if (cur->left != NULL)
				q.enqueue(cur->left);

			if (cur->right != NULL)
				q.enqueue(cur->right);
		}
	}
}

//insert for BST
bool BST::insert(type newItem) {
	BTNode	*cur = new BTNode(newItem);
	if (!cur) return false;		// special case 1
	if (root == NULL) {
		root = cur;
		count++;
		return true; 			// special case 2
	}
	insert2(root, cur);			// normal
	count++;
	return true;
}


void BST::insert2(BTNode *cur, BTNode *newNode) {
	//if (cur->item > newNode->item) {
	if (cur->item.compare1(newNode->item)){
		if (cur->left == NULL)
			cur->left = newNode;
		else
			insert2(cur->left, newNode);
	}
	else {
		if (cur->right == NULL)
			cur->right = newNode;
		else
			insert2(cur->right, newNode);
	}
}



bool BST::remove(type item) {
	if (root == NULL) return false; 		// special case 1: tree is empty
	return remove2(root, root, item); 		// normal case
}

bool BST::remove2(BTNode *pre, BTNode *cur, type item) {

	// Turn back when the search reaches the end of an external path
	if (cur == NULL) return false;

	// normal case: manage to find the item to be removed
	//if (cur->item == item) {
	if (cur->item.compare2(item)){
		if (cur->left == NULL || cur->right == NULL)
			case2(pre, cur);	// case 2 and case 1: cur has less than 2 sons
		else
			case3(cur);		// case 3, cur has 2 sons
		count--;				// update the counter
		return true;
	}

	// Current node does NOT store the current item -> ask left sub-tree to check
	//if (cur->item > item)
	if (cur->item.compare1(item))
		return remove2(cur, cur->left, item);

	// Item is not in the left subtree, try the right sub-tree instead
	return remove2(cur, cur->right, item);
}


void BST::case2(BTNode *pre, BTNode *cur) {

	// special case: delete root node
	if (pre == cur) {
		if (cur->left != NULL)	// has left son?
			root = cur->left;
		else
			root = cur->right;

		free(cur);
		return;
	}

	if (pre->right == cur) {		// father is right son of grandfather? 
		if (cur->left == NULL)			// father has no left son?
			pre->right = cur->right;			// connect gfather/gson
		else
			pre->right = cur->left;
	}
	else {						// father is left son of grandfather?
		if (cur->left == NULL)			// father has no left son? 
			pre->left = cur->right;				// connect gfather/gson
		else
			pre->left = cur->left;
	}

	free(cur);					// remove item
}


void BST::case3(BTNode *cur) {
	BTNode		*is, *isFather;

	// get the IS and IS_parent of current node
	is = isFather = cur->right;
	while (is->left != NULL) {
		isFather = is;
		is = is->left;
	}

	// copy IS node into current node
	cur->item = is->item;

	// Point IS_Father (grandfather) to IS_Child (grandson)
	if (is == isFather)
		cur->right = is->right;		// case 1: There is no IS_Father    
	else
		isFather->left = is->right;	// case 2: There is IS_Father

	// remove IS Node
	free(is);
}




