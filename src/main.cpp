#define _USE_MATH_DEFINES
#include <stdio.h>
#include <iostream>

#include <GLFW/glfw3.h>

#include "Rigidbody.h"
#include <math.h>
#include "Vec2.h"
#include "World.h"

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

    auto w = World();

    Rigidbody rock = Rigidbody{{-20,10},{0,10},{0,30},{-20,30}};
    rock.setColor(1, 1, 0.2);

    //rock.velocity = Vec2(100,500);
    rock.torque = -0.1;
    rock.ang_velocity = 1;
    rock.force = Vec2(0,-10);

    w.add(rock);
    go(w);

    return 0;
}