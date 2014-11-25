//
//  MultiEditDistanceBasedOnTwo.cpp
//  EditDistance
//
//  Created by Young on 11-17－此月第4周.
//  Copyright (c) 2014年 Young. All rights reserved.
//

#include "MultiEditDistanceBasedOnTwo.h"
#include <queue>
#include <assert.h>
MultiEditDistanceBasedOnTwo::MultiEditDistanceBasedOnTwo(vector<vector<BehaviorObj*> > &source)
{
    _source=source;
    _alignedResult=vector<list<BehaviorObj> >(_source.size());
    generateSuperResult();
    //printSuperResult();
    generateAlignedResult();

}
MultiEditDistanceBasedOnTwo::~MultiEditDistanceBasedOnTwo()
{
//    for(int i=0;i<_source.size();i++)
//    {
//        for(int j=0;j<_source[i].size();j++)
//        {
//            delete _source[i][j];
//            _source[i][j]=NULL;
//        }
//    }
    for(int i=0;i<_superResult.size();i++)
    {
        delete _superResult[i];
        _superResult[i]=NULL;
    }

}
//void MultiEditDistanceBasedOnTwo::generateSuperResult()
//{
//    int len = (int)_source.size();
//    vector<vector<BehaviorObj> > temp=_source;
//
//    while(len>1)
//    {
//        int k = (len+1)/2;
//        //vector<vector<BehaviorObj> >temp;
//        for(int i = 0; i < len/2; i++)
//        {
//            EditDistance myEd=EditDistance(temp[i],temp[i+k]);
//            temp[i]=myEd.getSuperResult();
//            //myEd.printSuperResult();
//            //assert(_source[i].size()>0);
//        }
//        len = k;
//    }
//    _superResult=temp[0];
//    //printSuperResult();
//    
//}

//vector<BehaviorObj> &MultiEditDistanceBasedOnTwo::generateSuperResult(int start,int end)
//{
//    if(start == end)
//    {
//        return _source[end];
//    }
//    else
//    {
//        int mid=1.0*(start+end)/2;
//        vector<BehaviorObj> left=generateSuperResult(start, mid);
//        vector<BehaviorObj> right=generateSuperResult(mid+1, end);
//        EditDistance myED= EditDistance(left,right);
//        vector<BehaviorObj> temp;
////        for(int i=0;i<myED.getSuperResult().size();i++)
////        {
////            temp.push_back(myED.getSuperResult()[i]);
////        }
//        return myED.getSuperResult();
//    }
//}

void MultiEditDistanceBasedOnTwo::generateSuperResult()
{
    queue<vector<BehaviorObj*> > myQueue;
    for(int i=0;i<_source.size();i++)
    {
        vector<BehaviorObj*> temp;
        for(int j=0;j<_source[i].size();j++)
        {
            temp.push_back(_source[i][j]);
        }
        myQueue.push(temp);
    }

    while(myQueue.size()>1)
    {
        vector<BehaviorObj*> s1=myQueue.front();
        //cout<<"!!!!"<<s1[0].getBehaviorName()<<endl;
        //(*s1)[0].superID=11111;
        //cout<<_source[0][0].superID<<endl;
        myQueue.pop();
        vector<BehaviorObj*> s2=myQueue.front();
        //cout<<"****"<<s2[0].getBehaviorName()<<endl;
        myQueue.pop();
        vector<vector<int> > editMatrix=vector< vector<int> >(s1.size()+1, vector<int>(s2.size()+1));
        if(s1.size()>0 && s2.size()>0)
        {
            generateEditMatrix(editMatrix, s1, s2);
            vector<BehaviorObj*> tempResult = vector<BehaviorObj*>();
            backTrace(editMatrix, s1, s2,tempResult);
            myQueue.push(tempResult);
            
            if(s1[0]->superID != -1)
            {
                for(int m=0;m<s1.size();m++)
                {
                    delete s1[m];
                    s1[m]=NULL;
                }
            }
            
            if(s2[0]->superID != -1)
            {
                for(int m=0;m<s2.size();m++)
                {
                    delete s2[m];
                    s2[m]=NULL;
                }
            }
        }
    }
    if(myQueue.size()==1)
    {
        _superResult=myQueue.front();
        myQueue.pop();
    }
}


