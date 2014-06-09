/**~*~*
    
    This program loads a set of iOS top application data and stores it in a BST Tree. The unique
    key is the unique number that apple has assigned to the specific application. The program
    can perform recursive depth first traversals, breadth first traversals, print the tree, search
    for specific unique keys, as well as search for a range of unique keys.

    Homework 4 - Binary Search Trees.

    Name: Alric Siu
    Date: May 25, 2014

 *~**/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

#include "BSTNode.h"
#include "BST.h"
#include "App.h"

const char SEARCH_CHOICE = 'S',
RECUR_DEPTH_CHOICE = 'D', 
BREADTH_FIRST_CHOICE = 'B', 
PRINT_TREE_CHOICE = 'T', 
PRINT_RANGE_CHOICE = 'R',
TOGGLE_MENU = 'M',
QUIT_CHOICE = 'Q';

const string WELCOME_STATEMENT = "Welcome to the Binary Search Tree Program.  This program parses a file of top iOS Applications into a binary search tree and allow a user to interact with the tree.\n\n";

////////////////-
// Prototypes //
////////////////
bool isValidNumber(int);
void parsetoBinaryTree(BST *, ifstream &);
void handleSearch(BSTNode*);
void randomizeApps(ifstream &);

int menu(bool);
char getValidChar();
int getValidKey();
void getValidRange(int &, int &);

//////////
// Main //
//////////
/**
 * Will open the inputFile, parse into a binary tree and prompt the user to interact with the data.
 * @return [Returns 0 when the program is successful.
 *          Returns -1 when the input file can not be open ]
 */
int main()
{
    cout<<WELCOME_STATEMENT;

    ifstream inputFile;

    cout<<"Loaded Input file: Data.txt\n";

    inputFile.open("Data.txt");
    if (!inputFile)
    {
        cout << "Error opening input.txt!\n";
        return -1; //unable to open file.
    }

    BST *BSTTree = new BST();
    parsetoBinaryTree(BSTTree, inputFile);

    inputFile.close();
    
    char choice;    // To hold a menu choice
    
    bool showMenu=true;
    
    while ((choice = menu(showMenu))!= QUIT_CHOICE)
    {
        switch (choice)
        {
            case TOGGLE_MENU:
            {
                showMenu=!showMenu;
            }
                break;
            case SEARCH_CHOICE:
            {
                int key = getValidKey();
                BSTNode *result = BSTTree->search(key);
                handleSearch(result);
            }
                break;
            case RECUR_DEPTH_CHOICE:
            {
                cout<<"\tInorder Traversal:"<<endl<<"\t\t ";
                BSTTree->inorderRecursive(BSTTree->getRoot());
                cout<<endl<<"\tPreorder Traversal:"<<endl<<"\t\t";
                BSTTree->preorderRecursive(BSTTree->getRoot());
                cout<<endl<<"\tPostorder Traversal:"<<endl<<"\t\t";
                BSTTree->postorderRecursive(BSTTree->getRoot());
                cout<<endl<<endl;
            }
                break;
            case BREADTH_FIRST_CHOICE:
            {
                BSTTree->breadthFirst();
            }
                break;
            case PRINT_TREE_CHOICE:
            {
                cout<<endl<<"Binary Search Tree displayed below:"<<endl<<endl;
                if(BSTTree->getCount())
                BSTTree->printTree(BSTTree->getRoot(), 0);
                else
                    cout<<"\t BST Tree is empty."<<endl<<endl;
            }
                break;
            case PRINT_RANGE_CHOICE :
            {
                int lower;
                int upper;
                getValidRange(lower, upper);
                
                cout<<"The unique keys between "<< lower<<" and "<<upper<<" are:"<<endl<<"\t";

                BSTTree->printRange(lower, upper, BSTTree->getRoot());
                
                cout<<endl;
            }
        }
    }

    delete BSTTree;

}
 
/////////
//Menu //
/////////
 /**
  * Displays the menu choices
  * @param  showMenu [true shows the menu, false hides the menu]
  * @return          [the menu item chosen by the user]
  */
int menu(bool showMenu)
{
    int choice;
    
    // Display the menu and get the user's choice.
    if(showMenu)
        cout << "\nWhat do you want to do?\n\t"
        << TOGGLE_MENU
        << " - Toggle Menu\n\t"
        << SEARCH_CHOICE
        << " - Search for a unique key\n\t"
        << RECUR_DEPTH_CHOICE
        << " - Recursive Depth First Traversal\n\t"
        << BREADTH_FIRST_CHOICE
        << " - Breadth First Traversal\n\t"
        << PRINT_TREE_CHOICE
        << " - Print Tree as an Indented List\n\t"
        << PRINT_RANGE_CHOICE
        << " - Prints all unique keys between a lower and upper bound\n\t"
        << QUIT_CHOICE
        << " - Quit the program\n";
    
    
    choice = getValidChar();
    return choice;
}

////////////////////
// Get Valid Char //
////////////////////
/**
 * This function prompts the user to enter a character.
 * If the input is not valid ( not a character ) it
 * prompts the user to enter a new character, until the input is valid.
 *
 * @return The character that the user inputs that is valid.
 */
char getValidChar()
{
    string input;
    char inputCharacter;
    bool success;
    
    do
    {
        cout << "Please enter an option: ";
        cin >> input;
        //make sure input string is just one letter long.
        bool correctLength = input.length()==1;
        bool stringSuccess = !cin.fail();
        success = correctLength && stringSuccess;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success);
    
    //allow lowercase inputs to work as well.
    std::transform(input.begin(), input.end(), input.begin(), ::toupper);
    
    inputCharacter = input.at(0);
    
    return inputCharacter;
}

