#include <iostream>
#include <raylib.h>
#include <raymath.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include <cmath>

#define WIDTH 800
#define HEIGHT 600
#define SCALE 20
#define GRAVITY 9.8f

float cosd(float degrees) {
    return std::cosf(degrees * M_PI / 180.0f);
}

float sind(float degrees) {
    return std::sinf(degrees * M_PI / 180.0f);
}
float tand(float degrees) {
    return std::tanf(degrees * M_PI / 180.0f);
}

class Object {
    public:
    //initial variables
    Vector2 Position;
    float Force; // m/s
    float InitialAngle; // Degrees
    //Variables
    float T;
    float range;
    float maxHeight;
    float VelocityX;
    float VelocityY;
    //Constructor
    Object (Vector2 Position,float Force, float initialAngle) {
        this->Position = Position;
        this->Force = Force;
        this->InitialAngle = initialAngle;
    }
    //Get all the values, should be executed in the Update func
    void CalculateValues() {
        VelocityX = Force * cosd(InitialAngle);
        VelocityY = Force * sind(InitialAngle);
        T = (2 * Force * sind(InitialAngle)) / GRAVITY;
        range = VelocityX * T;
        maxHeight = (VelocityY * VelocityY) / (2*GRAVITY);

    }
    //Calculates and displays the trajectory
    void Update() {
        CalculateValues();
        for (float x = 0; x < 10;) {
            float x_world = VelocityX * x;
            float y_world = VelocityY * x - 0.5f * GRAVITY * x * x;

            float x_screen = Position.x + (x_world * SCALE);
            float y_screen = Position.y - (y_world * SCALE);
            if (y_screen <= HEIGHT) {
                DrawCircle(x_screen, y_screen, 1, RED);
                DrawCircle(Position.x, Position.y, 50, BLUE);
                x = x + 0.001;
                continue;
            }
            return;

        }
    }
    // Creates 2 sliders and sets one for the force and one for the angle
    void GetValues() {

        GuiSlider(
            (Rectangle){50,50,200,20},
            "Force:",
            TextFormat("%.2f", Force),
            &Force,
            0,
            100);
        GuiSlider(
            (Rectangle){50,10,200,20},
            "Angle: ",
            TextFormat("%.2f", InitialAngle),
            &InitialAngle,
            0,
            90
        );
    }
    void ShowValues() {
        char* AngleString;
        char* VelocityXString;
        char* VelocityYString;
        char* MaxHeightString;
        char* RangeString;
        char* TimeString;
        asprintf(&AngleString, "Angle: %.2f", InitialAngle);
        asprintf(&VelocityXString, "VelocityX: %.2f", VelocityX);
        asprintf(&VelocityYString, "VelocityY: %.2f", VelocityY);
        asprintf(&MaxHeightString, "Max Height: %.2f", maxHeight);
        asprintf(&RangeString, "Range: %.2f", range);
        asprintf(&TimeString, "Time: %.2f", T);

        DrawText(VelocityXString,50,100, 21, BLACK);
        DrawText(VelocityYString,50,125, 21, BLACK);
        DrawText(AngleString,50,150, 21, BLACK);
        DrawText(MaxHeightString,50,175, 21, BLACK);
        DrawText(RangeString,50,200, 21, BLACK);
        DrawText(TimeString,50,225, 21, BLACK);

        free(AngleString);
        free(VelocityXString);
        free(VelocityYString);
        free(MaxHeightString);
        free(RangeString);
        free(TimeString);
    }
    //Debug function: displays in the terminal all the variables that gets calculated
    void ShowCalcs() {
        float VelocityX = Force * cosd(InitialAngle);
        float VelocityY = Force * sind(InitialAngle);
        T = (2 * Force * sind(InitialAngle)) / GRAVITY;
        float maxHeight = (VelocityY * VelocityY) / (2*GRAVITY);
        range = VelocityX * T;
        std::cout << "Max time: " << T << "\n";
        std::cout << "Max height: " << maxHeight << "\n";
        std::cout << "Force: " << Force << " Angle: " << InitialAngle << std::endl;
        std::cout << "VelocityX: " << VelocityX << " VelocityY: " << VelocityY << std::endl;
    }
};



int main() {

    InitWindow(WIDTH, HEIGHT, "Trayectory");

    Object obj = Object({100,500}, 0, 0);

    while (!WindowShouldClose()) {
        obj.GetValues();
        obj.CalculateValues();
        BeginDrawing();
        ClearBackground(RAYWHITE);
        obj.Update();
        obj.ShowValues();
        EndDrawing();
    }
    return 0;

}