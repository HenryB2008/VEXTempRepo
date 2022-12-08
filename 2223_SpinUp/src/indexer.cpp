#include "indexer.h"

Indexer::Indexer(int port1): m1(port1) {

}

void Indexer::runVoltage(double power) {
    m1.moveVoltage(power);
}

void Indexer::toggle() {
    runVoltage(powers.at(currPower));

    currPower += 1;

    // Cycle back to the beginning of the vector
    if (currPower == powers.size())
        currPower = 0;
}

Indexer indexer = Indexer(INDEXER_MOTOR);