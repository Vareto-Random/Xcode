//
//  Subject.hpp
//  FaceScrubSplitter
//
//  Created by Rafael Vareto on 4/16/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#ifndef SUBJECT_H_
#define SUBJECT_H_

#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Subject {
public:
    Subject();
    Subject(string&, int, int, string&);
    Subject(string&, int, int, int, int, int, int);
    virtual ~Subject();
    
    void setSubject(string&, int, int, string&);
    void setSubject(string&, int, int, int, int, int, int);

    string getBbox() const;
    void setBbox(string &bbox);
    int getBboxX1() const;
    void setBboxX1(int bboxX1);
    int getBboxX2() const;
    void setBboxX2(int bboxX2);
    int getBboxY1() const;
    void setBboxY1(int bboxY1);
    int getBboxY2() const;
    void setBboxY2(int bboxY2);
    int getFaceId() const;
    void setFaceId(int faceId);
    int getImageId() const;
    void setImageId(int imageId);
    const string& getName() const;
    void setName(const string& name);
    
private:
    inline void splitBbox(string &bbox);
    string name, bbox;
    int imageId, faceId, bboxY1, bboxX1, bboxY2, bboxX2;
};

#endif /* SUBJECT_H_ */

