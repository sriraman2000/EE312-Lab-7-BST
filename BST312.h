//
// Created by srira on 11/13/2019.
//

#ifndef LAB7BST_BST312_H
#define LAB7BST_BST312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312 & src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType &);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal();

/****************************
inOrderTraversal

Function: Returns the inOder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);


private:
    struct TreeNode {
        ItemType data;
        TreeNode *left;
        TreeNode *right;
    };

    TreeNode * root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode *originalTree);

};

/*******************************
//Function implementations
********************************/

template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312 & src)
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();

}


template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}


template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode *tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}



//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{

    while (t->right != NULL)
        t = t->right;

    data = t->data;

}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}


template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    //YOUR CODE GOES HERE
    if(t->left != NULL)
    {
        makeEmpty(t->left);
    }
    else
    {
        delete(t->left);
    }
    if(t->right != NULL)
    {
        makeEmpty(t->right);
    }
    else
    {
        delete(t->right);
    }

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}



template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode *temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }

}


template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{

    //YOUR CODE GOES HERE
    if(t == NULL) // if the tree is empty
    {
        TreeNode ins;       // initialize/create a new treeNode
        TreeNode *inserted = &ins;
        inserted->data = newItem;
        inserted->right = NULL;
        inserted->left = NULL;
        t->right = inserted; // choose to insert it into the right hand side of the tree node
    }
    else if(newItem >= t->data) // if the new item is the same as one of the existing items, just put it on the right
    {
        if(t->right == NULL)
        {
            TreeNode ins;       // initialize/create a new treeNode
            TreeNode *inserted = &ins;
            inserted->data = newItem;
            inserted->right = NULL;
            inserted->left = NULL;
            t->right = inserted; // insert node
        }
        else
        {
            insertItem(t->right, newItem);
        }
    }
    else if(newItem < t->data)
    {
        if(t->left == NULL)
        {
            TreeNode ins;       // initialize/create a new treeNode
            TreeNode *inserted = &ins;
            inserted->data = newItem;
            inserted->right = NULL;
            inserted->left = NULL;
            t->right = inserted; // insert node
        }
        else
        {
            insertItem(t->left, newItem);
        }
    }

}

template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    //YOUR CODE GOES HERE
    insertItem(root, newItem);
}



template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    //YOUR CODE GOES HERE
    int count = 0;
    if(t == NULL)
    {
        return count;
    }
    else
    {
        return countNodes(t->left) + countNodes(t->right) + 1; // the current Node is added to the sum of its predecessors
    }
}


template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    //YOUR CODE GOES HERE
    return countNodes(root);
}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if(t == NULL)
    {
        return;
    }
    result.push_back(t->data);
    preOrderTraversal(t->left, result);
    postOrderTraversal(t->right, result);

}


template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> preOrder;
    preOrderTraversal(root, preOrder);
    return preOrder;

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if(t == NULL)
    {
        return;
    }
    postOrderTraversal(t->left, result);
    result.push_back(t->data);
    postOrderTraversal(t->right, result);
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> inOrder;
    inOrderTraversal(root, inOrder);
    return inOrder;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if(t == NULL)
    {
        return;
    }
    postOrderTraversal(t->left, result);
    postOrderTraversal(t->right, result);
    result.push_back(t->data);
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> postOrder;
    postOrderTraversal(root, postOrder);
    return postOrder;
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{

    //YOUR CODE GOES HERE
    if(root == NULL)
    {
        return false;
    }
    else
    {
        if(root->data == item)
        {
            return true;
        }
        else
        {
            TreeNode *t = root;
            while(t != NULL)
            {
                if(item > t->data)
                {
                    t = t->right;
                }
                else if(item < t->data)
                {
                    t = t->left;
                }
                else
                {
                    return true;
                }
            }
        }
    }

}


#endif //LAB7BST_BST312_H
