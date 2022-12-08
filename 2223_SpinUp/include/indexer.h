#ifndef INDEXER_H
#define INDEXER_H

#include "main.h"
#include "ports.h"

using okapi::Motor;

class Indexer {
    private:
        Motor m1;

        const std::vector<double> powers = { 12000, 0 };

        int currPower = 0;

    public:
        Indexer(int port1);
        void runVoltage(double power = 12000);
        void toggle();
};

extern Indexer indexer;

#endif