
//
//  main.cpp
//  MegaFaceJson
//
//  Created by Rafael Vareto on 5/3/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <set>
#include <vector>

#include <opencv2/highgui.hpp>

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc != 5) {
        cerr << "Incorrect number of parameters." << endl
        << "./FaceScrubSplitter.app [path to dataset] [path to jpeg list] [negative set size] [number of iterations]" << endl;
    } else {
        string path = string(argv[1]);
        string jpegList = string(argv[2]);
        int negativeSize = atoi(argv[3]);
        int numiterations = atoi(argv[4]);
        
        cout << path + jpegList << endl;
        
        /** reading list of files **/
        string jpeg, json;
        vector<string> jpegFiles;
        ifstream jpegInput, jsonInput;
        
        jpegInput.open(path + jpegList);
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

        /** reading JSON buffer **/
        srand(1);
        int pos;
        string jsonPath;
        set<int> chosen;
        vector<string> bufferArray, boundingBox;
        for (int index = 0; index < negativeSize; index++) {
            pos = rand() % jpegFiles.size();
            
            if (chosen.find(pos) == chosen.end()) {
                jsonPath = path + jpegFiles[pos] + ".json";
                jsonInput.open(jsonPath, ifstream::in);
                
                if (jsonInput.is_open()) {
                    stringstream buffer;
                    vector<string> array;
                    
                    buffer << jsonInput.rdbuf();
                    cout << buffer.str().substr(18, buffer.str().find("}")) << endl;
                    bufferArray.push_back(buffer.str());
                } else {
                    cerr << jpegFiles[pos] << " file could not be opened\n";
                }
                
                jsonInput.close();
            }
        }
        
        /** splitting buffer into string vector **/
        
    }
    return 0;
}
