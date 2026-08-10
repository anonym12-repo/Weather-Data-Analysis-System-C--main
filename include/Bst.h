#ifndef BST_H
#define BST_H

//#include <iostream>

/**
 * @class Bst
 * @brief A template binary search tree implementation
 *
 * T The type of data to store in the BST. Must support comparison operators.
 *
 * This class maintains the BST property where for any node:
 * - All left subtree nodes have values <= current node
 * - All right subtree nodes have values >= current node
 * - All operations are implemented recursively.
 */
template <class T>
class Bst {

public:

     typedef void (*f1Type)(const T&); /// Function pointer type for traversal callbacks
     typedef bool (*f2Type)(const T&); /// Function pointer type for traversal callbacks

     /**
     * @brief Default constructor
     * Creates an empty BST (root pointer is set to nullptr)
     */
     Bst();

     /**
     * @brief Destructor
     *
     * Frees all dynamically allocated nodes in the BST.
     *
     * @post All memory used by tree nodes is released.
     */
     ~Bst();

     /**
     * @brief Copy constructor (deep copy)
     *
     * Creates an independent copy of another BST by cloning all nodes.
     *
     * @param other - The BST to copy.
     * @post This BST becomes a deep copy of `other`.
     */
     Bst(const Bst& other);

     /**
     * @brief Copy assignment operator (deep copy)
     *
     * Assigns one BST to another, performing deep copy of all nodes.
     * Handles self-assignment safely.
     *
     * @param other - The BST to assign from.
     * @return Bst& - Reference to this BST.
     * @post This BST becomes an independent copy of `other`.
     */
     Bst& operator=(const Bst& other);

     /**
     * @brief Inserts a value into the BST
     * @param value The data value to insert
     * @pre Type T must support comparison operators and be copyable
     * @post Value is inserted maintaining BST property, tree size increases by 1
     */
     void insert(const T& value);

     /**
     * @brief Searches for a value in the BST
     * @param value The data value to search for
     * @return true if value is found, false otherwise
     * @pre Type T must support comparison operators
     * @post BST remains unchanged
     */
     bool search(const T& value) const;

     /**
     * @brief Performs an in-order traversal of the BST.
     *
     * Visits all nodes in ascending order (left subtree → current node → right subtree).
     * Each visited node is processed using the provided callback function only if
     * the optional condition function evaluates to true for that node's data.
     *
     * @param callback Function pointer to apply to each node’s data that meets the condition.
     * @param condition Function pointer that determines whether a node should be processed.
     *        If nullptr, all nodes are visited unconditionally.
     * @pre Both function pointers must be valid, and @p condition may be nullptr.
     * @post Tree structure remains unchanged.
     */
     void inOrderTraversal(f1Type callback, f2Type condition) const;

     /**
     * @brief Performs a pre-order traversal of the BST.
     *
     * Visits each node in the order: current node → left subtree → right subtree.
     * Each node is processed using the provided callback only if the condition function
     * evaluates to true for that node's data.
     *
     * @param callback Function pointer to apply to each node’s data that meets the condition.
     * @param condition Function pointer that determines whether a node should be processed.
     *        If nullptr, all nodes are visited unconditionally.
     * @pre Both function pointers must be valid, and @p condition may be nullptr.
     * @post Tree structure remains unchanged.
     */
     void preOrderTraversal(f1Type callback, f2Type condition) const;

     /**
     * @brief Performs a post-order traversal of the BST.
     *
     * Visits each node in the order: left subtree → right subtree → current node.
     * Each node is processed using the provided callback only if the condition function
     * evaluates to true for that node's data.
     *
     * @param callback Function pointer to apply to each node’s data that meets the condition.
     * @param condition Function pointer that determines whether a node should be processed.
     *        If nullptr, all nodes are visited unconditionally.
     * @pre Both function pointers must be valid, and @p condition may be nullptr.
     * @post Tree structure remains unchanged.
     */
     void postOrderTraversal(f1Type callback, f2Type condition) const;

private:

     /**
     * @struct Node
     * @brief Represents a single node in the BST.
     */
     struct Node{
        T data;       ///< value stored in this node
        Node* left;   ///< Pointer to left child
        Node* right;  ///< Pointer to right child

         /**
         * @brief Node constructor
         * Constructs a node with a value, left and right children set to nullptr.
         * @pre Type T must be copyable
         * @post Node is created with given value and null children
         */
         Node(const T& value)
         :data(value), left(nullptr), right(nullptr){}
    };

    Node* root; ///< Pointer to root node of BST

