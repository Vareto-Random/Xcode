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
    Subject(string&, string&, string&, string&, string&);
    Subject(string&, string&, string&, string&, int, int, int, int);
    virtual ~Subject();
    
    void setSubject(string&, string&, string&, string&, string&);
    void setSubject(string&, string&, string&, string&, int, int, int, int);

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
    string getFaceId() const;
    void setFaceId(string& faceId);
    string getImageId() const;
    void setImageId(string& imageId);
    const string& getName() const;
    void setName(const string& name);
    const string& getFullName() const;
    void setFullName(const string& name);
    void setObox(string &obox);
    string getObox() const;
    
private:
    inline void splitBbox(string &bbox);
    string name, fullName, bbox, imageId, faceId, obox;
    int bboxY1, bboxX1, bboxY2, bboxX2;
};

#endif /* SUBJECT_H_ */

