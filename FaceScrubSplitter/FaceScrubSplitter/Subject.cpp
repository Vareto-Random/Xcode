//
//  Subject.cpp
//  FaceScrubSplitter
//
//  Created by Rafael Vareto on 4/16/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#include "Subject.hpp"

Subject::Subject() {
    this->imageId = 0;
    this->faceId = 0;
    this->bboxY1 = 0;
    this->bboxX1 = 0;
    this->bboxY2 = 0;
    this->bboxX2 = 0;
}

Subject::Subject(string &name, int imageId, int faceId, string &bbox) {
    this->setSubject(name, imageId, faceId, bbox);
}

Subject::Subject(string &name, int imageId, int faceId, int bboxY1, int bboxX1, int bboxY2, int bboxX2) {
    this->setSubject(name, imageId, faceId, bboxY1, bboxX1, bboxY2, bboxX2);
}

void Subject::setSubject(string &name, int imageId, int faceId, string &bbox) {
    this->name = name;
    this->imageId = imageId;
    this->faceId = faceId;
    this->bbox = bbox;
    this->splitBbox(bbox);
}

void Subject::setSubject(string &name, int imageId, int faceId, int bboxY1, int bboxX1, int bboxY2, int bboxX2) {
    this->name = name;
    this->imageId = imageId;
    this->faceId = faceId;
    this->bboxY1 = bboxY1;
    this->bboxX1 = bboxX1;
    this->bboxY2 = bboxY2;
    this->bboxX2 = bboxX2;
}

Subject::~Subject() {
    
}

string Subject::getBbox() const {
    return bbox;
}

void Subject::setBbox(string &bbox) {
    this->bbox = bbox;
}

int Subject::getBboxX1() const {
    return bboxX1;
}

void Subject::setBboxX1(int bboxX1) {
    this->bboxX1 = bboxX1;
}

int Subject::getBboxX2() const {
    return bboxX2;
}

void Subject::setBboxX2(int bboxX2) {
    this->bboxX2 = bboxX2;
}

int Subject::getBboxY1() const {
    return bboxY1;
}

void Subject::setBboxY1(int bboxY1) {
    this->bboxY1 = bboxY1;
}

int Subject::getBboxY2() const {
    return bboxY2;
}

void Subject::setBboxY2(int bboxY2) {
    this->bboxY2 = bboxY2;
}

int Subject::getFaceId() const {
    return faceId;
}

void Subject::setFaceId(int faceId) {
    this->faceId = faceId;
}

int Subject::getImageId() const {
    return imageId;
}

void Subject::setImageId(int imageId) {
    this->imageId = imageId;
}

const string& Subject::getName() const {
    return name;
}

void Subject::setName(const string& name) {
    this->name = name;
}

void Subject::splitBbox(string &bbox) {
    int temp = 0;
    vector<int> boxes;
    for (int index = 0; index < this->bbox.length(); index++) {
        if (bbox[index] == ',') {
            bbox[index] = ' ';
        }
    }
    
    stringstream stream(bbox);
    while (stream >> temp) {
        boxes.push_back(temp);
    }
        
    this->bboxY1 = boxes[0];
    this->bboxX1 = boxes[1];
    this->bboxY2 = boxes[2];
    this->bboxX2 = boxes[3];
}