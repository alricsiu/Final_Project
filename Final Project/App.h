//
//  App.cpp
//  Lab 4
//
//  App class that contains all the information for each mobile app entry.
//
//  Created by Alric Siu on 5/25/14.
//  Copyright (c) 2014 Alric Siu. All rights reserved.
//

#ifndef Lab_4_Application_h
#define Lab_4_Application_h

#include <iostream>
#include <string>

using namespace std;

class App
{
private:
    
    int uniqueKey;
    string appName;
    string author;
    string category;
     
public:
    //Constructor
    App();
    App(int uniqueKey, string appName, string author, string category);
    
    // Destructor
    ~App();
    
    // ListNode operations
    
    void print();
    
    void setUniqueKey(int);
    void setAppName(string);
    void setAuthor(string);
    void setCategory(string);
    
    int getUniqueKey();
    string getAppName();
    string getAuthor();
    string getCategory();
    
    
    
};


#endif

