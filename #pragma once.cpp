#include <iostream>
#include <cmath>   

class Coin {

public:
   
    Coin(float moveSpeed = 300.0f, float floatHeight = 20.0f, float floatSpeed = 1.0f, float rotationSpeed = 90.0f)
        : MoveSpeed(moveSpeed), FloatHeight(floatHeight), FloatSpeed(floatSpeed), RotationSpeed(rotationSpeed) {
           
            OriginalX = 0.0f;
            OriginalY = 0.0f;
            OriginalZ = 0.0f;
            currentRotation = 0.0f;
    }

    void Update(float deltaTime) {

        OriginalX += MoveSpeed * deltaTime;

        OriginalZ = FloatHeight * sin(FloatSpeed * timeElapsed);

        currentRotation += RotationSpeed * deltaTime;
        
        timeElapsed += deltaTime;
    }

    void PrintPosition() {
        std::cout << "Position: (" << OriginalX << ", " << OriginalY << ", " << OriginalZ << ")\n";
        std::cout << "Rotation: " << currentRotation << " degrees\n";
    }

private:
    float OriginalX, OriginalY, OriginalZ;  
    float MoveSpeed; 
    float FloatHeight;
    float FloatSpeed;
    float RotationSpeed;  
    float timeElapsed = 0.0f;  
    float currentRotation;  
};
