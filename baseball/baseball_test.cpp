#include "gmock/gmock.h"
#include "baseball.cpp"

using namespace testing;

TEST(BaseeballGame, ThrowExceptionWhenLengthIsUnmached) {
	Baseball game;
	EXPECT_THROW(game.guess(string("12")), length_error);

}

TEST(BaseeballGame, ThrowExceptionWhenInvalidChar) {
	Baseball game;
	EXPECT_THROW(game.guess(string("12s")), invalid_argument);

}