    /**
     * @brief Recursively inserts a new value into the BST.
     *
     * Traverses the tree starting from the given node and places the new
     * value in the correct position to maintain the BST property.
     *
     * @param node Pointer to the current node in the recursive traversal.
     * @param value The value to insert into the tree.
     * @return Node* Updated node pointer after insertion.
     * @pre node may be nullptr or a valid node in the BST.
     * @post Returns pointer to the subtree root after insertion.
     */
     Node* insertRecursive(Node* node, const T& value);

    /**
     * @brief Recursively searches for a value in the BST.
     *
     * Traverses the tree starting from the given node and compares
     * the target value to node data to locate the element.
     *
     * @param node Pointer to the current node in traversal.
     * @param value The value to search for.
     * @return bool True if value is found, false otherwise.
     * @pre node may be nullptr or a valid BST node.
     * @post Does not modify the tree.
     */
     bool searchRecursive(Node* node, const T& value) const;

    /**
     * @brief Recursively deletes all nodes in the BST.
     *
     * Performs a post-order traversal to delete each node and free memory.
     * Used internally by the destructor and assignment operator.
     *
     * @param node Pointer to the current subtree root.
     * @pre node may be nullptr or a valid node.
     * @post All nodes in the subtree are deallocated.
     */
     void deleteTreeRecursive(Node* node);

    /**
     * @brief Performs in-order traversal recursively.
     *
     * Recursively visits the left subtree, processes the current node if it meets
     * the specified condition, and then visits the right subtree. Produces a sorted
     * sequence of node values for BST data.
     *
     * @param node Pointer to the current node being visited.
     * @param callback Function pointer applied to each node’s data that meets the condition.
     * @param condition Function pointer used to test whether the node should be processed.
     *        If nullptr, all nodes are processed.
     * @pre @p node may be nullptr or a valid BST node; both function pointers must be valid.
     * @post Tree structure remains unchanged.
     */
     void inOrderRecursive(Node* node,f1Type callback,f2Type condition) const;

    /**
     * @brief Performs pre-order traversal recursively.
     *
     * Recursively processes the current node first (if it meets the condition),
     * then visits the left and right subtrees. Used when node data must be handled
     * before its children.
     *
     * @param node Pointer to the current node being visited.
     * @param callback Function pointer applied to each node’s data that meets the condition.
     * @param condition Function pointer used to test whether the node should be processed.
     *        If nullptr, all nodes are processed.
     * @pre @p node may be nullptr or a valid BST node; both function pointers must be valid.
     * @post Tree structure remains unchanged.
     */
     void preOrderRecursive(Node* node,f1Type callback,f2Type condition) const;

    /**
     * @brief Performs post-order traversal recursively.
     *
     * Visits left and right subtrees first, then processes the current node last.
     * Commonly used for safely deleting nodes or copying structures.
     *
     * @param node Pointer to the current node.
     * @param callback Function pointer to apply to each node’s data.
     * @pre callback must be a valid function accepting (T&).
     * @post Tree structure remains unchanged.
     */
     void postOrderRecursive(Node* node,f1Type callback,f2Type condition) const;

    /**
     * @brief Performs post-order traversal recursively.
     *
     * Recursively visits the left and right subtrees first, then processes the current
     * node if it meets the specified condition. Commonly used for deleting nodes,
     * copying trees, or performing cleanup tasks.
     *
     * @param node Pointer to the current node being visited.
     * @param callback Function pointer applied to each node’s data that meets the condition.
     * @param condition Function pointer used to test whether the node should be processed.
     *        If nullptr, all nodes are processed.
     * @pre @p node may be nullptr or a valid BST node; both function pointers must be valid.
     * @post Tree structure remains unchanged.
     */
     Node* copyConstRecursive(Node* node);
};

//===============
//IMPLEMENTATION
//===============

template <class T>
Bst<T>::Bst()
:root(nullptr) //initializes root to nullptr empty tree
{}

template <class T>
Bst<T>::~Bst() {
    deleteTreeRecursive(root); //Recursively delete all nodes
    root = nullptr; // Reset root to null for safety
}

//copy constructor: create a deep copy of another BST
template <class T>
Bst<T>::Bst(const Bst& other)
:root(nullptr) // Initialize this tree s root to null
{
    // recursively copy other tree
    root = copyConstRecursive(other.root);
}

//assignment operator: assign one BST to another (deep copy)
template <class T>
Bst<T>& Bst<T>::operator=(const Bst& other)
{
    if (this != &other) // Avoid self-assignment
    {
        deleteTreeRecursive(root); //delete current tree
        root = copyConstRecursive(other.root); // deep copy from other
    }
    return *this; // Return self-reference
}

