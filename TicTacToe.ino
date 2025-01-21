#include <EloquentTinyML.h>
#include "TicTacToe_model_esp32.h"
#define NUMBER_OF_INPUTS 27  
#define NUMBER_OF_OUTPUTS 2 
#define TENSOR_ARENA_SIZE 5*1024 
Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

void setup() {
    Serial.begin(115200);
    ml.begin(TicTacToe_model_esp32);
}

float fResult[NUMBER_OF_OUTPUTS] = {0};
float fRes = NULL;

void loop() {
    float input1[] = {1.0f, 0.0f, 0.0f, 
                      0.0f, 1.0f, 0.0f, 
                      0.0f, 0.0f, 1.0f, 
                      1.0f, 0.0f, 0.0f, 
                      0.0f, 1.0f, 0.0f, 
                      0.0f, 0.0f, 1.0f, 
                      1.0f, 0.0f, 0.0f, 
                      0.0f, 1.0f, 0.0f, 
                      0.0f, 0.0f, 1.0f};

    float input2[] = {0.0f, 1.0f, 0.0f, 
                      1.0f, 0.0f, 0.0f, 
                      0.0f, 1.0f, 0.0f, 
                      0.0f, 0.0f, 1.0f, 
                      1.0f, 0.0f, 0.0f, 
                      0.0f, 1.0f, 0.0f, 
                      0.0f, 0.0f, 1.0f, 
                      1.0f, 0.0f, 0.0f, 
                      0.0f, 1.0f, 0.0f};

    float input3[] = {1.0f, 0.0f, 0.0f, 
                      0.0f, 0.0f, 1.0f, 
                      0.0f, 1.0f, 0.0f, 
                      1.0f, 0.0f, 0.0f, 
                      1.0f, 0.0f, 0.0f, 
                      0.0f, 1.0f, 0.0f, 
                      1.0f, 0.0f, 0.0f, 
                      0.0f, 0.0f, 1.0f, 
                      1.0f, 0.0f, 0.0f};

    float input4[] = {0.0f, 0.0f, 1.0f, 
                      1.0f, 0.0f, 0.0f, 
                      0.0f, 1.0f, 0.0f, 
                      0.0f, 1.0f, 1.0f, 
                      1.0f, 0.0f, 0.0f, 
                      1.0f, 0.0f, 1.0f, 
                      0.0f, 0.0f, 1.0f, 
                      1.0f, 0.0f, 0.0f,
                      0.0f, 1.0f, 0.0f};

    // Process inputs
    processInput(input1, "input1");
    processInput(input2, "input2");
    processInput(input3, "input3");
    processInput(input4, "input4");

    Serial.println();
    delay(5000);
}

void initfResult(float *fResult){
    for(int i = 0; i < NUMBER_OF_OUTPUTS; i++){
       fResult[i] = 0.0f;
    }
}

void displayOutput(float *fResult){
    for(int i = 0; i < NUMBER_OF_OUTPUTS; i++){
        Serial.print(fResult[i]);
        Serial.print(" ");
    }
}

void processInput(float* input, const char* inputName) {
    initfResult(fResult);
    fRes = ml.predict(input, fResult);
    Serial.print("\nThe output value returned for ");
    Serial.print(inputName);
    Serial.println(":");
    Serial.println(fRes);
    displayOutput(fResult);
}
