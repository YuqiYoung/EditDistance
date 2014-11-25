
//  main.cpp
//  EditDistance
//
//  Created by Young on 11-16－此月第3周.
//  Copyright (c) 2014年 Young. All rights reserved.



#include <iostream>
#include "BehaviorObj.h"
#include "EditDistance.h"
#include <vector>
#include "MultiEditDistanceBasedOnTwo.h"

int main(int argc, const char * argv[]) {
//    BehaviorObj *r1=new BehaviorObj("r","file1");
//    BehaviorObj *r=new BehaviorObj("r","file1");
//    BehaviorObj *w1=new BehaviorObj("w","file1");
//    BehaviorObj *w=new BehaviorObj("w","file1");
//    BehaviorObj *r2=new BehaviorObj("r","file2");
//    BehaviorObj *t=new BehaviorObj("t","file2");
//    BehaviorObj *n=new BehaviorObj("n","file2");
//    BehaviorObj *w2=new BehaviorObj("w","file2");
    
    BehaviorObj *a1=new BehaviorObj("a","s1");
    BehaviorObj *b1=new BehaviorObj("b","s1");
    BehaviorObj *c1=new BehaviorObj("c","s1");
    BehaviorObj *d1=new BehaviorObj("d","s1");
    
    BehaviorObj *d2=new BehaviorObj("d","s2");
    BehaviorObj *e2=new BehaviorObj("e","s2");
    BehaviorObj *f2=new BehaviorObj("f","s2");
    
    BehaviorObj *e3=new BehaviorObj("e","s3");
    BehaviorObj *f3=new BehaviorObj("f","s3");
    BehaviorObj *a3=new BehaviorObj("a","s3");
    BehaviorObj *b3=new BehaviorObj("b","s3");
    BehaviorObj *c3=new BehaviorObj("c","s3");
    
    vector<BehaviorObj*> s1;
    s1.push_back(a1);
    s1.push_back(b1);
    s1.push_back(c1);
    s1.push_back(d1);
    
    vector<BehaviorObj*> s2;
    s2.push_back(d2);
    s2.push_back(e2);
    s2.push_back(f2);

    
    vector<BehaviorObj*> s3;
    s3.push_back(e3);
    s3.push_back(f3);
    s3.push_back(a3);
    s3.push_back(b3);
    s3.push_back(c3);

    
//    vector<BehaviorObj> v1;
//    v1.push_back(t);
//    v1.push_back(n);
//    v1.push_back(w);
//    v1.push_back(r);
//    v1.push_back(r);
//    
//    vector<BehaviorObj> v2;
//    v2.push_back(t);
//    v2.push_back(n);
//    v2.push_back(w);
//    v2.push_back(r);
//    v2.push_back(r);
//    
//    vector<BehaviorObj> v3;
//    v3.push_back(t);
//    v3.push_back(n);
//    v3.push_back(w);
//    v3.push_back(r);
//    
//    vector<BehaviorObj> v4;
//    v4.push_back(n);
//    v4.push_back(w);
//    v4.push_back(r);
//    
//    vector<BehaviorObj> v5;
//    v5.push_back(t);
//    v5.push_back(n);
//    v5.push_back(r2);
//    v5.push_back(w);
//    v5.push_back(r);
//    
//    vector<BehaviorObj> v6;
//    v6.push_back(r2);
//    v6.push_back(r1);
//    v6.push_back(r2);
//    v6.push_back(r1);
//    v6.push_back(r2);
//    //v4.push_back(w2);
    
    vector<vector<BehaviorObj*> > source;
    source.push_back(s1);
    source.push_back(s2);
    source.push_back(s3);

    //source.push_back(v4);
    //source.push_back(v5);
    //source.push_back(v6);
    
//    EditDistance myED=EditDistance(v4,v2);
//    myED.printSuperResult();
//    myED.printEditMatrix();
    cout<<"~~~~"<<endl;
    MultiEditDistanceBasedOnTwo MED(source);
    MED.printAlignedResults();
    
    for(int i=0;i<source.size();i++)
    {
        for(int j=0;j<source[i].size();j++)
        {
            delete source[i][j];
            source[i][j]=NULL;
        }
    }
    
    return 0;
}

