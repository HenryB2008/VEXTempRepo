#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "pros/misc.h"
using namespace pros; 






       

//Odometry 

pros::Imu imu(16); //imu
pros::Rotation horizontal_encoder(6);  // vertical tracking wheel encoder
pros::Rotation vertical_encoder(5);    //horizontal tracking wheel encoder
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, -5.75);  // Horizontal tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -2.5); // Vertical tracking wheel
// OdomSensors setup
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // Vertical tracking wheel 1, set to null
                            nullptr, // Vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // Horizontal tracking wheel 1
                            nullptr, // Horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // Inertial sensor
);


//PID
// latetral PID controller
lemlib::ControllerSettings lateral_controller(13, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              35, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(3.5, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              25, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);


//Drivetrain & Chassis

MotorGroup left_motors({-17, -18, 19}, MotorGearset::blue);
MotorGroup right_motors({-12, 13, 14}, MotorGearset::blue);
// Initialize the drivetrain with the specified settings
lemlib::Drivetrain drivetrain (
   &left_motors,
   &right_motors,
   12,       // track width          // this might be wrong
   2.75,              // wheel diameter      
   600,            // wheel rpm            
   2               // horizontal drift
);

lemlib::Chassis chassis(drivetrain, // drivetrain settings
                        lateral_controller, // lateral PID settings
                        angular_controller, // angular PID settings
                        sensors // odometry sensors
);





//other
pros::Optical colorSensor(5);
pros::Motor IntakeMotor1 (15);
pros::Motor LiftMotor(20);
pros::adi::Pneumatics mogo('A', false); 
pros::adi::Pneumatics intakeSolenoid('C', false);
pros::adi::Pneumatics doinker('D', false);
pros::ADIDigitalIn limit('E');
pros::Rotation rotation_sensor(9);





double kP = 0.0; 
double kI = 0.0; 
double kD = 0.0; 


int error; 
int prevError = 0; 
int derivative; 
int totalError = 0; 

bool enableLiftPID = true; 





void opcontrol() {
// Controller Buttons
    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    

    bool intake_forward = false;
    bool intake_reverse = false;
    int macro_step = 0;
    double timer_start;

    

    

    //Loop
    while (true) {


        
        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        int R2Button = controller.get_digital(E_CONTROLLER_DIGITAL_R2);
        int R1Button = controller.get_digital(E_CONTROLLER_DIGITAL_R1);
        int L1Button = controller.get_digital(E_CONTROLLER_DIGITAL_L1);
        int L2Button = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
        int xButton = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
        int yButton = controller.get_digital(pros::E_CONTROLLER_DIGITAL_Y);
        
        //move drivetrain
        chassis.tank(leftY, rightY);

        
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R1)){
            intake_reverse = false;
            intake_forward = !intake_forward;
        }

        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_R2)){
            intake_forward = false;
            intake_reverse = !intake_reverse;
        }

        if(intake_forward){
            IntakeMotor1.move(-127);
        }
        else if(intake_reverse){
            IntakeMotor1.move(127);
        }
        else{
            IntakeMotor1.brake();
        }

        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_UP)){
            enableLiftPID = true; 
            liftPID(30500); 

        } else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
            enableLiftPID = true; 
            liftPID(29500);
        } else if  (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)){
            enableLiftPID = true; 
            liftPID(4890);
        }


        

        
    

        
    

        
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) {
            mogo.toggle(); 
        }
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT))
            doinker.toggle();
        } 
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)) {
            intakeSolenoid.toggle();
        } 

        

        /*
           MACRO FOR LIMIT SWITCH
           1. right arrow is pressed --> intake at 75%
           2. limit switch is unpressed --> intake at 50%
           3. limit switch is repressed --> outtake at 100% for 2 seconds
           NOTE simplify later
       */
       if (macro_step == 0){

        if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)){
               limit.get_new_press();      // resets last press
               macro_step++;
        }

       } else if (macro_step == 1){

        IntakeMotor1.move(-90);         // intake until outtake
        if (limit.get_value() == 0) { macro_step++; }
          
       } else if (macro_step == 2){

        IntakeMotor1.move(-60);         // slow down when limit comes up
        if (limit.get_new_press()) { macro_step++; }

       } else if (macro_step == 3){

        timer_start = pros::millis();
        macro_step++;

       } else if (macro_step == 4){

        IntakeMotor1.move(127); // outtake is positive
        if (pros::millis() - timer_start > 2000){ macro_step++; }

       } else if (macro_step == 5){

        IntakeMotor1.move(0);
        macro_step = 0;
        
       }
       
        // stops brain from using too much resources
        pros::delay(20);

}

int liftPID(int desiredValue) {
    while(enableLiftPID) {
        int LiftMotorPosition = rotation_sensor.get_angle(); 
        error = LiftMotorPosition - desiredValue; 
        derivative = error - prevError; 
        totalError += error; 
        double liftMotorPower = error * kP + derivative * kP + totalError * kI;
        LiftMotor.move(liftMotorPower);     
        pros::delay(20); 
    }
}

void autonomous()
{   
}

void initialize() {
    mogo.retract(); 
    doinker.retract();
    pros::lcd::initialize(); // initialize brain screen
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);    
    chassis.calibrate(); // calibrate sensors
    LiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rotation_sensor.reset_position();  




    pros::Task screen_task([&]() {
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());

            // delay to save resources  
            pros::delay(20);

        }
    });
    opcontrol(); 
}





void skills()
{

}


