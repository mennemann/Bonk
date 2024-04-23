#include <stdio.h>
#include <iostream>

#include <GLFW/glfw3.h>

#include "Rigidbody.h"

#include "Vec2.h"
#include "World.h"

using namespace std;



void go(World w) {
    glfwInit();
    GLFWwindow *window = glfwCreateWindow(800, 600, "Bonk", NULL, NULL);
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

    Rigidbody rock = Rigidbody{{0,0},{0,0.5},{0.5,0.5},{0.5,0}};

    w.add(rock);
    go(w);

    return 0;
}