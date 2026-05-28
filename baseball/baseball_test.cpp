#include "gmock/gmock.h"
#include "baseball.cpp"
#include <random>
#include <algorithm>
#include <vector>

using namespace testing;

class BaseballFixture : public Test {
public:
	Baseball game{ "123" };
	void assertIllegalArgument(string guessNumber) {
		try {
			game.guess(string(guessNumber));
			FAIL();
		}
		catch (exception e) {
			//PASS
		}
	}
};


TEST_F(BaseballFixture, ThrowExceptionWhenInvalidCase) {
	assertIllegalArgument("12");
	assertIllegalArgument("12s");
	assertIllegalArgument("121");
}

TEST_F(BaseballFixture, SolvedResultIfMatchedNumber) {
	GuessResult result = game.guess("123");

	EXPECT_TRUE(result.solved);
	EXPECT_EQ(3, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, TwoStrikesWhenTwoDigitsMatchInPlace) {
	GuessResult result = game.guess("124");

	EXPECT_FALSE(result.solved);
	EXPECT_EQ(2, result.strikes);
	EXPECT_EQ(0, result.balls);
}

TEST_F(BaseballFixture, OneStrikeTwoBallsWhenMixed) {
	GuessResult result = game.guess("132");

	EXPECT_FALSE(result.solved);
	EXPECT_EQ(1, result.strikes);
	EXPECT_EQ(2, result.balls);
}

static vector<string> allValidNumbers() {
	vector<string> nums;
	for (int a = 0; a < 10; a++) {
		for (int b = 0; b < 10; b++) {
			if (b == a) continue;
			for (int c = 0; c < 10; c++) {
				if (c == a || c == b) continue;
				string s;
				s += ('0' + a);
				s += ('0' + b);
				s += ('0' + c);
				nums.push_back(s);
			}
		}
	}
	return nums;
}

static string randomQuestion() {
	random_device rd;
	mt19937 rng(rd());
	vector<int> digits = { 0,1,2,3,4,5,6,7,8,9 };
	shuffle(digits.begin(), digits.end(), rng);
	string q;
	for (int i = 0; i < 3; i++) q += ('0' + digits[i]);
	return q;
}

TEST(BaseballGame, ConvergesToRandomAnswerUsingFeedback) {
	string question = randomQuestion();
	Baseball game(question);

	vector<string> candidates = allValidNumbers();
	string finalGuess;
	int attempts = 0;

	while (!candidates.empty()) {
		attempts++;
		string g = candidates.front();
		GuessResult r = game.guess(g);

		if (r.solved) {
			finalGuess = g;
			EXPECT_EQ(3, r.strikes);
			EXPECT_EQ(0, r.balls);
			break;
		}

		int gotStrikes = r.strikes;
		int gotBalls = r.balls;
		candidates.erase(
			remove_if(candidates.begin(), candidates.end(),
				[&](const string& cand) {
					Baseball trial(cand);
					GuessResult tr = trial.guess(g);
					return tr.strikes != gotStrikes || tr.balls != gotBalls;
				}),
			candidates.end());
	}

	EXPECT_EQ(question, finalGuess);
	EXPECT_LE(attempts, 10);
}