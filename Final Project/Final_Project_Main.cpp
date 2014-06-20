/**~*~*
    
    This program loads a set of iOS top application data and stores it in a custom database.
    The database consists of a List head, which contains a Hash List, BST, and a Heap. Using
    these data structures, this app can allow users to insert and delete entries, print the entries
    in order by unique key, search for a specific app by their unique key, view the hash table,
    the BST Tree as well as hash statistics. Finally, the app persists changes to the database 
    by saving the changes to the data file each time the database is changed.

    Final Project - Mobile Application Database

    Team #13

    Name: Alric Siu
    Date: June 20, 2014

 *~**/

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <sstream>


using namespace std;

#include "BST.h"
#include "ListHead.h"
#include "Heap.h"

const char INSERT_CHOICE = 'I',
DELETE_CHOICE = 'D',
SEARCH_CHOICE = 'S',
PRINT_HASH_LIST = 'H',
PRINT_SEQ_LIST = 'O',
PRINT_TREE_CHOICE = 'T',
SAVE_TO_FILE_CHOICE = 'W',
HASH_STATS_CHOICE = 'X',
FREQUENT_SEARCH= 'G',
TOGGLE_MENU = 'M',
QUIT_CHOICE = 'Q';

const string WELCOME_STATEMENT = "Welcome to the Binary Search Tree Program.  This program parses a file of top iOS Applications into a binary search tree and allow a user to interact with the tree.\n\n";

////////////////
// Prototypes //
////////////////

int menu(bool);
char getValidChar();
int getValidKey(string);
string getValidString(string);
int countLines(ifstream &inputFile);
void parseToListHead(ListHead* , ifstream &, string);
void handleResult(App* result, string displayMessage);


//////////
// Main //
//////////
/**
 * Will open the inputFile, parse into listhead and prompt the user to interact with the data.
 * @return [Returns 0 when the program is successful.
 *          Returns -1 when the input file can not be open ]
 */
int main()
{
    cout<<WELCOME_STATEMENT;

    ifstream inputFile;

    cout<<"Loaded Input file: Data.txt\n";

    string filename = "data.txt";
    
    inputFile.open(filename);
    if (!inputFile)
    {
        cout << "Error opening input.txt!\n";
        return -1; //unable to open file.
    }

    int lines = countLines(inputFile);

    ListHead *listHead = new ListHead(lines);
    
    parseToListHead(listHead, inputFile, filename);
    
    
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
            case INSERT_CHOICE:
            {
                string appName = getValidString(" Enter App Name:");
                int key = getValidKey(" Enter Unique Key:");
                string author = getValidString(" Enter Author:");
                string category = getValidString(" Enter Category:");

                App *app = new App(key, appName, author, category);
                
                listHead->getBST()->BST_insert(app);
                listHead->getHash()->insert(app);
                
                //persist changes
//                listHead->getBST()->outputTofile("data.txt");

            }
                break;
            case DELETE_CHOICE:
            {
                int key = getValidKey(" Enter Unique Key:");

                App *bstResult = listHead->getBST()->BST_delete(key);

                App *hashResult = listHead->getHash()->remove(key);

                if(bstResult == hashResult)
                    handleResult(hashResult,"Deleted Item");
                else
                    cout<<"Program Error! Delete mismatch - Contact administrator"<<endl;
                
                delete hashResult;
                //persist changes
//                listHead->getBST()->outputTofile("data.txt");

            }
                break;
            case SEARCH_CHOICE:
            {
                int key = getValidKey(" Enter Unique Key:");
                App *app = listHead->getHash()->search(key);
                handleResult(app, "Search Result");
               
                listHead->getHeap()->insert(key);      
            }
                break;
            case PRINT_HASH_LIST:
            {
                cout << "Hash Table:" << endl;
                listHead->getHash()->printHash();
            }
                break;
            case PRINT_SEQ_LIST:
            {
                cout<<"  Key Sequence:"<<endl;
                listHead->getBST()->BST_list();
            }
                break;
            case PRINT_TREE_CHOICE:
            {
                cout<<endl<<"  Binary Search Tree:"<<endl<<endl;
                if(listHead->getBST()->getCount())
                    listHead->getBST()->BST_print();
                else
                    cout<<"\t BST Tree is empty."<<endl<<endl;
            }
                break;
            case SAVE_TO_FILE_CHOICE:
            {
                string filename = getValidString(" Enter filename:");
                listHead->getBST()->outputTofile(filename);
            }
                break;
            case FREQUENT_SEARCH:
            {
                listHead->getHeap()->displayTop();
            }
                break;
            case HASH_STATS_CHOICE:
            {
                listHead->getHash()->showStats();
            }
                break;
        }
    }
    
    listHead->getBST()->outputTofile("data.txt");
    cout << "The updated data has been saved to "<< DATABASE <<endl;;
    //Cleanup BST and Hash
    delete listHead;

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
        << INSERT_CHOICE
        << " - Insert an Entry\n\t"
        << DELETE_CHOICE
        << " - Delete an Entry\n\t"
        << SEARCH_CHOICE
        << " - Search by Unique Key\n\t"
        << PRINT_HASH_LIST
        << " - Print Hash Table\n\t"
        << PRINT_SEQ_LIST
        << " - Print Entries by Key sequence.\n\t"
        << PRINT_TREE_CHOICE
        << " - Print Tree as an Indented List\n\t"
        << HASH_STATS_CHOICE
        << " - Display Hash Statistics\n\t"
        << FREQUENT_SEARCH
        << " - Display most Frequent Search\n\t"
        << SAVE_TO_FILE_CHOICE
        << " - Save Changes\n\t"
        << TOGGLE_MENU
        << " - Toggle Menu \n\t"
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

