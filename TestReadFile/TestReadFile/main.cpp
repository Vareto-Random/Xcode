//
//  main.cpp
//  TestReadFile
//
//  Created by Rafael Vareto on 6/10/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    string data1, data2, data3, data4, data5;
    ifstream infile("/Users/Vareto/Downloads/ICB-RW/icbrw/annotations_GalleryImages.txt", ifstream::in);
    
    if (infile.is_open()) {
        while (infile.good()) {
            infile >> data1;
            infile >> data2;
            infile >> data3;
            infile >> data4;
            infile >> data5;
        }
        cout << endl;
        return true;
    }
    return 0;
}
