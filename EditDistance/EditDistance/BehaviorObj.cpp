//
//  BehaviorObj.cpp
//  TestED
//
//  Created by Young on 07-04－此月第1周.
//  Copyright (c) 2014年 Young. All rights reserved.
//

#include "BehaviorObj.h"
BehaviorObj::BehaviorObj(const string bn, const string tFN)
{
        _behaviorName=bn;
        _targetFileName=tFN;
}

BehaviorObj::BehaviorObj(const string bn, const string tFN, tinyxml2::XMLElement* d)
{
    _behaviorName=bn;
    _targetFileName=tFN;
    _details=d;
}

string BehaviorObj::getBehaviorName()
{
        return _behaviorName;
}
    
string BehaviorObj::getTargetFileName()
{
        return _targetFileName;
}

tinyxml2::XMLElement* BehaviorObj::getDetails()
{
        return _details;
}

void BehaviorObj::printInfo()
{
        cout<<getBehaviorName()+"("+getTargetFileName()+") ";
}