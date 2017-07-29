#pragma once
#include<string>

using FString = std::string;
using int32 = int;


struct FBullsCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EGuessStatus 
{
	Invalid,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Not_Lowercase
};


class FBullCowGame 
{
public:

	FBullCowGame();

	
	void Reset();

	int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString);

	// count bulls and cows assuming valid guess 
	FBullsCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
