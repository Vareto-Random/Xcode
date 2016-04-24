//
//  main.cpp
//  FaceScrubSplitter
//
//  Created by Rafael Vareto on 4/16/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#define PARAM 0.4
#define RANDOM true

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>

#include <opencv2/highgui.hpp>

#include "Subject.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 5) {
        cerr << "Incorrect number of parameters." << endl
            << "./FaceScrubSplitter.app [path to dataset] [train set size] [test set size] [number of iterations]" << endl;
        return 1;
    } else {
        string path = string(argv[1]);
        int sizeTrain = atoi(argv[2]);
        int sizeTest =  atoi(argv[3]);
        int numiterations = atoi(argv[4]);
        
        /** reading file **/
        vector<string> head;
        map<string, Subject> singleDataset;
        multimap<string, Subject> multiDataset, train, test;
        
        ifstream infile;
        string text, firstName, fullName, imageId, faceId, url, bbox, sha256;
        string fileName[] = {"facescrub_actors.txt", "facescrub_actresses.txt"};
        
        for (int outer = 0; outer < 2; outer++) {
            cout << path + fileName[outer] << endl;
            infile.open(path + fileName[outer]);
            
            for (int inner = 0; inner < 6; inner++) {
                infile >> text;
                head.push_back(text);
            }
            
            if (!infile.is_open()) {
                cerr << "File could not be opened\n";
            } else {
                Subject individual = Subject();
                
                while (!infile.eof()) {
                    infile >> firstName;
                    infile >> imageId;
                    infile >> faceId;
                    infile >> url;
                    infile >> bbox;
                    infile >> sha256;
                    
                    fullName = firstName + "/" + firstName + "_" + faceId + ".jpg";
                    individual.setSubject(firstName, imageId, faceId, bbox);
                    singleDataset.insert(pair<string, Subject>(fullName, individual));
                }
            }
            infile.close();
        }
        
        /** verifying if images are not corrupted or nonexistent **/
        bool remove;
        map<string, Subject>::iterator it;
        for (it = singleDataset.begin(); it != singleDataset.end(); it++) {
            fullName = it->first;
            remove = true;
            
            infile.open(path + fullName);
            if (infile.good()) {
                cv::Mat image = cv::imread(path + fullName);
                
                if (image.data) {
                    remove = false;
                    Subject individual = it->second;
                    multiDataset.insert(pair<string, Subject>(individual.getName(), individual));
                }
                
                image.release();
            }
            infile.close();
        }
        
        
        /** splitting into training and testing sets **/
        for (int index = 1; index <= numiterations; index++) {
            int pos, counter;
            multimap<string, Subject>::iterator itOut, itInner;
            set<int> chosen;
            vector<Subject> list;
            for (itOut = multiDataset.begin(); itOut != multiDataset.end(); itOut = multiDataset.upper_bound(itOut->first)) {

                firstName = itOut->first;
                for (itInner = multiDataset.lower_bound(itOut->first); itInner != multiDataset.upper_bound(itOut->first); itInner++) {
                    list.push_back(itInner->second);
                }
                
                if (list.size() > sizeTrain + sizeTest) {
                    counter = 0;
                    while (counter < sizeTrain) {
                        pos = rand() % list.size();
                        if (chosen.find(pos) == chosen.end()) {
                            chosen.insert(pos);
                            train.insert(pair<string, Subject>(firstName, list[pos]));
                            counter++;
                        }
                    }
                    
                    counter = 0;
                    while (counter < sizeTest) {
                        pos = rand() % list.size();
                        if (chosen.find(pos) == chosen.end()) {
                            chosen.insert(pos);
                            test.insert(pair<string, Subject>(firstName, list[pos]));
                            counter++;
                        }
                    }
                }
                
                chosen.clear();
                list.clear();
            }
            
            printf("Iteration %d\nSingleDataset: %lu\nMultiDataset: %lu\nTrainset: %lu\nTestset: %lu\n\n",
                   index, singleDataset.size(), multiDataset.size(), train.size(), test.size());
            
            /** saving training and testing sets **/
            ofstream training, testing;
            
            training.open("train-" + to_string(sizeTrain) + "-" + to_string(sizeTest) + "-" + to_string(index) + ".txt");
            for (itInner = train.begin(); itInner != train.end(); itInner++) {
                training << itInner->second.getName() << "/" << itInner->second.getName()
                << "_" << itInner->second.getFaceId() << ".jpg "
                << itInner->second.getBboxX1() << " " << itInner->second.getBboxY1() << " "
                << itInner->second.getBboxX2() << " " << itInner->second.getBboxY2() << endl;
            }
            training.close();
            
            testing.open("test-" + to_string(sizeTrain) + "-" + to_string(sizeTest) + "-" + to_string(index) + ".txt");
            for (itInner = test.begin(); itInner != test.end(); itInner++) {
                testing << itInner->second.getName() << "/" << itInner->second.getName()
                << "_" << itInner->second.getFaceId() << ".jpg "
                << itInner->second.getBboxX1() << " " << itInner->second.getBboxY1() << " "
                << itInner->second.getBboxX2() << " " << itInner->second.getBboxY2() << endl;
            }
            testing.close();
            
            train.clear();
            test.clear();
        }
        
        return 0;
    }
}