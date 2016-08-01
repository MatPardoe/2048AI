#ifndef CONTROLERFACTORY_H
#define CONTROLERFACTORY_H

#include <Controler.h>
#include <RandomDirection.h>

class ControlerFactory
{
    public:
        ControlerFactory();
        Controler* GetControler();
    protected:
    private:
};

#endif // CONTROLERFACTORY_H
