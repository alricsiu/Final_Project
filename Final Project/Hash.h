//
//  Hash.h
//  1GroupProject
//
//  Created by Alexis Candelaria on 5/18/14.
//  Copyright (c) 2014 DreamDrivenApps. All rights reserved.
//

#ifndef _GroupProject_Hash_h
#define _GroupProject_Hash_h

class Hash
{
private:
    MobileApp app;
    string searchKey; // get clarification on wether string should be keytype
    
protected:
    void setKey(const string& searchKey ); // necesarry so that constructor of any derived calss can
                                            // initialize search key
    
public:
    Hash();
    Hash(MobileApp app, string searchKey);
    MobileApp getItem() const;
    string getKey() const;
    void setItem(const MobileApp & newEntry)
    
};

#endif
