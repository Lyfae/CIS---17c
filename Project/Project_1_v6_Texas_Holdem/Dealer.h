/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dealer.h
 * Author: serva
 *
 * Created on April 24, 2020, 8:03 PM
 */

#ifndef DEALER_H
#define DEALER_H

//libraries
#include <string>

//user libraries
#include "Hand.h"

using namespace std;

class Dealer {
private:
    //reveals the hands of the player
    Hand* player;
    //Cards in the deck 
    Cards* c[52];
    //deck of cards
    void DOC();
    //total in the pot
    int potTot;
    //initial bet to the pot
    int iBet;
    //get the number of people playing
    int nPlayers;
    //small blind
    int smallB;
    //Big Blind
    int bigB;
    //rounds
    int rounds;

public:
    //constructor
    Dealer(int);
    //destructor

    ~Dealer() {
    };

    //function setters
    //determine the number of plays
    void setnPlayers(int);
    //set the cards

    void setCards() {
        this->DOC();
    }
    //set the Blinds
    void setBlinds();
    //set the rounds

    void setRounds() {
        this->rounds = 0; //instantiate it = 0;
    }
    //set the initial bet

    void setIBet(int n) {
        this->iBet = n;
    }

    //functions getters
    //get players

    Hand* getPlayers()const {
        return player;
    }
    //get cards from deck

    Cards** getDeck() {
        return this->c;
    }
    //get the small blind

    int getSmallBlind() {
        return this->smallB;
    }
    //get the big blind

    int getBigBlind() {
        return this->bigB;
    }
    //get number of rounds

    int getnRounds() const {
        return this->rounds;
    }
    //get number of players

    int getnPlayers() const {
        return this->nPlayers;
    }

    //functions regarding the rules of the game
    //get the total in the pot

    int grandPot() {
        return this->potTot;
    }
    //get the number of the act
    int getNumAct();
    //first rounds of betting
    int roundOneBet();
    //second round of betting
    int roundTwoBet(int, int);
    //third round of betting
    int roundThreeBet(int, int);
    //fourth round of better
    int roundFourBet(int, int);
    //determine the winner
    int determineWinner();
    //resetting the game
    int reset();

    //void functions that occurs before the bet
    //shuffle the deck
    void shuffle();
    //pre-flop
    void preflop();
    //flop
    void flop();
    //turn
    void turn();
    //river
    void river();
    //go to the next round

    void nRound() {
        this->rounds++;
    }
    //calculate the total money earned
    void calcTot();
    //reset the pot

    void resetPot() {
        this->potTot = 0;
    }
    //display the player info
    void pInfo(int);





};

#endif /* DEALER_H */

