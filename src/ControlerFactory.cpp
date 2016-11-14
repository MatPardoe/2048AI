#include "ControlerFactory.h"
#include "iostream"

#include <Greedy.h>

ControlerFactory::ControlerFactory()
{

}

Controler* ControlerFactory::GetControler(int choiceAlgorithm, int TreeDepth)
{
    // get the correct evaluation class
    Evaluation* usedEvaluation = GetEvaluator(0);

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


Evaluation* ControlerFactory::GetEvaluator(int choice)
{
    switch (choice)
    {
    case 0:
        return new Greedy();
    default:
        return new Greedy();
    }
}
