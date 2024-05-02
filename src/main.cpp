#define _USE_MATH_DEFINES
#include <stdio.h>
#include <iostream>

#include <GLFW/glfw3.h>

#include "Rigidbody.h"
#include <math.h>
#include "Vec2.h"
#include "World.h"
#include <ctime>
#include <stdlib.h>

using namespace std;



void go(World w) {
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(800, 800, "Bonk", NULL, NULL);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        
        w.step();
        w.render();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

int main(void) {
    srand((unsigned int)time(NULL));
    auto w = World();


    Rigidbody a = Rigidbody{{-5,-5},{5,-5},{5,5},{-5,5}};
    Rigidbody b = Rigidbody{{-5,-5},{5,-5},{5,5},{-5,5}};
    a.position = {-90,0};
    b.position = {90,-8};
    a.velocity={-70 + (rand()%140),0};
    b.velocity={-70 + (rand()%140),0};
    a.inertia=5;
    b.inertia=5;

    a.ang_velocity = -5+(rand()%10);
    b.ang_velocity = -5+(rand()%10);

    w.add(a);
    w.add(b);
    go(w);

    return 0;
}