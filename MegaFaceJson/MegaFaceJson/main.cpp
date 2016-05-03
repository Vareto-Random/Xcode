
//
//  main.cpp
//  MegaFaceJson
//
//  Created by Rafael Vareto on 5/3/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include <opencv2/highgui.hpp>

#include "Subject.hpp"

using namespace std;

void removeCharsFromString(string &str, char* charsToRemove);

int main(int argc, const char * argv[]) {
    if (argc != 5) {
        cerr << "Incorrect number of parameters." << endl
        << "./FaceScrubSplitter.app [path to dataset] [path to jpeg list] [extra set size] [number of iterations]" << endl;
    } else {
        string path = string(argv[1]);
        string jpegList = string(argv[2]);
        int extraSize = atoi(argv[3]);
        int numIterations = atoi(argv[4]);
        
        cout << path + jpegList << endl;
        
        for (unsigned int outer = 0; outer < numIterations; outer++) {
            /** reading list of files **/
            string jpeg, json;
            vector<string> jpegFiles;
            ifstream jpegInput, jsonInput;
            ofstream outfile;
            
            jpegInput.open(jpegList);
            if (!jpegInput.is_open()) {
                cerr << "File could not be opened\n";
            } else {
                while (!jpegInput.eof()) {
                    jpegInput >> jpeg;
                    
                    jsonInput.open(path + jpeg + ".json");
                    if (jsonInput.is_open()) {
                        jpegFiles.push_back(jpeg);
                    }
                }
            }
            jpegInput.close();
            
            /** reading JSON buffer **/
            // srand(outer);
            int pos;
            string jsonPath;
            set<int> chosen;
            vector<Subject> individuals;
            
            for (unsigned int inner = 0; inner < extraSize && inner < jpegFiles.size(); inner++) {
                // pos = rand() % jpegFiles.size();
                pos = inner;
                
                // if (chosen.find(pos) == chosen.end()) {
                    jsonPath = path + jpegFiles[pos] + ".json";
                    jsonInput.open(jsonPath, ifstream::in);
                    
                    if (jsonInput.is_open()) {
                        string token;
                        stringstream buffer;
                        vector<string> array;
                        
                        buffer << jsonInput.rdbuf();
                        while (buffer >> token) {
                            removeCharsFromString(token, (char*) "{}:,");
                            array.push_back(token);
                        }
                        
                        int x = atoi(array[4].c_str());
                        int y = atoi(array[2].c_str());
                        int w = atoi(array[8].c_str());
                        int h = atoi(array[6].c_str());
                        
                        individuals.push_back( Subject(jpegFiles[pos], x, y, w, h) );
                    } else {
                        cerr << jpegFiles[pos] << ".json file could not be opened\n";
                    }
                    
                    jsonInput.close();
                // }
            }
            
            /** saving testing set **/
            outfile.open("extra-" + to_string(extraSize) + "-" + to_string(outer) + ".txt");
            for (int inner = 0; inner < individuals.size(); inner++) {
                outfile << individuals[inner].getPath() << " "
                << individuals[inner].getX() << " " << individuals[inner].getY()
                << individuals[inner].getWidth() << " " << individuals[inner].getHeight() << endl;
            }
            outfile.close();
        }
    }
    return 0;
}

inline void removeCharsFromString(string &str, char* charsToRemove) {
    for (unsigned int i = 0; i < strlen(charsToRemove); i++) {
        str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
    }
}
