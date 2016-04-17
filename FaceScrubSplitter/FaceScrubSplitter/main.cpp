//
//  main.cpp
//  FaceScrubSplitter
//
//  Created by Rafael Vareto on 4/16/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "Subject.hpp"

using namespace std;

int main() {
    vector<string> head;
    multimap<string, Subject> dataset;
    
    string text, name, url, bbox, sha256;
    string fileName[] = {"facescrub_actors.txt", "facescrub_actresses.txt"};
    int imageId, faceId;
    
    ifstream infile;
    infile.open(fileName[1]);
    
    for (int index = 0; index < 6; index++) {
        infile >> text;
        head.push_back(text);
    }
    
    if (!infile.is_open()) {
        cerr << "File could not be opened\n";
    } else {
        Subject individual = Subject();
        
        while (!infile.eof()) {
            infile >> name;
            infile >> imageId;
            infile >> faceId;
            infile >> url;
            infile >> bbox;
            //infile >> bboxY1; infile >> bboxX1; infile >> bboxY2; infile >> bboxX2;
            infile >> sha256;
            
            individual.setSubject(name, imageId, faceId, bbox);
            dataset.insert(pair<string, Subject>(name, individual));
            
            printf("%s %d %d %s - %lu\n", name.c_str(), imageId, faceId, bbox.c_str(), dataset.size());
            //printf("%s %d %d %d %d %d %d - %lu\n", name.c_str(), imageId, faceId, bboxY1, bboxX1, bboxY2, bboxX2, dataset.size());
        }
    }
}