//
//  main.cpp
//  FaceScrubSplitter
//
//  Created by Rafael Vareto on 4/16/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#define PARAM 0.3

#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "Subject.hpp"

using namespace std;

int main() {
    
    /** reading file **/
    vector<string> head;
    multimap<string, Subject> dataset, train, test;
    
    string text, name, imageId, faceId, url, bbox, sha256;
    string fileName[] = {"../../facescrub_actors.txt", "../../facescrub_actresses.txt"};
    
    for (int outer = 0; outer < 2; outer++) {
        ifstream infile;
        infile.open(fileName[outer]);
        
        for (int inner = 0; inner < 6; inner++) {
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
                infile >> sha256;
                
                individual.setSubject(name, imageId, faceId, bbox);
                dataset.insert(pair<string, Subject>(name, individual));
            }
        }
        infile.close();
    }
    
    /** splitting into training and testing sets **/
    int counter;
    multimap<string, Subject>::iterator itOut, itInner;
    for (itOut = dataset.begin(); itOut != dataset.end(); itOut = dataset.upper_bound(itOut->first)) {
        counter = 0;
        name = itOut->first;
        for (itInner = dataset.lower_bound(itOut->first); itInner != dataset.upper_bound(itOut->first); itInner++) {
            if (counter < int(PARAM * dataset.count(name))) {
                train.insert(pair<string, Subject>(name, itInner->second));
            } else {
                test.insert(pair<string, Subject>(name, itInner->second));
            }
            counter++;
        }
    }
    
    printf("Dataset: %lu\nTrainset: %lu\nTestset: %lu\n", dataset.size(), train.size(), test.size());
    
    /** saving training and testing sets **/
    ofstream training, testing;
    
    training.open("train.txt");
    for (itInner = train.begin(); itInner != train.end(); itInner++) {
        training << "Writing this to a file.\n";
    }
    training.close();
    
    testing.open("test.txt");
    for (itInner = test.begin(); itInner != test.end(); itInner++) {
        testing << "Writing this to a file.\n";
    }
    training.close();
}