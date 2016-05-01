//
//  main.cpp
//  FaceScrubSplitter
//
//  Created by Rafael Vareto on 4/16/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

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
    } else if (argc == 5) {
        string path = string(argv[1]);
        int sizeTrain = atoi(argv[2]);
        int sizeTest =  atoi(argv[3]);
        int numiterations = atoi(argv[4]);
    } else if (argc == 2)
        int quantity = 14;
        int galleySize[] = {1, 2, 3, 4, 5, 8, 10, 15, 20, 25, 30, 35, 40, 50};
        int iterations[] = {15, 15, 10, 10, 10, 8, 8, 5, 5, 3, 3, 2, 2, 1};
    }
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
                    individual.setSubject(firstName, fullName, imageId, faceId, bbox);
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
        
        /** fundamental variables **/
        int counter, pos;
        set<int> chosen;
        set<string> testChosen;
        vector<Subject> available, list;
        ofstream training, testing;
        multimap<string, Subject>::iterator itOut, itInner;
        
        /** splitting into testing set **/
        for (itOut = multiDataset.begin(); itOut != multiDataset.end(); itOut = multiDataset.upper_bound(itOut->first)) {
            
            firstName = itOut->first;
            for (itInner = multiDataset.lower_bound(firstName); itInner != multiDataset.upper_bound(firstName); itInner++) {
                list.push_back(itInner->second);
            }
            
            if (list.size() > sizeTest) {
                counter = 0;
                while (counter < sizeTest) {
                    pos = rand() % list.size();
                    fullName = list[pos].getFullName();
                    
                    if (testChosen.find(fullName) == testChosen.end()) {
                        testChosen.insert(fullName);
                        test.insert(pair<string, Subject>(firstName, list[pos]));
                        counter++;
                    }
                }
            }
            
            list.clear();
        }
        
        /** splitting into training sets **/
        for (int index = 1; index <= numiterations; index++) {
            for (itOut = multiDataset.begin(); itOut != multiDataset.end(); itOut = multiDataset.upper_bound(itOut->first)) {

                firstName = itOut->first;
                for (itInner = multiDataset.lower_bound(firstName); itInner != multiDataset.upper_bound(firstName); itInner++) {
                    list.push_back(itInner->second);
                    
                    fullName = itInner->second.getFullName();
                    if (testChosen.find(fullName) == testChosen.end()) {
                        available.push_back(itInner->second);
                    }
                }
                
                if ( (list.size() > sizeTrain + sizeTest) && (available.size() > sizeTrain) ) {
                    counter = 0;
                    while (counter < sizeTrain) {
                        pos = rand() % available.size();
                        if (chosen.find(pos) == chosen.end()) {
                            chosen.insert(pos);
                            train.insert(pair<string, Subject>(firstName, available[pos]));
                            counter++;
                        }
                    }
                }
                
                available.clear();
                chosen.clear();
                list.clear();
            }
            
            printf("Iteration %d\nSingleDataset: %lu\nMultiDataset: %lu\nTrainset: %lu\n\n",
                   index, singleDataset.size(), multiDataset.size(), train.size());
            
            /** saving training and testing sets **/
            training.open("train-" + to_string(sizeTrain) + "-" + to_string(sizeTest) + "-" + to_string(index) + ".txt");
            for (itInner = train.begin(); itInner != train.end(); itInner++) {
                training << itInner->second.getName() << "/" << itInner->second.getName()
                << "_" << itInner->second.getFaceId() << ".jpg "
                << itInner->second.getBboxX1() << " " << itInner->second.getBboxY1() << " "
                << itInner->second.getBboxX2() << " " << itInner->second.getBboxY2() << endl;
            }
            training.close();
            
            train.clear();
        }
        
        /** saving testing set **/
        testing.open("test-" + to_string(sizeTrain) + "-" + to_string(sizeTest) + ".txt");
        for (itInner = test.begin(); itInner != test.end(); itInner++) {
            testing << itInner->second.getName() << "/" << itInner->second.getName()
            << "_" << itInner->second.getFaceId() << ".jpg "
            << itInner->second.getBboxX1() << " " << itInner->second.getBboxY1() << " "
            << itInner->second.getBboxX2() << " " << itInner->second.getBboxY2() << endl;
        }
        testing.close();
        
        return 0;
    }
}