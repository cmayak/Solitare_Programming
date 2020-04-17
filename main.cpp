#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <string>
using namespace std;



struct card {
	/* 0=hearts
	 * 1=diamond
	 * 2=clubs
	 * 3=spades
	 */
	int suit = 0;
	int num = 0;
	bool vis = false;//visibility
};


void dispTopLine(int n = 1) {//displays top lines
	for (int i = 0; i < n; i++) {
		cout << "__________" << "   ";
	}
}

void dispBtmLine(int n = 1) {//displays bottom lines
	for (int i = 0; i < n; i++) {
		cout << "|________|" << "   ";
	}
}

void dispMidsec(int n = 1) {//displays empty mid sections
	for (int i = 0; i < n; i++) {
		cout << "|        |" << "   ";
	}
	cout << endl;
}

class stack {
public:
	void addCardDeck(vector<card>& drew) {// add a card from the deck
		card x = drew.back();
		bool kingRule = (x.num == 13) && (cards.size() == 0);
		if (((cards.back().suit < 2) && (x.suit >= 2)) || ((cards.back().suit >= 2) && (x.suit < 2)) || kingRule) {
			if (x.num + 1 == (cards.back().num || kingRule)) {
				cards.push_back(x);// adding card to local stack
				drew.pop_back();// deleting card from drew stack
			}
			else {
				cout << "Error: Card is not correct number.";
			}
		}
		else {
			cout << "Error: Card is not correct suit.";
		}
	}

	void addCard(vector<card> x, stack& other) {// add cards from other stack
		bool kingRule = (x.front().num == 13) && (cards.size() == 0);
		cout << "The num: " << x.front().num << " King: " << kingRule << " other size: " << cards.size() << endl;
		if ((cards.back().suit < 2) && (x.front().suit >= 2) || ((cards.back().suit >= 2) && (x.front().suit < 2)) || kingRule) {
			if ((x.front().num + 1 == cards.back().num) || kingRule) {
				for (int i = 0; i < x.size(); i++) {
					cards.push_back(x.at(i));//push cards of the stack to the back
				}
				other.subCard(x);//delete cards from orignal posistion
			}
			else {
				cout << "Error: Card is not correct number.";
			}
		}
		else {
			cout << "Error: Card is not correct suit.";
		}
	}

	void subCard() {//subtract one card
		cards.pop_back();
	}
	void subCard(vector<card> x) {//subtrack a stack of cards
		for (int i = 0; i < x.size(); i++) {
			cards.pop_back();
		}
	}

	vector<card> cards;// The cards of the stack

};



class topStack {
public:
	topStack() {//init function
		card temp;//to avoid a error with an empty vector, adding a blank card
		cards.push_back(temp);
	}

	void addCardDeck(vector<card>& drew) {// add card from the deck
		card x = drew.back();
		if (((cards.back().suit == x.suit) && (x.num - 1 == cards.back().num)) || ((x.num == 1) && (cards.size() == 1))) {
			if ((x.num - 1 == (cards.back().num)) || ((x.num == 1) && (cards.size() == 1))) {
				cards.push_back(x);
				drew.pop_back();
				suit = cards.back().suit;
			}
			else {
				cout << "Error: Card is not correct number.";
			}
		}
		else {
			cout << "Error: Card is not correct suit.";
		}

	}

	void addCard(stack& other) {//add a card from the bottom
		card x = other.cards.back();
		if (((cards.back().suit == x.suit) && (x.num - 1 == cards.back().num)) || ((x.num == 1) && (cards.size() == 1))) {
			if ((x.num - 1 == (cards.back().num)) || ((x.num == 1) && (cards.size() == 1))) {
				cards.push_back(x);
				other.cards.pop_back();
				suit = cards.back().suit;
			}
			else {
				cout << "Error: Card is not correct number.";
			}
		}
		else {
			cout << "Error: Card is not correct suit.";
		}
	}

	vector<card> cards;// vect of cards
	int suit = 0;
};

class board {
public:

