#include "init.h"




void init() {
    
    pros::lcd::initialize(); // initialize brain screen
    chassis.setBrakeMode(MOTOR_BRAKE_COAST);    
    chassis.calibrate(); // calibrate sensors
    liftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    colorSensor.set_integration_time(3);
    colorSensor.set_led_pwm(100);


    pros::Task liftPIDController(liftPIDTask, nullptr, "Lift PID Task");
    pros::Task colorSorting(colorSortTask, nullptr, "Color Sort Task");

    //pros::Task toggleDoinker(toggleDoinkerTask, nullptr, "Toggle Doinker");

     pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

            std::cout << "distance: " << colorSensor.get_proximity() << " color: " << colorSensor.get_hue() << std::endl; 
            // delay to save resources  
            pros::delay(20);

        }

    });    
    autonomous(); 
 
 
}