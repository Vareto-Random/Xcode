//
//  main.cpp
//  AlterSubjectSample
//
//  Created by Rafael Vareto on 5/15/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#include <fstream>
#include <iostream>
#include <vector>

#include "Sample.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    string sub, sam;
    int x, y, w, h;
    
    if (argc > 1) {
        for (unsigned int index = 1; index < argc; index++) {
            cout << argv[index] << endl;
            
            ifstream infile;
            infile.open(argv[index]);
            
            if (infile.is_open()) {
                vector<Sample> samples;
                
                while (infile.good()) {
                    infile >> sub;
                    infile >> sam;
                    infile >> x;
                    infile >> y;
                    infile >> w;
                    infile >> h;
                    
                    Sample temp = Sample(sub, sam, x, y, w, h);
                    temp.addSamplePrefix("facescrub/downloaded/");
                    samples.push_back(temp);
                }
                
                ofstream outfile;
                outfile.open(string(argv[index]));
                for (unsigned int step = 0; step < samples.size(); step++) {
                    Sample temp = samples[step];
                    outfile << temp.getSubject() << " " << temp.getSample() << " "
                    << temp.getX() << " " << temp.getY() << " "
                    << temp.getWidth() << " " << temp.getHeight() << endl;
                }
            } else {
                cerr << "Could not read argument " << index << endl;
            }
            infile.close();
        }
    } else {
        cerr << "Not enough arguments." << endl;
    }

    return 0;
}