/////////////////////
// getValid String //
/////////////////////
/**
 * This function prompts the user to enter a string.
 *
 * @param  displayMessage The message to be displayed to the user.
 * @return The string that the user inputs until they hit a carriage return.
 */
string getValidString(string displayMessage)
{
    string result;
    cout << displayMessage;
    getline(cin , result);

    return result;
}


////////////////////
// getValid Key   //
////////////////////
/**
 * This function prompts the user to enter an integer that is a valid key.
 * If the input is not valid ( not an integer ) it
 * prompts the user to enter a new integer, until the input is valid.
 *
  * @param  displayMessage The message to be displayed to the user.
 * @return The integer that the user inputs that is valid.
 */
int getValidKey(string displayMessage)
{
    int num;
    bool success;
    
    do
    {
        cout << displayMessage;
        cin >> num;
        success = !cin.fail();
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success);
    
    return num;
}


//////////////////
//Handle Result //
//////////////////
/**
 * Generates the output from the result App returned from searching the database.
 * @param result An App* that is the search result.
 */
void handleResult(App* result, string displayMessage)
{
    if(result)
    {
        cout<<"\t"<<displayMessage<<":"<<endl;
        cout<<"\t\t"<<"Unique Key: "<<result->getUniqueKey()<<endl;
        cout<<"\t\t"<<"App Name: "<<result->getAppName()<<endl;
        cout<<"\t\t"<<"Author: "<<result->getAuthor()<<endl;
        cout<<"\t\t"<<"Category: "<<result->getCategory()<<endl;
    }
    else
    {
        cout<<"\tUnique key is not found."<<endl;
    }
}


/////////////////
// Count Lines //
/////////////////
/**
 * Count the number of entries in the inputFile
 * @param  inputFile the input file to count.
 * @return           returns the number of entries.
 */
int countLines(ifstream &inputFile)
{
    char c;
    
    string buffer="";
    
    int counter=0;
    
    while (inputFile.get(c))
    {
        if(c=='\r'||c=='\n')
        {
            if(buffer.length()!=0)
            {
                counter++;
            }
            buffer = "";

        }
        else
        {
            buffer = buffer + c;
        }
    }
    
    inputFile.clear() ;
    inputFile.seekg(0, ios::beg) ;
    
    return counter/4;
    
    
}


//////////////////////
//ParseToBinaryTree //
//////////////////////
/**
 * Parses the input file into the binary tree. Creates an app object for each entry and inserts
 * the entry into the binary search tree using its unique key.
 
 EDIT: now also inserts into Hash Table for each insert. A better function name might be readData.
 
 * @param tree      The BST tree to insert the entries into.
 * @param inputFile The inputfile with the entries. Entries must span 4 lines, separated by new lines. 
 */
void parseToListHead(ListHead *listHead, ifstream &inputFile, string filename)
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
                    
                    listHead->getHash()->insert(app);
                    listHead->getBST()->BST_insert(app);
                    
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
    
    // after the data is all entered, rehash if load factor exceeds 75%.
    
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