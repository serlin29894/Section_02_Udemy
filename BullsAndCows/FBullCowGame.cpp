#include "FBullCowGame.h"
#include <map>
#define TMap std::map



FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{

	constexpr int32 MAX_TRY = 5;
	const FString HIDDEN_WORD = "plant";
	
	MyMaxTries = MAX_TRY;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

int32 FBullCowGame::GetMaxTries () const
{
	return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLenght() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

bool FBullCowGame::IsIsogram(FString Word) const
{

	// treat 0 and 1 letter word as isogram

	// setup our map
	TMap<char, bool> LetterSeen;

	for (auto Letter : Word)
	{
		Letter = tolower(Letter);

		if (LetterSeen[Letter])  //if the lleter is in the map we don't have an isogram
		{
			return false;
		}
		else //otherwise
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen 
		}
    }

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) 
	{
		if (!islower(Letter)) 
		{
			return false;
		}
	}

	return true;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	//if the guess is not an isogram return error 
	if (!IsIsogram(Guess)) 
	{
		return EGuessStatus::Not_Isogram;
	}
	//if the guess isn't all lowercase return error
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	//if the guess isn't same lenght return error 
	else if (Guess.length() != GetHiddenWordLenght())
	{
		return EGuessStatus::Wrong_Lenght;
	}
	// else return ok 
	else
	{
		return EGuessStatus::OK;
	}
	 
}

// Assuming we have a valid guess 
FBullsCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullsCowCount BullsCowCount;
	int32 WordLenght = MyHiddenWord.length(); // assuming same lenght as guess

	//Compare guess against my hidden word 
	for (int32 i = 0; i < WordLenght; i++) 
	{ 
		char Guessletter = Guess[i];
		for (int32 j = 0; j < WordLenght; j++) 
		{
			char HiddenWordLetter = MyHiddenWord[j];

			if (Guessletter == HiddenWordLetter && i == j) 
			{
				BullsCowCount.Bulls++;
			}
			else if (Guessletter == HiddenWordLetter && i != j)
			{
				BullsCowCount.Cows++;
			}
		}
	}

	if (BullsCowCount.Bulls == WordLenght )
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullsCowCount;
}


