//
//  Sample.hpp
//  rafaels2cassiosInput
//
//  Created by Rafael Vareto on 5/15/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#ifndef Sample_hpp
#define Sample_hpp

#include <iostream>

using namespace std;

class Sample {
public:
    /** constructors **/
    Sample();
    Sample(string, string, int, int, int, int);
    
    
    /** getters **/
    string getSample();
    string getSubject();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
    
    
    /** setters **/
    void setSample(string);
    void setSubject(string);
    void setX(int);
    void setY(int);
    void setWidth(int);
    void setHeight(int);
    
    /** other methods **/
    void addSamplePrefix(string);
private:
    string subject;
    string sample;
    
    int posX;
    int posY;
    int width;
    int height;
};

#endif /* Sample_hpp */
