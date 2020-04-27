/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

//libraries
#include <cstdlib>
#include <iostream>
#include <string>

//user libraries
#include "Dealer.h"

using namespace std;

//constructor

Dealer::Dealer(int n) {
    //    int
}

//Creating the deck of cards

void Dealer::DOC() {
    for (int i = 0; i < 52; i++) {
        //pass the cards through as new cards
        this->c[i] = new Cards(i);
    }
}


//setting the number of player

void Dealer::setnPlayers(int num) {
    //set the players equal to the number passed in
    this->nPlayers = num;
    //create the hand according to the players
    this->player = new Hand[this->nPlayers];

    //set the player name
    for (int i = 0; i<this->nPlayers; i++) {
        this->player[i].setName("Player: " + to_string(i));
    }

}

//setting the blinds

void Dealer::setBlinds() {
    //divide by the players, minus 1 because that person is the dealer
    this->bigB = this->getnRounds() % (this->getnPlayers() - 1);
    this->smallB = this->bigB + 1;
}


//shuffling the deck of cards

void Dealer::shuffle() {
    //set the random seed time
    srand(time(0));
    //shuffle the cards 
    for (int i = 0; i < 52; i++) {
        int j = i + (rand() % (52 - i));
        //swap the shuffled deck with base deck
        swap(this->c[i], this->c[j]);
    }
}


//display the peron's information

void Dealer::pInfo(int num) {
    //determine the player
    cout << this->Dealer::player[num].getName() << endl;
    //determine where the big blind starts
    if (num == this->Dealer::getBigBlind()) {
        cout << "Big Blind" << endl;
    } else if (num == this->Dealer::getSmallBlind()) {
        cout << "Small Blind" << endl;
    }
    cout << "Here is the total balance: $" << this->Dealer::player[num].getTot() << endl;

    for (auto& i : this->player[num].getCards()) {
        i.output();
    }
    cout << endl;
}

//getting the players that are still actively playing

int Dealer::getNumAct() {
    int num = 0;
    for (int i = 0; i<this->nPlayers; i++) {
        if (this->player[i].getConfirm()) {
            num++;
        }
        return num;
    }
}

//calculate the balance each player has

int Dealer::calcTot() {
    int win = this->determineWinner();
    cout << "Congratulations! Player" << win << " has won $" << this->grandPot() << endl;
    //add the pot to the player's total
    this->player[win].addTot(this->grandPot());
    //then reset the pot
    this->Dealer::resetPot();
}

//determine the winner

int Dealer::determineWinner() {
    //initialize and declare variables
    int numPlayers = this->getnPlayers();
    int winner = 0;
    int strongest = 0;

    //compare who's in play and their hand
    for (int i = 0; i < numPlayers; i++) {
        if (this->player[i].getConfirm() == 1) {
            if (this->player[i].getHand() > strongest) {
                strongest = this->player[i].getHand();
                winner = i;
            }
        }
    }
    return winner;
}

//resetting the game

int Dealer::reset() {
    int input;
    this->nRound();
    //reset all the player's Hands
    for (int i = 0; i<this->getnPlayers(); i++) {
        this->player[i].clearHand();
    }
    //option to quit
    cout << "Game Master if you want to quit press 0" << endl;
    cin>>input;
    return input;
}

//rules of the game
//pre-flop

void Dealer::preflop() {
    //declare and initialize variables
    int numCards = 2;
    int numPlayers = this->nPlayers;
    int bigB = this->bigB; //big blind
    int order;

    //deal out two cards to the players
    for (int i = 0; i < numCards; i++) {
        for (int j = 0; j < numPlayers; j++) {
            order = (j + bigB) % numPlayers;
            this->player[order].addCards(*this->c[j + numPlayers * i]);
        }
    }

}

//first round of betting

int Dealer::roundOneBet() {
    int raise; //raise the highest blind
    int input; //get player's decision
    int amount; //how much is going in the pot
    int dif; //how much is left
    int numPlayers = this->nPlayers;

    //making the big blind
    this->player[bigB].bet(this->iBet); //take in bet
    this->potTot += this->iBet; //make blind = bet 
    cout << "Player " << this->bigB << ": bet $" << this->iBet << " as the total for Big Blind" << endl;
    cout << "Current total in pot: " << this->grandPot() << endl;
    amount = this->player[bigB].potTot();

    //making the small blind
    this->player[smallB].bet(this->iBet / 2);
    this->potTot += this->iBet / 2;
    cout << "Player " << this->smallB << ": bet $" << this->iBet / 2 << " as the total for Big Blind" << endl;
    cout << "Current total in pot: " << this->grandPot() << endl;
    dif = amount - this->iBet / 2;

    //player call, raise or fold
    do {
        cout << "To call you have to put $" << dif << endl;
        cout << "Player" << this->smallB << ": Call - 1, Raise - 2, Fold -3" << endl;
        cin >> input;
        //set the bet the same
        if (input == 1) {
            this->player[smallB].bet(dif);
            this->potTot += dif;
            cout << "Player#" << smallB << ": $" << dif << endl;
            cout << "Pot: $" << this->grandPot() << endl;
        //at least double the amount
        } else if (input == 2) {
            cout << "Amount: ";
            do {
                cin >> raise;
                if (raise <= dif) cout << "Amount should be greater than call Amount\n";
            } while (raise <= dif);
            this->player[smallB].bet(raise + dif);
            this->potTot += (raise + dif);
            cout << "Player#" << smallB << ": $" << raise + dif << " into the Pot" << endl;
            cout << "Pot: $" << this->grandPot() << endl;
            amount = this->player[smallB].potTot();
        //withdraw the player from the round
        } else if (input == 3) {
            this->player[smallB].setAFK();
            cout << "Player#" << smallB << ": folded" << endl;
            cout << "Pot: $" << this->grandPot() << endl;
        } else {
            cout << "wrong input" << endl;
        }
    } while (input < 1 || input > 3);

    return amount;



}

