#ifndef CONTROLERFACTORY_H
#define CONTROLERFACTORY_H

#include <Controler.h>
#include <RandomDirection.h>
#include <MinMax.h>
#include <ExpectiMax.h>
#include <Evaluation.h>
#include <Reinforcement.h>

class ControlerFactory
{
    public:
        ControlerFactory();
        Controler* GetControler(int choiceAlgorithm, int TreeDepth, int choiceEvaluation);
        void DisplayOptions();
        void DisplayEvaluationOptions();
    protected:
    private:
        Evaluation* GetEvaluator(int choice);

};

#endif // CONTROLERFACTORY_H
