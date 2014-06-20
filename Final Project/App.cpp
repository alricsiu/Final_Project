//
//  App.cpp
//  Lab 4
//
//  Created by Siuperman on 5/25/14.
//  Copyright (c) 2014 Siuperman. All rights reserved.
//

#include "App.h"

/////////////////
// Constructor //
/////////////////
/**
 * Constructor, initializes all private members.
 */
App::App()
{
    uniqueKey = 0;
    appName = "";
    author= "";
    category = "";
}


////////////////
//Constructor //
////////////////
/**
 * Takes all private member variables as parameters.
 */
App::App(int uniqueKey, string appName, string author, string category)
{
    this->uniqueKey = uniqueKey;
    this->appName = appName;
    this->author = author;
    this->category = category;
}

////////////////
// Destructor //
////////////////
App::~App()
{
    uniqueKey = 0;
    appName = "";
    author = "";
    category = "";
}

/**
 * Prints the data in the application. For debugging purposes.
 */
void App::print()
{
    cout<<uniqueKey<<endl;
    cout<<appName<<endl;
    cout<<author<<endl;
    cout<<category<<endl;
}
 
/////////////////////////
// Getters and Setters //
/////////////////////////

/**
 * sets the unique key
 * @param key The unique key as an int.
 */
void App::setUniqueKey(int key)
{
    this->uniqueKey = key;
}

/**
 * sets the app name
 * @param appName as a String.
 */
void App::setAppName(string appName)
{
    this->appName = appName;
}
/**
 * sets the Author
 * @param author the author as a string.
 */
void App::setAuthor(string author)
{
    this->author = author;
}

/**
 * sets the App Category
 * @param category category as a string
 */
void App::setCategory(string category)
{
    this->category = category;
}

/**
 * gets the unique key
 * @return returns the unique key as an int.
 */
int App::getUniqueKey()
{
    return uniqueKey;
}
/**
 * Gets the app name
 * @return Returns the app name as a string
 */
string App::getAppName()
{
    return appName;
}
/**
 * Gets the author name
 * @return Returns the author name as a string.
 */
string App::getAuthor()
{
    return author;
}
/**
 * gets the category
 * @return Returns the category as a string.
 */
string App::getCategory()
{
    return category;
}