//void MultiEditDistanceBasedOnTwo::printSuperResult()
//{
//    cout<<"Super_Result:"<<endl;
//    for(int i=0;i<(int)(*_superResult).size();i++)
//    {
//        cout<<(*_superResult)[i].getBehaviorName()<<" ";
//    }
//    cout<<endl;
//    cout<<"SourceResult:"<<endl;
//    for(int i=0;i<(int)_source.size();i++)
//    {
//        for(int j=0;j<_source[i].size();j++)
//        {
//            cout<<_source[i][j].getBehaviorName()<<" ";
//        }
//        cout<<endl;
//    }
//}

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
        cout<<_superResult[count]->getBehaviorName()<<endl;
        count++;
    }

}

void MultiEditDistanceBasedOnTwo::generateAlignedResult()
{
    for(int i=0;i<_source.size();i++)
    {
        int preID=-1;
        assert(_source[i][0]->parentNode!=NULL);
        int curID=_source[i][0]->parentNode->superID;
        
        for(int j=0; j<curID; j++)
        {
            _alignedResult[i].push_back(BehaviorObj("_","_"));
        }
        
        preID=curID-1;
        for(int j=0;j<_source[i].size();j++)
        {
            assert(_source[i][j]->parentNode!=NULL);
            curID=_source[i][j]->parentNode->superID;
            if(preID == -1)
            {
                _alignedResult[i].push_back(BehaviorObj(_source[i][j]->getBehaviorName(),""));
            }
            else
            {
                for(int n=preID+1; n<curID; n++)
                {
                    _alignedResult[i].push_back(BehaviorObj("_","_"));
                }
                _alignedResult[i].push_back(BehaviorObj(_source[i][j]->getBehaviorName(),""));
            }
            preID=curID;
        }
        
        for(int j=curID+1; j<_superResult.size(); j++)
        {
            _alignedResult[i].push_back(BehaviorObj("_","_"));
        }
    }
}

void MultiEditDistanceBasedOnTwo::generateEditMatrix(vector< vector<int> > &editMatrix,vector<BehaviorObj*> &s1,vector<BehaviorObj*> &s2)
{
    //initialization
    editMatrix[0][0]=0;
    for(int i=1;i<s1.size()+1;i++)
    {
        editMatrix[i][0]=i;
    }
    for(int i=1;i<s2.size()+1;i++)
    {
        editMatrix[0][i]=i;
    }
    
    
    for(int i=1;i<editMatrix.size();i++)
    {
        for(int j=1;j<editMatrix[i].size();j++)
        {
            if(s1[i-1]->getBehaviorName() == s2[j-1]->getBehaviorName())
            {
                editMatrix[i][j]= editMatrix[i-1][j-1];//keep the same
                
            }
            else
            {
                if(editMatrix[i-1][j]>editMatrix[i][j-1])
                {
                    editMatrix[i][j]=editMatrix[i][j-1]+1;//add j;
                }
                else
                {
                    editMatrix[i][j]=editMatrix[i-1][j]+1;//add i;
                }
            }
        }
    }

}

