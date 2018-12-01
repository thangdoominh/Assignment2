#pragma once
#include"AVLNode.h"
class TreeSet
{
private:
	AVLNode * root;
	int count;

protected:
	void clearRec(AVLNode*root);
	
public:
	TreeSet();
	~TreeSet();
	void clear();
	// print out the set in ascending order
	friend ostream& operator<<(ostream& os, const TreeSet& t);

	// YOUR TASKS START HERE	
	int add(int val);		
	bool contains(int val);
	void copy(const TreeSet& set);
	int first();
	int higher(int val);
	int last();
	int lower(int val);
	int remove(int val);
	TreeSet* subSet(int fromVal, int toVal);
	int size();
    
    //------test in -------
    //function print tree
    void print2DUtil(AVLNode *root, int space)
    {
        // Base case
        if (root == NULL)
            return;
        
        // Increase distance between levels
        space += 5;
        // Process right child first
        print2DUtil(root->right, space);
        
        // Print current node after space
        // count
        cout << endl;
        for (int i = 5; i < space; i++)
            cout <<" ";
        cout << root->key<< endl;
        // Process left child
        print2DUtil(root->left, space);
    }
    //-------end test in --------
    
	// END HERE
};

