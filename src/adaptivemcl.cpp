/*
#include "mcl.h"

struct Particle {
    float x;
    float y;   
    float theta; 
    float weight; 
};

std::vector<Particle> particles;
const int NUM_PARTICLES = 1300;

const float FIELD_MIN_X = -72.0f;
const float FIELD_MAX_X = 72.0f;
const float FIELD_MIN_Y = -72.0f; 
const float FIELD_MAX_Y = 72.0f; 

const float FIELD_WIDTH = FIELD_MAX_X - FIELD_MIN_X; 
const float FIELD_HEIGHT = FIELD_MAX_Y - FIELD_MIN_Y; 

struct LidarSensor {
    pros::Distance sensor; 
    float offsetX;
    float offsetY;
    float offsetTheta;
};

const LidarSensor FRONT_SENSOR = {frontDistance, -5, 4, 0};  
const LidarSensor LEFT_SENSOR = {leftDistance, -6.75, 0.5, M_PI_2};
const LidarSensor RIGHT_SENSOR = {rightDistance, 6.75, 0.25, -M_PI_2};
std::vector<LidarSensor> SENSORS = {FRONT_SENSOR, LEFT_SENSOR, RIGHT_SENSOR}; 

std::mt19937 randGen(std::random_device{}()); 

void initParticlesUniform(){
    particles.clear();
    std::uniform_real_distribution<float> distX(FIELD_MIN_X, FIELD_MAX_X);
    std::uniform_real_distribution<float> distY(FIELD_MIN_Y, FIELD_MAX_Y);
    std::uniform_real_distribution<float> distTheta(0.0, 2*M_PI);
    for(int i = 0; i < NUM_PARTICLES; ++i) {
        Particle p; 
        p.x = distX(randGen);
        p.y = distY(randGen);
        p.theta = distTheta(randGen);
        p.weight = 1.0f /  NUM_PARTICLES;
        particles.push_back(p);
    }
}





void motionUpdate() {
    static lemlib::Pose previousPose = {chassis.getPose().x, chassis.getPose().y, 
        lemlib::sanitizeAngle(chassis.getPose().theta - M_PI_2)
    };
    lemlib::Pose currentPose = {chassis.getPose().x, chassis.getPose().y, 
        lemlib::sanitizeAngle(chassis.getPose().theta - M_PI_2)
    }; 
    float dx = currentPose.x - previousPose.x; 
    float dy = currentPose.y - previousPose.y;
    float dtheta = currentPose.theta - previousPose.theta; 
    dtheta = atan2(sin(dtheta), cos(dtheta)); //normalizes the angle from [-pi to pi]
    float linearNoise = 1.5;  //inches
    float rotationNoise = 0.05;  //radians
    std::normal_distribution<float> noiseLinear(0, linearNoise);
    std::normal_distribution<float> noiseRotation(0, rotationNoise);
    for (Particle &p : particles) {
        p.x += dx + noiseLinear(randGen);
        p.y += dy + noiseLinear(randGen);
        p.theta += dtheta + noiseRotation(randGen);
        //normalizes angle 
        if (p.theta < 0) 
            p.theta += 2 * M_PI;
        else if (p.theta >= 2 * M_PI) 
            p.theta -= 2 * M_PI;
    }
    previousPose = currentPose; 
}

void transformSensorPose(const Particle &p, const LidarSensor &sensor, float &sensor_x, 
    float &sensor_y, float &sensor_theta) {
    sensor_theta = p.theta + sensor.offsetTheta; 

    if (sensor_theta < 0)
        sensor_theta += 2 * M_PI;
    else if (sensor_theta >= 2 * M_PI)
        sensor_theta -= 2 * M_PI;

    sensor_x = p.x + sensor.offsetX * cos(p.theta) - sensor.offsetY * sin(p.theta);
    sensor_y = p.y + sensor.offsetX * sin(p.theta) + sensor.offsetY * cos(p.theta);
}

void sensorUpdate() {
    
    float sumW = 0.0f, sumWsq = 0.0f;
    for (const Particle &p : particles) {
        sumW += p.weight; 
        sumWsq += p.weight * p.weight; 
    }
    float N_eff = (sumWsq > 0) ? (sumW * sumW / sumWsq) : 0; 
    float sigma = (N_eff < NUM_PARTICLES * 0.5f) ? 5.0f : 15.0f; 
    float sigma2 = sigma * sigma; 
    float gaussianNorm = 1.0f / (sigma * sqrt(2 * M_PI));

    for (Particle &p : particles) {
        float combinedProb = 1.0f;

        //reject ladder pole readings
        for(size_t i = 0; i < SENSORS.size(); ++i) {    
            if(SENSORS[i].sensor.get_object_size() > 90) {
                continue; 
            }

            float sensor_x, sensor_y, sensor_theta;
            //get global orientation of the sensors
            transformSensorPose(p, SENSORS[i], sensor_x, sensor_y, sensor_theta); 

            //estimate the position of the robot using trig 
            float dx_left = sensor_x - FIELD_MIN_X; 
            float dx_right = FIELD_MAX_X - sensor_x; 
            float dy_top = sensor_y - FIELD_MIN_Y; 
            float dy_bottom = FIELD_MAX_Y - sensor_y;
            float expected_distance = 1e6f; 
            float cosT = cos(sensor_theta);
            float sinT = sin(sensor_theta);
            if (fabs(cosT) > 1e-6f) { //removes any divide by zero errors
                if (cosT < 0)
                    expected_distance = std::min(expected_distance, dx_left / (float)fabs(cosT));
                else
                    expected_distance = std::min(expected_distance, dx_right / (float)fabs(cosT));  
            }
            if (fabs(sinT) > 1e-6f) { //removes any divide by zero erros
                if (sinT < 0)
                    expected_distance = std::min(expected_distance, dy_top / (float)fabs(sinT));
                else
                    expected_distance = std::min(expected_distance, dy_bottom / (float)fabs(sinT));
            }

            float z = SENSORS[i].sensor.get() / 25.4;
            float error = z - expected_distance; 
            float prob = gaussianNorm * exp(-(error * error) / ( 2 * sigma2));
            combinedProb *= (prob + 1e-6f); 
        }

        p.weight = combinedProb;
    }

    float total = 0.0f; 
    for(const Particle &p : particles) {
        total += p.weight; 
    } 
    if (total > 0) {
        for(Particle &p : particles) {
            p.weight /= total; 
        }
    } else {
        for (Particle &p : particles){
            p.weight = 1.0f / particles.size();
        }
    }
}

void resampleParticles() {
    std::vector<float> weights; 
    weights.reserve(particles.size());
    for(const Particle &p : particles){
        weights.push_back(p.weight);
    }
    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    std::vector<Particle> newParticles;
    newParticles.reserve(particles.size());
    for(int i = 0; i < particles.size(); ++i) {
        int idx = dist(randGen);
        Particle p = particles[idx];
        p.weight = 1.0 / particles.size();
        newParticles.push_back(p);
    }
    particles = std::move(newParticles);
}

lemlib::Pose getEstimatedPose() {
    float sumW = 0.0f, meanX = 0.0f, meanY = 0.0f, meanSin = 0.0f, meanCos = 0.0f;
    for (const Particle &p : particles) {
        sumW   += p.weight;
        meanX  += p.weight * p.x;
        meanY  += p.weight * p.y;
        meanSin += p.weight * sin(p.theta);
        meanCos += p.weight * cos(p.theta);
    }
    if (sumW == 0)
        return lemlib::Pose(0, 0, 0);
    meanX /= sumW;
    meanY /= sumW;
    meanSin /= sumW;
    meanCos /= sumW;
    float meanTheta = atan2(meanSin, meanCos);
    return lemlib::Pose(meanX, meanY, meanTheta);
}



float calculateNEff() {
    float sumW = 0.0f, sumWsq = 0.0f;
    for (const Particle &p : particles) {
        sumW   += p.weight;
        sumWsq += p.weight * p.weight;
    }
    if (sumWsq <= 0.0f) return 0.0f;
    return (sumW * sumW) / sumWsq;
}


float x;
float y; 
float z; 
float N_eff; 

void updateMCL()  {
    motionUpdate();
    sensorUpdate();
    resampleParticles();

}

bool mclThreadRunning = true; 
pros::Mutex mclMutex;


void mclTask(void* param) {
    while (mclThreadRunning) {
        if(mclMutex.take(TIMEOUT_MAX))  {
            updateMCL();
            mclMutex.give();
        }
        pros::delay(20);  
    }
}

*/