void MultiEditDistanceBasedOnTwo::backTrace(vector< vector<int> > &editMatrix,vector<BehaviorObj*> &s1,vector<BehaviorObj*> &s2,vector<BehaviorObj*> &superResult)
{
    int i=(int)s1.size();
    int j=(int)s2.size();
    std::vector<BehaviorObj*>::iterator it;
    while(i>=1 && j>=1)
    {
        it=superResult.begin();
        if(s1[i-1]->getBehaviorName() == s2[j-1]->getBehaviorName())
        {
            BehaviorObj *superNode= new BehaviorObj(s1[i-1]->getBehaviorName(),"");
            if(superNode == NULL)
                cerr<<"superNode is NULL"<<endl;
            //superNode.setParentNode(NULL);
            if(s1[i-1]->childNodesVec.size()>0)//is not a original node
            {
                for(int n=0; n<s1[i-1]->childNodesVec.size(); n++)
                {
                    (s1[i-1]->childNodesVec[n])->parentNode=superNode;
                    superNode->childNodesVec.push_back(s1[i-1]->childNodesVec[n]);
                }
            }
            else
            {
                s1[i-1]->parentNode=superNode;
                superNode->childNodesVec.push_back(s1[i-1]);
                
            }
            if(s2[j-1]->childNodesVec.size()>0)
            {
                for(int n=0; n<s2[j-1]->childNodesVec.size(); n++)
                {
                    (s2[j-1]->childNodesVec[n])->parentNode=superNode;
                    superNode->childNodesVec.push_back(s2[j-1]->childNodesVec[n]);
                }
            }
            else
            {
                s2[j-1]->parentNode=superNode;
                superNode->childNodesVec.push_back(s2[j-1]);
            }
            
            superResult.insert(it,superNode);
            i=i-1;
            j=j-1;
        }
        else
        {
            if(editMatrix[i][j-1]<editMatrix[i-1][j])
            {
                BehaviorObj *superNode= new BehaviorObj(s2[j-1]->getBehaviorName(),"");
                if(superNode == NULL)
                    cerr<<"superNode is NULL"<<endl;
                if(s2[j-1]->childNodesVec.size()>0)
                {
                    for(int n=0; n<s2[j-1]->childNodesVec.size(); n++)
                    {
                        s2[j-1]->childNodesVec[n]->parentNode=superNode;
                        superNode->childNodesVec.push_back(s2[j-1]->childNodesVec[n]);
                    }
                }
                else
                {
                    s2[j-1]->parentNode=superNode;
                    superNode->childNodesVec.push_back(s2[j-1]);
                }
                
                superResult.insert(it,superNode);
                j=j-1;
            }
            else
            {
                BehaviorObj *superNode= new BehaviorObj(s1[i-1]->getBehaviorName(),"");
                if(superNode == NULL)
                    cerr<<"superNode is NULL"<<endl;
                //superNode.setParentNode(NULL);
                if(s1[i-1]->childNodesVec.size()>0)//is not a original node
                {
                    for(int n=0; n<s1[i-1]->childNodesVec.size(); n++)
                    {
                        s1[i-1]->childNodesVec[n]->parentNode=superNode;
                        superNode->childNodesVec.push_back(s1[i-1]->childNodesVec[n]);
                    }
                }
                else
                {
                    s1[i-1]->parentNode=superNode;
                    superNode->childNodesVec.push_back(s1[i-1]);
                    
                }
                superResult.insert(it,superNode);
                i=i-1;
            }
        }
    }
    while(i>=1)
    {
        it=superResult.begin();
        BehaviorObj *superNode=new BehaviorObj(s1[i-1]->getBehaviorName(),"");
        if(superNode == NULL)
            cerr<<"superNode is NULL"<<endl;
        //superNode.setParentNode(NULL);
        if(s1[i-1]->childNodesVec.size()>0)//is not a original node
        {
            for(int n=0; n<s1[i-1]->childNodesVec.size(); n++)
            {
                s1[i-1]->childNodesVec[n]->parentNode=superNode;
                superNode->childNodesVec.push_back(s1[i-1]->childNodesVec[n]);
            }
        }
        else
        {
            s1[i-1]->parentNode=superNode;
            superNode->childNodesVec.push_back(s1[i-1]);
            
        }
        superResult.insert(it,superNode);
        i--;
    }
    while(j>=1)
    {
        it=superResult.begin();
        BehaviorObj *superNode= new BehaviorObj(s2[j-1]->getBehaviorName(),"");
        if(superNode == NULL)
            cerr<<"superNode is NULL"<<endl;
        if(s2[j-1]->childNodesVec.size()>0)
        {
            for(int n=0; n<s2[j-1]->childNodesVec.size(); n++)
            {
                s2[j-1]->childNodesVec[n]->parentNode=superNode;
                superNode->childNodesVec.push_back(s2[j-1]->childNodesVec[n]);
            }
        }
        else
        {
            s2[j-1]->parentNode=superNode;
            superNode->childNodesVec.push_back(s2[j-1]);
        }
        
        superResult.insert(it,superNode);
        j--;
    }
    
    for(int i=0;i<superResult.size();i++)
    {
        superResult[i]->superID=i;
    }
}

vector<BehaviorObj*> MultiEditDistanceBasedOnTwo::getSuperResult()
{
    //assert(_superResult.size()>0);
    return _superResult;
}
vector<list<BehaviorObj> > MultiEditDistanceBasedOnTwo::getAlignedResult()
{
    //assert(_alignedResult.size()>0);
    return _alignedResult;
}