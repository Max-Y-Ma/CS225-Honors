/**
 * @file stree.h
 * Declaraction of the NaryTree class. You will probably need to modify this
 *  file to add helper functions.
 */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

/**
 * The NaryTree class represents a linked-memory tree data structure.
 */
//template <typename T>
class NaryTree
{
    public:
        /**
         * Represents a tree node; that is, an element in a NaryTree.
         * It has an integer storing the index (only used in leaves)
         * and a map linking characters to child pointers
         */
        struct Node {
            int index = -12; //don't edit this if you want to pass tests
            std::map<std::string, Node*> children;

            /**
             * Node element constructor; Given S, creates a path from root to leaf
             * Also stores the index position of S at the leaf of the path
             * @param s The string being stored starting at current Node
             * @param i The integer storing the index pos of S in T
             */
            Node(std::string s, int i) 
            { 
                if(s.length() > 0 ){
                    std::string f = s.substr(0,1);
                    children[f] = new Node(s.substr(1), i );
                } else{
                    index = i;
                }
            }

            // Support function to check whether we have any children at current Node.
            bool isLeaf(){
                if(children.size() == 0){
                    return true;
                }
                return false;
            }
        };

        /**
         * Constructor to create an empty tree.
         */
        NaryTree();

        /**
         * Destructor; frees all nodes associated by this tree.
         */
        virtual ~NaryTree();

        /**
         * Frees all nodes associated with this tree and sets it to be empty.
         */
        void clear();

        /**
         * Inserts into the NaryTree
         * @param s The string being stored starting at current Node
         * @param i The integer storing the index pos of S in T
         */
        void insert(const std::string & s, int i);

        /**
         * Searches the NaryTree for all occurences of s
         * Returns {-1} if no occurences 
         * @param s The string to search
         *
         * YOU MUST CODE THIS (AND ANY SUPPORT FUNCTIONS YOU NEED)
         *
         */
        std::vector<int> patternMatch(const std::string & s);

        /**
         * Prints the contents of the tree to stdout.
         */
        void print();

        /**
         * @return The root of the Nary tree
         */
        Node* getRoot() const;

        /**
         * These helper functions may help you debug your code:
         */

        /**
         * @return The height of the nary tree. Recall that the height of a
         *  tree is just the length of the longest path from the root to a leaf, and
         *  that the height of an empty tree is -1.
         */
        int height() const;

        /**
         * Traverses the NaryTree in lexicographic order.
         * That is, at each node we will push_back to treeVector the children at the node
         * starting with a depth-first walk from smallest to largest .
         * @param treeVector stores edges in order
         */
        void inLexOrder(std::vector<std::string>& treeVector);


        /**
         * Traverses the NaryTree in lexicographic order.
         * That is, at each node we will visit the children at the node
         * starting with a depth-first walk from smallest to largest.
         * At each node, we coalesce any edges that have a non-branching path
         */
        void trie_to_tree();

        /*
        * Reserved functions (don't use in your code)
        */

        bool checkLeaves();
        void checkLeaves(Node* subRoot);
        bool checkNodes();
        void checkNodes(Node* subRoot);
        

    protected:

        Node* root;

    private:

        /**
         * Put your own private helper functions here.
         * Look at the private helpers for height and printLeftToRight
         *  as examples.
         */

        /**
         * Private helper function for the public height function.
         * @param subRoot The current node in the recursion
         * @return The height of the subtree
         */
        int height(const Node* subRoot) const;

        /**
         * Private helper function for the public printLeftToRight function.
         * @param subRoot The current node in the recursion
         */
        void printNode(const Node* subRoot) const;

        void printHelper(Node*& subRoot, int depth, std::string part, std::vector<bool> dflag) ;

        /**
         * Private helper function for the sorted public insert function.
         * @param node The current node in the recursion
         * @param s The current substring being stored
         * @param index The start position of the string being stored.
         */
        void insert(Node*& node, const std::string& s, int index);

        /**
         * Private helper function for clear that clears beneath the parameter node.
         * @param subRoot The current node in the recursion
         */
        void clear(Node* subRoot);
        
        void checkLeaves(Node* subRoot, std::vector<int>& lVec);

        /**
         * Private helper function for the public inLexOrder function.
         * @param subRoot The current node in the recursion
         * @param treeVector stores nodes in order
         */
        void inLexOrder(Node* subRoot, std::vector<std::string>& treeVector);

        /**
         * Private helper function for the patternMatch function.
         * @param s The pattern being matched
         * @param subRoot The current node in the recursion
         * @param outList stores the output index values
         */

        void patternMatch(const std::string & s, Node* subRoot, std::vector<int>& outList);

        void getLeaves(Node* subRoot, std::vector<Node*>& leafList);

        void trie_to_tree(Node* subRoot);

};

NaryTree build_strie(std::string T);