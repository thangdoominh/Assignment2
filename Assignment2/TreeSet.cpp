#include "TreeSet.h"
#define LH +1   //Left High
#define EH  0   //Even High
#define RH -1   //Right High
TreeSet::TreeSet()
{
	root == NULL;
	count = 0;
}


TreeSet::~TreeSet()
{
	clear();
}

//rotate right
AVLNode *_rotateRight (AVLNode *root)
{
    AVLNode *temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}

//Rotate Left
AVLNode *_rotateLeft(AVLNode * root)
{
    AVLNode *temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;
}

// insert left balance
AVLNode *insLeftBal(AVLNode *root,bool *taller)
{
    AVLNode *leftTree;
    AVLNode *rightTree;
    
    leftTree = root->left;
    
    switch (leftTree->balance)
    {
        case LH: // Case 1: Left of left. Single rotation right.
            root->balance = EH;
            leftTree->balance = EH;
            
            root = _rotateRight(root);
            *taller = false;
            break;
        case EH: // error
            break;
        case RH: // Case 2: Right of left. Double rotation (left then right).
            rightTree = leftTree->right;
            switch (rightTree->balance)
            {
                case LH:
                    root->balance = RH;
                    leftTree->balance = EH;
                    break;
                case EH:
                    root->balance = EH;
                    leftTree->balance = EH; // LH
                    break;
                case RH:
                    root->balance = EH;
                    leftTree->balance = LH;
                    break;
                default:
                    break;
            } // switch rightTree->Balance
            rightTree->balance = EH;
            
            //rotate left
            root->left = _rotateLeft(root->left);
            //rotate right
            root = _rotateRight(root);
            
            *taller = false;
            break;
        default:
            break;
    }   // switch leftTree->Balance
    
    return root;
}

// insert right balance
AVLNode *insRightBal(AVLNode *root,bool *taller)
{
    AVLNode *rightTree;
    AVLNode *leftTree;
    
    rightTree = root->right;
    
    switch (rightTree->balance)
    {
        case LH:// Case 1: Left of Right
            leftTree = rightTree->left;
            switch (leftTree->balance)
            {
                case LH:
                    root->balance = EH;
                    rightTree->balance = RH;
                    break;
                case EH:
                    root->balance = EH;
                    rightTree->balance = EH;
                    break;
                case RH:
                    root->balance = LH;
                    rightTree->balance = EH;
                    break;
                    
                default:
                    break;
            } // end switch leftTree->balance
            leftTree->balance = EH;
            
            rightTree = _rotateRight(rightTree);
            root = _rotateLeft(root);
            *taller = false;
            
            break;
        case EH:// erorr!!!
            break;
        case RH: //Case 2: Right of Right
            root->balance = EH;
            rightTree->balance = EH;
            
            root = _rotateLeft(root);
            *taller = false;
            break;
        default:
            break;
            
        return root;
    } //switch rightTree->balance
    
    return root;
}

//Insert AVLNode into Root in TreeSet
AVLNode *_insert(AVLNode *root, AVLNode *newPtr, bool *taller, bool *added)
{
    //statement
    if(!root)
    {
        //Insert at root
        root = newPtr;
        *taller = true;
        return root;
    }// if NULL tree
   
    if(newPtr->key == root->key)
    {
        *added = false;
        return root;
    }
    
    if(newPtr->key < root->key)
    {
        // --> go left
        root->left = _insert(root->left, newPtr, taller, added);
        
        if(*taller)
            //Left Subtree is taller
            switch (root->balance) {
                case LH:    //Was left high--rotate
                    root->balance = RH;
                    root = insLeftBal(root, taller);
                    break;
                case EH:    // Was balanced--now LH
                    root->balance = LH;
                    break;
                case RH:    // Was balanced--now EH
                    root->balance = EH;
                    *taller = false;
                    break;
                default:
                    break;
            }// switch
            return root;
    }   //new < root
    else
        //new data >= root
    {
        root->right = _insert(root->right, newPtr, taller, added);
            
            if(*taller)
                //Right Subtree is taller
                switch (root->balance) {
                    case LH:    //Was left high--now EH
                        root->balance = EH;
                        *taller = false;
                        break;
                    case EH:    // Was balanced--now RH
                        root->balance = RH;
                        break;
                    case RH:    // Was right high--rotate
                        root->balance = LH;
                        root = insRightBal(root, taller);
                        break;
                    default:
                        break;
                }// switch
        return root;
    } //else new data >= root
    return root;
}


void TreeSet::clearRec(AVLNode* root) {
	if (root != NULL) {
		clearRec(root->left);
		clearRec(root->right);
		delete root;
	}
}
void TreeSet::clear() {
	clearRec(root);
	root = NULL;
	count = 0;
}



int TreeSet::add(int val) {
	// TODO
    AVLNode *newPtr = new AVLNode(val);
    bool forTaller;
    bool added = true; // kiem tra AVL Tree da co gia tri Val chua
    
    root = _insert(root,newPtr, &forTaller, &added);
    
    if(added == false) return false;
    
    count++;
    return true;
}

bool TreeSet::contains(int val) {
	// TODO
    return false; //test
}

void TreeSet::copy(const TreeSet& set) {
	// TODO
    
}

int TreeSet::first() {	
	if (root == NULL) {
		throw "NoSuchElementException";
	}

	// TODO
    return -1; // test
}

int TreeSet::last() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}

	// TODO
    return -1;  //test
}

int TreeSet::higher(int val) {
	// TODO
    return -1; //test
}

int TreeSet::lower(int val) {
	// TODO
    return -1;  //test
}

int TreeSet::remove(int val) {
	// TODO
    return -1; //test
}


TreeSet* TreeSet::subSet(int fromVal, int toVal) {
	// TODO
    return this; // test
}

int TreeSet::size() {
	// TODO
    print2DUtil(root, 10); //test in
    return count; //test
}




