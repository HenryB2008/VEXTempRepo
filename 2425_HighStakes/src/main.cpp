#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "pros/misc.h"
using namespace pros; 


ASSET(bigGrab_txt); 
ASSET(test_txt);




       

//Odometry 

pros::Imu imu(16); //imu.
pros::Rotation horizontal_encoder(5); 
pros::Rotation vertical_encoder(7);   
lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_2, 5);  // Horizontal tracking wheel
lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_2, -2.5); // Vertical tracking wheel
// OdomSensors setup
lemlib::OdomSensors sensors(&vertical_tracking_wheel, // Vertical tracking wheel 1, set to null
                            nullptr, // Vertical tracking wheel 2, set to nullptr as we are using IMEs
                            &horizontal_tracking_wheel, // Horizontal tracking wheel 1
                            nullptr, // Horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu // Inertial sensor
);


//PID
// latetral PID controller
lemlib::ControllerSettings lateral_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
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
   11.75,       // track width          // this might be wrong
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
pros::adi::Pneumatics mogo('B', false); 
pros::adi::Pneumatics intakeSolenoid('H', false);
pros::adi::Pneumatics doinker('D', false);
pros::ADIDigitalIn limit('E');
pros::Rotation rotation_sensor(9);






double liftkP = 0.5; 
double liftkI = 0.0; 
double liftkD = 3; 


int liftError; 
int liftPrevError = 0; 
int liftDerivative; 
int liftTotalError = 0; 

bool enableLiftPID = true; 




int desiredLiftValue = 0; // Shared desired value for the lift
bool liftPIDRunning = false; // Flag to indicate if the liftPID is active

void liftPIDTask(void* param) {
    while (true) {
        if (liftPIDRunning) {
            int LiftMotorPosition = rotation_sensor.get_angle();
            liftError = LiftMotorPosition - desiredLiftValue;
            liftDerivative = liftError - liftPrevError;
            liftTotalError += liftError;

            double liftMotorPower = liftError * liftkP + liftDerivative * liftkD + liftTotalError * liftkI;
            LiftMotor.move(liftMotorPower);

            // Stop condition
            if (abs(liftError) < 1000) {
                liftPIDRunning = false;
                LiftMotor.brake();
            }

            liftPrevError = liftError;
        }

        pros::delay(20); // Save resources
    }
}





void opcontrol() {
// Controller Buttons
    pros::Controller controller(pros::E_CONTROLLER_MASTER);
    


    bool intake_forward = false;
    bool intake_reverse = false;


   


    //Loop
    while (true) {  

        int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
        int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
        int LiftMotorPosition = rotation_sensor.get_angle();


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
        

        
        if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L2)) {
            desiredLiftValue = 2000;
            liftPIDRunning = true;
        } else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_LEFT)) {
            desiredLiftValue = 4100;
            liftPIDRunning = true;
        } else if (controller.get_digital_new_press(E_CONTROLLER_DIGITAL_L1)) {
            desiredLiftValue = 13800;
            liftPIDRunning = true;
        }
        
    
        

        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)) {
            mogo.toggle(); 
        }
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_RIGHT)) { 
            doinker.toggle();
        } 
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B)){
            intakeSolenoid.toggle(); 
        }


        // stops brain from using too much resources    
        pros::delay(20);
    }
}



void test() {
    chassis.setPose(48, 48, 180); 
    pros::delay(5);
    chassis.moveToPose(36, 0, 180, 2000);   
}
void redLeft()
{
    doinker.extend(); 
    chassis.setPose(-45, 30, 66);    
    pros::delay(5);
    chassis.moveToPoint(-9.885, 45.634, 2000);
    chassis.waitUntilDone(); 
}

void autonomous() {
    redLeft(); 
    

}





void initialize() {
    mogo.retract(); 
    doinker.retract();
    pros::lcd::initialize(); // initialize brain screen
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);    
    chassis.calibrate(); // calibrate sensors
    LiftMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

   

    pros::Task liftPIDController(liftPIDTask, nullptr, "Lift PID Task");

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
    autonomous(); 
}





void skills()
{

}


