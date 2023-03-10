/**
 * @file stree.cpp
 * Definitions of the n-ary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include "stree.h"


NaryTree::NaryTree()
    : root(NULL)
{ /* nothing */
}

NaryTree::~NaryTree()
{
    clear(root);
}

void NaryTree::clear()
{
    clear(root);
    root = NULL;
}

/**
 * @return The root of the Nary tree.
 */

typename NaryTree::Node* NaryTree::getRoot() const
{
    return root;
}


/**
 * @return Prints a text representation of the edge connections of the NaryTree
 */

void NaryTree::print() 
{
    if (root == NULL){
        std::cout << "x" << std::endl;
    } else{ 
        std::cout << "o" << std::endl;
        std::vector<bool> dflag(this->height(),false);
        printHelper(root, 0, "", dflag);
        std::cout << std::endl;
    }

}

void NaryTree::printHelper(Node*& node, int depth, std::string partial, std::vector<bool> dflag) {
    
    std::map<std::string,Node*>::iterator it;
    std::vector<std::string> keyList;
    for (it = node->children.begin(); it != node->children.end(); it++){
        keyList.push_back(it->first);
    }

    std::sort(keyList.begin(),keyList.end()); 

    for(size_t i = 0; i < keyList.size(); ++i){
        std::string spacing = "";

        for(int j = 0; j < depth; ++j){
            if(dflag[j]){
                spacing+= "|    ";
            } else{
                spacing+= "     ";
            }
        }

        for(size_t q = 0; q < partial.size(); ++q){
            spacing += " ";
        }

        std::cout << spacing;

        std::cout << "+--" << keyList[i] << "--o" << std::endl;

        if (i < keyList.size() - 1){
            dflag[depth] = true;
        } else{
            dflag[depth] = false;
        }

        printHelper(node->children[keyList[i]], depth+1, partial+keyList[i],  dflag);

    }
}


void NaryTree::insert(const std::string& s, int i)
{
    insert(root, s, i);
}


void NaryTree::insert(Node*& node, const std::string & s, int i)
{
    // If we're at a NULL pointer, we make a new Node
    if (node == NULL) {
        node = new Node(s, i);
    } else {
        if(s.length() > 0 ){
            std::string f = s.substr(0,1);
            if(node->children.count(f) > 0){ //If this character is already an edge
                insert(node->children[f],s.substr(1), i); // move down the branch and try again (minus 1 char)
            }else{
                node->children[f] = new Node(s.substr(1), i); // If we haven't seen this edge, fill in the rest of the branch
            }
        } else{ // If end of the path, store our value
            node->index = i;
        }
    }
}


void NaryTree::clear(NaryTree::Node* subRoot)
{
    if (subRoot == NULL)
        return;

    std::map<std::string,Node*>::iterator it;
    for (it = subRoot->children.begin(); it != subRoot->children.end(); it++){
        clear(it->second);
    }
    
    delete subRoot;
}

/**
 * @return The height of the Nary tree. Recall that the height of a 
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
int NaryTree::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
int NaryTree::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    std::map<std::string,Node*>::const_iterator it;
    int max = -1;
    for (it = (subRoot->children).begin(); it != (subRoot->children).end(); it++){
        int temp = height(it->second);
        if (temp > max){
            max = temp;
        }
    }
    return 1 + max;
}

void NaryTree::inLexOrder(std::vector<std::string>& treeVector){
    inLexOrder(root, treeVector);
}

void NaryTree::inLexOrder(Node* subRoot, std::vector<std::string>& treeVector){
    if(subRoot == NULL){
        return;
    }

    std::map<std::string,Node*>::iterator it;
    for (it = subRoot->children.begin(); it != subRoot->children.end(); it++){
        treeVector.push_back(it->first);
        inLexOrder(it->second, treeVector);
    }

}

/*
 YOUR CODE BEGINS HERE.
*/


/**
 * Returns a NaryTree encoding the suffix-trie for a std::string T.
 *
 * @param T A std::string object which holds the text being pre-processed.
 *
 * @return An N-ary Tree storing a full n-dimensional suffix trie
 */
NaryTree build_strie(std::string T){
    // Insert All Suffixes
    NaryTree myTree;
    for (unsigned long i{0}; i <= T.length(); ++i) {
        std::string substring = T.substr(i) + "$";
        myTree.insert(substring, i);
    }

    return myTree;
}

/**
 * Returns all the leaf pointers for the current subtree
 *
 * @param subRoot A Node* object pointing to the current subtree's root
 *
 * @return Pointers to all leaves in the subtree stored in leafList
 */
void NaryTree::getLeaves(Node* subRoot, std::vector<Node*>& leafList){
    // Base Case: Leaf Node
    if (subRoot->index >= 0) {
        leafList.push_back(subRoot); return;
    }

    // Recursive Through All Children in std::map
    for (auto it : subRoot->children)
        getLeaves(it.second, leafList);

    return;
}


/**
 * Returns all the exact matches for the input string s
 *
 * @param s A std::string storing the pattern of interest
 *
 * @return An std::vector<int> storing all matching indices (or -1)
 */
std::vector<int> NaryTree::patternMatch(const std::string & s){
    // Check Empty String
    if (this->root == NULL)
        return {-1};

    // Call Helper Function
    std::vector<int> outList;
    patternMatch(s, root, outList);

    // No Matches
    if (outList.size() == 0)
        return {-1};

    return outList;
}


/**
* Private helper function for the patternMatch function.
* @param s The pattern being matched
* @param subRoot The current node in the recursion
* @param outList stores the output index values
*/
void NaryTree::patternMatch(const std::string& s, Node* subRoot, std::vector<int>& outList){
    // Iterate Until No Matches 
    int ptr = 0;
    int length = static_cast<int>(s.length());
    while (1) {
        auto it = subRoot->children.find(s.substr(ptr,1));

        // Found Path
        if (it != subRoot->children.end()) {
            ptr++;
            subRoot = it->second;
        } else {
            break;
        }
    }
    
    // Check Valid Prefix
    if (ptr != length)
        return;

    // Find Indexes @ Leaf Nodes
    std::vector<Node*> leafList;
    getLeaves(subRoot, leafList);

    // Process Leaf List
    for (auto it: leafList)
        outList.push_back(it->index);
    
    return;
}

/**
 * Converts a NaryTree encoding the suffix-trie to a NaryTree encoding a suffix-tree
 * The same tree object is used for both encodings
 */
void NaryTree::trie_to_tree(){
    trie_to_tree(root);
}

/**
 * Support function for suffix trie to suffix tree conversion
 *
 * @param subRoot A Node* object pointing to the current subtree's root
 *
 * @return A direct edit to the current tree replacing trie edges with tree edges
 */
void NaryTree::trie_to_tree(Node* subRoot) {
    // Base Case: Leaf Node
    if (subRoot->isLeaf()) {return;}

    // Coalesce Paths that Don't Branch (size == 1)
    std::vector<std::string> remove_keys;
    for (auto it: subRoot->children) {
        // Coalesce
        if (it.second->children.size() == 1) {
            // Node to Remove
            auto next = it.second->children.begin();

            // Modify Key and Edge
            std::string s = it.first + next->first;
            subRoot->children.insert(std::make_pair(s, next->second));

            // Remove Temporary Edge
            remove_keys.push_back(it.first);
        }
    }

    // Remove Nodes
    for (auto it: remove_keys)
        subRoot->children.erase(it);

    // Recursive Case: Visit Children
    for (auto it: subRoot->children)
        trie_to_tree(it.second);
}

