#include "ControlerFactory.h"

ControlerFactory::ControlerFactory()
{

}

Controler* ControlerFactory::GetControler()
{
    return new RandomDirection();
}
