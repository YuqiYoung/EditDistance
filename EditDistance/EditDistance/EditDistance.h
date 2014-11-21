//
//  EditDistance.h
//  EditDistance
//
//  Created by Young on 11-16－此月第3周.
//  Copyright (c) 2014年 Young. All rights reserved.
//

#ifndef __EditDistance__EditDistance__
#define __EditDistance__EditDistance__

#include <stdio.h>
#include "BehaviorObj.h"
#include <vector>
#include <list>
class EditDistance
{
public:
    EditDistance(vector<BehaviorObj> &s1,vector<BehaviorObj> &s2);
    void generateEditMatrix();
    void backTrace();
    vector<BehaviorObj> getSuperResult();
    void printSuperResult();
    void printEditMatrix();
private:
    vector<BehaviorObj> _s1;
    vector<BehaviorObj> _s2;
    vector<vector<int> > _editMatrix;
    //vector<vector<vector<int> > > _statusMatrix;
    vector<BehaviorObj> _superResult;

};
#endif /* defined(__EditDistance__EditDistance__) */
