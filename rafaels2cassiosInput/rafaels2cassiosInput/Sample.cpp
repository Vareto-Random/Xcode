//
//  Sample.cpp
//  rafaels2cassiosInput
//
//  Created by Rafael Vareto on 5/15/16.
//  Copyright © 2016 Rafael Vareto. All rights reserved.
//

#include "Sample.hpp"

Sample::Sample() {
    this->posX = -1;
    this->posY = -1;
    this->width = -1;
    this->height = -1;
}

Sample::Sample(string _file, int _x, int _y, int _w, int _h) {
    this->setFile(_file);
    this->setX(_x);
    this->setY(_y);
    this->setWidth(_w);
    this->setHeight(_h);
    
    this->genSubject(_file);
}

string Sample::getFile() {
    return this->file;
}

string Sample::getSubject() {
    return this->subject;
}

int Sample::getX() {
    return this->posX;
}

int Sample::getY() {
    return this->posY;
}

int Sample::getWidth() {
    return this->width;
}

int Sample::getHeight() {
    return this->height;
}

void Sample::setFile(string _file) {
    this->file = _file;
}

void Sample::setX(int _x) {
    this->posX = _x;
}

void Sample::setY(int _y) {
    this->posY = _y;
}

void Sample::setWidth(int _w) {
    this->width = _w;
}

void Sample::setHeight(int _h) {
    this->height = _h;
}

void Sample::genSubject(string _file) {
    long beg = _file.find_last_of("/") + 1;
    long end = _file.find_last_of(".");
    this->subject =  _file.substr(beg, end - beg);
}
