//
//  Subject.cpp
//  MegaFaceJson
//
//  Created by Rafael Vareto on 5/3/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#include "Subject.hpp"

Subject::Subject() {
    
}

Subject::Subject(string &path, int x, int y, int w, int h) {
    this->setSubject(path, x, y, w, h);
}

void Subject::setSubject(string &path, int x, int y, int w, int h) {
    this->path = path;
    this->pointX = x;
    this->pointY = y;
    this->width = w;
    this->height = h;
}

string Subject::getPath() {
    return this->path;
}

void Subject::setPath(string &path) {
    this->path = path;
}

int Subject::getX() {
    return this->pointX;
}

void Subject::setX(int x) {
    this->pointX = x;
}

int Subject::getY() {
    return this->pointY;
}

void Subject::setY(int y) {
    this->pointY = y;
}

int Subject::getWidth() {
    return this->width;
}

void Subject::setWidth(int w) {
    this->width = w;
}

int Subject::getHeight() {
    return this->height;
}

void Subject::setHeight(int h) {
    this->height = h;
}