//#include <stdio.h>
//#include <iostream>
//#include <vector>
//#include <string>
//#include "tinyxml2.h"
//#include "BehaviorObj.h"
//#include "MultiEditDistanceBasedOnTwo.h"
//#include "EditDistance.h"
//
//char* getRelatedAttribute(const char * sectName)
//{
//    if(!strcmp(sectName,"registry"))
//    {
//        return "key";
//    }
//    else if(!strcmp(sectName,"filesystem"))
//    {
//        return "file";
//    }
//    else if(!strcmp(sectName,"system"))
//    {
//        return "module";
//    }
//    else if(!strcmp(sectName,"virtual_memory"))
//    {
//        return "api";
//        //<vm_alloc timestamp="00:01.922" api="VirtualAllocEx" args="( ffffffff, 0, 10000, 2000, 4 )" ret="8f0000"/>
//        //<vm_alloc timestamp="00:01.922" api="VirtualAlloc" args="( 0, 10000, 2000, 4 )" ret="8f0000"/>
//    }
//    else if(!strcmp(sectName,"service"))
//    {
//        return "api";
//        //<create_sc_manager timestamp="00:04.547" api="OpenSCManagerW" args="( , , 1 )" ret="1852d8" machinename="" databasename=""/>
//        //<open_service timestamp="00:04.547" api="OpenServiceW" args="( 1852d8, ProtectedStorage, 5 )" ret="188540" servicename="ProtectedStorage"/>
//    }
//    else if(!strcmp(sectName,"network"))
//    {
//        return "api";//not sure
//    }
//    else if(!strcmp(sectName,"window"))
//    {
//        return "api";//not sure
//    }
//    else if(!strcmp(sectName,"systeminfo"))
//    {
//        return "api";//not sure
//    }
//    else
//    {
//        std::cerr<<"dont have "<<sectName<<" section"<<std::endl;
//        return "";
//    }
//    
//}
//
////a is the file path
//void readXMLFiles(const char * a, vector<BehaviorObj> &stra, const char * sectName=0)
//{
//    //std::cout<<"readXMLFiles"<<a<<std::endl;
//    char* attr=getRelatedAttribute(sectName);
//    
//    tinyxml2::XMLDocument doca;
//    tinyxml2::XMLElement *rootElement,*listElement,*procElement,*sectElement,*currElement;
//    std::cout<<"load file "<<a<<std::endl;
//    doca.LoadFile(a);
//    
//    //std::vector<const char *> seqa;
//    
//    rootElement = doca.FirstChildElement();
//    if(rootElement){
//        std::cout<<"rootElement is found"<<std::endl;
//        listElement = rootElement->FirstChildElement("processes");
//        if(listElement){
//            std::cout<<"listElement is found"<<std::endl;
//            procElement = listElement->FirstChildElement();
//            if(procElement){
//                do{
//                    //find the right section
//                    std::cout<<"procElement is found"<<std::endl;
//                    sectElement = procElement->FirstChildElement();
//                    if(sectElement){
//                        if(sectName)
//                        {
//                            std::cout<<"sectElement "<<sectName<<" is found"<<std::endl;
//                            do{
//                                if(!strcmp(sectName, sectElement->Attribute("name"))){
//                                    //iterate over sequence
//                                    currElement = sectElement->FirstChildElement();
//                                    do{
//                                        //seqa.push_back(currElement->Name());
//                                        std::cout<<"*****_"<<currElement->Name()<<" ";
//                                        if(currElement->Attribute(attr))
//                                        {
//                                            std::cout<<"!!!!!_"<<currElement->Attribute(attr);
//                                            
//                                            BehaviorObj tmpObj=BehaviorObj(currElement->Name(),currElement->Attribute(attr),currElement);
//                                            stra.push_back(tmpObj);
//                                            std::cout<<"vector.push_back"<<std::endl;
//                                        }
//                                        else
//                                        {
//                                            std::cout<<"@@@@@_";
//                                            BehaviorObj tmpObj=BehaviorObj(currElement->Name(),"",currElement);
//                                            stra.push_back(tmpObj);
//                                            std::cout<<"vector.push_back"<<std::endl;
//                                        }
//                                        /*const tinyxml2::XMLAttribute *tmpAttr = currElement -> FirstAttribute();
//                                         std::cout<<"!!!!!!sectElement "<<sectName<<": ("<<tmpAttr->Name()<<","<<tmpAttr->Value()<<"),";
//                                         while(tmpAttr->Next())
//                                         {
//                                         //std::cout<<tmpAttr->Name()<<","<<tmpAttr->Value()<<"),";
//                                         tmpAttr=tmpAttr->Next();
//                                         }
//                                         cout<<endl;*/
//                                        currElement=currElement->NextSiblingElement();
//                                    }while(currElement);
//                                    break;
//                                }
//                                sectElement=sectElement->NextSiblingElement();
//                            }while(sectElement);
//                        }
//                        
//                    }
//                    procElement=procElement->NextSiblingElement();
//                }while(procElement);
//            }
//        }
//    }
//    if(stra.size()==0)
//        std::cout<<"the size of result is 0"<<std::endl;
//}
//
//void grabInfoFromXMLFiles(std::vector<std::string> xfiles, vector<vector<BehaviorObj> > &source, const char * secName)
//{
//    for(int i=0;i<xfiles.size();i++)
//    {
//        vector<BehaviorObj> stra;
//        readXMLFiles(xfiles[i].c_str(), stra, secName);
//        if(stra.size()>0)
//        {
//            for(int j=0;j<stra.size();j++)
//            {
//                cout<<stra[j].getBehaviorName()<<endl;
//            }
//            source.push_back(stra);
//        }
//    }
//    
//    cout<<"Finished(transfer xml files to targetRawArray)"<<endl;
//    
//}
//
//int main(int argc, char ** argv){
//    if(argc<2)
//        exit(-1);
//    vector<string> sectionNameArray;
//    sectionNameArray.push_back("registry");
//    sectionNameArray.push_back("filesystem");
//    sectionNameArray.push_back("mutex");
//    sectionNameArray.push_back("process");
//    sectionNameArray.push_back("thread");
//    sectionNameArray.push_back("file");
//    sectionNameArray.push_back("system");
//    sectionNameArray.push_back("virtual_memory");
//    sectionNameArray.push_back("service");
//    sectionNameArray.push_back("network");
//    sectionNameArray.push_back("internet_helper");
//    sectionNameArray.push_back("window");
//    sectionNameArray.push_back("systeminfo");
//    
//    //d=compareCStrings(argv[1], argv[2]);
//    //d=EDCStrings(argv[1], argv[2]);
//    vector<string> xfiles= vector<string>(argc-1);
//    for(int i=0;i<xfiles.size();i++)
//    {
//        xfiles[i].append(argv[i+1]);
//        cout<<i<<" "<<xfiles[i]<<endl;
//    }
//    //d=compareXMLFiles(argv[1], argv[2],argc>3?argv[3]:"filesystem");
//    //printf("distance is %f\n",d);
//    //for(int i=0;i<sectionNameArray.size();i++)
//    for(int i=0;i<1;i++)
//    {
//        vector<vector<BehaviorObj> > source;
//        cout<<"<"<<sectionNameArray[i]<<">"<<endl;
//        grabInfoFromXMLFiles(xfiles,source,sectionNameArray[i].c_str());
//        if(source.size()>1)
//        {
//            MultiEditDistanceBasedOnTwo myED=MultiEditDistanceBasedOnTwo(source);
//            myED.printAlignedResults();
//        }
//        cout<<"<"<<sectionNameArray[i]<<"/>"<<endl;
//    }
//    
//    return 0;
//}

