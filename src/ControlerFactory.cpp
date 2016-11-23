#include "ControlerFactory.h"
#include "iostream"

#include <Greedy.h>
#include <Positional.h>
#include <Tidy.h>
#include <SmoothGreedy.h>

ControlerFactory::ControlerFactory()
{

}

Controler* ControlerFactory::GetControler(int choiceAlgorithm, int TreeDepth, int choiceEvaluation)
{
    // get the correct evaluation class
    Evaluation* usedEvaluation = GetEvaluator(choiceEvaluation);

    // no need for breaks in this switch statement as return stops the rest of the function from being executed
    switch (choiceAlgorithm)
    {
    case 0:
        return new RandomDirection();
    case 1:
        return new MinMax(TreeDepth, usedEvaluation);
    default:
        return new RandomDirection();
    }
}

void ControlerFactory::DisplayOptions()
{
    std::cout << "0 = Random non-AI base class" << std::endl;
    std::cout << "1 = MinMax" << std::endl;

    std::cout << "All other Values default to the Random non-AI class" << std::endl;
}

void ControlerFactory::DisplayEvaluationOptions()
{
    std::cout << "0 = Greedy" << std::endl;
    std::cout << "1 = Positional" << std::endl;
    std::cout << "2 = Tidy" << std::endl;
    std::cout << "3 = SmoothGreedy" << std::endl;

    std::cout << "All other values default to the Greedy evaluation" << std::endl;
}

Evaluation* ControlerFactory::GetEvaluator(int choice)
{
    switch (choice)
    {
    case 0:
        return new Greedy();
    case 1:
        return new Positional();
    case 2:
        return new Tidy();
    case 3:
        return new SmoothGreedy();
    default:
        return new Greedy();
    }
}
