/*
#ifndef MCL_H
#define MCL_H

#include "lemlibSetup.h"
#include "ports.h"

#include <vector>
#include <random>
#include <cmath>
#include <algorithm> 




struct LidarSensor;

extern const LidarSensor FRONT_SENSOR;
extern const LidarSensor LEFT_SENSOR;
extern const LidarSensor RIGHT_SENSOR;

extern std::vector<LidarSensor> SENSORS;


//////////////////////////////////////////////////////////////////////////
/// Function definitions
//////////////////////////////////////////////////////////////////////////

extern void initParticlesUniform();

extern void motionUpdate();

extern void transformSensorPose();

extern void resampleParticles();

extern lemlib::Pose getEstimatedPose();

extern float calculateNEff();

extern void updateMCL();

extern void mclTask(void* param); 

extern float x;
extern float y; 
extern float z; 



#endif

*/