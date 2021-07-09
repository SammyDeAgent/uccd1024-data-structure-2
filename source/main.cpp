#include	<iostream>
#include	<fstream>
#include	<cstdlib>
#include	<cstdio>
#include	<ctime>
#include	"BST.h"
#include    "Student.h"

using namespace std;

const int SIZE = 256;

bool readFile(const char *, BST *);
int menu();

int main() {
	cout << "@All rights reserved to 1802834";
	int x;
	BST* tree = new BST;
	Student stu_info;

	x = menu();
	while (x!=7) {
		if (x==1) {
			if (!readFile("student.txt", tree)) cout << "\n\nUnexpected error has occured!\n";
		}
		if (x == 2) {
			if (!tree->deepestNodes()) cout << "\n\nAlert! The tree is empty.\n";
		}
		if (x == 3) {
			int order, source;
			cout << "\n\nOrder of Preview:\n1. Ascending\n2. Descending\nPlease enter your choice: ";
			cin >> order;
			cout << "\n\nOutput Option:\n1. Display to Screen\n2. Save to File\nPlease enter your choice: ";
			cin >> source;
			if (!tree->display(order, source))  cout << "\n\nAlert! The tree is empty.\n";
		}
		if (x == 4) {
			BST* tree2 = new BST;
			cout << "\n\nPlease enter the Student ID you wish to be a Root: ";
			cin >> stu_info.id;
			if (!tree2->CloneSubtree(*tree, stu_info));
			else {
				cout << "\n\nDisplaying Tree 1 via Pre-Order:\n";
				tree->preOrderPrint();
				cout << "\n\nDisplaying Cloned Tree 2 Subtree via Pre-Order:\n";
				tree2->preOrderPrint();			
				delete tree2;
			}
		}
		if (x == 5) {
			cout << "\n\nPlease enter the Student ID that you wish to find it's Ancestor: ";
			cin >> stu_info.id;
			if (!tree->printAncestor(stu_info)) {
				if(tree->size()==0) cout << "\n\nAlert! The tree is empty.\n";
			}
		}
		if (x == 6) {
			if (!tree->printSpiral()) cout << "\n\nAlert! The tree is empty.\n";
		}
		x = menu();
	}
	cout << "\nPROGRAM TERMINATED\n\n";
	system("pause");
	return 0;
}

int menu() {
	int x;
	cout << "\n\nMenu:				\n";
	cout << "1. Read data to BST	\n";
	cout << "2. Print deepest nodes	\n";
	cout << "3. Display student		\n";
	cout << "4. Clone Subtree		\n";
	cout << "5. Print Ancestor		\n";
	cout << "6. Print Spiral		\n";
	cout << "7. Exit				\n";
	cout << "Please enter your choice: ";
	cin >> x;
	return x;
}

bool readFile(const char* filename, BST* t1) {
	Student stu_info;
	char temp[SIZE];
	int count = 0;

	ifstream in;
	in.open(filename);
	if (in.is_open()) {
		while (!in.eof()) {
			for (int i = 0; i < 2; i++) in >> temp;
			in >> stu_info.id;
			for (int i = 0; i < 2; i++) in >> temp;
			in.getline(stu_info.name, 30);
			for (int i = 0; i < 2; i++) in >> temp;
			in.getline(stu_info.address, 100);
			for (int i = 0; i < 2; i++) in >> temp;
			in >> stu_info.DOB;
			for (int i = 0; i < 2; i++) in >> temp;
			in >> stu_info.phone_no;
			for (int i = 0; i < 2; i++) in >> temp;
			in >> stu_info.course;
			for (int i = 0; i < 2; i++) in >> temp;
			in >> stu_info.cgpa;
			t1->insert(stu_info);
			count++;
		}
		cout << "\n\n" << count << " Record(s) has successfully been read.\n";
		in.close();
		return true;
	}
	else {
		cout << "\n\nAlert! Unable to open \"" << filename << "\" file.\n";
		in.close();
		return false;
	}
}
