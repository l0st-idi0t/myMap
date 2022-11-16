// mymap.h
//
// TODO: write this file header comment.
#pragma once

#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>

using namespace std;

template<typename keyType, typename valueType>
class mymap {
 private:
    struct NODE {
        keyType key;  // used to build BST
        valueType value;  // stored data for the map
        NODE* left;  // links to left child
        NODE* right;  // links to right child
        int nL;  // number of nodes in left subtree
        int nR;  // number of nodes in right subtree
        bool isThreaded;
    };
    NODE* root;  // pointer to root node of the BST
    int size;  // # of key/value pairs in the mymap
    //
    // iterator:
    // This iterator is used so that mymap will work with a foreach loop.
    //
    struct iterator {
     private:
        NODE* curr;  // points to current in-order node for begin/end

     public:
        iterator(NODE* node) {
            curr = node;
        }

        keyType operator *() {
            return curr -> key;
        }

        bool operator ==(const iterator& rhs) {
            return curr == rhs.curr;
        }

        bool operator !=(const iterator& rhs) {
            return curr != rhs.curr;
        }

        bool isDefault() {
            return !curr;
        }

        //
        // operator++:
        //
        // This function should advance curr to the next in-order node.
        // O(logN)
        //
        iterator operator++() {
          if (curr -> isThreaded) {
              curr = curr -> right;
          } else {
              curr = curr -> right;
              while (curr -> left) {
                  curr = curr -> left;
              }
          }
          return iterator(curr);
        }
    };

    //copy function to copy BST tree
    void copyHelper(NODE* node) {
      if (node == nullptr) {
        return;
      }
      else {
        put(node->key, node->value);
        copyHelper(node->left);
        copyHelper(node->right);
      }
    }

    //helper for the toString function
    string toStringHelper(keyType key) {
      stringstream ss;
      ss << key;
      return ss.str();
    }

    void clearHelper(NODE* node) {
      if (node == nullptr) {
        return;
      }
      else {
        clearHelper(node->left);
        clearHelper(node->right);
        delete node;
      }
    }

    //helper function for the mymap balance method
    void checkBalanceHelper(NODE* node) {
      if (node == nullptr) {
        return;
      }
      else {
        checkBalanceHelper(node->left);
        checkBalanceHelper(node->right);
        if (node->left != nullptr) {
          node->nL = node->left->nL + node->left->nR + 1;
        }
        if (node->right != nullptr) {
          node->nR = node->right->nL + node->right->nR + 1;
        }
      }
    }

    //balance bst tree helper, no AVL rotations
    void balanceHelper(NODE* node) {
      //TODO: implement this function
    }

    //successor
    NODE* successor(NODE* curr) {
      if (curr->right != nullptr) {
        curr = curr->right;
        while (curr->left != nullptr) {
          curr = curr->left;
        }
        return curr;
      }
      else {
        NODE* parent = curr->right;
        while (parent != nullptr && curr == parent->right) {
          curr = parent;
          parent = parent->right;
        }
        return parent;
      }
    }

  public:
      //
      // default constructor:
      //
      // Creates an empty mymap.
      // Time complexity: O(1)
      //
      mymap() {
        root = nullptr;
        size = 0;
      }

      //
      // copy constructor:
      //
      // Constructs a new mymap which is a copy of the "other" mymap.
      // Sets all member variables appropriately.
      // Time complexity: O(nlogn), where n is total number of nodes in threaded,
      // self-balancing BST.
      //
      mymap(const mymap& other) {
        root = nullptr;
        size = 0;
        copyHelper(other.root);
      }

      //
      // operator=:
      //
      // Clears "this" mymap and then makes a copy of the "other" mymap.
      // Sets all member variables appropriately.
      // Time complexity: O(nlogn), where n is total number of nodes in threaded,
      // self-balancing BST.
      //
      mymap& operator=(const mymap& other) {
        if (this != &other) {
          clear();
          copyHelper(other.root);
        }
        return *this;
      }

      // clear:
      //
      // Frees the memory associated with the mymap; can be used for testing.
      // Time complexity: O(n), where n is total number of nodes in threaded,
      // self-balancing BST.
      //
      void clear() {
        if (root == nullptr) {
          return;
        }
        else {
          clearHelper(root);
          root = nullptr;
          size = 0;
        }
      }

      //
      // destructor:
      //
      // Frees the memory associated with the mymap.
      // Time complexity: O(n), where n is total number of nodes in threaded,
      // self-balancing BST.
      //
      ~mymap() {
        clear();
      }