//////////////////
//GetValidRange //
//////////////////
/**
 * Prompts the user to enter a valid range for the printRange function. Will prompt for a 
 * lower bound and then prompt for a upper bound. Also ensures that the upper bound is 
 * larger than the lower bound. Will reprompt if the upper bound is smaller than the lower
 * bound.  
 * @param lowerbound the lower search bound as an integer
 * @param upperbound the upper search bound as an integer
 */
void getValidRange(int &lowerbound, int &upperbound)
{
    int num;
    bool success;
    
    do
    {
        cout << " Enter the lower bound: ";
        cin >> num;
        success = !cin.fail();
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success);
    
    lowerbound = num;
    
    do
    {
        cout << " Enter the upper bound: ";
        cin >> num;
        success = !cin.fail();
        if(num<lowerbound)
        {
            success = false;
            cout<< "\t Enter a value larger than the lower bound."<<endl;
        }
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success);
    
    upperbound = num;
    
    
    
}

////////////////////
// getValid Key   //
////////////////////
/**
 * This function prompts the user to enter an integer that is a valid key.
 * If the input is not valid ( not an integer ) it
 * prompts the user to enter a new integer, until the input is valid.
 *
 * @return The integer that the user inputs that is valid.
 */
int getValidKey()
{
    int num;
    bool success;
    
    do
    {
        cout << " Enter a unique key: ";
        cin >> num;
        success = !cin.fail();
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success);
    
    return num;
}


//////////////////
//Handle Search //
//////////////////
/**
 * Generates the output from the result BSTNode returned from seaching the Tree.
 * @param result A BSTNode that is the search result.
 */
void handleSearch(BSTNode* result)
{
    if(result)
    {
        cout<<"\tSearch Result:"<<endl;
        cout<<"\t\t"<<"Unique Key: "<<result->getData()->getUniqueKey()<<endl;
        cout<<"\t\t"<<"App Name: "<<result->getData()->getAppName()<<endl;
        cout<<"\t\t"<<"Author: "<<result->getData()->getAuthor()<<endl;
        cout<<"\t\t"<<"Category: "<<result->getData()->getCategory()<<endl;
    }
    else
    {
        cout<<"\tUnique key is not found."<<endl;
    }
}

//////////////////////
//ParseToBinaryTree //
//////////////////////
/**
 * Parses the input file into the binary tree. Creates an app object for each entry and inserts
 * the entry into the binary search tree using its unique key.
 * @param tree      The BST tree to insert the entries into.
 * @param inputFile The inputfile with the entries. Entries must span 4 lines, separated by new lines. 
 */
void parsetoBinaryTree(BST *tree, ifstream &inputFile)
{
    char c;

    string output="";
    
    string buffer="";
    
    string uniquekey="";
    string appName="";
    string author="";
    string category="";
    
    int counter=0;

    while (inputFile.get(c))
    {
        
        if(c=='\r'||c=='\n')
        {
            if(buffer.length()!=0)
            {
                if( counter == 0 )
                {
                    uniquekey = buffer;
                    counter ++;

                }
                else if( counter == 1 )
                {
                    appName = buffer;
                    counter ++;

                }
                else if( counter == 2 )
                {
                    author = buffer;
                    counter ++;

                }
                else if( counter == 3 )
                {
                    category = buffer;
                    
                    int key;
                    istringstream ( uniquekey ) >> key;
                    
                    App *app = new App(key, appName, author, category);
                    tree->insert(app);
                    
                    counter = 0;

                }
             
                buffer = "";
            }
        }
        else
        {
            buffer = buffer + c;
        }
    }
    
}


////////////////////////////
//Random number generator //
////////////////////////////
/* Helper method to generate a random number. */
int myrandom (int i) { return std::rand()%i;}

////////////////////////
//Randomize Data File //
////////////////////////
/**
 * Prints a randomized data file with the correct entries. Allows us to create a better balanced 
 * binary tree.
 * @param inputFile the Data file with the non-randomized entries.
 */
void randomizeApps(ifstream &inputFile)
{
    
    vector<App*> applist;
    
    
    char c;
    

    string output="";
    
    string buffer="";
    
    string uniquekey="";
    string appName="";
    string author="";
    string category="";
    
    int counter = 0;
    
    while (inputFile.get(c))
    {
        
        if(c=='\r'||c=='\n')
        {
            if(buffer.length()!=0)
            {
  
                if( counter == 0 )
                {
                    uniquekey=buffer;
                    counter++;
                }
                else if( counter == 1 )
                {
                    appName = buffer;
                    counter++;

                }
                else if( counter == 2 )
                {
                    author = buffer;
                    counter++;

                }
                else if( counter == 3 )
                {
                    category = buffer;

                    int key;
                    istringstream ( uniquekey ) >> key;
                    
                    App *app = new App(key, appName, author, category);
                    
                    applist.push_back(app);
                    
                    counter = 0;
                }
                
                buffer = "";
            }
        }
        else
        {
            buffer = buffer + c;
        }
    }
    
    //Randomize Data
    //
    
    std::srand ( unsigned ( std::time(0) ) );
    std::random_shuffle ( applist.begin(), applist.end(), myrandom);
    
    for(std::vector<App*>::size_type i = 0; i != applist.size(); i++) {
        applist[i]->print();
        
    }
    
}

/***************   Program Output can be found in the BST_Output.txt file **************************/