#include "lemlib/api.hpp" // IWYU pragma: keep
#include "main.h"
#include "pros/misc.h"
using namespace pros; 

ASSET(IntakeRedRing_txt);
ASSET(GrabMogo_txt);
ASSET(hitLadder_txt);
ASSET(IntakeBlueRing_txt);
ASSET(hitLadderBlue_txt);
ASSET(left_five_txt);
ASSET(cross_field_first_txt);
ASSET(right_five_txt);
ASSET(cross_field_second_txt);
ASSET(last_rings_txt);
ASSET(final_mogo_txt);
ASSET(GrabMogoSafeSide_txt);
ASSET(GrabMogoSafeSideBlue_txt);
ASSET(skillsMogo1_txt);




       

//Odometry 

pros::Imu imu(9); //imu
pros::Rotation horizontal_encoder(19);  // vertical tracking wheel encoder
pros::Rotation vertical_encoder(16);    //horizontal tracking wheel encoder
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

MotorGroup left_motors({-8, -2, -10}, MotorGearset::blue);
MotorGroup right_motors({11, 14, 17}, MotorGearset::blue);
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
pros::Motor IntakeMotor1 (1);
pros::Motor LiftMotor(3);
pros::adi::Pneumatics mogo('B', false);
pros::adi::Pneumatics doinker('C', false);
pros::ADIDigitalIn limit('D');






/*
 ____             _            
|  _ \ ___  _   _| |_ ___  ___ 
| |_) / _ \| | | | __/ _ \/ __|
|  _ < (_) | |_| | ||  __/\__ \
|_| \_\___/ \__,_|\__\___||___/
*/