      //
      // put:
      //
      // Inserts the key/value into the threaded, self-balancing BST based on the key.
      // Time complexity: O(logn + mlogm), where n is total number of nodes in the
      // threaded, self-balancing BST and m is the number of nodes in the
      // sub-tree that needs to be re-balanced.
      // Space complexity: O(1)
      //
      void put(keyType key, valueType value) {   
        NODE* newNode = new NODE;
        newNode->key = key;
        newNode->value = value;
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->nL = 0;
        newNode->nR = 0;
        newNode->isThreaded = false;

        if (root == nullptr) {
          root = newNode;
          size++;
        }
        else {
          NODE* curr = root;
          NODE* prev = nullptr;
          while (curr != nullptr) {
            prev = curr;
            if (key < curr->key) {
              curr = curr->left;
            }
            else if (key > curr->key) {
              curr = curr->right;
            }
            else {
              curr->value = value;
              return;
            }
          }
          if (key < prev->key) {
            prev->left = newNode;
            prev->nL++;
            newNode->right = prev;
            newNode->isThreaded = true;
          }
          else {
            prev->right = newNode;
            prev->nR++;
          }
          size++;
          balanceHelper(prev);
        }
      }

      //
      // contains:
      // Returns true if the key is in mymap, return false if not.
      // Time complexity: O(logn), where n is total number of nodes in the
      // threaded, self-balancing BST
      //
      bool contains(keyType key) {
        NODE* curr = root;
        while (curr != nullptr) {
            if (key < curr->key) {
                curr = curr->left;
            } 
            else if (key > curr->key) {
                if (curr->isThreaded) {
                    curr = nullptr;
                }
                else {
                    curr = curr->right;
                }
            }
            else {
                return true;
            }
        }
        return false;
      }


      //
      // get:
      //
      // Returns the value for the given key; if the key is not found, the
      // default value, valueType(), is returned (but not added to mymap).
      // Time complexity: O(logn), where n is total number of nodes in the
      // threaded, self-balancing BST
      //
      valueType get(keyType key) {
        NODE* curr = root;
        while (curr != nullptr) {
            if (key < curr->key) {
                curr = curr->left;
            } 
            else if (key > curr->key) {
                if (curr->isThreaded) {
                    curr = nullptr;
                } else {
                    curr = curr->right;
                }
            }
            else {
                return curr->value;
            }
            return valueType();
        }
      }


      //
      // operator[]:
      //
      // Returns the value for the given key; if the key is not found,
      // the default value, valueType(), is returned (and the resulting new
      // key/value pair is inserted into the map).
      // Time complexity: O(logn + mlogm), where n is total number of nodes in the
      // threaded, self-balancing BST and m is the number of nodes in the
      // sub-trees that need to be re-balanced.
      // Space complexity: O(1)
      //
      valueType operator[](keyType key) {
        if (contains(key)) {
            return get(key);
        }
        else {
            put(key, valueType());
            return valueType();
        }
      }

      //
      // Size:
      //
      // Returns the # of key/value pairs in the mymap, 0 if empty.
      // O(1)
      //
      int Size() {
        return size;
      }

      //
      // begin:
      //
      // returns an iterator to the first in order NODE.
      // Time complexity: O(logn), where n is total number of nodes in the
      // threaded, self-balancing BST
      //
      iterator begin() {
        NODE* curr = root;
        while (curr->left != nullptr) {
          curr = curr->left;
        }
        return iterator(curr);
      }


      //
      // end:
      //
      // returns an iterator to the last in order NODE.
      // this function is given to you.
      // 
      // Time Complexity: O(1)
      //
      iterator end() {
        return iterator(nullptr);
      }

      //
      // toString:
      //
      // Returns a string of the entire mymap, in order.
      // Format for 8/80, 15/150, 20/200:
      // "key: 8 value: 80\nkey: 15 value: 150\nkey: 20 value: 200\n
      // Time complexity: O(n), where n is total number of nodes in the
      // threaded, self-balancing BST
      //
      string toString() {
        string s = "";
        NODE* curr = root;
        while (curr->left != nullptr) {
          curr = curr->left;
        }
        while (curr != nullptr) {
          s += "key: " + toStringHelper(curr->key) + " value: " + toStringHelper(curr->value) + "\n";
          curr = successor(curr);
        }
        return s;
      }


      //
      // toVector:
      //
      // Returns a vector of the entire map, in order without using iterator  For 8/80, 15/150, 20/200:
      // {{8, 80}, {15, 150}, {20, 200}}
      // Time complexity: O(n), where n is total number of nodes in the
      // threaded, self-balancing BST
      //
      vector<pair<keyType, valueType>> toVector() {
        vector<pair<keyType, valueType>> v;
        NODE* curr = root;
        while (curr->left != nullptr) {
          curr = curr->left;
        }
        while (curr != nullptr) {
          v.push_back(make_pair(curr->key, curr->value));
          curr = successor(curr);
        }
        return v;
      }


      //
      // checkBalance:
      //
      // Returns a string of mymap that verifies that the tree is properly
      // balanced.  For example, if keys: 1, 2, 3 are inserted in that order,
      // function should return a string in this format (in pre-order):
      // "key: 2, nL: 1, nR: 1\nkey: 1, nL: 0, nR: 0\nkey: 3, nL: 0, nR: 0\n";
      // Time complexity: O(n), where n is total number of nodes in the
      // threaded, self-balancing BST
      //
      string checkBalance() {
        string s = "";
        checkBalanceHelper(root, s);
        return s;
      }


};