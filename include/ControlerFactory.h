#ifndef CONTROLERFACTORY_H
#define CONTROLERFACTORY_H

#include <Controler.h>
#include <RandomDirection.h>
#include <MinMax.h>

class ControlerFactory
{
    public:
        ControlerFactory();
        Controler* GetControler(int choice, int TreeDepth);
        void DisplayOptions();
    protected:
    private:
};

#endif // CONTROLERFACTORY_H