void redWallStakeAuton()
{   
    //pick up red ring and setup
    LiftMotor.move(127);
    doinker.extend();   
    pros::delay(300);
    LiftMotor.brake();
    chassis.setPose(-52.339, 13.475, 140);

    //deposit ring on field
    chassis.turnToHeading(75, 2000);
    chassis.waitUntilDone();

    chassis.setPose(-52.339, 13.475, 75);
    doinker.retract();
    pros::delay(500);
    


    // get ready to reverse
    chassis.turnToHeading(15, 2000);
    chassis.waitUntilDone();

    chassis.setPose(-52.339, 13.475, 15);
    pros::delay(250);
    
    chassis.moveToPoint(-57.911, -4.68,2000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(-57.092, -2.021, 2000);
    pros::delay(300);
    chassis.turnToHeading(90, 2000  );
    //chassis.moveToPoint(-55.661, -0.794, 3000);
    chassis.waitUntilDone();

    chassis.setPose(-57.092, -2.021, 90);

    pros::delay(20);
    
    chassis.moveToPoint(-62.65, -2.021, 2000, {.forwards = false});
    mogo.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(-65, -2.021, 2000, {.forwards = false});
    IntakeMotor1.move(-127);
    pros::delay(900);
    mogo.retract();
    chassis.setPose(-61.077, 0, 90);
   


    chassis.follow(IntakeRedRing_txt, 8, 3000);
    chassis.waitUntilDone();
    chassis.setPose(-44.002, 7.388, 40);
    pros::delay(1000);  
    IntakeMotor1.brake();

    chassis.turnToHeading(220, 2000);
    chassis.waitUntilDone();
    chassis.setPose(-39.911, 7.338,220);

    chassis.moveToPoint(-30.093, 22.554, 2000, {.forwards = false}); 
    chassis.waitUntil(14);
    IntakeMotor1.move(-127);
    LiftMotor.move(-127);
    mogo.extend();
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.setPose(-30.093, 22.554, 220);
    pros::delay(20);
    chassis.turnToHeading(90, 2000);
    chassis.waitUntilDone();
    chassis.setPose(-30.093, 22.554, 90);
    pros::delay(20);
    chassis.moveToPoint(-10.865, 22.524, 2000, {.forwards=true});  

}
void redSafeAuton()
{
    chassis.setPose(-51.365, -23.703, 90);
    LiftMotor.move(127);
    pros::delay(10);
    chassis.moveToPoint(-26.5, -23.703, 2000, {.forwards = false, .maxSpeed=70});
    chassis.waitUntil(19);
    LiftMotor.brake(); 
    mogo.toggle();
    chassis.waitUntilDone();
    chassis.turnToHeading(177.3, 2000);
    chassis.waitUntil(50);
    IntakeMotor1.move(-127);
    chassis.waitUntilDone();
    chassis.setPose(-26.5, -23.703, 180);
    pros::delay(500);
    chassis.moveToPoint(-26.5, -46.7, 2000);
    chassis.waitUntilDone();
    chassis.setPose(-26.5, -46.7, 180);
    pros::delay(500);
    chassis.turnToHeading(0, 2000);
    chassis.waitUntilDone();
    chassis.setPose(-26.5, -46.7, 0);
    pros::delay(10);
    chassis.follow(hitLadder_txt, 15, 3000, true);  
    chassis.waitUntilDone();
    IntakeMotor1.brake();
}

/*
void redGoalRush ()
{
    chassis.setPose(-52.797, -61.339, 90);
    pros::delay(10);
    chassis.follow(goalRush_txt, 15, 3000);
    chassis.waitUntilDone();
    doinker.extend();
    chassis.setPose(-13.115, -54.793, 55);
    pros::delay(10);
    chassis.follow(curvedReverse_txt, 15, 2000, false);
    chassis.waitUntilDone();
    chassis.setPose(-36.443, -58.844, 65);
    pros::delay(10);
    chassis.follow(intakeMogoRush_txt, 15, 2000, true);
    IntakeMotor1.move(-127);
    chassis.waitUntilDone();
    IntakeMotor1.brake();
    chassis.turnToHeading(90, 2000);
    chassis.waitUntilDone();
    mogo.extend();



}
*/
void blueWallStakeAuton()
{
    //pick up red ring and setup
    LiftMotor.move(127);
    doinker.extend();   
    pros::delay(300);
    LiftMotor.brake();
    
    chassis.setPose(54.18, 13.729, 180);

    //deposit ring on field
    chassis.turnToHeading(225, 2000);
    chassis.waitUntilDone();


    doinker.retract();
    pros::delay(500);
    


    // get ready to reverse
    chassis.turnToHeading(345, 2000);
    chassis.waitUntilDone();

    chassis.setPose(-52.339, 13.475, 345);
    pros::delay(250);

    chassis.moveToPoint(57.911, -4.68,2000, {.forwards = false});
    chassis.waitUntilDone();
    chassis.moveToPoint(57.092, -2.021, 2000);
    pros::delay(300);
    chassis.turnToHeading(270, 2000  );
    //chassis.moveToPoint(-55.661, -0.794, 3000);
    chassis.waitUntilDone();

    chassis.setPose(57.092, -2.021, 270);

    pros::delay(20);
    
    chassis.moveToPoint(62.65, -2.021, 2000, {.forwards = false});
    mogo.extend();
    chassis.waitUntilDone();
    chassis.moveToPoint(65, -2.021, 2000, {.forwards = false});
    IntakeMotor1.move(-127);
    pros::delay(900);
    mogo.retract();
    chassis.setPose(61.077, 0, 270);
   


    chassis.follow(IntakeBlueRing_txt, 8, 3000);
    chassis.waitUntilDone();
    chassis.setPose(44.002, 7.388, 40);
    pros::delay(1000);  
    IntakeMotor1.brake();

    chassis.turnToHeading(140, 2000);
    chassis.waitUntilDone();
    chassis.setPose(39.911, 7.338,220);

    chassis.moveToPoint(30.093, 22.554, 2000, {.forwards = false}); 
    chassis.waitUntil(14);
    IntakeMotor1.move(-127);
    LiftMotor.move(-127);
    mogo.extend();
    chassis.waitUntilDone();
    pros::delay(200);
    chassis.setPose(30.093, 22.554, 220);
    pros::delay(20);
    chassis.turnToHeading(270, 2000);
    chassis.waitUntilDone();
    chassis.setPose(30.093, 22.554, 270);
    pros::delay(20);
    chassis.moveToPoint(10.865, 22.524, 2000, {.forwards=true});  
}
void blueSafeAuton()
{
    chassis.setPose(51.365, -23.703, 90);
    pros::delay(10);
    chassis.moveToPoint(25, -23.703, 2000, {.forwards = false});
    LiftMotor.move(127);
    chassis.waitUntil(19);
    LiftMotor.brake();
    mogo.toggle();
    chassis.waitUntilDone();
    chassis.turnToHeading(177.3, 2000);
    chassis.waitUntil(50);
    IntakeMotor1.move(-127);
    chassis.waitUntilDone();
    chassis.setPose(25, -23.703, 180);
    pros::delay(500);
    chassis.moveToPoint(23, -46.7, 2000);
    chassis.waitUntilDone();
    chassis.setPose(25, -46.7, 180);
    pros::delay(500);
    chassis.turnToHeading(0, 2000);
    chassis.waitUntilDone();
    chassis.setPose(25, -46.7, 0);
    pros::delay(10);
    chassis.follow(hitLadderBlue_txt, 15, 3000, true);  
    chassis.waitUntil(22);
    IntakeMotor1.brake();
    chassis.waitUntilDone();
}

void blueRightSideSafe()
{
    chassis.setPose(51.57, 25, 90);
    pros::delay(10);
    chassis.follow(GrabMogoSafeSideBlue_txt, 10, 2000, false);
    chassis.waitUntil(17);
    mogo.toggle();
    chassis.waitUntilDone();
    IntakeMotor1.move(-127);
    pros::delay(900);
    // chassis.turnToHeading(17, 2000);
    // chassis.waitUntilDone();
    chassis.turnToHeading(0, 2000);
    chassis.waitUntilDone();
    chassis.setPose(31, 25, 0);
    pros::delay(10);
    chassis.moveToPoint(31, 43, 2000); 
    chassis.waitUntilDone();
    chassis.turnToHeading(180, 2000);

    chassis.waitUntilDone();
    chassis.setPose(31, 43, 180);
    pros::delay(10);
    chassis.moveToPoint(31, 5, 2000);
    chassis.waitUntil(10);
    IntakeMotor1.move(127);
    chassis.waitUntil(20);
    IntakeMotor1.move(-127);
    chassis.waitUntil(35);
    IntakeMotor1.brake();
    chassis.waitUntilDone();
}


/*
 _/___       _              ____          _      
|  _ \ _ __(_)_   _____   / ___|___   __| | ___ 
| | | | '__| \ \ / / _ \ | |   / _ \ / _` |/ _ \
| |_| | |  | |\ V /  __/ | |__| (_) | (_| |  __/
|____/|_|  |_| \_/ \___|  \____\___/ \__,_|\___|
*/

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


        //intake code
        /*if(R2Button)
        {
            IntakeMotor1.move(127);
        } else if (R1Button)
        {
            IntakeMotor1.move(-127);
        } else
        {
            IntakeMotor1.brake();
        }*/

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

        if(L1Button)
        {
            LiftMotor.move(127);
        } else if (L2Button)
        {
            LiftMotor.move(-127);
        } else
        {
            LiftMotor.brake();
        }

        
        
        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_Y)){
            mogo.toggle();
        }

        if(controller.get_digital_new_press(E_CONTROLLER_DIGITAL_B))
            doinker.toggle();
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
        pros::delay(25);
    }



