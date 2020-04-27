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
    //declare and initialize the variables
    int replay = 1;
    this->setnPlayers(n);
    this->DOC();

    do {
        //start of the game. 
        this->setIBet(10); //initialize the starting bet to 10 (testing)
        this->setBlinds(); //make sure blinds are associated with the right person 
        this->resetPot(); //clear the pot to avoid leaking mem
        this->shuffle(); //shuffle the deck
        this->preflop(); //deal out 2 cards

        //starting the bet
        //first round of betting
        int betValue = roundOneBet();
        cout << "The first round of betting has ended. We will continue to the flop." << endl << endl;

        //second round of betting.
        int num = 0;
        int count = 1;
        int nP = this->nPlayers;
        int x = 1;

        //flop
        cout<<"The Flop"<<endl;
        this->flop();
        cout << "hit2" << endl;
        while (num < nP) {
            do {

                betValue = this->roundTwoBet((count + this->smallB) % nP, betValue);
                if ((count + this->bigB) % nP == this->bigB) x = 0;
                if (this->Dealer::getNumAct() == 1) {
                    x = 0;
                }
                count++;
                num++;
            } while (betValue - this->player[(count + this->smallB) % nP].potTot() || x);
        }

        cout << "The Second Round of betting is done, proceeding to the turn." << endl << endl;


        //the turn
        this->turn();

        //third round of betting
        count = 0;
        x = 1;
        num = 0;
        while (num < nP) {
            do {
                int aP = this->Dealer::getNumAct();
                betValue = this->roundThreeBet((count + this->bigB) % nP, betValue);
                count++;
                if ((count + this->bigB) % nP == this->bigB) x = 0;
                if (this->Dealer::getNumAct() == 1) {
                    x = 0;
                }
                num++;
            } while ((betValue - this->player[(count + this->bigB) % nP].potTot()) || x);
            }
        cout << "Third Round of betting is done. Proceeding to the river." << endl << endl;


        //the river
        this->river();

        //fourth round of betting
        count = 0;
        x = 1;
        num = 0;
        
        while(num<nP){
        do{
            int aP = this->Dealer::getNumAct();
            betValue = this->roundFourBet((count + this->bigB) % nP, betValue);
            count++;
            if ((count + this->bigB) % nP == this->bigB) x = 0;
            if (this->Dealer::getNumAct() == 1) {
                x = 0;
            }
            num++;
        }while ((betValue - this->player[(count + this->bigB) % nP].potTot()) || x);
        }
        
        cout << "Fourth Round of betting is done. Proceeding to finding the winner." << endl << endl;


        for (int i = 0; i<this->nPlayers; i++) {
            int order = (i + this->bigB) % this->nPlayers;
            cout << "Player" << order << ": " << this->player[order].getHandName() << endl;
        }
        this->calcTot();
        for (int i = 0; i<this->nPlayers; i++) {
            int order = (i + this->bigB) % this->nPlayers;
            this->Dealer::pInfo(order);
        }

        replay = this->reset();

    } while (replay != 0);

    delete [] player;
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
        if (this->player[i].pStatus()) {
            num++;
        }
        return num;
    }
}

//calculate the balance each player has