	void disp() {
		//display deck------ this is messy~I know, sorry | fix it
		dispTopLine(4);// top row
		cout << "          ";
		dispTopLine(2);
		cout << endl;
		// Second row-----------
		for (int i = 0; i < 4; i++) {
			if (top[i].cards.size() == 1) {
				cout << "|        |" << "   ";
			}
			else {
				cout << dispNum(top[i].cards.back()) << "\b";
			}
		}
		cout << "          ";
		if (drew.size() == 0) {
			cout << "|        |" << "   ";
		}
		else {
			cout << dispNum(drew.back()) << "\b";
		}
		cout << "|   " << deck.size() << "   |" << "   " << endl;

		// Third row-----------
		for (int i = 0; i < 4; i++) {
			if (top[i].cards.size() == 1) {
				cout << "|        |" << "   ";
			}
			else {
				cout << dispSuit(top[i].cards.back()) << "   ";
			}
		}
		cout << "          ";
		if (drew.size() == 0) {
			cout << "|        |" << "   ";
		}
		else {
			cout << dispSuit(drew.back()) << "   ";
		}
		cout << "|        |" << "   " << endl;

		//bottom row
		dispBtmLine(4);
		cout << "          ";
		dispBtmLine(2);
		cout << endl << endl << endl;

		// Display bottom stuff---------------------
		vector<vector<string>> dispar(7);//2d vector for clean simple display of the bottom

		for (int i = 0; i < 7; i++) {//fill the display vector
			stackstr(i, dispar.at(i));
		}
		for (int i = 0; i < numLines() + 4; i++) { //for each line
			for (int j = 0; j < 7; j++) {//for each row
				cout << dispar.at(j).at(i);

			}
			cout << endl;
		}
	}

	void draw() {//draw a card
		drew.push_back(deck.back());
		deck.pop_back();
	}

	void resetDeck() {//reset the deck
		deck.swap(drew);
		reverse();
	}

	topStack top[4];
	stack btm[7];
	vector<card> nothing;//This needs to be here
	vector<card> deck;  //  ^For some reason it seems as if the the previous array bleads over to the
	vector<card> drew; //    deck vector and the 'nothing' vecotor seems to be working as a buffer.
					  //     [if you know why this is, and for some forsaken reason is going through this code, please email me(email is in the header)]

private:
	//fuctions that are only used internally
	int numLines() {//gets the max num of lines in the bottom stacks
		int sz = 0;
		for (int i = 0; i < 7; i++) {
			if (btm[i].cards.size() > sz) {
				sz = btm[i].cards.size();
			}
		}
		if (sz == 0) {
			return 0;
		}
		else {
			return 2 * (sz - 1) + 7;
		}

	}

	void reverse() {//reverse the order of the cards
		vector<card> temp;
		temp.swap(deck);
		for (int i = temp.size() - 1; i >= 0; i--) {
			deck.push_back(temp.at(i));
		}
	}


	void stackstr(int n, vector<string> & temp) {// |Stack string| Function for creating the nested vector for displaying stuff
		for (int i = 0; i < numLines() + 4; i++) {
			if (i < btm[n].cards.size() * 3) {
				if (i % 3 == 0) {
					temp.push_back("__________    ");
				}
				else if (i % 3 == 1) {
					if (btm[n].cards.at(i / 3).vis == true) {
						temp.push_back(dispNum(btm[n].cards.at(i / 3)));
					}
					else {
						temp.push_back("|        |    ");
					}
				}
				else {
					if (btm[n].cards.at(i / 3).vis == true) {
						temp.push_back(dispSuit(btm[n].cards.at(i / 3)) + "    ");
					}
					else {
						temp.push_back("|        |    ");
					}
				}

			}
			else {
				temp.push_back("              ");
			}
		}
	}

	string dispNum(card x) {//convert number to words
		string out;
		if (x.num == 1) {
			out = "|  Ace   |";
		}
		else if (x.num == 11) {
			out = "|  Jack  |";
		}
		else if (x.num == 12) {
			out = "|  Queen |";
		}
		else if (x.num == 13) {
			out = "|  King  |";
		}
		else if (x.num == 10) {
			out = "|   10   |";
		}
		else {
			out += "|   ";
			out += to_string(x.num);
			out += "    |";
		}
		out += "    ";
		return out;
	}

	string dispSuit(card x) {//convert numbers to suit
		string out;
		if (x.suit == 0) {
			out = "|Diamonds|";
		}
		else if (x.suit == 1) {
			out = "| Hearts |";
		}
		else if (x.suit == 2) {
			out = "| Clubs  |";
		}
		else {
			out = "| Spades |";
		}
		return out;
	}
};


