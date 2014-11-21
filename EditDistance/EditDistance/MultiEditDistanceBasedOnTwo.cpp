//
//  MultiEditDistanceBasedOnTwo.cpp
//  EditDistance
//
//  Created by Young on 11-17－此月第4周.
//  Copyright (c) 2014年 Young. All rights reserved.
//

#include "MultiEditDistanceBasedOnTwo.h"
MultiEditDistanceBasedOnTwo::MultiEditDistanceBasedOnTwo(vector<vector<BehaviorObj> > &source)
{
    _source=source;
    _alignedResult=vector<list<BehaviorObj> >(_source.size());
    generateSuperResult();
    generateAlignedResult();
}

void MultiEditDistanceBasedOnTwo::generateSuperResult()
{
    int len = (int)_source.size();
    vector<vector<BehaviorObj> > temp=_source;

    while(len>1)
    {
        int k = (len+1)/2;
        //vector<vector<BehaviorObj> >temp;
        for(int i = 0; i < len/2; i++)
        {
            EditDistance myEd=EditDistance(temp[i],temp[i+k]);
            temp[i]=myEd.getSuperResult();
            //myEd.printSuperResult();
            //assert(_source[i].size()>0);
        }
        len = k;
    }
    _superResult=temp[0];
    //printSuperResult();
    
}

void MultiEditDistanceBasedOnTwo::printSuperResult()
{
    cout<<"Super_Result:"<<endl;
    for(int i=(int)_superResult.size()-1;i>=0;i--)
    {
        cout<<_superResult[i].getBehaviorName()<<" ";
    }
    cout<<endl;
    cout<<"SourceResult:"<<endl;
    for(int i=0;i<(int)_source.size();i++)
    {
        for(int j=0;j<_source[i].size();j++)
        {
            cout<<_source[i][j].getBehaviorName()<<" ";
        }
        cout<<endl;
    }
}

void MultiEditDistanceBasedOnTwo::printAlignedResults()
{
    if(_alignedResult.size()==0)
    {
        std::cout<<"the size of result is zero"<<endl;
        return;
    }
    cout<<"alignedResult: "<<endl;
    long size= _source.size();
    int count=0;
    while(count<_alignedResult[0].size())
    {
        for(int i=0; i != size;i++)
        {
            list<BehaviorObj>::iterator iter=_alignedResult[i].begin();
            int j=0;
            while(j<count)
            {
                iter++;
                j++;
            }
            cout<<setw(10)<<(*iter).getBehaviorName()<<"\t";
        }
        cout<<_superResult[count].getBehaviorName()<<endl;
        count++;
    }

}

void MultiEditDistanceBasedOnTwo::generateAlignedResult()
{
    for(int i=0;i<_source.size();i++)
    {
        int cur=0;
        for(int j=0; j<_superResult.size();j++)
        {
            if(_source[i][cur].getBehaviorName() == _superResult[j].getBehaviorName())
            {
                _alignedResult[i].push_back(_source[i][cur]);
                cur=cur+1;
            }
            else
            {
                _alignedResult[i].push_back(BehaviorObj("_","_"));
            }
        }
    }
}
vector<BehaviorObj> MultiEditDistanceBasedOnTwo::getSuperResult()
{
    //assert(_superResult.size()>0);
    return _superResult;
}
vector<list<BehaviorObj> > MultiEditDistanceBasedOnTwo::getAlignedResult()
{
    //assert(_alignedResult.size()>0);
    return _alignedResult;
}