//
//  Subject.hpp
//  MegaFaceJson
//
//  Created by Rafael Vareto on 5/3/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#ifndef Subject_hpp
#define Subject_hpp

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Subject {
public:
    Subject();
    Subject(string&, int, int, int, int);
    virtual ~Subject();
    
    void setSubject(string&, int, int, int, int);
    
    string getPath();
    void setPath(string &path);
    
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    int getWidth();
    void setWidth(int w);
    int getHeight();
    void setHeight(int h);
    
private:
    string path;
    int pointX, pointY, width, height;
};

#endif /* Subject_hpp */
