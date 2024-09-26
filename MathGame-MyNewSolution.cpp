#include<iostream>
#include<cstdlib>
#include<cmath>
using namespace std;
enum enQuestionLevel { Easy = 1, Med = 2, Hard = 3, Mixed = 4};
enum enOpeType {Add = 1, Sub = 2, Mul = 3, Div = 4, Mix = 5};
struct stQuestion
{
	int Num1 = 0;
	int Num2 = 0;
	enQuestionLevel Level;
	enOpeType Ope;
	int PlayerAnswer = 0;
	int CorrectAnswer = 0;
	bool AnswerResult = false;
};
struct stQuiz
{
	stQuestion QuestionList[100];
	int NumberOfQuestions = 0;
	enQuestionLevel QLevel;
	enOpeType QOpe;
	int NumberOfRightAnswers = 0;
	int NumberOfWrongAnswers = 0;
	bool FinalResult = false;
};
void PlayGame();
stQuestion GenerateAQuestion(enQuestionLevel Level, enOpeType Ope);
int RandomNumberGenerator(int From, int To)
{
	int N = rand() % (To - From + 1) + From;
	return N;
}
int ReadNumberOfQuestions()
{
	int N = 0;
	do
	{
		cout << "How Many Questions do you want to answer? " << endl;
		cin >> N;
	} while (1 > N || N > 10);
	return N;
}
enQuestionLevel ReadLevel()
{
	int N = 0;
	do
	{
		cout << "Enter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix? " << endl;
		cin >> N;
	}while(1 > N || N > 4);
	return (enQuestionLevel)N;
}
enOpeType ReadOperation()
{
	int N = 0;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix? " << endl;
		cin >> N;
		cout << endl;
	} while (1 > N || N > 5);
	return (enOpeType)N;
}
string GetOperationSign(enOpeType Ope)
{
	string PossibleOpe[5] = { "+", "-", "*", "/" };
	return PossibleOpe[Ope - 1];
}
string GetQuestionsLevel(enQuestionLevel Level)
{
	string PossibleLevels[5] = { "Easy", "Med", "Hard", "Mix" };
	return PossibleLevels[Level - 1];
}
string GetQuestionsOpe(enOpeType Ope)
{
	string PossibleOpe[6] = { "Add", "Sub", "Mul", "Div", "Mix" };
	return PossibleOpe[Ope - 1];
}
void SetScreenColor(bool Q)
{
	if (Q)
	{
		system("color 2F");
	}
	else
	{
		system("color 4F");
	}
}
int SimpleCalc(int Num1, int Num2, enOpeType Ope)
{
	switch (Ope)
	{
	case enOpeType::Add:
		return Num1 + Num2;
	case enOpeType::Sub:
		return Num1 - Num2;
	case enOpeType::Mul:
		return Num1 * Num2;
	case enOpeType::Div:
		return Num1 / Num2;
	default:
		return Num1 + Num2;
	}
}
void GenerateQuestions(stQuiz& Quiz)
{
	for (int i = 0; Quiz.NumberOfQuestions > i; i++)
	{
		Quiz.QuestionList[i] = GenerateAQuestion(Quiz.QLevel, Quiz.QOpe);
	}
}
void PrintQuestion(stQuiz Quiz, int Q)
{
	cout << Quiz.QuestionList[Q].Num1 << endl;
	cout << Quiz.QuestionList[Q].Num2 << " ";
	cout << GetOperationSign(Quiz.QuestionList[Q].Ope) << endl;
	cout << "_______\n";
}
void CorrectQuestion(stQuiz& Quiz, int QNum)
{
	if (Quiz.QuestionList[QNum].PlayerAnswer != Quiz.QuestionList[QNum].CorrectAnswer)
	{
		Quiz.NumberOfWrongAnswers++;
		Quiz.QuestionList[QNum].AnswerResult = false;
		cout << "Wrong Answer :-(\n";
		cout << "The right answer is: " << Quiz.QuestionList[QNum].CorrectAnswer;
		cout << "\n\n";
	}
	else
	{
		Quiz.NumberOfRightAnswers++;
		Quiz.QuestionList[QNum].AnswerResult = true;
		cout << "Right Answer :-)\n\n";
	}
	SetScreenColor(Quiz.QuestionList[QNum].AnswerResult);
}
int ReadUserAnswer()
{
	int N = 0;
	cin >> N;
	return N;
}
void ResetScreen()
{
	system("cls && color 0F");
}
void AskAndCorrectQuestions(stQuiz& Quiz)
{
	for (int i = 0; Quiz.NumberOfQuestions > i; i++)
	{
		PrintQuestion(Quiz, i);
		Quiz.QuestionList[i].PlayerAnswer = ReadUserAnswer();
		CorrectQuestion(Quiz, i);
	}
	Quiz.FinalResult = Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers;
}
string PassFailScreen(bool Result)
{
	if (Result)
		return "PASS :-) ";
	else
		return "FAIL :-( ";
}
stQuestion GenerateAQuestion(enQuestionLevel Level, enOpeType Ope)
{
	stQuestion Question;
	if (Level == enQuestionLevel::Mixed)
	{
		Level = (enQuestionLevel)RandomNumberGenerator(1, 3);
	}
	if (Ope == enOpeType::Mix)
	{
		Ope = (enOpeType)RandomNumberGenerator(1, 4);
	}

	Question.Ope = Ope;
	switch (Level)
	{
	case enQuestionLevel::Easy:
	{
		Question.Num1 = RandomNumberGenerator(1, 10);
		Question.Num2 = RandomNumberGenerator(1, 10);

		Question.CorrectAnswer = SimpleCalc(Question.Num1, Question.Num2, Ope);
		Question.Level = Level;
		return Question;
	}
	case enQuestionLevel::Med:
	{
		Question.Num1 = RandomNumberGenerator(11, 50);
		Question.Num2 = RandomNumberGenerator(1, 10);

		Question.CorrectAnswer = SimpleCalc(Question.Num1, Question.Num2, Ope);
		Question.Level = Level;
		return Question;
	}
	case enQuestionLevel::Hard:
	{
		Question.Num1 = RandomNumberGenerator(51, 100);
		Question.Num2 = RandomNumberGenerator(51, 100);

		Question.CorrectAnswer = SimpleCalc(Question.Num1, Question.Num2, Ope);
		Question.Level = Level;
		return Question;
	}
	}
}
void PrintQuizResults(stQuiz Quiz)
{
	cout << "__________________________________\n";
	cout << "\tFinal Result is " << PassFailScreen(Quiz.FinalResult) << endl;
	cout << "__________________________________\n";
	cout << "Number Of Questions    : " << Quiz.NumberOfQuestions << endl;
	cout << "Question Level         : " <<GetQuestionsLevel(Quiz.QLevel) << endl;
	cout << "Operation Type         : " << GetQuestionsOpe(Quiz.QOpe) << endl;
	cout << "Number of Right Answers: " << Quiz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quiz.NumberOfWrongAnswers << endl;
	cout << "__________________________________\n";

}
void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		ResetScreen();
		PlayGame();
		cout << "Do you want to play again?(Y/N)" << endl;
		cin >> PlayAgain;
	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}
void PlayGame()
{
	stQuiz Quiz;
	Quiz.NumberOfQuestions = ReadNumberOfQuestions();
	Quiz.QLevel = ReadLevel();
	Quiz.QOpe = ReadOperation();

	GenerateQuestions(Quiz);
	AskAndCorrectQuestions(Quiz);
	PrintQuizResults(Quiz);
}
int main()
{
	srand((unsigned)time(NULL));
	StartGame();
	return 0;

}



