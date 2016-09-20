//http://www.glfw.org/documentation.html

#include <GLFW/glfw3.h>
#include <stdlib.h>		  // srand, rand
#include <math.h>

const int width = 640;
const int height = 480;

// color = (Red, Green, Blue)
float *pixels = new float [width * height * 3];
//float *pixels = (float *)malloc(sizeof(float) * width * height * 3);

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}


void drawLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		drawPixel(i, j, red, green, blue);
	}
}

void drawBoldLine(const int& i0, const int& j0, const int& i1, const int& j1, const float& red, const float& green, const float& blue)
{
	for (int i = i0; i <= i1; i++)
	{
		const int j = (j1 - j0)*(i - i0) / (i1 - i0) + j0;

		for (int k = 0; k < 20; k++) {
			drawPixel(i+k, j, red, green, blue);
		}
	}
}

void draw() {

	//배경

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			pixels[(i + width* j) * 3 + 0] = 1.0f;
			pixels[(i + width* j) * 3 + 1] = 1.0f;
			pixels[(i + width* j) * 3 + 2] = 1.0f;
		}
	}
	
	//굵은 대각선
	const int i0 = 50, i1 = 150;
	const int j0 = 350, j1 = 450;
	//drawLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);
	drawBoldLine(i0, j0, i1, j1, 1.0f, 0.0f, 0.0f);


	//빈사각형
	int i_center = 300, j_center = 400;
	int thickness = 50;

	for (int j = j_center - thickness; j < j_center + thickness; j++) {
		for (int i = i_center - thickness; i < i_center + thickness; i++) {
			if (i < ((i_center - thickness) + 10) || i > ((i_center + thickness) - 10)) {
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
			}
			else if (j < ((j_center - thickness) + 10) || j >((j_center + thickness) - 10)) {
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
			}
		}
	}

	//사각형
	i_center = 500;
	j_center = 400;

	for (int j = j_center - thickness; j < j_center + thickness; j++) {
		for (int i = i_center - thickness; i < i_center + thickness; i++) {
			drawPixel(i, j, 1.0f, 0.0f, 0.0f);
		}
	}


	//삼각형
	i_center = 100;
	j_center = 100;
	thickness = 70;
	
	for (int j = j_center - thickness; j < j_center + thickness; j++) {
		for (int i = i_center - thickness + (j / 2); i < i_center + thickness - (j / 2); i++) {
			drawPixel(i, j, 1.0f, 0.0f, 0.0f);
		}
		//thickness--;
	}

	//오각형
	i_center = 500;
	j_center = 100;
	thickness = 70;

	for (int j = j_center - thickness; j < j_center + thickness; j++) {
		for (int i = i_center - thickness + (j / 5); i < i_center + thickness - (j / 5); i++) {
			drawPixel(i, j, 1.0f, 0.0f, 0.0f);
		}
		//thickness--;
	}

	
	//원
	double radius = 0;

	for (int j = 1; j <= 60; j++)
	{
		radius = j;
		for (double i = 0.0; i < 360.0; i += 0.1)
		{
			double angle = i * 3.1415926535897932384626433832795 / 180;

			int x = (int)(300 + radius * cos(angle));
			int y = (int)(100 + radius * sin(angle));

			drawPixel(x, y, 1.0f, 0.0f, 0.0f);
		}
	}

	//


}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// assign all pixels red color
		draw();

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	delete[] pixels;
	// free(pixels);

	return 0;
}