void autonomous()
{
    LiftMotor.move(127);
    doinker.extend();   
    
    chassis.setPose(54.18, 13.729, 180);
    pros::delay(200);

    //deposit ring on field
    chassis.turnToHeading(225, 2000);
    chassis.waitUntilDone();


    doinker.retract();
    


    // get ready to reverse
    chassis.turnToHeading(0, 2000);
    chassis.waitUntilDone();
    LiftMotor.brake(); 
    chassis.setPose(54.18, 13.729, 0);
    pros::delay(10);

    chassis.moveToPoint(54.18, 2, 2000, {.forwards = false, .maxSpeed = 60});
    chassis.waitUntilDone();
    chassis.turnToHeading(90, 2000);
    chassis.waitUntilDone();
    chassis.setPose(54.18, 2.5, 90);
    pros::delay(10);

    chassis.moveToPoint(57.5, 2.5, 2000);
    chassis.waitUntilDone();
    LiftMotor.move(-127);
    pros::delay(400);
    
    chassis.setPose(57.5, 0, 90);
    IntakeMotor1.move(-127); 
    pros::delay(250);
    LiftMotor.brake();
    chassis.setPose(57.5, 0, 130);
    pros::delay(10);
    // chassis.moveToPoint(26, 23.5, 2000, {.forwards = false, .maxSpeed = 70}); 
    // chassis.waitUntil(27);
    // mogo.toggle();
    // chassis.waitUntilDone();
    




    // chassis.moveToPoint(57.911, -4.68,2000, {.forwards = false});
    // chassis.waitUntilDone();
    // chassis.moveToPoint(57.092, -2.021, 2000);
    // pros::delay(300);
    // chassis.turnToHeading(270, 2000  );
    // //chassis.moveToPoint(-55.661, -0.794, 3000);
    // chassis.waitUntilDone();

    // chassis.setPose(57.092, -2.021, 270);

    // pros::delay(20);
    
    // chassis.moveToPoint(62.65, -2.021, 2000, {.forwards = false});
    // mogo.extend();
    // chassis.waitUntilDone();
    // chassis.moveToPoint(65, -2.021, 2000, {.forwards = false});
    // IntakeMotor1.move(-127);
    // pros::delay(900);
    // mogo.retract();
    // chassis.setPose(61.077, 0, 270);
   


    // chassis.follow(IntakeBlueRing_txt, 8, 3000);
    // chassis.waitUntilDone();
    // chassis.setPose(44.002, 7.388, 40);
    // pros::delay(1000);  
    // IntakeMotor1.brake();

    // chassis.turnToHeading(140, 2000);
    // chassis.waitUntilDone();
    // chassis.setPose(39.911, 7.338,220);

    // chassis.moveToPoint(30.093, 22.554, 2000, {.forwards = false}); 
    // chassis.waitUntil(14);
    // IntakeMotor1.move(-127);
    // LiftMotor.move(-127);
    // mogo.extend();
    // chassis.waitUntilDone();
    // pros::delay(200);
    // chassis.setPose(30.093, 22.554, 220);
    // pros::delay(20);
    // chassis.turnToHeading(270, 2000);
    // chassis.waitUntilDone();
    // chassis.setPose(30.093, 22.554, 270);
    // pros::delay(20);
    // chassis.moveToPoint(10.865, 22.524, 2000, {.forwards=true});  
    
}

