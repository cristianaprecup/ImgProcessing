#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

struct QuadNode 
{
    char color;
    QuadNode* children[4];

    QuadNode(char c) : color(c) 
    {
        for (int i = 0; i < 4; i++) 
        {
            children[i] = nullptr;
        }
    }
};//this defines the quadnode struct, which represents a node in the quadtree
//It has a color and an array of children

QuadNode* buildQuadTree(const string& image, int& index) 
{
    char color = image[index++];
    if (color == 'b' || color == 'w') 
    {
        return new QuadNode(color);
    }

    QuadNode* node = new QuadNode('p');
    for (int i = 0; i < 4; i++) {
        node->children[i] = buildQuadTree(image, index);
    }

    return node;
}//This function builds a quadtree from an image string using a recursive approach. 
//It takes the image string and an index to keep track of the current position in the string. 
//It returns a pointer to the root node of the quadtree.

void deleteQuadTree(QuadNode* node) 
{
    if (node == nullptr) 
    {
        return;
    }

    for (int i = 0; i < 4; i++) 
    {
        deleteQuadTree(node->children[i]);
    }

    delete node;
}//This function recursively deletes a quadtree. 
//It takes the root node as input and deletes all nodes in the tree.

QuadNode* preorderToQuadTree(const string& preorder, int& index) 
{
    if (index >= preorder.length()) 
    {
        return nullptr;
    }

    char color = preorder[index++];
    if (color == 'b' || color == 'w') 
    {
        return new QuadNode(color);
    }

    QuadNode* node = new QuadNode('p');
    for (int i = 0; i < 4; i++)
    {
        node->children[i] = preorderToQuadTree(preorder, index);
    }

    return node;
}
//it takes the preorder string and an index to keep track of the current position in the string
// it returns a pointer to the root node of the quadtree

string quadTreeToPreorder(QuadNode* node) 
{
    if (node == nullptr) {
        return "";
    }

    string preorder = "";
    preorder += node->color;
    for (int i = 0; i < 4; i++) 
    {
        preorder += quadTreeToPreorder(node->children[i]);
    }

    return preorder;
} 
//it takes the root node of the quadtree and returns the preorder string

QuadNode* mergeQuadTrees(QuadNode* quadTree1, QuadNode* quadTree2) 
{
    if (quadTree1 == nullptr) 
    {
        return quadTree2;
    }

    if (quadTree2 == nullptr) 
    {
        return quadTree1;
    }

    if (quadTree1->color == 'b' || quadTree2->color == 'b') 
    {
        return new QuadNode('b');
    }

    if (quadTree1->color == 'w' && quadTree2->color == 'w') 
    {
        return new QuadNode('w');
    }

    QuadNode* mergedNode = new QuadNode('p');
    bool hasDifferentColors = false;
    for (int i = 0; i < 4; i++) 
    {
        mergedNode->children[i] = mergeQuadTrees(quadTree1->children[i], quadTree2->children[i]);
        if (mergedNode->children[i]->color == 'b') 
        {
            hasDifferentColors = true;
        }
    }

    if (!hasDifferentColors) 
    {
        mergedNode->color = 'w';
        for (int i = 0; i < 4; i++) 
        {
            delete mergedNode->children[i];
            mergedNode->children[i] = nullptr;
        }
    } 
    else 
    {
        int whiteCount = 0;
        for (int i = 0; i < 4; i++) {
            if (mergedNode->children[i]->color == 'w') 
            {
               
                whiteCount++;
            }
        }
        if (whiteCount == 4) 
        {
            mergedNode->color = 'w';
        } 
        else 
        {
            mergedNode->color = 'p';
        }
    }

    return mergedNode;
}
//merges two quadtrees quadTree1 and quadTree2 by combining corresponding nodes
// it returns a new merged quadtree
//if either quadTree1 or quadTree2 has a black color node the merged node will be black.
//if both quadTree1 and quadTree2 have white color nodes the merged node will be white.

