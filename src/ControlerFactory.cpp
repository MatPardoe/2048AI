#include "ControlerFactory.h"
#include "iostream"

ControlerFactory::ControlerFactory()
{

}

Controler* ControlerFactory::GetControler(int choice, int TreeDepth)
{
    // no need for breaks in this switch statement as return stops the rest of the function from being executed
    switch (choice)
    {
    case 0:
        return new RandomDirection();
    case 1:
        return new MinMax(TreeDepth);
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