//flop

void Dealer::flop() {
    //declare and initialize variables
    int numCards = 3;
    int numPlayers = this->nPlayers;
    int bigB = this->bigB;
    int order;

    //deal out the three cards to the center of the table
    for (int i = numPlayers * 2 + 1; i < numPlayers * 2 + 1 + numCards; i++) {
        for (int j = 0; j < numPlayers; j++) {
            order = (j + bigB) % numPlayers;
            this->player[order].addCards(*this->c[i]);
        }
    }
}

//round two of betting
int Dealer::roundTwoBet(int num, int amount){
    int input;
    
        do{
        if(this->player[num].getConfirm()){
            int nP=this->nPlayers;
            
            int raise;
            int diff=amount - this->player[num].potTot();
            cout << "To call you have to put $" << diff << endl;
            cout << "Player" << num <<": call - 1, Raise - 2, Fold -3" << endl;
            cin >> input;
            if(input==1) {
                this->player[num].bet(diff);
                this->potTot+=(diff);
                cout << "Player#" << num << ": $" << diff << endl; 
                cout << "Pot: $" << this->grandPot() << endl;
            }
            else if(input==2){
                cout << "Amount: " ;
                do{
                    cin >> raise;
                    if(raise<=diff) cout << "Amount should be greater than call Amount\n";
                }while(raise<=diff);

                this->player[num].bet(raise+diff);
                this->potTot+=(raise+diff);
                cout << "Player#" << num << ": $" << raise+diff << endl; 
                cout << "Pot: $" << this-grandPot() << endl;
                amount=this->player[num].potTot();
            }
            else if(input==3){
                this->player[num].setAFK();
                cout << "Player#" << num << ": folded" << endl;
                cout << "Pot: $" << this->grandPot() << endl;
            }
            else {cout << "wrong input" << endl;}
        }
    }while(input<1||input>3);
    
    return amount;
}

//turn

void Dealer::turn() {
    //declare and initialize variables
    int numCards = 1;
    int numPlayers = this->nPlayers;
    int bigB = this->bigB;
    int order;

    //add another card to the flop
    for (int i = numPlayers * 2 + 5; i < numPlayers * 2 + 5 + numCards; i++) {
        for (int j = 0; j < numPlayers; j++) {
            order = (j + bigB) % numPlayers;
            this->player[order].addCards(*this->c[i]);
        }
    }

}

//third round of betting
int Dealer::roundThreeBet(int num, int amount){
    int nP=this->nPlayers;
    int input;
    int raise;
    int dif;
    do{
        if(this->player[num].getConfirm()){
            dif=amount - this->player[num].potTot();
            if(!dif){
                cout << "You can check" << endl;
                cout << "Player" << num <<": check - 1, Raise - 2, Fold -3" << endl;
            
            }
            else{
                cout << "To call you have to put $" << dif << endl;
                cout << "Player" << num <<": call - 1, Raise - 2, Fold -3" << endl;
            
            }
            
            cin >> input;
            if(input==1) {
                
                this->player[num].bet(dif);
                this->potTot+=(dif);
                cout << "Player#" << num << ": $" << dif << endl; 
                cout << "Pot: $" << this->grandPot() << endl;
            }
            else if(input==2){
                cout << "Amount: " ;
                do{
                    cin >> raise;
                    if(raise<=dif) cout << "Amount should be greater than call Amount\n";
                }while(raise<=dif);

                this->player[num].bet(raise+dif);
                this->potTot+=(raise+dif);
                cout << "Player#" << num << ": $" << raise+dif << endl; 
                cout << "Pot: $" << this->grandPot() << endl;
                amount=this->player[num].potTot();
            }
            else if(input==3){
                this->player[num].setAFK();
                cout << "Player#" << num << ": folded" << endl;
                cout << "Pot: $" << this->grandPot() << endl;
            }
            else {cout << "wrong input" << endl;}
        }
    }while(input<1||input>3);
    
    return amount;
}

//river

void Dealer::river() {
    //declare and initialize the variables
    int numCards = 1;
    int numPlayers = this->nPlayers;
    int bigB = this->bigB;
    int order;

    //add one more card from the deck to the turn & flop;
    for (int i = numPlayers * 2 + 7; i < numPlayers * 2 + 7 + numCards; i++) {
        for (int j = 0; j < numPlayers; j++) {
            order = (j + bigB) % numPlayers;
            this->player[order].addCards(*this->c[i]);
        }
    }
}