void initialize() {
    mogo.retract();
    pros::lcd::initialize(); // initialize brain screen
    chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);    
    chassis.calibrate(); // calibrate sensors
    



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
}





void skills()
{
        int start = millis();

    

    // back up into wall stake and score
    mogo.toggle();
    left_motors.move(-40);
    right_motors.move(-40);
    delay(100);
    left_motors.move(0);
    right_motors.move(0);
    IntakeMotor1.move(-127);
    delay(500);
    IntakeMotor1.move(0);
    left_motors.move(40);
    right_motors.move(40);
    delay(100);
    left_motors.move(-40);
    right_motors.move(-40);
    delay(120);
    left_motors.move(0);
    right_motors.move(0);

    chassis.setPose(-62.992, 0, 90);

    // left 5 rings
    chassis.moveToPoint(-47.244, 0, 1000);
    mogo.toggle();
    delay(100);
    chassis.turnToHeading(180, 5000);
    chassis.waitUntilDone();
    delay(200);
    left_motors.move(-60);
    right_motors.move(-60);
    delay(500);
    left_motors.move(0);
    right_motors.move(0);
    delay(500);
    mogo.toggle();
    delay(500);
    chassis.turnToHeading(90, 5000);
    chassis.waitUntilDone();


    IntakeMotor1.move(-127);
    chassis.setPose(-47.244, 17.717, 90);
    delay(50);
    chassis.moveToPoint(-21.397, 25.553, 3000); // ring 1
    delay(100);
    chassis.turnToHeading(350, 2000);
    chassis.waitUntilDone();
    delay(100);
    chassis.moveToPoint(-28.316, 53.603, 3000); // ring 2
    delay(100);
    chassis.turnToHeading(280, 2000);
    chassis.waitUntilDone();
    delay(100);
    chassis.moveToPoint(-43.571, 59.377, 2000); // ring 3
    delay(100);
    chassis.turnToHeading(180, 2000);
    chassis.waitUntilDone();
    delay(100);
    chassis.moveToPoint(-47.147, 47.562, 2000); // ring 4
    delay(100);
    chassis.turnToHeading(270, 2000);
    chassis.waitUntilDone();
    delay(100);
    chassis.moveToPoint(-58.744, 47.073, 2000);  // ring 5
    delay(100);
    chassis.turnToHeading(170, 2000);
    chassis.waitUntilDone();
    delay(100);
    //chassis.follow(left_five_txt, 11, 7000); // speed is ~50
    //chassis.waitUntilDone();
    
    delay(100);
    
    IntakeMotor1.move(0);                       // heading ~200 at this point
    /*
    chassis.turnToHeading(160, 3000);
    left_motors.move(-90);
    right_motors.move(-90);
    delay(1000);
    mogo.toggle();
    left_motors.move(0);                        // back up into corner
    right_motors.move(0);
    delay(100);
    left_motors.move(40);                       // move up again
    right_motors.move(40);
    delay(200);
    left_motors.move(0);
    right_motors.move(0);


    /*


    // travel to right 5
    chassis.setPose(-155, 153, 170);
    chassis.follow(cross_field_first_txt, 9, 3000, false);  // false for backwards
    chassis.waitUntilDone();


    // right 5 rings
    mogo.toggle();
    chassis.turnToHeading(90, 3000);
    IntakeMotor1.move(-127);
    chassis.follow(right_five_txt, 9, 7000);
    chassis.waitUntilDone();
    delay(100);
    IntakeMotor1.move(0);
    chassis.turnToHeading(20, 3000);
    left_motors.move(-90);
    right_motors.move(-90);
    delay(1000);
    mogo.toggle();
    left_motors.move(0);                        // back up into corner
    right_motors.move(0);

    // reset odom
    left_motors.move(40);
    right_motors.move(40);
    delay(100);
    left_motors.move(0);
    right_motors.move(0);
    chassis.turnToHeading(90, 3000);
    left_motors.move(-40);
    right_motors.move(-40);
    delay(300);
    left_motors.move(0);
    right_motors.move(0);
    chassis.setPose(-162, -120, 90);


    // more red rings + mogo
    IntakeMotor1.move(-90);
    chassis.follow(cross_field_second_txt, 11, 5000);
    while (chassis.getPose().x < 69 || chassis.getPose().y < -110)
    {
        delay(10);
    }
    IntakeMotor1.move(0); // stop motor as soon as 2 rings are picked up
    chassis.waitUntilDone();
    delay(200);
    chassis.turnToHeading(195, 2000);
    chassis.waitUntilDone();
    delay(200);
    left_motors.move(-20);
    right_motors.move(-20);
    delay(100);
    left_motors.move(0);
    right_motors.move(0);
    delay(100);
    mogo.toggle();
    delay(200);
    IntakeMotor1.move(-127);
    delay(100);


    // more red rings second phase
    chassis.turnToHeading(230, 3000);
    chassis.waitUntilDone();
    left_motors.move(40);
    right_motors.move(40);
    delay(500);
    left_motors.move(0);
    right_motors.move(0);
    delay(100);
    chassis.follow(last_rings_txt, 10, 5000);
    chassis.waitUntilDone();
    delay(500);
    chassis.turnToHeading(240, 3000);
    chassis.waitUntilDone();
    delay(100);
    left_motors.move(-40);
    right_motors.move(-40);
    delay(1000);
    left_motors.move(0);
    right_motors.move(0);
    mogo.toggle();                      // release mogo
    IntakeMotor1.move(0);
    delay(500);
    left_motors.move(40);
    right_motors.move(40);
    delay(200);
    left_motors.move(0);
    right_motors.move(0);
    delay(100);


    // push final mogo
    chassis.follow(final_mogo_txt, 10, 5000);
    chassis.waitUntilDone();
    left_motors.move(-40);
    right_motors.move(-40);
    delay(200);
    left_motors.move(0);
    right_motors.move(0);

    */


    lcd::print(0, "Time: %d", millis() - start);
}


