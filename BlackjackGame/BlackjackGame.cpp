#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

class Card{
private:
    string symbol;
    string number;
    int value;

public:
    Card(string symbol, string number, int value):symbol(symbol), number(number), value(value){}

    int getValue(){
        return value;
    }

    string getNumber(){
        return number;
    }

    void setValue(int newValue){
        value = newValue;
    }

    string toString(){
        return number + " of " + symbol;
    }
};

class Deck{
private:
    vector<Card> cards;

public:
    Deck(){}

    void createDeck(){
        string symbols[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string numbers[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
        int values[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10, 11};

        for (int i=0; i<4; i++){
            for (int j=0; j<13; j++){
                cards.emplace_back(symbols[i], numbers[j], values[j]);
            }
        }
    }

    void shuffleDeck(){
        auto rng=default_random_engine{ static_cast<unsigned>(time(nullptr))};
        shuffle(cards.begin(), cards.end(), rng);
    }

    Card getCard(){
        Card card=cards.front();
        cards.erase(cards.begin());
        return card;
    }
};

class Player{
protected:
    vector<Card> hand;
    int score=0;

public:
    Player(){}

    int getScore(){
        return score;
    }

    void addCard(Card card){
        hand.push_back(card);
        score += card.getValue();

        for (int i=0; i<hand.size(); i++){
            if (hand[i].getNumber() == "Ace" && score > 21 && hand[i].getValue()==11) {
                hand[i].setValue(1);
                score -= 10;
            }
        }
    }

    void displayHand(){
        for (int i=0; i<hand.size(); i++){
            cout << hand[i].toString() << endl;
        }
    }

    void play(){
        cout << "Your hand:" << endl;
        displayHand();
        cout << "Your score: " << getScore() << endl;
    }
};

class Dealer{
private:
    vector<Card> hand;
    int score = 0;

public:
    Dealer(){}

    int getScore(){
        return score;
    }

    void addCard(Card card){
        hand.push_back(card);
        score += card.getValue();

        for (int i=0; i<hand.size(); i++){
            if (hand[i].getNumber() == "Ace" && score>21 && hand[i].getValue()==11){
                hand[i].setValue(1);
                score-=10;
            }
        }
    }

    void displayHand(){
        for (int i=0; i<hand.size(); i++){
            cout << hand[i].toString() << endl;
        }
    }

    void firstPlay(){
        cout << "\nDealer's hand:" << endl;
        cout << hand[0].toString() << endl;
        cout << "Hidden card" << endl;
    }

    void play(){
        cout << "Dealer's hand:" << endl;
        displayHand();
        cout << "\nDealer's score: " << getScore() << endl;
    }
};

class Game{
public:
    void initializeGame(){
        Deck deck;
        deck.createDeck();
        deck.shuffleDeck();

        Player player;
        Dealer dealer;

        player.addCard(deck.getCard());
        player.addCard(deck.getCard());

        dealer.addCard(deck.getCard());
        dealer.addCard(deck.getCard());

        player.play();
        dealer.firstPlay();

        string choice;
        while (true){
            if (player.getScore()==21){
                cout << "\nYou win!" << endl;
                return;
            }
            cout << "\nDo you want to hit or stand? (h/s): ";
            cin >> choice;
            system("cls");
            if (choice == "h"){
                player.addCard(deck.getCard());
                player.play();
                if (player.getScore() > 21){
                    cout << "\nYou bust! Dealer wins." << endl;
                    return;
                }
            }
            else{
                break;
            }
        }

        while (dealer.getScore()<17){
            dealer.addCard(deck.getCard());
        }
        dealer.play();

        if (dealer.getScore()>21 || player.getScore()>dealer.getScore()){
            cout << "\nYou win!" << endl;
        }
        else if(dealer.getScore()==player.getScore()){
            cout << "\nIt's a tie!" << endl;
        }
        else {
            cout << "\nDealer wins." << endl;
        }
    }
};

int main(){
    Game game;
    game.initializeGame();
    return 0;
}
