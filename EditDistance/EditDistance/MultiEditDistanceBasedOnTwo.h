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
#include "BehaviorObj.h"
#include <list>
#include <vector>
#include <map>
#include <iomanip>
class MultiEditDistanceBasedOnTwo
{
public:
    MultiEditDistanceBasedOnTwo(vector<vector<BehaviorObj*> > &source,int baseID);
    ~MultiEditDistanceBasedOnTwo();
    void generateSuperResult();
    void generateAlignedResult();
    vector<BehaviorObj*> getSuperResult();
    vector<list<BehaviorObj> > getAlignedResult();
    void printAlignedResults();
    //void printSuperResult();
    void generateEditMatrix(vector< vector<int> > &editMatrix,vector<BehaviorObj*> &s1,vector<BehaviorObj*> &s2);
    void backTrace(vector< vector<int> > &editMatrix,vector<BehaviorObj*> &s1,vector<BehaviorObj*> &s2,vector<BehaviorObj*> &superResult);
    
    void initGraph(int node_num);
    void initEdges();
    void insert_edge(int source,int target);
    int** init_matrix(int** matrix, int number);
    void Create_Level();
    void display_level(int node_num);
    void Split_edges();
    int NumberOfCrossEdge();
    void Phase1_up(int level);
    void Phase1_down(int level);
    void Phase2_down(int level);
    void Phase2_up(int level);
    void Reduce_crossing();
    map<int, map<int,float> > getEdgesMap();

    
private:
    int _baseID;
    vector<vector<BehaviorObj*> > _source;
    vector<BehaviorObj*> _superResult;
    vector<list<BehaviorObj> > _alignedResult;
    
    std::vector<int> node_vector;
    std::vector< vector<int> > graph_vector;  // Vector list represents the graph edges(representing a matrix by a vector of 2)
    std::vector< vector<int> > level_vector;  // Vector list indicating the level of each node,
    std::vector<int> level_node;
    int * node_level_list;                    // List to be used when calculating the level of the node
    //int * check_node; // Cycle node list to use when scanning
    int Max_node;
    map<int, map<int,float> > edgesMap;

    
    
};

#endif /* defined(__EditDistance__MultiEditDistanceBasedOnTwo__) */
