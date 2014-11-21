//
//  BehaviorObj.h
//  TestED
//
//  Created by Young on 07-04－此月第1周.
//  Copyright (c) 2014年 Young. All rights reserved.
//

#ifndef __TestED__BehaviorObj__
#define __TestED__BehaviorObj__

#include <iostream>
#include "tinyxml2.h"
using namespace std;
//behavior object
class BehaviorObj
{
private:
    string _behaviorName;//some operation names such as write, read and so on
    string _targetFileName;//the target file name of this operation，eg. file1.txt
    tinyxml2::XMLElement *_details;
    
public:
    BehaviorObj(const string bn, const string tFN);
    BehaviorObj(const string bn, const string tFN, tinyxml2::XMLElement* d);
    string getBehaviorName();
    string getTargetFileName();
    tinyxml2::XMLElement* getDetails();
    void printInfo();//_behaviorName+_targetFileName
};
#endif /* defined(__TestED__BehaviorObj__) */

