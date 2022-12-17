#pragma once

#include <iostream>

#include <sstream>

#include <algorithm>

#include <string>

#include <random>


using namespace std;


template <typename T> class priorityqueue{

    

private:

  struct NODE{

      

    int priority; // used to build BST

    T value;      // stored data for the p-queue

    bool dup;     // marked true when there are duplicate priorities

    NODE *parent; // links back to parent

    NODE *link;   // links to linked list of NODES with duplicate priorities

    NODE *left;   // links to left child

    NODE *right;  // links to right child

  };

    

  NODE *root; // pointer to root node of the BST

  int size;   // # of elements in the pqueue

  NODE *curr; // pointer to next item in pqueue (see begin and next)


public:

 

    //Step 1: create a default constructor O(1) => DONE

    priorityqueue(){

        size = 0;

        root = nullptr;

        curr = nullptr;

    }


    

    //Helper function to print the queue => DONE

    void printQueue(NODE *curr){

        

        if(curr != nullptr) {

          printQueue(curr -> left);

          cout << curr -> value << " " << curr -> priority << endl;

          printQueue(curr -> right);

        }

      }

    

    

    //Recursive helper function for toString() => DONE

    void _recursiveFunciton(NODE* targetNode, ostream& output){


        bool initializer = false;

        NODE *ptr = targetNode;

        

        if(targetNode -> left != nullptr){

            _recursiveFunciton(targetNode -> left, output);

        }

        

        try{

            if(targetNode -> left != nullptr){

                initializer = true;

                throw true;

                _recursiveFunciton(targetNode -> left, output);

            }

            else{

                initializer = false;

                throw false;

            }

        }

        catch(bool initializer){

            if(false){

                cout << "Error: node -> left == nullptr!" << endl;

            }

            else{

                //cout << "The program behaves correctly." << endl;

            }

        }


        

        while(ptr != nullptr){

            

            output << ptr -> priority << " value: " << ptr -> value << endl;

            ptr = ptr -> link;

        

        }


        

        if(targetNode -> right != nullptr){

            _recursiveFunciton(targetNode -> right, output);

        }

        

        return;

    }

    

    

    //Step 2: write toString() => returns a string of the entire priority queue, in order => DONE

    string toString(){

        

        stringstream str;

        

        //Check if the root is not empty

        if(root != nullptr){

            _recursiveFunciton(root, cout);

        }

        

        //Return an empty string

        return "";

    }

    

    

    //Helper function for next() => DONE

    bool equalityCaseHandler(){

        

        if(curr -> parent -> priority == curr -> priority){

            if(curr -> link == nullptr && curr -> dup == true){

                if(curr -> right != nullptr){

                    curr = curr -> right;

                    curr = curr -> parent;

                    if(curr -> left != nullptr){

                        curr = curr -> left;

                        return true;

                    }

                }

            }

        }

    }

    

    

    //Helper function for the clear() => deletes the subtrees => DONE

    void deleteTree(NODE* curNode){

        

        //Check if the current node is empty => throw an exception immediately

        try{

            if(curNode == NULL){

                throw false;

                return;

            }

            else{

                throw true;

            }

        }

        

        //Handle the exception

        catch(bool decision){

            if(decision == false){

                //cout << "The current node is empty!" << endl;

                return;

            }

            else{

                //Delete both subtrees

                deleteTree(curNode -> left);

                deleteTree(curNode -> right);

            }

        }

      

        delete curNode;

    }

    

    

    //Step 3: clear() => frees the memory associated with the priority queue but is public => DONE

    void clear(){

       

        NODE* generic = root;

        

        try{

            if(root == nullptr){

                throw false;

                //return;

            }

        }

        catch(bool decision){

            //cout << "The root has reached a nullptr!" << endl;

            return;

        };

        

        //Begin the recursive function on the generic node => DONE

        deleteTree(generic);

        

        root = nullptr;

        size = 0;

        curr = nullptr;

        

    }

    

    

    //Helper function for next() => DONE

    bool equalityCaseHandle(){

        

        do{

             curr = curr -> parent;

            

        }while(curr != curr -> parent -> left && curr -> parent != nullptr);

         

         if(curr -> parent == nullptr){

             curr = nullptr;

             return false;

         }

         if(curr == curr -> left){

             curr = curr -> parent;

         }

         return true;

        

    }


    

    //Reference: zybooks (Linked Lists + BST)

    NODE* recursiveDuplicator(NODE* curNode, NODE* other){

        

        //Step 1: check if the node has no duplicates

        if(other == nullptr){

            return nullptr;

        }

        

        curNode = new NODE();

        curNode -> value = other -> value;

        curNode -> priority = other -> priority;

        curNode -> left = nullptr;

        curNode -> right = nullptr;

        curNode -> link = nullptr;

        curNode -> parent = nullptr;

        curNode -> dup = other -> dup;

        

        //Step 2: save the parent, links + traverse the BST to the right and left

        curNode -> link = recursiveDuplicator(curNode -> link, other -> link);

        curNode -> parent = other -> parent;

        curNode -> right = recursiveDuplicator(curNode -> right, other -> right);

        curNode -> left = recursiveDuplicator(curNode, other -> left);

        

        return curNode;

    }

    

    

    //Step 4: create a priorityqueue &operator= => clears *this + makes a copy of the other => DONE

    //Reference: ourvector.h by Professor Koehler

    priorityqueue &operator=(const priorityqueue &other) {


        this -> clear();

        this -> curr = curr;

        this -> size = other.size;

        NODE* curNode = other.root;

        

        try{

            if(curNode == nullptr){

                throw false;

            }

        }

        catch(bool decision){

            if(decision == false){

                cout << "The current node is a nullptr!" << endl;

            }

        }

        

        this -> root = recursiveDuplicator(this -> root, curNode);

        

        return *this;

    }



    //Step 5: create a destructor => DONE

    ~priorityqueue(){


        //cout << "The destructor is called!" << endl;

      

        if(root != nullptr){

            cout << endl << "Initializaing the destruction protocol." << endl;

            root = nullptr;

            size = 0;

            curr = nullptr;

            clear();

            return;

        }

      

        clear();

        root = nullptr;

        size = 0;

        curr = nullptr;

      

        //cout << "The end of the destruction call." << endl;

    }


    

    //Helper function for enqueue() => helps to insert new children inside the BST using recursive insertion algorithm => DONE

    void treeBuilder(NODE *newNode, NODE *current){

        

        

        if(newNode -> priority > current -> priority){

            if(current -> right != nullptr){

                //size++;

                return treeBuilder(newNode, current -> right);

            }

            current -> right = newNode;

        }

        else if(newNode -> priority == current -> priority){

            NODE *cursor = current;

            while(cursor -> link != nullptr){

                //size++;

                cursor = cursor -> link;

            }

            cursor -> link = newNode;

        }

        else if(newNode -> priority != current -> priority){

            try{

                if(false){

                    throw false;

                }

                else{

                    throw true;

                }

            }

            catch(bool choice){

                if(newNode -> priority == current -> priority && choice == false){

                    NODE *cursor = current;

                    while(cursor -> link != nullptr){

                        //size++;

                        cursor = cursor -> link;

                    }

                    cursor -> link = newNode;

                }

            }

        }

        else{

            if(current -> left != nullptr){

                //size++;

                return treeBuilder(newNode, current -> left);

            }

            current -> left = newNode;

        }

    

}

        

    

    //Step N: create enqueue() => inserts the value into the custom BST in the correct location based on priority => DONE

  void enqueue(T value, int priority){

      

      

      NODE *myNode = new NODE();

      myNode -> value = value;

      myNode -> priority = priority;


      if(root == nullptr){

          root = myNode;

      }

      else{

          //Insert new nodes

          treeBuilder(myNode, root);

      }

      

      //Increase the size after insertion

      size++;

  }


    

    //Step N: peek() => returns the value of the next element in the priority queue but does not remove the item from the priority queue. => DONE

    T peek(){

      

        T object;

        NODE* curr = root;

      

        try{

            if(root == nullptr){

                cout << "The root is empty!" << endl;

                throw false;

            }

            else{

                throw true;

            }

        }

        catch(bool decision){

            if(decision == false){

                return object;

            }

            else{

                while(curr -> left != nullptr){

                    curr = curr -> left;

                }

            }

        }

      

        object = curr -> value;

          

        return object;

    }


    

    //Helper function for dequeue() => returns the value of the next element in the priority queue and removes the element from the priority queue => DONE

    NODE* dequeEngine(NODE *target){

        

        //Step 1: initialize the object => used for storing the result from recursion

        T object;

        bool starter = true;

      

      

        //Step 2: begin the loop

        do{

            try{

                //Step 3: check if the passed argument's left child is not empty

                if(target -> left != nullptr){

                    throw true;

                }

                else if(target -> link != nullptr){

                    target -> link -> right = target -> right;

                    return target -> link;

                }

                else{

                    throw false;

                }

            }

            catch(bool decision){

                if(decision == true){

                    //Step 4: store the recursive result inside the object of type NODE* => assign it to the child => return the target node

                    NODE* object = dequeEngine(target -> left);

                    target -> left = object;

                    return target;

                }

                else{

                    if(!decision){

                        starter = false;

                        break;

                    }

                }

            }

          

        }while(starter == true);

      

      

        return target -> right;

    }




    //Step N: dequeue() => returns the value of the next element in the priority queue and removes the element from the priority queue.

    T dequeue(){

        

        T object;

        bool generator = true;


        

        //Use peek() to get the value of the next element in the priority queue => TA OH

        object = peek();

        

        do{

            try{

                if(root != nullptr){

                    size--;

                    throw true;

                }

                else{

                    throw false;

                }

            }

            catch(bool decision){

                if(decision == true){

                    if(root != nullptr){

                        root = dequeEngine(root);

                        return object;

                    }

                }

                else{

                    if(root == nullptr && Size() == 0){

                        cout << "The root is empty!" << endl;

                        generator = false;

                        break;

                    }

                }

            }

        }while(generator == true);

        

        if(Size() == 0 || size == 0){

            cout << "All the elements were removed." << endl;

        }

        

        return object;

    }


  

    

    //Step N: create Size() => returns the # of elements in the priority queue, 0 if empty => DONE

    int Size(){

        

        if(size != 0){

            return size;

        }

        else{

            return 0;

        }

        

        return size;

    }


    

    /*Step N: begin() => resets internal state for an inorder traversal.

    After the call to begin(), the internal state denotes the first inorder node;

    this ensure that first call to next() function returns the first inorder node value. => FIXME

    */

    

    void begin(){

      

        cout << "The begin() is called!" << endl;

      

        try{

            if(root == nullptr){

                throw false;

                return;

            }

            else{

                throw true;

            }

        }

        catch(bool decision){

            if(decision == true){

                curr = root;

                while(curr -> left != nullptr) {

                    curr = curr -> left;

                }

            }

            else{

                cout << "Error detected inside begin() function!" << endl;

            }

        }

    }

    

    

    //Helper function for next() => DONE

    bool equality(int& priority, T& value, bool& starter){

        

        

        do{

            try{

                if(!(curr -> parent -> priority == curr -> priority && curr -> dup == true && curr -> link == nullptr)){

                    throw 1;

                }

                else if(!(priority == curr -> priority)){

                    throw 2;

                }

                else{

                    throw 3;

                }

            }

            catch(int decision){

                switch(decision){

                        

                    case 1:

                        if(curr -> parent -> priority == curr -> priority && curr -> dup == true && curr -> link == nullptr){

                            cout << "Activating recursion!" << endl;

                            return equalityCaseHandler();

                        }

                        

                    case 2:

                        if(priority == curr -> priority){

                            while(curr -> link != nullptr){

                                curr = curr -> link;

                            }

                        }

                        

                    case 3:

                        cout << "Activating recursion!" << endl;

                        return equalityCaseHandle();

                        

                    default:

                        starter = false;

                }

            }

        }while(starter == true);

    }

        

    

    

    //

    // next

    //

    // Uses the internal state to return the next inorder priority, and

    // then advances the internal state in anticipation of future

    // calls.  If a value/priority are in fact returned (via the reference

    // parameter), true is also returned.

    //

    // False is returned when the internal state has reached null,

    // meaning no more values/priorities are available.  This is the end of the

    // inorder traversal.

    //

    // O(logn), where n is the number of unique nodes in tree

    //

    // Example usage:

    //    pq.begin();

    //    while (pq.next(value, priority)) {

    //      cout << priority << " value: " << value << endl;

    //    }

    //    cout << priority << " value: " << value << endl;

    //

      

      /*

       If the right subtree of the node is not empty, then the next inorder node lies in the right subtree.  Go to the right subtree and return the node with the minimum priority in the right subtree.

       If the right subtree is empty, then the next inorder node is one of its ancestors.  Travel up the tree using the parent pointer until you see a node which is the left child of its parent.  The parent of such a node is the next inorder node.


       */

    bool next(T& value, int &priority) {

         

        

        bool starter = false;

        

        try{

            if(curr != nullptr){

                //size = size;

                return false;

            }

            else{

                throw true;

            }

        }

        catch(bool decision){

            if(decision == true){

                priority = curr -> priority;

                value = curr -> value;

                starter = true;

                bool result = equality(priority, value, starter);

                return result;

            }

            else{

                return false;

            }

        }

  }

    

    

    //Step 4: overload eqauls operator => returns true if this priority queue as the priority queue passed in as other. Otherwise returns false => FIXME

    bool operator==(const priorityqueue &other) const{

      

        //Step 1: check if the size is not equal to the other's size

        if(this -> size != other.size){

            //cout << "The size is not equal to the size of other! Returning false!" << endl;

            return false;

        }

        else{

            

            NODE *curNode1 = root;

            NODE *curNode2 = other.root;

            

            do{

                if(curNode1 -> value != curNode2 -> value){

                    cout << "operator == returns false!" << endl;

                    return false;

                }

                else{

                    return true;

                }

                

                curNode1 = curNode1 -> link; //links to linked list of NODES with duplicate priorities

                curNode2 = curNode2 -> link; //links to linked list of NODES with duplicate priorities

            }while(curNode1 != nullptr && curNode2 != nullptr);

            

            return true;

        }

        

        return true;

    }


    

  

    //Step N: getRoot() => returns the root node for testing => DONE

    NODE *getRoot() { return root; }

};
