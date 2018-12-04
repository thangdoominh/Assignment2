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
AVLNode *_rotateLeft(AVLNode *root)
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
                    leftTree->balance = EH; // LH or EH
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
            root->left = _rotateLeft(leftTree);
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
                    rightTree->balance = EH;    // EH or RH
                    break;
                case RH:
                    root->balance = LH;
                    rightTree->balance = EH;
                    break;
                    
                default:
                    break;
            } // end switch leftTree->balance
            leftTree->balance = EH;
            
            root->right = _rotateRight(rightTree);
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
        *taller = false;
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
                        root = insRightBal(root, taller);
                        break;
                    default:
                        break;
                }// switch
        return root;
    } //else new data >= root
    return root;
}


//delete left balance
AVLNode *_dltLeftBal (AVLNode *root, bool &shorter)
{
    AVLNode *leftTree;
    AVLNode *rightTree;
    
    switch (root->balance)
    {
        case EH:    // now Left high
            root->balance = LH;
            shorter = false;
            break;
            
        case RH:    //deleted Right -- now balanced
            root->balance = EH;
            break;
            
        case LH:    //Left high -> rotate right
            leftTree = root->left;
            if(leftTree->balance == RH)
            {
                rightTree = leftTree->right;
                switch (rightTree->balance)
                {
                    case LH:
                        root->balance = RH;
                        leftTree->balance = EH;
                        break;
                    case EH:
                        root->balance = RH; //EH or RH
                        leftTree->balance = EH;
                        break;
                    case RH:
                        root->balance = EH;
                        leftTree->balance = LH;
                        break;
                    default:
                        break;
                }   //end switch(rightTree->balance)
                rightTree->balance = EH;
                
                //Rotate Left then Right
                root->left = _rotateLeft(leftTree);
                root = _rotateRight(root);
            }   //end if(leftTree->balance == RH)
            else
                //sigle Rotation Only
            {
                switch (leftTree->balance) {
                    case LH:
                    case RH:
                        root->balance = EH;
                        leftTree->balance = EH;
                        break;
                    case EH:
                        root->balance = LH;
                        leftTree->balance = RH;
                        shorter = false;
                        break;
                    default:
                        break;
                }   //end switch(leftTree->balance)
                root = _rotateRight(root);
            }   //end else
            break;
               default:
            break;
    } //end switch(root->balance)
    return root;
}

//delete right balance
AVLNode *_dltRightBal (AVLNode *root, bool &shorter)
{
    AVLNode *rightTree;
    AVLNode *leftTree;
    
    switch (root->balance) {
        case LH:    //deleted left -- now balanced
            root->balance = EH;
            break;
            
        case EH:    //now right high
            root->balance = RH;
            shorter = false;
            break;
            
        case RH:   // Right high -> rotate left
            rightTree = root->right;
            if (rightTree->balance == LH)
            {
                leftTree = rightTree->left;
                switch (leftTree->balance)
                {
                    case LH:
                        root->balance = EH;
                        rightTree->balance = RH;
                        break;
                    case EH:
                        root->balance = LH; // LH or EH
                        rightTree->balance = EH;
                        break;
                    case RH:
                        root->balance = LH;
                        rightTree->balance = EH;
                        break;
                    default:
                        break;
                }   // end switch rightTree->balance
                leftTree->balance = EH;
                
                //  rotate Right then Left
                root->right = _rotateRight(rightTree);
                root = _rotateLeft(root);
            }   //end if (rightTree->balance == LH)
            else
                //sigle Rotation Only
            {
                switch (rightTree->balance) {
                    case LH:
                    case RH:
                        root->balance = EH;
                        rightTree->balance = EH;
                        break;
                    case EH:
                        root->balance = RH;
                        rightTree->balance = LH;
                        shorter = false;
                        break;
                        
                    default:
                        break;
                }   //end switch (rightTree->balance)
                
                root = _rotateLeft(root);
            }   // end else
            break;
        default:
            break;
    }   //end switch root->balance
    return root;
}

AVLNode *_delete(AVLNode *root, int dltkey,bool &shorter,bool &success)
{
    AVLNode *dltPtr;
    AVLNode *exchPtr;
    AVLNode *newRoot;
    
    if(!root)
    {
        shorter = false;
        success = false;
        return NULL;
    }
    
    if(dltkey < root->key)
    {
        root->left = _delete(root->left, dltkey, shorter, success);
        if(shorter)
            root = _dltRightBal(root, shorter);
            
    }   //if less
    else if(dltkey > root->key)
    {
        root->right = _delete(root->right, dltkey, shorter, success);
        if(shorter)
            root = _dltLeftBal(root, shorter);
        
    }   //if greater
    else
    // Found equal node
    {
        dltPtr = root;
        
        if(!root->right)    // only left Subtree
        {
            newRoot = root->left;
            success = true;
            shorter = true;
            free(dltPtr);
            return newRoot;
        }
        else if(!root->left) //only right Subtree
        {
            newRoot = root->right;
            success = true;
            shorter = true;
            free(dltPtr);
            return newRoot;
        }
        else
            // Delete Node has two Subtree
        {
            exchPtr = root->left;
            while (exchPtr->right)
                exchPtr = exchPtr->right;
            root->key = exchPtr->key;
            root->left = _delete(root->left, exchPtr->key, shorter, success);
            if(shorter)
                root = _dltRightBal(root, shorter);
        }// else
    }   //equal node
    return root;
}   //end _delete

//contains
AVLNode *_searchKey(AVLNode *root, int val)
{
    if(!root)
        return root;
    if(val > root->key)
        root = _searchKey(root->right, val);
    else if(val < root->key)
        root = _searchKey(root->left, val);
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

bool TreeSet::contains(int val)
{
    
    AVLNode *seach = root;
    seach = _searchKey(seach, val);
    if(seach == NULL)
        return false;
    if(seach->key == val)
        return true;
    return false;
}

void TreeSet::_copy(AVLNode *root, AVLNode *set)
{
    if(set)
    {
        _copy(root, set->left);
        this->add(set->key);
        _copy(root, set->right);
    }
}

void TreeSet::copy(const TreeSet& set) {
    _copy(root, set.root);
}

int TreeSet::first() {	
	if (root == NULL) {
		throw "NoSuchElementException";
	}
    AVLNode *temp = root;
    while (temp->left) {
        temp = temp->left;
    }
    return temp->key;
}

int TreeSet::last() {
	if (root == NULL) {
		throw "NoSuchElementException";
	}
    AVLNode *temp = root;
    while (temp->right) {
        temp = temp->right;
    }
    return temp->key;
}
void _find(AVLNode *root, int val)
{
    if(root)
    {
        if(root->key < val)
        {
            _find(root->left, val);
            _find(root->right, val);
        }
    }
}
int TreeSet::higher(int val) {
	
    return -1; //test
}

int TreeSet::lower(int val) {
	// TODO
    return -1;  //test
}

int TreeSet::remove(int val) {
    AVLNode *newRoot;
    bool shorter;
    bool success;
    
    newRoot = _delete(root, val, shorter, success);
    if(success)
    {
        root = newRoot;
        count --;
        return true;
    }
    else
        return false;
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
