#include "path_builder.h"

void PathBuilder::execute() {

    // Loop through each path

    while (!paths.empty()) {

        paths.front().execute(callbacks);
        paths.pop();

        std::cout << "End movement" << std::endl;
    }

    std::cout << "Completed all movements" << std::endl;

    Chassis::arcade(0, 0);
}