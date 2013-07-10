#include "tree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

TEST_CASE( "tree" , "[insertion]") {
    std::vector <int> data;
    data.push_back(23);
    data.push_back(14);
    data.push_back(31);
    data.push_back(7);
    data.push_back(17);
    data.push_back(9);
    // exampleTree.show_level();

    Tree<int> exampleTree;
    for(auto it=data.begin(); it!=data.end(); ++it) {
        exampleTree.insert(*it);
    }

    CHECK (exampleTree.size() == data.size());

    // check preorder
    std::vector<int> preorder({23, 14, 7, 9, 17, 31}); 
    auto result = exampleTree.traversePreorder();
    CHECK(true == equal(result.begin(), result.end(),
                  preorder.begin()));
    // check postorder
    result = exampleTree.traversePostorder();
    std::vector<int> postorder({9, 7, 17, 14, 31, 23}); 
    cout << endl;
    CHECK(true == equal(result.begin(), result.end(),
                  postorder.begin()));
    // check inorder
    result = exampleTree.traverseInorder();
    std::vector<int> inorder({7, 9, 14, 17, 23, 31});
    CHECK(true == equal(result.begin(), result.end(),
                  inorder.begin()));
    // check breadthfirstsearch
    result = exampleTree.breadthFirstSearch();
    std::vector<int> bfs({23, 14, 31, 7, 17, 9});
    CHECK(true == equal(result.begin(), result.end(),
                  bfs.begin()));

    for(auto it=data.begin(); it!=data.end(); ++it) {
        CHECK (exampleTree.contains(*it) == true);
    }
    CHECK (exampleTree.contains(0) == false);


    // try to remove something that isn't there
    CHECK (exampleTree.remove(0) == false);
    exampleTree.insert(18);
    exampleTree.insert(16);

    CHECK (exampleTree.findParent(18)->value == 
            exampleTree.findNode(17)->value);
    CHECK (exampleTree.findParent(16)->value == 
            exampleTree.findNode(17)->value);

    CHECK (exampleTree.size() == data.size()+2);

    // CHECK (exampleTree.remove(17) == true);
    // // CHECK (exampleTree.remove(18) == true);
    // CHECK (exampleTree.remove(16) == true);
    // CHECK (exampleTree.remove(18) == true);
    // CHECK (exampleTree.size() == data.size() - 1);
    // CHECK (exampleTree.size() == data.size() - 1);
    // exampleTree.insert(17);

}
