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
MultiEditDistanceBasedOnTwo::MultiEditDistanceBasedOnTwo(vector<vector<BehaviorObj*> > &source,int baseID)
{
    _source=source;
    _baseID=baseID;
    _alignedResult=vector<list<BehaviorObj> >(_source.size());
    generateSuperResult();
    generateAlignedResult();
    printAlignedResults();
    Max_node=(int)_superResult.size();
    initGraph((int)_superResult.size());
    initEdges();
    Create_Level();
    Split_edges();
    
    Reduce_crossing();
    //printSuperResult();

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
        superResult[i]->superID=i+_baseID;
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

void MultiEditDistanceBasedOnTwo::initGraph(int node_num)
{
    //cout<<node_num<<endl;
    // Represents a graph of two vector
    //node_num-1 for our special situation
    for(int i=0;i<node_num;i++)
    {
        for(int j=0;j<node_num;j++)
        {
            node_vector.push_back(0);
        }
        graph_vector.push_back(node_vector);
        node_vector.clear();
    }
}

void MultiEditDistanceBasedOnTwo::initEdges()
{
    for(int i=0;i<_source.size();i++)
    {
        if(_source[i].size()>1)
        {
            for(int j=0;j<_source[i].size()-1;j++)
            {
                assert(_source[i][j]->parentNode!=NULL);
                assert(_source[i][j+1]->parentNode!=NULL);
                int curID=_source[i][j]->parentNode->superID;
                int nextID=_source[i][j+1]->parentNode->superID;
                insert_edge(curID, nextID);
                map<int,map<int,float> >::iterator it=edgesMap.find(curID);
                if(it == edgesMap.end())
                {
                    map<int,float> tmp;
                    tmp.insert(std::pair<int, float>(nextID,1.0));
                    edgesMap.insert(std::pair<int, map<int,float> >(curID,tmp));
                }
                else
                {
                    map<int,float>::iterator iter=edgesMap[curID].find(nextID);
                    if(iter == edgesMap[curID].end())
                    {
                        edgesMap[curID].insert(std::pair<int, float>(nextID,1.0));
                    }
                    else
                    {
                        edgesMap[curID][nextID]=edgesMap[curID][nextID]+1.0;
                    }
                }
            }
        }
    }

}

void MultiEditDistanceBasedOnTwo::insert_edge(int source,int target)
{
    graph_vector[source][target] = 1;
}

int** MultiEditDistanceBasedOnTwo::init_matrix(int** matrix, int number)
{
    for(int i=0;i<number;i++)
    {
        for(int j=0;j<number;j++)
        {
            matrix[i][j] = 0;
        }
    }
    
    return matrix;
}

void MultiEditDistanceBasedOnTwo::Create_Level()
{
    // End process by using the matrix by creating a matrix of the graph size
    int node_number = (int)graph_vector.size();
    int edge_number=0;
    int current_level=0;
    int input_check=0;
    int** level_matrix = (int **) malloc(node_number*sizeof(int *));
    node_level_list = (int *) malloc(Max_node*sizeof(int));//save the level of each node
    for (int i=0; i<node_number; i++)
    {
        level_matrix[i] = (int *) malloc(node_number*sizeof(int));
    }
    // Copy the original graph.
    for(int j=0;j<node_number;j++)
    {
        for(int k=0;k<node_number;k++)
        {
            level_matrix[j][k] = graph_vector[j][k];
            if(level_matrix[j][k] == 1)
                edge_number++; // Determine the number of edges in the graph
        }
        // Initialize the level of all nodes to 0.
        node_level_list[j] = -1;
    }
    
    //Level calculates the information.
    
    while (edge_number > 0) // Turns the while loop as long as the number of edges.
    {
        // Then makes the value of the level that was already checked for level check to zero.
        if(current_level >0)
        {
            for(int i=0;i<node_number;i++)
            {
                if (node_level_list[i] == current_level-1) // Clear the edge of the input node that was in the previous level.
                {
                    for(int j=0;j<node_number;j++)
                    {
                        if (level_matrix[i][j] == 1)
                        {
                            level_matrix[i][j] = 0;
                            edge_number--;             // Delete the test allows one edge.
                        }
                    }
                }
            }
        }
        // If there is an edge coming into the input level increases
        // If there is no column to examine the input edge is the highest level.
        for(int i=0;i<node_number;i++)
        {
            if (node_level_list[i] >= 0) continue;
            
            input_check=0;
            for(int j=0;j<node_number;j++)
            {
                if (level_matrix[j][i] == 1) // The input edge in the I-th node.
                {
                    break;
                }
                input_check++;
            }
            if (input_check == node_number) // There is no input edge.
            {
                level_node.push_back(i);   // Insert the i-node for the current level
                // cout<<"No input edge"<<i<<endl;
                node_level_list[i] = current_level;
            }
        }
        level_vector.push_back(level_node);
        level_node.clear();
        current_level++; // Increase level for the next level
    }
    
    for(int i=0;i<node_number;i++)
    {
        //cout<<node_level_list[i]<<' ';
    }
    cout<<endl;
    free(level_matrix);
}

void MultiEditDistanceBasedOnTwo::display_level(int node_num)
{
    std::vector <int> temp;
    cout<<level_vector.size()<<endl;
    for(int i=0;i<level_vector.size();i++)
    {
        temp = level_vector.at(i);
        for(int j=0;j<temp.size();j++)
        {
            if (temp[j]+1 > node_num)
                continue;
            else
                cout<<temp[j]+1<<' ';
        }
        cout<<endl;
    }
}

void MultiEditDistanceBasedOnTwo::Split_edges()
{
    // The level of the value of the next node from one node in the graph metrics time must be one difference.
    // 1 inserts the dummy nodes when more difference occurs.
    int node_number =(int)graph_vector.size();
    int node_id=0;
    for(int i=0;i<node_number;i++)
    {
        for(int j=0;j<node_number;j++)
        {
            if (graph_vector[i][j] == 1)
            {
                // The edge is in the j-th node in the i-th node.
                if (node_level_list[i]+1 != node_level_list[j])
                {
                    // If you are not immediately adjacent to create a dummy node
                    // Dummy number of node i + 1 and the level of the difference of the j
                    int prenode=i;
                    for(int k=node_level_list[i]+1;k<node_level_list[j];k++)
                    {
                        // Adds a dummy node in the graph matrix.
                        node_id = (int)graph_vector.size();
                        
                        // Adds a dummy node for each node.
                        for(int p=0;p<node_id;p++)//<node_id
                        {
                            graph_vector[p].push_back(0);
                        }
                        node_vector.clear();
                        for(int t=0;t<=node_id;t++)//<=node_id
                        {
                            node_vector.push_back(0);
                        }
                        graph_vector.push_back(node_vector);
                        ///////////////////////////////////////////////////
                        graph_vector[prenode][j] =0;
                        graph_vector[prenode][node_id] =1;
                        graph_vector[node_id][j] =1;
                        prenode=node_id;
                        node_level_list[node_id] = k;
                        level_vector[k].push_back(node_id);
                    }
                }
            }
        }
    }
}

int MultiEditDistanceBasedOnTwo::NumberOfCrossEdge()
{
    int result_cross=0;
    // Use the calculation expression in the paper
    for (int i=0; i<level_vector.size()-1; i++)//without the last level,choose the current level
    {
        for (int j=0; j<level_vector[i].size()-1; j++)//without the last node, the node set of current level, choose the current node
        {
            for (int k=j+1; k<level_vector[i].size(); k++)//the next node set which need to compared
            {
                for (int a=0; a<level_vector[i+1].size()-1; a++)//the node of next level
                {
                    for (int b=a+1; b<level_vector[i+1].size(); b++)//the all node in the next level
                    {
                        if(graph_vector[level_vector[i][j]][level_vector[i+1][b]] == 1 && graph_vector[level_vector[i][k]][level_vector[i+1][a]] == 1)
                        {
                            result_cross++;
                        }
                    }
                }
            }
        }
    }
    return result_cross;}

void MultiEditDistanceBasedOnTwo::Phase1_up(int level)
{
    std::vector <int> row_value,col_value;
    int input_edge_sum=0;       // Number of edges coming into self node
    int input_edge_value_sum=0; // Sum of the position value of the magnetic incoming edge node
    float *bc_value;
    for(int i=level-1;i>0;i--)
    {
        row_value = level_vector[i-1];
        col_value = level_vector[i]; // The following line BC calculation method Column.
        bc_value = (float *) malloc(row_value.size()*sizeof(float)); // BC variable to store the value
        // Calculate the BC value for each column.
        for(int j=0;j<row_value.size();j++)
        {
            input_edge_sum=0;
            input_edge_value_sum=0;
            for(int k=0;k<col_value.size();k++)
            {
                if (graph_vector[row_value[j]][col_value[k]] == 1)
                {
                    input_edge_sum++;                  // Denominator value of BC
                    input_edge_value_sum = input_edge_value_sum+k; // The value of the numerator of the BC value
                }
            }
            //if()
            bc_value[j] = input_edge_value_sum / input_edge_sum; //
        }
        // Sort-up to the value of the BC-shifts the sequence of level_vector.
        
        int temp=0; // Sort value temporary storage
        for (int j=0;j<row_value.size()-1;j++)
        {
            for(int k=j+1;k<row_value.size();k++)
            {
                if (bc_value[k] <  bc_value[j])
                {
                    // SWAP
                    //smallest = k;
                    temp = bc_value[j];
                    bc_value[j] = bc_value[k];
                    bc_value[k] = temp;
                    
                    temp = row_value[k];
                    row_value[k] = row_value[j];
                    row_value[j] = temp;
                }
            }
        }
        level_vector[i-1] = row_value;
        free(bc_value);
    }
}
void MultiEditDistanceBasedOnTwo::Phase1_down(int level)
{
    std::vector <int> row_value,col_value;
    int input_edge_sum=0;       // Number of edges coming into self node
    int input_edge_value_sum=0; // Sum of the position value of the magnetic incoming edge node
    float * bc_value;
    for(int i=0;i<level-1;i++)
    {
        row_value = level_vector[i];
        col_value = level_vector[i+1]; // The following line BC calculation method Column.
        bc_value = (float *) malloc(col_value.size()*sizeof(float)); // BC variable to store the value
        
        // Calculate the BC value for each column.
        for(int j=0;j<col_value.size();j++)
        {
            input_edge_sum=0;
            input_edge_value_sum=0;
            for(int k=0;k<row_value.size();k++)
            {
                if (graph_vector[row_value[k]][col_value[j]] == 1)
                {
                    input_edge_sum++;                  // Denominator value of BC
                    input_edge_value_sum = input_edge_value_sum+k; // The value of the numerator of the BC value
                }
            }
            bc_value[j] = input_edge_value_sum / input_edge_sum; //
        }
        // Sort-up to the value of the BC-shifts the sequence of level_vector.
        
        int temp=0; // Sort value temporary storage
        //int smallest=0;
        for (int j=0;j<col_value.size()-1;j++)
        {
            //smallest = j;
            
            for(int k=j+1;k<col_value.size();k++)
            {
                if (bc_value[k] <  bc_value[j])
                {
                    // SWAP
//                    smallest = k;
//                    temp = bc_value[i];
//                    bc_value[i] = bc_value[smallest];
//                    bc_value[smallest] = temp;
//                    temp = col_value[i];
//                    col_value[i] = col_value[smallest];
//                    col_value[smallest] = temp;
                    temp=bc_value[j];
                    bc_value[j]=bc_value[k];
                    bc_value[k]=temp;
                    //smallest=k;
                    
                    temp=col_value[j];
                    col_value[j]=col_value[k];
                    col_value[k]=temp;                    
                }
            }
        }
        level_vector[i+1] =col_value;
        free(bc_value);
    }
}

void MultiEditDistanceBasedOnTwo::Phase2_down(int level)
{
    // BC If the values are equal to each other, reverse calculation
    std::vector <int> row_value,col_value;
    int input_edge_sum=0;       // Number of edges coming into self node
    int input_edge_value_sum=0; //The sum of the position value of the magnetic incoming edge node
    float * bc_value;
    int best_cross_edge=0;      //Best edges out the best, if not less
    int current_cross_edge = 0; //The current number of edges
    std::vector <int> Backup_node_level;
    std::vector< vector<int> > Backup_level_vector;
    
    
    // Thereby backup the current level.
    for(int q=0;q<level_vector.size();q++)
    {
        for(int s=0;s<level_vector[q].size();s++)
        {
            Backup_node_level.push_back(level_vector[q][s]);
        }
        Backup_level_vector.push_back(Backup_node_level);
        Backup_node_level.clear();
    }
    
    // Record the number of the current edge.
    current_cross_edge = NumberOfCrossEdge();
    best_cross_edge = current_cross_edge;
    for(int i=0;i<level-1;i++)
    {
        row_value = level_vector[i];
        col_value = level_vector[i+1]; // The following line BC calculation method Column.
        bc_value = (float *) malloc(col_value.size()*sizeof(float)); // BC variable to store the value
        // Calculate the BC value for each column.
        for(int j=0;j<col_value.size();j++)
        {
            input_edge_sum=0;
            input_edge_value_sum=0;
            for(int k=0;k<row_value.size();k++)
            {
                if (graph_vector[row_value[k]][col_value[j]] == 1)
                {
                    input_edge_sum++;                  // Denominator value of BC
                    input_edge_value_sum = input_edge_value_sum+k; // The value of the numerator of the BC value
                }
            }
            bc_value[j] = input_edge_value_sum / input_edge_sum; //
        }
        
        
        // Change the order of BC have all the same value.
        int temp_value=0;
        bool is_change=false;      // BC to examine the value of such
        for (int j=0; j<col_value.size()-1; j++)
        {
            if (bc_value[j] == bc_value[j+1])
            {
                is_change=true;
                temp_value = col_value[j];
                col_value[j] = col_value[j+1];
                col_value[j+1] = temp_value;
            }
        }
        // After the Phase2 down makes a down, up the Phase1.
        if (is_change)
        {
            level_vector[i+1] = col_value;
            for(int m=0;m<10;m++)
            {
                Phase1_down(level);
                Phase1_up(level);
            }
        }
        
        // Calculate the number of re-cross edge.
        current_cross_edge = NumberOfCrossEdge();
        
        if (current_cross_edge < best_cross_edge)
        {
            best_cross_edge = current_cross_edge;
            // Store the backup information in the new leveling
            for(int j=0;j<level_vector.size();j++)
            {
                Backup_level_vector[j] = level_vector[j];
            }
        }
        else
        {
            // Restore the backed-leveling
            for(int j=0;j<level_vector.size();j++)
            {
                level_vector[j]=Backup_level_vector[j];
            }
        }
        free(bc_value);
    }
}

void MultiEditDistanceBasedOnTwo::Phase2_up(int level)
{
    // BC If the values are equal to each other, reverse calculation
    std::vector <int> row_value,col_value;
    int input_edge_sum=0;       // Number of edges coming into self node
    int input_edge_value_sum=0; // Sum of the position value of the magnetic incoming edge node
    float * bc_value;
    int best_cross_edge=0;      // If not the best edge out the best low
    int current_cross_edge = 0; // The current number of edges
    std::vector <int> Backup_node_level;
    std::vector< vector<int> > Backup_level_vector;
    
    
    // To backup the current level.
    for(int q=0;q<level_vector.size();q++)
    {
        for(int s=0;s<level_vector[q].size();s++)
        {
            Backup_node_level.push_back(level_vector[q][s]);
        }
        Backup_level_vector.push_back(Backup_node_level);
        Backup_node_level.clear();
    }
    
    // Record the number of the current edge.
    current_cross_edge = NumberOfCrossEdge();
    best_cross_edge = current_cross_edge;
    for(int i=level-1;i>0;i--)
    {
        row_value = level_vector[i-1];
        col_value = level_vector[i]; // The following line BC calculation method Column.
        bc_value = (float *) malloc(row_value.size()*sizeof(float)); // BC variable to store the value
        // Calculate the BC value for each column.
        for(int j=0;j<row_value.size();j++)
        {
            input_edge_sum=0;
            input_edge_value_sum=0;
            for(int k=0;k<col_value.size();k++)
            {
                if (graph_vector[row_value[j]][col_value[k]] == 1)
                {
                    input_edge_sum++;                  // Denominator value of BC
                    input_edge_value_sum = input_edge_value_sum+k; // The value of the numerator of the BC value
                }
            }
            bc_value[j] = input_edge_value_sum / input_edge_sum; //
        }
        
        
        // Change the order of BC have all the same value.
        int temp_value=0;
        bool is_change=false;      // BC to examine the value of such
        for (int j=0; j<row_value.size()-1; j++)
        {
            if (bc_value[j] == bc_value[j+1])
            {
                is_change=true;
                temp_value = row_value[j];
                row_value[j] = row_value[j+1];
                row_value[j+1] = temp_value;
            }
        }
        // After the Phase2 down makes a down, up the Phase1.
        if (is_change)
        {
            level_vector[i-1] = row_value;
            for(int m=0;m<10;m++)
            {
                Phase1_up(level);
                Phase1_down(level);
            }
        }
        
        // Calculate the number of re-cross edge.
        current_cross_edge = NumberOfCrossEdge();
        
        if (current_cross_edge < best_cross_edge)
        {
            best_cross_edge = current_cross_edge;
            // Store the backup information in the new leveling
            for(int j=0;j<level_vector.size();j++)
            {
                Backup_level_vector[j] = level_vector[j];
            }
        }
        else
        {
            // Restore the backed-leveling
            for(int j=0;j<level_vector.size();j++)
            {
                level_vector[j]=Backup_level_vector[j];
            }
        }
        free(bc_value);
    }
}

void MultiEditDistanceBasedOnTwo::Reduce_crossing()
{
    int level_number = (int)level_vector.size();
    // Repeatedly up and down as much as Levels
    int cross_edge=0;
    cross_edge = NumberOfCrossEdge();
    //cout<<"The total number of edges"<<cross_edge<<endl;
    for(int i=0;i<10;i++)
    {
        Phase1_down(level_number);
        Phase1_up(level_number);
    }
    cross_edge = NumberOfCrossEdge();
    //cout<<" Phase1 after the total number of edges"<<cross_edge<<endl;
    for(int j=0;j<10;j++)
    {
        Phase2_up(level_number);
        Phase2_down(level_number);
    }
    cross_edge = NumberOfCrossEdge();
    //cout<<"Phase2 then the total number of edges"<<cross_edge<<endl;
    
}

map<int, map<int,float> > MultiEditDistanceBasedOnTwo::getEdgesMap()
{
    return edgesMap;
}