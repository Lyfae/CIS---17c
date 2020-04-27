/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//libraries
#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <map>
#include <iterator>
#include <algorithm>
#include <list>

//user libraries 
#include "Hand.h"

using namespace std;


//constructor

Hand::Hand(){
    this->Hand::setConfirm();
    this->Hand::setPot();
}

//getting the name of the hands

string Hand::getHandName() {
    switch (this->Hand::getHand()) {
        case 0:
            this->handName = "High-Card";
            break;
        case 1:
            this->handName = "One-Pair";
            break;
        case 2:
            this->handName = "Two-Pair";
            break;
        case 3:
            this->handName = "Three-of-a-Kind";
            break;
        case 4:
            this->handName = "Straight";
            break;
        case 5:
            this->handName = "Flush";
            break;
        case 6:
            this->handName = "Full-house";
            break;
        case 7:
            this->handName = "Four-of-a-kind";
            break;
        case 8:
            this->handName = "Straight-Flush";
            break;
        default:
            this->handName = "Invalid";
    }
    return this->handName;
}

//check the cards if they order 5 in a row

void Hand::checkStraight() {
    this->pS = 0;
    //set faces / declare variables
    set<int, greater<int>> faceSet;
    int count = 0;

    //get face
    for (auto& i : this->Hand::getCards()) {
        faceSet.insert(i.getFace());
    }

    //start
    set<int>::iterator a = faceSet.begin();
    //checking the cards
    while (a != faceSet.end() && count != 4) {
        if (*a - *faceSet.upper_bound(*a) == 1) {
            count++;
        } else {
            count = 0;
        }
        ++a;
    }

    if (count == 4 && *a + 4 != 14) {
        this->pS = *a + 4;
    } else if (count == 4 && *a + 4 == 14) {
        this->pS = 15;
    }
    if (*a == 14) {
        while (a != faceSet.end() && count != 3) {
            if (*a - *faceSet.upper_bound(*a) == 1) {
                count++;
            } else {
                count = 0;
            }
            ++a;
        }
    }
    if (count == 3 && *a + 3 == 5) {
        this->pS = 14;
    }
    faceSet.clear();

}

//check for flush by determining the suits

void Hand::setSuits() {
    //initialize
    this->pf = 0;
    multiset<int> setSuit;

    //enhanced for loop to get the suits
    for (auto& i :this->Hand::getCards()) {
        setSuit.insert(i.getSuit());
    }
    //loop through 
    for (int i = 0; i < 4; i++) {
        if (setSuit.count(i) > 4) {
            this->suits.insert(pair<int, int>(setSuit.count(i), i));
            this->pf = 1;
        }
    }
    //clear the set
    setSuit.clear();

}

//checking for pairs

void Hand::setFaces() {
    //declare and initialize variables
    this->pP = 0;
    multiset<int> setFace;

    //enhanced for loop to get the face
    for (auto& i : Hand::getCards()) {
        setFace.insert(i.getFace());
    }

    //insert card
    for (int i = 2; i < 15; i++) {
        if (setFace.count(i) > 1) {
            this->faces.insert(pair<int, int>(setFace.count(i), i));
        }
    }

    map<int, int>::iterator pos;

    if (this->faces.empty()) {
        this->pP = 0;
    } else if (this->faces.size() == 1) {
        pos = this->faces.begin();
        if (pos->first == 2) {
            this->pP = 1;
        } else if (pos->first == 3) {
            this->pP = 3;
        } else if (pos->first == 4) {
            this->pP = 7;
        }
    } else if (this->faces.size() > 1) {
        pos = this->faces.begin();
        if (pos->first == 2) {
            this->pP = 2;
        } else if (pos->first == 3) {
            this->pP = 6;
        }
    }
    setFace.clear();
}

int Hand::getHand() {
    this->checkStraight();
    this->Hand::setSuits();
    this->Hand::setFaces();

    if (this->pS != 0 && this->pf != 0) {
        this->pSF = 1;
        this->handType = 8;
        set<int, greater<int>> psf; //poker-straight-flush

        for (auto& i : this->Hand::getCards()) {
            if (i.getSuit() == this->pSF) {
                psf.insert(i.getFace());
            }
        }
        if (this->pS == 15) {
            for (int i = 14; i > 9; i--) {
                if (psf.find(i) == psf.end()) {
                    this->pSF = 0;
                }
            }
        } else if (this->pS == 15) {
            for (int i = 5; i > 1; i--) {
                if (psf.find(i) == psf.end()) {
                    this->pSF = 0;
                }
            }
        } else {
            for (int i = this->pS; i> this->pS - 5; i--) {
                if (psf.find(i) == psf.end()) {
                    this->pSF = 0;
                }
            }
        }
        if (this->pSF == 0) {
            this->handType = 5;
        }
    }        
    //setting the hand type according to the cards
    else if (this->Hand::pP == 7) {
        this->handType = 7;
    } else if (this->Hand::pP = 6) {
        this->handType = 6;
    } else if (this->Hand::pf != 0) {
        this->handType = 5;
    } else if (this->Hand::pS != 0) {
        this->handType = 4;
    } else if (this->Hand::pP == 3) {
        this->handType = 3;
    } else if (this->Hand::pP == 2) {
        this->handType = 2;
    } else if (this->Hand::pP == 1) {
        this->handType = 1;
    } else {
        this->handType = 0;
    }
return this->handType;
}
