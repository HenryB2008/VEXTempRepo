#include "turn.h"

void Turn::execute(const Direction& dir) {
    PIDController Turn = PIDController(turnGains, turnSlew, integralMax, turnMax);

    double turnError = 999999999;

    double turnPower;

    double turnTol = tol.convert(okapi::degree);

    double endTime = pros::millis() + time.convert(okapi::millisecond);

    if (dir == REVERSE) {
        target += 180_deg;
    }

    double EXECUTE_DELAY_MS = 10;

    double thetaDiff = okapi::OdomMath::constrainAngle180(target - Chassis::Odometry::getPos().theta).convert(okapi::degree);

    Logistic turnControl = Logistic(
        -time.convert(okapi::second) * 2, 
        time.convert(okapi::millisecond) / EXECUTE_DELAY_MS, 
        thetaDiff,
        Chassis::Odometry::getPos().theta
    );

    //std::cout << thetaDiff << std::endl;

    while(abs(thetaDiff) > tol.convert(okapi::degree) && pros::millis() < endTime) {

        thetaDiff = okapi::OdomMath::constrainAngle180(target - Chassis::Odometry::getPos().theta).convert(okapi::degree);
        // std::cout << "theta diff: " << thetaDiff << std::endl;

        Chassis::Odometry::printPos();

        turnError = okapi::OdomMath::constrainAngle180(turnControl.step() - Chassis::Odometry::getPos().theta).convert(okapi::degree);

        turnPower = Turn.step(turnError);

        Chassis::arcade(0, turnPower);

        // std::cout << "turn power: " << turnPower << std::endl;
    
        pros::delay(EXECUTE_DELAY_MS);

    }

    Chassis::arcade(0,0);
}