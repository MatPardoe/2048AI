#include "ControlerFactory.h"
#include "iostream"

#include <Greedy.h>
#include <Positional.h>
#include <Tidy.h>
#include <SmoothGreedy.h>

ControlerFactory::ControlerFactory()
{

}

/**
returns a pointer to the selected controler with the other settings
such as the depth of trees generated and which evaluation to use
*/
Controler* ControlerFactory::GetControler(int choiceAlgorithm, int TreeDepth, int choiceEvaluation, std::string stateName)
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
    case 2:
        return new ExpectiMax(TreeDepth, usedEvaluation);
    case 3:
        return new Reinforcement(TreeDepth, stateName);
    default:
        return new RandomDirection();
    }
}

/**
displays what options are available for the controler
including what the default value is
*/
void ControlerFactory::DisplayOptions()
{
    std::cout << "0 = Random non-AI base class" << std::endl;
    std::cout << "1 = MinMax" << std::endl;
    std::cout << "2 = ExpectiMax" << std::endl;
    std::cout << "3 = Reinforcement learning (q-learning)" << std::endl;

    std::cout << "All other Values default to the Random non-AI class" << std::endl;
}

/**
displays what options are available for the evaluation function
including what the default value is
*/
void ControlerFactory::DisplayEvaluationOptions()
{
    std::cout << "0 = Greedy" << std::endl;
    std::cout << "1 = Positional" << std::endl;
    std::cout << "2 = Tidy" << std::endl;
    std::cout << "3 = SmoothGreedy" << std::endl;

    std::cout << "All other values default to the Greedy evaluation" << std::endl;
}

/**
returns a pointer to the select evaluation class
*/
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