void Dealer::calcTot() {
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
        if (this->player[i].pStatus() == 1) {
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

    for (int j = 0; j < numPlayers; j++) {
        order = (j + bigB) % numPlayers;
        cout << "Player : " << j << endl;
        for (int i = 0; i < numCards; i++) {
            this->player[order].addCards(*this->c[j + numPlayers * i]);

            this->c[j + i + numPlayers * i]->output();
        }
    }

    cout << endl;

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
    cout << "Current total in pot: " << this->grandPot() << endl << endl;
    amount = this->player[bigB].potTot();

    //making the small blind
    this->player[smallB].bet(this->iBet / 2);
    this->potTot += this->iBet / 2;
    cout << "Player " << this->smallB << ": bet $" << this->iBet / 2 << " as the total for Small Blind" << endl;
    cout << "Current total in pot: " << this->grandPot() << endl << endl;
    ;
    dif = amount - this->iBet / 2;

    //player call, raise or fold
    do {
        cout << "To call you have to match $" << dif << endl;
        cout << "Player" << this->smallB << ": Call - 1, Raise - 2, Fold -3" << endl;
        cin >> input;
        //set the bet the same
        if (input == 1) {
            cout << dif << endl;
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

    //output
    //deal out the three cards to the center of the table
    for (int i = numPlayers * 2 + 1; i < numPlayers * 2 + 1 + numCards; i++) {
        //print out card
//        this->c[i]->output();

        for (int j = 0; j < numPlayers; j++) {
            order = (j + bigB) % numPlayers;
            this->player[order].addCards(*this->c[i]);
        }
    }
}

//round two of betting

int Dealer::roundTwoBet(int num, int amount) {
    int input;

    do {
        if (this->player[num].pStatus()) {
            int nP = this->nPlayers;

            int raise;
            int diff = amount - this->player[num].potTot();
            cout << "\nTo call you have to put $" << amount << endl;
            cout << "Player" << num << ": call - 1, Raise - 2, Fold -3" << endl;
            cin >> input;
            if (input == 1) {
                this->player[num].bet(diff);
                this->potTot += (diff);
                cout << "Player#" << num << ": $" << amount << endl;
                cout << "Pot: $" << this->grandPot() << endl;
            } else if (input == 2) {
                cout << "Amount: ";
                do {
                    cin >> raise;
                    if (raise <= diff) cout << "Amount should be greater than call Amount\n";
                } while (raise <= diff);

                this->player[num].bet(raise + diff);
                this->potTot += (raise + diff);
                cout << "Player#" << num << ": $" << raise + diff << endl;
                cout << "Pot: $" << this->grandPot() << endl;
                amount = this->player[num].potTot();
            } else if (input == 3) {
                this->player[num].setAFK();
                cout << "Player#" << num << ": folded" << endl;
                cout << "Pot: $" << this->grandPot() << endl;
            } else {
                cout << "wrong input" << endl;
            }
        }
    } while (input < 1 || input > 3);

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
        //output
//        cout << "The Turn is: " << endl;
//        this->c[i]->output();
//        cout << endl;
//        cout << "On the table: " << endl;
//        this->flop();
//        this->c[i]->output();
        for (int j = 0; j < numPlayers; j++) {
            order = (j + bigB) % numPlayers;
            this->player[order].addCards(*this->c[i]);
        }
    }

}

//third round of betting

int Dealer::roundThreeBet(int num, int amount) {
    int nP = this->nPlayers;
    int input;
    int raise;
    int dif;
    do {
        if (this->player[num].pStatus()) {
            dif = amount - this->player[num].potTot();
            if (!dif) {
                cout << "You can check" << endl;
                cout << "Player" << num << ": check - 1, Raise - 2, Fold -3" << endl;

            } else {
                cout << "To call you have to put $" << dif << endl;
                cout << "Player" << num << ": call - 1, Raise - 2, Fold -3" << endl;

            }

            cin >> input;
            if (input == 1) {

                this->player[num].bet(dif);
                this->potTot += (dif);
                cout << "Player#" << num << ": $" << dif << endl;
                cout << "Pot: $" << this->grandPot() << endl;
            } else if (input == 2) {
                cout << "Amount: ";
                do {
                    cin >> raise;
                    if (raise <= dif) cout << "Amount should be greater than call Amount\n";
                } while (raise <= dif);

                this->player[num].bet(raise + dif);
                this->potTot += (raise + dif);
                cout << "Player#" << num << ": $" << raise + dif << endl;
                cout << "Pot: $" << this->grandPot() << endl;
                amount = this->player[num].potTot();
            } else if (input == 3) {
                this->player[num].setAFK();
                cout << "Player#" << num << ": folded" << endl;
                cout << "Pot: $" << this->grandPot() << endl;
            } else {
                cout << "wrong input" << endl;
            }
        }
    } while (input < 1 || input > 3);

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
        //output
//        cout << "The River is:" << endl;
//        this->c[i]->output();
//        cout << endl;
//        this->flop();
//        this->turn();
//        this->c[i]->output();
        for (int j = 0; j < numPlayers; j++) {
            order = (j + bigB) % numPlayers;
            this->player[order].addCards(*this->c[i]);
        }
    }
}

//fourth round of betting

int Dealer::roundFourBet(int num, int amount) {
    int nP = this->nPlayers;
    int input;
    int raise;
    int dif;
    do {
        if (this->player[num].pStatus()) {
            dif = amount - this->player[num].potTot();
            if (!dif) {
                cout << "You can check" << endl;
                cout << "Player" << num << ": check - 1, Raise - 2, Fold -3" << endl;

            } else {
                cout << "To call you have to put $" << dif << endl;
                cout << "Player" << num << ": call - 1, Raise - 2, Fold -3" << endl;

            }

            cin >> input;
            if (input == 1) {

                this->player[num].bet(dif);
                this->potTot += (dif);
                cout << "Player#" << num << ": $" << dif << endl;
                cout << "Pot: $" << this->grandPot() << endl;
            } else if (input == 2) {
                cout << "Amount: ";
                do {
                    cin >> raise;
                    if (raise <= dif) cout << "Amount should be greater than call Amount\n";
                } while (raise <= dif);

                this->player[num].bet(raise + dif);
                this->potTot += (raise + dif);
                cout << "Player#" << num << ": $" << raise + dif << endl;
                cout << "Pot: $" << this->grandPot() << endl;
                amount = this->player[num].potTot();
            } else if (input == 3) {
                this->player[num].setAFK();
                cout << "Player#" << num << ": folded" << endl;
                cout << "Pot: $" << this->grandPot() << endl;
            } else {
                cout << "wrong input" << endl;
            }
        }
    } while (input < 1 || input > 3);

    return amount;
}