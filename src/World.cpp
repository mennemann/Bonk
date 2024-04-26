#define _USE_MATH_DEFINES
#include "World.h"
#include "Intersections.h"
#include <stdint.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <chrono>
#include <math.h>
#include <set>
#include <algorithm>

using namespace std;


World::World() {
    this->last_step = this->currentTime();
}

chrono::high_resolution_clock::time_point World::currentTime() {
    return chrono::high_resolution_clock::now();
}

void World::add(Rigidbody obj) {
    this->objects.push_back(obj);
}


vector<intersection> intersections;

void World::step() {
    auto delta_time_ns = currentTime() - this->last_step;
    this->last_step = currentTime();

    auto delta_time = delta_time_ns.count()/1e9;


    for (Rigidbody& obj : this->objects) {
        obj.velocity += obj.force*(1/obj.mass)*delta_time;
        obj.position += obj.velocity*delta_time;

        obj.ang_velocity += obj.torque/obj.mass*delta_time;
        obj.angle += obj.ang_velocity*delta_time;
    }



    int i,j,N;
    N = this->objects.size();

    auto mm = (struct max_min*)malloc(N*sizeof(struct max_min));
    for (i = 0; i<N; i++) mm[i] = this->objects[i].getMaxMin();

    set<Rigidbody*> might_bonk;

    for (i = 0; i < N; i++) {
        for (j = 0; j<N; j++) {
            if (i==j) continue;
            if(!(mm[i].max_x > mm[j].min_x && mm[j].max_x > mm[i].min_x) || !(mm[i].max_y > mm[j].min_y && mm[j].max_y > mm[i].min_y)) continue;
            
            might_bonk.insert(&this->objects[i]); 
            might_bonk.insert(&this->objects[j]); 
        }
    }

    free(mm);
    
    intersections.clear();
    if (might_bonk.size()>0) {
        vector<Rigidbody*> m_b(might_bonk.begin(), might_bonk.end());
        
        intersections = get_intersections(m_b);
        intersections.erase(unique(intersections.begin(), intersections.end()), intersections.end());
    }


    for (Rigidbody& obj : this->objects) {
        for (auto v : obj.getVertices()) {
            if (v.y < -100) {
                obj.velocity.y = abs(obj.velocity.y);
                obj.position.y += abs(v.y+100);
                break;
            }
            if (v.y > 100) {
                obj.velocity.y = -abs(obj.velocity.y);
                obj.position.y -= abs(v.y-100);
                break;
            }
            if (v.x < -100) {
                obj.velocity.x = abs(obj.velocity.x);
                obj.position.x += abs(v.x+100);
                break;
            }
            if (v.x > 100) {
                obj.velocity.x = -abs(obj.velocity.x);
                obj.position.x -= abs(v.x-100);
                break;
            }
        }
    }

}


void World::render(GLFWwindow *window) {
    for (Rigidbody obj : this->objects) {
        glBegin(GL_POLYGON);
        glColor3f(obj.color[0],obj.color[1],obj.color[2]);
        for (Vec2 v : obj.getVertices()) {
            glVertex2d(v.x/100,v.y/100);
        }
        glEnd();





        Vec2 center = obj.getCenter();
        glBegin(GL_POLYGON);
        glColor3f(0,1,1);
        glVertex2d((center.x-3)/100,(center.y-3)/100);
        glVertex2d((center.x+3)/100,(center.y-3)/100);
        glVertex2d((center.x+3)/100,(center.y+3)/100);
        glVertex2d((center.x-3)/100,(center.y+3)/100);
        glEnd();

    }

    for (auto p : intersections) 
        {
            glBegin(GL_POLYGON);
            glColor3f(0,1,0);
            glVertex2d((p.p.x-1)/100,(p.p.y-1)/100);
            glVertex2d((p.p.x+1)/100,(p.p.y-1)/100);
            glVertex2d((p.p.x+1)/100,(p.p.y+1)/100);
            glVertex2d((p.p.x-1)/100,(p.p.y+1)/100);
            glEnd();
        }

    glfwSwapBuffers(window);

    if (intersections.size()>2) {
        cout << intersections.size() << endl;
        for (auto p: intersections) cout << p.p << endl;
    }
}