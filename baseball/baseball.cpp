#include <iostream>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	Baseball(const string& question)
		: question(question)
	{
	}

	GuessResult guess(const string& guessNum) {
		assertIllegalArgument(guessNum);
		if (guessNum == question) {
			return { true,3,0 };
		}

		return {false, 0, 0};
	}

	void assertIllegalArgument(const std::string& guessNum)
	{
		if (guessNum.length() != 3) {
			throw length_error("Must be three letters.");
		}
		for (char ch : guessNum) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}
		if (isDuplicateNumber(guessNum))
		{
			throw invalid_argument("Must not have the same number");
		}
	}
	bool isDuplicateNumber(const std::string& guessNum)
	{
		return guessNum[0] == guessNum[1]
			|| guessNum[1] == guessNum[2]
			|| guessNum[2] == guessNum[0];
	}
private:
	string question;
};