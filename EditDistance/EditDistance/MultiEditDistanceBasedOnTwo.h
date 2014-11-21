//
//  MultiEditDistanceBasedOnTwo.h
//  EditDistance
//
//  Created by Young on 11-17－此月第4周.
//  Copyright (c) 2014年 Young. All rights reserved.
//

#ifndef __EditDistance__MultiEditDistanceBasedOnTwo__
#define __EditDistance__MultiEditDistanceBasedOnTwo__

#include <stdio.h>
#include "EditDistance.h"
#include "BehaviorObj.h"
#include <list>
#include <vector>
#include <iomanip>
class MultiEditDistanceBasedOnTwo
{
public:
    MultiEditDistanceBasedOnTwo(vector<vector<BehaviorObj> > &source);
    void generateSuperResult();
    void generateAlignedResult();
    vector<BehaviorObj> getSuperResult();
    vector<list<BehaviorObj> > getAlignedResult();
    void printAlignedResults();
    void printSuperResult();

    
private:
    vector<vector<BehaviorObj> > _source;
    vector<BehaviorObj> _superResult;
    vector<list<BehaviorObj> > _alignedResult;

    
    
};

#endif /* defined(__EditDistance__MultiEditDistanceBasedOnTwo__) */
