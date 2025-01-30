#include "ramsete.h"




//ALL COMMENTS IN THIS FILE TAKEN FROM PURDUE SIGBOTS WIKI
/* 
The first step with any control algorithm is determining the current error value. 
We can easily compute the robot's error in the global frame by subtracting the desired position from the current position. 
*/




void printPath(std::vector<squiggles::ProfilePoint> path) {
    std::cout << "PRINTING PATH POINTTS"; 
    for(int i = 0; i < path.size(); i++) {
        std::cout << "Point " << i << "X: " << path[i].vector.pose.x << "Y: " << path[i].vector.pose.y << "Yaw: " << 
        path[i].vector.pose.yaw << "Time: " << path[i].time << std::endl;
        pros::delay(10);
    }
}

void driveRamsete(
    std::vector<squiggles::ProfilePoint> path, 
    float zeta, 
    float b, 
    bool backward,
    float errorDistance 
    ) 
    {

    auto startTime = pros::millis(); 

    size_t index = 0;   

    while(true)   {
        double elapsedSec = (pros::millis() - startTime) / 1000.0; 

        if(elapsedSec >= path.back().time) {
            break; 
        }

        while((index + 1 < path.size()) && path[index+1].time <= elapsedSec) {
            index++; 
        }

        const auto& targetPoint = path[index];

        //get desired values from path
        float xDesired = targetPoint.vector.pose.x; 
        float yDesired = targetPoint.vector.pose.y;
        float thetaDesired = targetPoint.vector.pose.yaw;
        float linearDesired = targetPoint.vector.vel;
        float angularDesired = linearDesired * targetPoint.curvature; 

        //backwards movement 
        if(backward) {
            linearDesired = -linearDesired; 
        }

        //robot current position from odom 
        std::vector<float> currentPose = convertUnits(chassis.getPose()); 

        float xCurrent = currentPose[0];
        float yCurrent = currentPose[1];
        float thetaCurrent = currentPose[2];

        //calculate global error 
        float globalErrorX = xDesired - xCurrent;
        float globalErrorY = yDesired - yCurrent;

        //Calculate locale rror
        float errorX = std::cos(thetaCurrent) * globalErrorX  + std::sin(thetaCurrent) * globalErrorY; 
        float errorY = -std::sin(thetaCurrent) * globalErrorX + std::cos(thetaCurrent) * globalErrorY; 
        float errorTheta = thetaDesired - thetaCurrent; 
                
        //set thetaError range to [-pi, pi]
        errorTheta = std::atan2(std::sin(errorTheta), std::cos(errorTheta));

        //ramsete formulas
        float k = 2 * zeta * std::sqrt(b * std::pow(linearDesired, 2) + std::pow(angularDesired, 2));
        float v = linearDesired * std::cos(errorTheta) + k * errorX; 
        float denom = (std::fabs(errorTheta) < 1e-6) ? 1e-6f : errorTheta;
        float omega = angularDesired + k * errorTheta +  ((b * linearDesired * std::sin(errorTheta) * errorY) / denom);

 
        //robot width: 0.2921, then multiply by 0.5


        float wheelVelLeftMps = v + (omega * 0.14605);
        float wheelVelRightMps = v - (omega * 0.14605);
        
        float wheelCircumference = 0.219329; 

        float leftRevPerSecond = (wheelVelLeftMps / wheelCircumference);
        float rightRevPerSecond = (wheelVelRightMps / wheelCircumference);

        float leftRPM = leftRevPerSecond * 60.0 * 0.75;
        float rightRPM = rightRevPerSecond * 60.0 * 0.75; 

        drivetrain.leftMotors->move_velocity(leftRPM);
        drivetrain.rightMotors->move_velocity(rightRPM);


        //error checking 
        float xFinal = path.back().vector.pose.x;
        float yFinal = path.back().vector.pose.y;
        float dx = xFinal - xCurrent;
        float dy = yFinal - yCurrent;
        float distToEnd = std::sqrt(dx*dx + dy*dy);
        if (distToEnd < errorDistance) {
            // We’re close enough to the end, so break out
            break;
        }

        // 12) Small delay for the control loop (e.g. 10ms)
        pros::delay(10);
        std::cout<< "errorX: " << errorX << " errorY: " << errorY << " ErrorTheta: " << errorTheta
        << " leftRPM: " << leftRPM << " rightRPM: " << rightRPM << " ElapsedSec:  " << elapsedSec << std::endl;
    

    }
    chassis.tank(0,0);
}
