#include <glew.h>
#include <glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <Windows.h>

const float PI = 3.1415926f;


struct Sphere {
    float centrx, centry, centrz, radius;//координаты центра и радиус сферы
    std::vector<float> verticies = {};
    void build(float x, float y, float z, float r) {

        this->centrx = x;
        this->centry = y;
        this->centrz = z;
        this->radius = r;
        verticies.clear();
        for (int i = 0; i < 20; i++) {//вычисление вершин на сфере
            for (int j = 0; j < 20; j++) {
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);
                j++;
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);
                i++;
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);

                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);
                j--;
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);
                i--;
                verticies.push_back(cosf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centrx);
                verticies.push_back(sinf(PI * float(i) / 10.0f) * radius * sinf(float(j) * PI / 10.0f) + centry);
                verticies.push_back(cosf(PI * float(j) / 10.0f) * radius + centrz);

            }
        }

    }
    void draw() {//вывод сферы на экран
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, verticies.data());
        glDrawArrays(GL_TRIANGLES, 0, verticies.size() / 3);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
};

int main(void)
{
    GLFWwindow* window;
    if (!glfwInit())
        return -1;
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Glew is not ok\n";
    }
    Sphere earth, moon;
    earth.build(0.0f, 0.0f, -0.5f, 0.125f);
    glViewport(0, 0, 640, 480);
    glEnable(GL_DEPTH_TEST);
    float fi = 0;//угол, который задает точку на орбите
    float fang, sang, r, speed;//угол вращения относительно экватора, радиус орбиты, скорость вращения
    std::cout << "Insert orbit radius (from 0 to 0.5)\n";
    std::cin >> r;
    std::cout << "Insert moon speed (angle per frame)\n";
    std::cin >> speed;
    std::cout << "Insert equator angle\n";
    std::cin >> fang;
    std::cout << "Insert grinvich angle\n";
    std::cin >> sang;
    speed = speed / 360;
    fang *= 2 * PI / 360;
    sang *= 2 * PI / 360;
    fi = sang;
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3ub(255, 0, 0);
        earth.draw();
        glColor3ub(0, 255, 0);
        fi += PI * speed;
        fi = fmod(fi, 2 * PI);
        moon.build(earth.centrx + cosf(fi) * cosf(sang) * r,
            earth.centry + sinf(fi) * sinf(fang)* r,
            earth.centrz + sinf(fi) * cosf(fang) * sinf(sang) * r,
            0.0625f);
        moon.draw();
        Sleep(17);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}