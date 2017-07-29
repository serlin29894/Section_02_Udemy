#include <iostream>
#include<string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PrintSumarizeGame();
void PlayGame();
FText GetValidGuess();
bool AskToPlay();


//Global Variables 
FBullCowGame BCGame;


int main() 
{

	//Variables 
	bool bWantPlay = true;
	
	do 
	{
		PrintIntro();
		PlayGame();
		bWantPlay = AskToPlay();
		
	} 
	while (bWantPlay);
	
	return 0;
	
}

void PlayGame()
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();

	// Loop getting guesses until game is not won and we have remaining tries
	while(!BCGame.IsGameWon()  && BCGame.GetCurrentTry() <= MaxTries )
	{
		
		FText Guess = "None";
		Guess = GetValidGuess(); // check input validation
		
		// submit valid guess to thhe game 
		FBullsCowCount BullsCowCount = BCGame.SubmitValidGuess(Guess);
		
		// print number of bulls and cows 
		std::cout << "Bulls = " << BullsCowCount.Bulls;
		std::cout << ". Cow = " << BullsCowCount.Cows << std::endl;
		std::cout << std::endl;
	}

	PrintSumarizeGame();

}

//introduce the game				
void PrintIntro ()
{
	// Constant expresions
	
	std::cout << "\n\nWelcome To Bulls and Cows" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLenght() << " letter isogram I'm thinking off?" << std::endl;
	std::cout << std::endl;
	return;
}

void PrintSumarizeGame() 
{
	if (BCGame.IsGameWon()) 
	{
		std::cout << "WELL DONE YOU WON THE GAME. \n\n";
	}
	else
	{
		std::cout << "YOU LOSE don't worry try again. \n\n";
	}

}


//get a guess from the player
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::Invalid;
	FText Local_Guess = "None";

	do
	{
		//Get guess from the player 
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try:" << CurrentTry << " of " << BCGame.GetMaxTries() << std::endl;
		std::cout << "Make a guess: ";
		std::getline(std::cin, Local_Guess);

		//Check status of the guess
        Status = BCGame.CheckGuessValidity(Local_Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Please enter a word with " << BCGame.GetHiddenWordLenght() << " letters. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word in lowercase. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters(isogram). \n";
			break;

		default:
			//assume the guess is valid 
			break;
		}
		std::cout << std::endl;

	} while (Status != EGuessStatus::OK); //Loop until status is equal to OK 
	
	return Local_Guess;
}

bool AskToPlay()
{
	FText response = "None";
	std::cout << "Do you want to play again (y/n): ";
    std::getline(std::cin, response);
	std::cout << std::endl;

	return (response[0] == 'y') || (response[0] == 'Y');
}
