/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cards.h
 * Author: serva
 * Purpose: Creating the Class Cards
 * Created on April 21, 2020, 11:49 AM
 */

#ifndef CARDS_H
#define CARDS_H

//libraries
#include <string>

using namespace std;

class Cards {
private:
    //card number
    int cNum;
    //get card face
    int cFace; 
    //get suit
    int cSuit;
    //get suit name
    string suitName;
    //get face name
    string faceName;
    //get playing cards 
    string playCard;
    
public:
    //constructor for cards
    Cards(int);
    
    //getter functions
    //get suit
    int getSuit()const {return this->cSuit;}
    //get face
    int getFace()const {return this->cFace;}
    //get number
    int getNum()const {return this->cNum;}
    //get the playing cards
    string gPlayCard()const {return this->playCard;}
    //get the face name
    string gFaceName()const {return this->faceName;}
    //get the suits name
    string gSuitName()const {return this->suitName;}
    
    //setter functions 
    //set suit
    void setSuit();
    //set face
    void setFace();
    //set play card
    void setPlayCard();
    //output
    void output();
    
};

#endif /* CARDS_H */

