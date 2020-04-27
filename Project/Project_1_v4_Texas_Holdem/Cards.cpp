/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//libraries
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>

//user libraries
#include "Cards.h"

using namespace std;

//constructor for cards

Cards::Cards(int n) {
    //true
    if (n >=0 && n < 52) {
        //set values 
        this->cNum = n;
        this->setPlayCard();
        this->setSuit();
        this->setFace();
    } else { //precaution if it doesn't match
        this->cNum = -1;
        this->cFace = -1;
        this->cSuit = -1;
        this->faceName = "Invalid";
        this->playCard = "Invalid";
        this->suitName = "Invalid";
    }
}

//setter functions 
//set suit

void Cards::setSuit() {
    //set values of clubs
    if (this->cNum < 13) {
        this->cSuit = 0;
        this->suitName = "Clubs";
    } else if (this->cNum < 26) { //set values for diamonds
        this->cSuit = 1;
        this->suitName = "Diamonds";
    } else if (this->cNum < 39) { //set the values for hearts
        this->cSuit = 2;
        this->suitName = "Hearts";
    } else if (this->cNum < 52) { //set the value for spades
        this->cSuit = 3;
        this->suitName = "Spades";
    } else { //if neither matches
        this->cSuit = -1;
        this->suitName = "Invalid Card";
    }
}
//set face

void Cards::setFace() {
    //setting value of the cards
    //setting the card face equal to the card number
    if (this->cNum % 13 + 1 == 1) {
        this->cFace = 14;
    } else {
        this->cFace = this->cNum % 13+1;
    }

        
    switch (this->cFace) {
        case 2:
            this->faceName = "Two";
            break;
        case 3:
            this->faceName = "Three";
            break;
        case 4:
            this->faceName = "Four";
            break;
        case 5:
            this->faceName = "Five";
            break;
        case 6:
            this->faceName = "Six";
            break;
        case 7:
            this->faceName = "Seven";
            break;
        case 8:
            this->faceName = "Eight";
            break;
        case 9:
            this->faceName = "Nine";
            break;
        case 10:
            this->faceName = "Ten";
            break;
        case 11:
            this->faceName = "Jack";
            break;
        case 12:
            this->faceName = "Queen";
            break;
        case 13:
            this->faceName = "King";
            break;
        case 14:
            this->faceName = "Ace";
            break;
        default:
            this->faceName = "Not applicable";
    }
}
//set play card
//the code string to the cards = pictures

void Cards::setPlayCard() {
    string c[52] = 
        {"\U0001F0D1", "\U0001F0D2", "\U0001F0D3", "\U0001F0D4", "\U0001F0D5"
        , "\U0001F0D6", "\U0001F0D7", "\U0001F0D8", "\U0001F0D9", "\U0001F0DA", "\U0001F0DB"
        , "\U0001F0DD", "\U0001F0DE", "\U0001F0C1", "\U0001F0C2", "\U0001F0C3", "\U0001F0C4"
        , "\U0001F0C5", "\U0001F0C6", "\U0001F0C7", "\U0001F0C8", "\U0001F0C9", "\U0001F0CA"
        , "\U0001F0CB", "\U0001F0CD", "\U0001F0CE", "\U0001F0B1", "\U0001F0B2", "\U0001F0B3"
        , "\U0001F0B4", "\U0001F0B5", "\U0001F0B6", "\U0001F0B7", "\U0001F0B8", "\U0001F0B9"
        , "\U0001F0BA", "\U0001F0BB", "\U0001F0BD", "\U0001F0BE", "\U0001F0A1", "\U0001F0A2"
        , "\U0001F0A3", "\U0001F0A4", "\U0001F0A5", "\U0001F0A6", "\U0001F0A7", "\U0001F0A8"
        , "\U0001F0A9", "\U0001F0DA", "\U0001F0AB", "\U0001F0AD", "\U0001F0AE"};

    //print out the cards
    //if cards match to the value being called
    for (int i = 0; i < 52; i++) {
        if (this->cNum == i) {
            //value of card equal to the actual card
            this->playCard = c[i];
        }
    }
}

//output

void Cards::output() {
    //output the playing card
    cout << this->Cards::gPlayCard() << " ";
    //output face name
    cout << this->Cards::gFaceName() << " ";
    //output the suits
    cout << this->Cards::gSuitName() << endl;
}