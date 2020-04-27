/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Hand.h
 * Author: serva
 * Purpose: Creating the hand
 * Created on April 24, 2020, 10:04 AM
 */

#ifndef HAND_H
#define HAND_H

//libraries
#include <map>
#include <string>

//user libraries
#include "Player.h"

class Hand : public Player{
private:
    //map out the suits
    map<int, int, greater<int>> suits;
    //multi-map for the faces
    multimap<int, int, greater<int>> faces;
    //types of hand
    int handType;
    //name of the hands
    string handName;
    //poker-straight-flush
    int pSF;
    //poker-straight
    int pS;
    //poker-flush
    int pf;
    //poker-pair
    int pP;
    
public:
    //constructors
    Hand();
    Hand(const Hand& a);
    virtual ~Hand(){
        
    }
    
    //getters
    //map to get suits
    map<int,int,greater<int>> getSuits(){
        return this->suits;
    }
    //multi-map to get faces
    multimap<int,int, greater<int>> getFaces(){
        return this->faces;
    }
    //getting the hand type
    int getHand();
    //getting the name of the hands
    string getHandName();
    
    //setters
    //set faces
    void setFaces();
    //set suits
    void setSuits();
    //check for poker-straight
    void checkStraight();
    
    //clear the hands
    void clearHands(){
        this->Player::clearHand();
        this->faces.clear();
        this->suits.clear();
        this->pSF = 0;
        this->pS = 0;
        this->pf = 0;
        this->pP = 0;
        this->handType = 0;
        this->handName= "";
        
    }
    
};

#endif /* HAND_H */

