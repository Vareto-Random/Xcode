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

Sample::Sample(string _subject, string _sample, int _x, int _y, int _w, int _h) {
    this->setSubject(_subject);
    this->setSample(_sample);
    this->setX(_x);
    this->setY(_y);
    this->setWidth(_w);
    this->setHeight(_h);
}

string Sample::getSubject() {
    return this->subject;
}

string Sample::getSample() {
    return this->sample;
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

void Sample::setSubject(string _subject) {
    this->subject = _subject;
}

void Sample::setSample(string _sample) {
    this->sample = _sample;
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

void Sample::addSamplePrefix(string _prefix) {
    string temp = _prefix + this->sample;
    this->sample = temp;
}