int getLastLevel(QuadNode* root) 
{
    if (root == nullptr) 
    {
        return -1;  // Invalid tree, return -1 indicating an error
    }

    if (root->children[0] == nullptr) 
    {
        return 0;  // Root node is the last level (level 0)
    }

    // Check the children of the root node
    int lastChildLevel = getLastLevel(root->children[0]);

    // Verify if all children have the same level
    for (int i = 1; i < 4; i++) {
        if (getLastLevel(root->children[i]) != lastChildLevel) 
        {
            return -1;  // Invalid tree, children have different levels
        }
    }

    return lastChildLevel + 1;  // Increment the level by 1 for the root node
}
//this function determines the level of the last level in a quadtree
//
int countBlackPixelsInImageV3(QuadNode* root) 
{
    int count = 0;
    stack<pair<QuadNode*, int>> s; // using a stack to avoid recursion
    s.push({root, 1024}); // start with root node and max multiplier value

    while (!s.empty()) 
    {
        QuadNode* node = s.top().first;
        int multiplier = s.top().second;
        s.pop();

        if (node->color == 'b') 
        {
            count += multiplier;
        } else if (node->color == 'p') 
        {
            multiplier /= 4;
            for (int i = 0; i < 4; i++) 
            {
                s.push({node->children[i], multiplier});
            }
        }
    }

    return count;
}//iteratively counts black pixels in a quadtree using a stack
 //it starts with a root node and a multiplier of 1024. 
 //nodes are processed from the stack adding to the count for black nodes based on the multiplier
 //parent nodes divide the multiplier by 4 and push their children onto the stack 
 //the process continues until all nodes are processed yielding the count of black pixels in the quadtree

// Function to build Quad tree from image string

// Function to convert preorder string to Quad tree 

// Function to merge Quad trees 

// Function to count black pixels in a Quad tree 


int main()
{
    // Initialize variables for two quadtrees and a merged quadtree
    QuadNode* quadTree1 = nullptr;
    QuadNode* quadTree2 = nullptr;
    QuadNode* mergedQuadTree = nullptr;

    int choice = -1;
    while (choice != 0)
    {
        cout << "Interaction Menu" << endl;
        cout << "1. Build Quad tree from image string" << endl;
        cout << "2. Convert preorder string to Quad tree" << endl;
        cout << "3. Merge Quad trees" << endl;
        cout << "4. Count black pixels in a Quad tree" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                // Option 1: Build quadtree from an image string
                string image;
                cout << "Enter the image string: ";
                cin >> image;
                int index = 0;
                quadTree1 = buildQuadTree(image, index);
                cout << "Quad tree built from image string." << endl;
                break;
            }
            case 2:
            {
                // Option 2: Convert preorder string to quadtree
                string preorder;
                cout << "Enter the preorder string: ";
                cin >> preorder;
                int index = 0;
                quadTree2 = preorderToQuadTree(preorder, index);
                cout << "Quad tree built from preorder string." << endl;
                break;
            }
            case 3:
            {
                // Option 3: Merge two quad trees
                string preorder1;
                string preorder2;
                cout << "Enter the preorder for the first image: ";
                cin >> preorder1;
                cout << "Enter the preorder for the second image: ";
                cin >> preorder2;

                int index = 0;
                quadTree1 = preorderToQuadTree(preorder1, index);

                index = 0;
                quadTree2 = preorderToQuadTree(preorder2, index);

                if (quadTree1 != nullptr && quadTree2 != nullptr)
                {
                    mergedQuadTree = mergeQuadTrees(quadTree1, quadTree2);
                    cout << "Quad trees merged." << endl;
                    cout << "Merged Quad Tree (Preorder): " << quadTreeToPreorder(mergedQuadTree) << endl;
                }
                else
                {
                    cout << "Quad trees are not available. Please build Quad trees first." << endl;
                }
                break;
            }
            case 4:
            {
                // Option 4: Count black pixels in the merged quadtree
                if (mergedQuadTree != nullptr)
                {
                    int blackPixelCount = countBlackPixelsInImageV3(mergedQuadTree);
                    cout << "Number of black pixels: " << blackPixelCount << endl;
                }
                else
                {
                    cout << "No Quad tree available. Please merge Quad trees first." << endl;
                }
                break;
            }
            case 0:
            {
                // Option 0: Exit the program
                // Clean up Quad trees
                deleteQuadTree(quadTree1);
                deleteQuadTree(quadTree2);
                deleteQuadTree(mergedQuadTree);
                cout << "Exiting program." << endl;
                break;
            }
            default:
            {
                // Invalid choice
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
    return 0;
}