template <class T>
void Bst<T>::insert(const T& value) {
    root = insertRecursive(root, value); //insert starting from root
}

template <class T>
bool Bst<T>::search(const T& value) const {
    return searchRecursive(root, value);
}

// In-order traversal: left > root > right
template <class T>
void Bst<T>::inOrderTraversal(f1Type callback,f2Type condition) const {
    //std::cout << "In-order traversal: ";
    inOrderRecursive(root,callback,condition);
    //std::cout << std::endl;
}

// Pre-order traversal: root > left > right
template <class T>
void Bst<T>::preOrderTraversal(f1Type callback,f2Type condition) const {
    //std::cout << "Pre-order traversal: ";
    preOrderRecursive(root,callback,condition);
    //std::cout << std::endl;
}

// Post-order traversal: left > right > root
template <class T>
void Bst<T>::postOrderTraversal(f1Type callback,f2Type condition) const {
    //std::cout << "Post-order traversal: ";
    postOrderRecursive(root,callback,condition);
    //std::cout << std::endl;
}

//helper methods
template <class T>
typename Bst<T>::Node* Bst<T>::insertRecursive(Node* node, const T& value) {

    //if found empty spot, create new node
    if (node == nullptr){
        // Create and return a new node containing value
        return new Node(value);
    }

    // Recurse left if value <= current node s value
    if (value < node->data){
        // If the value is smaller or equal, go to left subtree
        node->left = insertRecursive(node->left, value);
    }else if(value > node->data){
        // Value greater then go right
        node->right = insertRecursive(node->right, value);
    }else{
        return node;
    }
    return node;
}

template <class T>
bool Bst<T>::searchRecursive(Node* node, const T& value) const {
    if (node == nullptr) {
        // Reached empty leaf then not found
        return false;
    }
    if (node->data == value){
        return true;
    }

    if (value <= node->data){
        // Search in left subtree
        return searchRecursive(node->left, value);
    }else{
        // Search in right subtree
        return searchRecursive(node->right, value);
    }
}

//Recursively deletes all nodes (used by destructor)
template <class T>
void Bst<T>::deleteTreeRecursive(Node* node){
    // If subtree exists
    if (node != nullptr){
        // Delete left subtree first then right subtree then delete node
        deleteTreeRecursive(node->left);
        deleteTreeRecursive(node->right);
        delete node;
    }
}

//In-order traversal: Left to Root to Right
template <class T>
void Bst<T>::inOrderRecursive(Node* node,f1Type callback,f2Type condition) const{
    // If node exists
    if (node != nullptr) {
        inOrderRecursive(node->left,callback, condition); // Traverse left subtree first
        if (!condition || condition(node->data)){  //condition check added
            callback(node->data);
        }
        //std::cout << node->data << " "; // Then visit (print) current node s data
        inOrderRecursive(node->right,callback, condition); // Finally, traverse right subtree
    }
}

//Pre-order traversal: Root to Left to Right
template <class T>
void Bst<T>::preOrderRecursive(Node* node, f1Type callback, f2Type condition) const{
    if (node != nullptr) { // If node exists
        //std::cout << node->data << " "; // Visit (print) current node s data first
        if (!condition || condition(node->data)){  //condition check added
            callback(node->data);
        }
        preOrderRecursive(node->left, callback, condition);  // Then traverse left subtree
        preOrderRecursive(node->right, callback,condition); // Then traverse right subtree
    }
}

//Post-order traversal: Left to Right to Root
template <class T>
void Bst<T>::postOrderRecursive(Node* node, f1Type callback, f2Type condition) const{
    if (node != nullptr) { // If node exists
        postOrderRecursive(node->left,callback,condition);  // Visit left subtree first
        postOrderRecursive(node->right,callback,condition); // Then visit right subtree
        if (!condition || condition(node->data)){  //condition check added
        callback(node->data);
        }
        //std::cout << node->data << " "; // Visit (print) current node last
    }
}

// Clones an entire tree recursively (for deep copy)
template <class T>
typename Bst<T>::Node* Bst<T>::copyConstRecursive(Node* node)
{
    if (node == nullptr){ //if empty subtree
        return nullptr;
    }
    Node* newNode = new Node(node->data); // Create new node copying current node s data
    newNode->left = copyConstRecursive(node->left);   // copy left subtree
    newNode->right = copyConstRecursive(node->right); // copy right subtree
    return newNode;  // Return pointer to new cloned subtree root
}


#endif // BST_H

