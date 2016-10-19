#ifndef AThreat_HPP
# define AThreat_HPP

# include <iostream>
# include <string>
# include <unordered_map>
using namespace std;

# define MAX_VALUE 1000000
# define NUMBER_THREATS 6

class Board;
class AThreat {
public:
	unordered_map<string, int> blackThreats;
	unordered_map<string, int> whiteThreats;

	AThreat(void);
	AThreat(AThreat &rhs);
	~AThreat(void);
	void clearThreats(void);
	bool isPlacedAtEnd(Board &b, short x, short y, string ori);
	bool isXStraight(Board &board, short x, short y, int nb);
	void arrangeThreats(unordered_map<string, int> *t);
	void findThreats(Board &b, short x, short y, unordered_map<string, int> *threats);
	void computeScore(Board &b);
	void computeThreats(Board &b);
	void printThreats(void);
	bool isBrokenThree(Board &b, short x, short y);
	void countThreats(Board &b, short x, short y, unordered_map<string, int> *t);

	static string 						threatsName[NUMBER_THREATS];
	static unordered_map<string, int>	threatsScore;
};

#endif
