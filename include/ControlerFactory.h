#ifndef CONTROLERFACTORY_H
#define CONTROLERFACTORY_H

#include <Controler.h>
#include <RandomDirection.h>
#include <MinMax.h>
#include <Evaluation.h>

class ControlerFactory
{
    public:
        ControlerFactory();
        Controler* GetControler(int choiceAlgorithm, int TreeDepth);
        void DisplayOptions();
    protected:
    private:
        Evaluation* GetEvaluator(int choice);

};

#endif // CONTROLERFACTORY_H
