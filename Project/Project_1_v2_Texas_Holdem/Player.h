/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: serva
 *
 * Created on April 24, 2020, 9:03 AM
 */

#ifndef PLAYER_H
#define PLAYER_H

//libraries
#include <iostream>
#include <string>
#include <list>

//user libraries
#include "Cards.h"

using namespace std;

class Player{
private:
    //list for the cards
    list <Cards> pCards; //keep the player's cards
    //confirmation of the player
    bool done;
    //create the pot
    int pot;
    //create the total
    int total; 
    //input name of player
    string name;
    
public:
    //constructor
    Player();
    //Destructor
    ~Player();
    
    //getter functions
    //get the cards from the dealer. 
    list<Cards> getCards(){
        return this->pCards; 
    }
    //get name of player
    string getName() const{
        return this->name;
    }
    //get total of player
    int getTot() const{
        return this->total;
    }
    //confirm the player's decision
    int getConfirm(){
        return this->done;
    }
    //setters
    //set a player's yes
    void setConfirm(){
        this->done = 1; //true
    }
    //set the player's name  
    void setName(string n){
        this->name = n;
    }
    //set the player's total
    void setPlayerTotal(){
        this->total = 100; //for now
    }
    //if the player doesn't want to participate in the round
    void setAFK(){
        this->done = 0;
    }
    //initialize the pot to 0
    void setPot(){
        this->pot = 0;
    }
    //add cards to the hand
    void addCards(Cards);
    //take money from player and add to pot
    void bet(int b){
        this->total -= b;
        this->pot +=b;
    }
    //track how much is in the pot
    int potTot(){
        return this->pot;
    }
    //check if the player is still playing
    bool pStatus(){
        return this->done;
    }
    //add to pot from different rounds
    void addTot(int pot){
        this->total += pot;
    }
    //reset 
    void clearHand(){
        this->pCards.clear();
    }
};



#endif /* PLAYER_H */

