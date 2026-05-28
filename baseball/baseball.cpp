#include <iostream>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	static constexpr int LENGTH = 3;

	Baseball(const string& question)
		: question(question)
	{
	}

	GuessResult guess(const string& guessNum) {
		assertIllegalArgument(guessNum);

		int strikes = countStrikes(guessNum);
		int balls = countBalls(guessNum);
		return { strikes == LENGTH, strikes, balls };
	}

	int countStrikes(const string& guessNum) {
		int strikes = 0;
		for (int i = 0; i < LENGTH; i++) {
			if (guessNum[i] == question[i]) strikes++;
		}
		return strikes;
	}

	int countBalls(const string& guessNum) {
		int balls = 0;
		for (int i = 0; i < LENGTH; i++) {
			if (guessNum[i] == question[i]) continue;
			for (int j = 0; j < LENGTH; j++) {
				if (guessNum[i] == question[j]) balls++;
			}
		}
		return balls;
	}

	void assertIllegalArgument(const std::string& guessNum)
	{
		if (guessNum.length() != LENGTH) {
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
		for (int i = 0; i < LENGTH; i++) {
			for (int j = i + 1; j < LENGTH; j++) {
				if (guessNum[i] == guessNum[j]) return true;
			}
		}
		return false;
	}
private:
	string question;
};