void help() {
	cout << "------------------------------ Help ------------------------------" << endl;
	cout << "Moving a card(s) from bottom stack to bottom stack: \"m row colum target-row\" (m 1 1 4) " << endl;
	cout << "Moving a card from deck to bottom stack: \"d target-row\"  (d 4)" << endl;
	cout << "Moving a card from deck to top stack: \"fd target-row\" (fd 1)" << endl;
	cout << "Moving a card from bottom stack to top stack: \"fb row target-row\" (fb 1 4)" << endl;
	cout << "Draw a card: \"draw\" (draw)" << endl;
	cout << "Quit: \"q\" (q)" << endl;
}


// Initial the game--------------------------------
bool searchV(vector<int> rnum, int r) {//random number checker
	bool c = false;
	for (int i = 0; i < rnum.size(); i++) {
		if (rnum.at(i) == r) {
			c = true;
			break;
		}
		else {
			c = false;
		}
	}
	return c;
}


void setup(board & bd) {//Function that sets up the board
	// Create cards-----------------------------
	vector<card> tempDeck;
	card inCards[52];
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j < 14; j++) {
			inCards[i * 13 + j - 1].num = j;
			inCards[i * 13 + j - 1].suit = i;
		}
	}
	for (int i = 0; i < 52; i++) {
		cout << "Suit: " << inCards[i].suit << "  Num: " << inCards[i].num << endl;
	}
	// Shuffle the cards----------------------
	card unCards[52];
	vector<int> rnum;
	int r = rand() % 52;
	for (int i = 0; i < 52; i++) {
		cout << r << endl;
		while (searchV(rnum, r)) {
			r = rand() % 52;
		}
		rnum.push_back(r);
		unCards[i] = inCards[r];
	}
	for (int i = 0; i < 52; i++) {
		cout << "Suit: " << unCards[i].suit << "  Num: " << unCards[i].num << endl;
	}
	int k = 0;
	for (int i = 0; i < 7; i++) {
		if (i < 7) {
			for (int j = 0; j < i + 1; j++) {
				bd.btm[i].cards.push_back(unCards[k]);
				k++;
			}
		}
	}
	for (int i = k; i < 52; i++) {//put the rest of the cards in the deck
		bd.deck.push_back(unCards[i]);
	}
}



// Input --------------------------------

string input(board & bd) {// get and interpret input functions
	string in;
	string out;
	int r1;
	int col;
	int r2;
	vector<card> temp;
	cout << "(Enter \"help\" for a list of comands)" << endl;
	cout << "Enter : ";
	cin >> in;
	if (in == "draw") {//draw from the deck
		if (bd.deck.size() == 0) {
			bd.resetDeck();
		}
		bd.draw();
		out = "g";
	}
	else if ((in.front() == 'm') && (in.size() == 1)) {//moving the cards arround the bottom
		cin >> r1;
		cin >> col;
		cin >> r2;
		out = "g";
		r1--;
		r2--;
		col--;
		if (bd.btm[r1].cards.at(col).vis == false) {//check if the card is a visible card
			cout << "Cannot move this card" << endl;
			input(bd);//start input over
		}
		else {
			for (int i = col; i < bd.btm[r1].cards.size(); i++) {
				temp.push_back(bd.btm[r1].cards.at(i));
			}
			bd.btm[r2].addCard(temp, bd.btm[r1]);
		}

	}
	else if ((in.front() == 'q') && (in.size() == 1)) {
		out = "q";
	}
	else if ((in.front() == 'd') && (in.size() == 1)) {
		cin >> r2;
		r2--;
		bd.btm[r2].addCardDeck(bd.drew);
	}
	else if ((in == "fd") && (in.size() == 2)) {
		cin >> r2;
		r2--;
		bd.top[r2].addCardDeck(bd.drew);
	}
	else if ((in == "fb") && (in.size() == 2)) {
		cin >> r1;
		cin >> r2;
		r1--;
		r2--;
		bd.top[r2].addCard(bd.btm[r1]);
	}
	else if (in == "help") {
		out = "h";
	}
	else {
		out = "g";
	}
	return out;
}



void checkVis(board & bd) {// Update visible cards
	for (int i = 0; i < 7; i++) {
		bd.btm[i].cards.back().vis = true;
	}
}

int main() {
	srand(time(NULL));

	board bd;
	setup(bd);
	checkVis(bd);
	bd.disp();

	while (true) {
		string str;
		str = input(bd);
		if (str == "h") {
			help();
		}
		else if (str == "q") {
			break;
		}
		else {
			checkVis(bd);
			bd.disp();
		}

	}

	return 0;
}