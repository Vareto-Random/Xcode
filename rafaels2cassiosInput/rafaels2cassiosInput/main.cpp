//
//  main.cpp
//  rafaels2cassiosInput
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
    
    for (unsigned int index = 0; index < argc; index++) {
        cout << argv[index] << endl;
        
        ifstream infile;
        infile.open(argv[index]);
        
        if (infile.is_open()) {
            string file;
            int x, y, width, height;
            vector<Sample> samples;
            
            while (infile.good()) {
                infile >> file;
                infile >> x;
                infile >> y;
                infile >> width;
                infile >> height;
                
                Sample temp = Sample(file, x, y, width, height);
                samples.push_back(temp);
            }
            infile.close();
            
            ofstream outfile;
            outfile.open("cass_" + string(argv[index]));
            
            if (outfile.is_open()) {
                for (unsigned int step = 0; step < samples.size(); step++) {
                    Sample temp = samples[step];
                    outfile << temp.getSubject() << " " << temp.getFile() << " "
                    << temp.getX() << " " << temp.getY() << " "
                    << temp.getWidth() << " " << temp.getHeight() << endl;
                    
                }
            }
            outfile.close();
            
            samples.clear();
        } else {
            cerr << "No parameter informed." << endl;
        }
    }
    
    return 0;
}
