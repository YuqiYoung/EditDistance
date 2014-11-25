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
    parentNode=NULL;
    _details=NULL;
    childNodesVec=vector<BehaviorObj*>();
    superID=-1;
}

BehaviorObj::BehaviorObj(const string bn, const string tFN, tinyxml2::XMLElement* d)
{
    _behaviorName=bn;
    _targetFileName=tFN;
    _details=d;
    parentNode=NULL;
    childNodesVec=vector<BehaviorObj*>();
    superID=-1;
}

BehaviorObj::~BehaviorObj()
{
    parentNode=NULL;
    for(int i=0;i<childNodesVec.size();i++)
    {
        childNodesVec[i]=NULL;
    }
}

BehaviorObj::BehaviorObj(const BehaviorObj &temp)
{
    _behaviorName=temp._behaviorName;
    _targetFileName=temp._targetFileName;
    _details=temp._details;
    parentNode=temp.parentNode;
    childNodesVec=temp.childNodesVec;
    superID=temp.superID;
}

BehaviorObj & BehaviorObj::operator =(const BehaviorObj &temp)
{
    if (this == &temp)
    {
        return *this;
    }
    else
    {
        //delete [] m_data;
        _behaviorName=temp._behaviorName;
        _targetFileName=temp._targetFileName;
        _details=temp._details;
        parentNode=temp.parentNode;
        childNodesVec=temp.childNodesVec;
        superID=temp.superID;
        return *this;
    }
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