//
//  EditDistance.cpp
//  EditDistance
//
//  Created by Young on 11-16－此月第3周.
//  Copyright (c) 2014年 Young. All rights reserved.
//

#include "EditDistance.h"

EditDistance::EditDistance(vector<BehaviorObj> &s1,vector<BehaviorObj> &s2)
{
    //assert(s1.size()>0 && s2.size()>0);
    if(s1.size()>0 && s2.size()>0)
    {
        _s1=s1;
        _s2=s2;
        _editMatrix=vector< vector<int> >(s1.size()+1, vector<int>(s2.size()+1));
        _statusMatrix=vector<vector<vector<int> > >(s1.size()+1, vector<vector<int> >(s2.size()+1,vector<int>(3)));//0:i,1:j,3:operation number
        generateEditMatrix();
        backTrace();
    }
    else if(s1.size()<1&&s2.size()>0)
    {
        _superResult=s2;
    }
    else if(s2.size()<1&&s1.size()>0)
    {
        _superResult=s1;
    }
    else
    {
        _superResult=vector<BehaviorObj>();
    }
}

void EditDistance::backTrace()
{
    int i=(int)_s1.size();
    int j=(int)_s2.size();
    std::vector<BehaviorObj>::iterator it;
    while(i>=1 && j>=1)
    {
        it=_superResult.begin();
        int temp_i=_statusMatrix[i][j][0];
        int temp_j=_statusMatrix[i][j][1];
        int operation=_statusMatrix[i][j][2];
        if(operation==1)
        {
            _superResult.insert(it,_s1[i-1]);
        }
        else if(operation==2)
        {
            _superResult.insert(it,_s1[i-1]);
            it=_superResult.begin();
            _superResult.insert(it,_s2[j-1]);
        }
        else if(operation==3)
        {
            _superResult.insert(it,_s2[j-1]);
        }
        else//operation==4
        {
            _superResult.insert(it,_s1[i-1]);
        }
        i=temp_i;
        j=temp_j;
    }
    while(i>=1)
    {
        it=_superResult.begin();
        _superResult.insert(it,_s1[i-1]);
        i--;
    }
    while(j>=1)
    {
        it=_superResult.begin();
        _superResult.insert(it,_s2[j-1]);
        j--;
    }
}

void EditDistance::generateEditMatrix()
{
    //initialization
    _editMatrix[0][0]=0;
    for(int i=1;i<_s1.size()+1;i++)
    {
        _editMatrix[i][0]=i;
    }
    for(int i=1;i<_s2.size()+1;i++)
    {
        _editMatrix[0][i]=i;
    }


    for(int i=1;i<_editMatrix.size();i++)
    {
        for(int j=1;j<_editMatrix[i].size();j++)
        {
            if(_s1[i-1].getBehaviorName() == _s2[j-1].getBehaviorName())
            {
                _editMatrix[i][j]= _editMatrix[i-1][j-1];
                _statusMatrix[i][j][0]=i-1;
                _statusMatrix[i][j][1]=j-1;
                _statusMatrix[i][j][2]=1;//keep the same
                
            }
            else
            {
                if( (_editMatrix[i-1][j-1] < _editMatrix[i-1][j]) && (_editMatrix[i-1][j-1] < _editMatrix[i][j-1]) )
                {
                    _editMatrix[i][j]= _editMatrix[i-1][j-1]+1;
                    _statusMatrix[i][j][0]=i-1;
                    _statusMatrix[i][j][1]=j-1;
                    _statusMatrix[i][j][2]=2;//subtitude or add i and j

                }
                else
                {
                    if(_editMatrix[i-1][j]>_editMatrix[i][j-1])
                    {
                        _editMatrix[i][j]=_editMatrix[i][j-1]+1;
                        _statusMatrix[i][j][0]=i;
                        _statusMatrix[i][j][1]=j-1;
                        _statusMatrix[i][j][2]=3;//add j;
                    }
                    else
                    {
                        _editMatrix[i][j]=_editMatrix[i-1][j]+1;
                        _statusMatrix[i][j][0]=i-1;
                        _statusMatrix[i][j][1]=j;
                        _statusMatrix[i][j][2]=4;//add i;
                    }
                }
            }
        }
    }
}

vector<BehaviorObj> EditDistance::getSuperResult()
{
    return _superResult;
}

void EditDistance::printEditMatrix()
{
    cout<<"  0 ";
    for(int i=0;i<_s2.size();i++)
    {
        cout<<_s2[i].getBehaviorName()<<" ";
    }
    cout<<endl;
    for(int i=0;i<_editMatrix.size();i++)
    {
        if(i!=0)
            cout<<_s1[i-1].getBehaviorName()<<" ";
        else
            cout<<"0"<<" ";
        for(int j=0;j<_editMatrix[i].size();j++)
        {
            cout<<_editMatrix[i][j]<<" ";
        }
        cout<<endl;
    }

}


void EditDistance::printSuperResult()
{
    for(int i=0;i<(int)_superResult.size();i++)
    {
        cout<<_superResult[i].getBehaviorName()<<" ";
    }
    cout<<endl;
    
    for(int i=0;i<_s1.size();i++)
    {
        cout<<_s1[i].getBehaviorName()<<" ";
    }
    cout<<endl;
    
    for(int i=0;i<_s2.size();i++)
    {
        cout<<_s2[i].getBehaviorName()<<" ";
    }
    cout<<endl;
}
