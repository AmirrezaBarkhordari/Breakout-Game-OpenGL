#include <glew.h>
#include <freeglut.h>
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#pragma comment(lib, "glew32.lib")

#define p 3.1415f
using namespace std;

float offsetX = 0.0,
offsetY = 400.0f,
rocketWidth = 100.0f,
rocketY = 50.0f;
float offsetRocket =0.0f;
float radius = 20.0f;
float speed = 10.0f;
float jahatVahedX = -0.5f,
jahatVahedY = -0.5f;
float velocityX;
float velocityY;
float savedVelocityX = 0.0f;
float savedVelocityY = 0.0f;
bool isHitted = false;
bool isAlive = true;
bool isStopped = false;
bool playIconshow = false;
int id = 0;
bool entered = false;
bool won = false;
string menuQ = "Quit";
string menuR = "Restart";
string scoreText = "Score: ";
int score = 0;
float rr = 1.0f, rg = 1.0f, rb = 0.5f;
float qr = 1.0f, qg = 1.0f, qb = 0.5f;
struct Brick
{
	float x;
	float y;
	float w;
	float h;
	bool alive;
};
float payefesh = 0;
vector<Brick> bricks;

float clamp(float v, float low, float high)
{
	if (v < low)
	{
		return low;
	}
	else if (v > high)
	{
		return high;
	}
	else
	{
		return v;
	}
}

//void celebratePayeFeshfeshe()
//{
//	glColor3f(0.7f, 0.2f, 1.0f);
//	glPointSize(10);
//	glBegin(GL_POINTS);
//	glVertex2f(0.0f ,payefesh);
//	glEnd();
//}
//void celebrateFeshfeshe()
//{
//	glColor3f(0.7f, 0.2f, 1.0f);
//	glPointSize(5);
//	for (int i = 300; i >= 0; i -= 10)
//	{
//		glBegin(GL_POINTS);
//		for (int j = 0; j <= 50; j++)
//		{
//			float a = (2.0f * p) * (float(j) / 50.f);
//			float x = i * cosf(a);
//			float y = i * sinf(a);
//			glVertex2i(x, y+600);
//
//		}
//		glEnd();
//	}
//}

//void animFesh(int v)
//{
//
//	if (payefesh <= 600) {
//		payefesh += 10;
//	}
//	glutTimerFunc(30, animFesh, 0);
//
//}

void drawText(string text, float x, float y, float r = 0, float g = 0, float b = 0) {
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	for (int i = 0; text[i] != '\0'; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[i]);
	}
}

void menu() 
{

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex2f(-250, 300);
	glVertex2f(250, 300);
	glVertex2f(250, 450);
	glVertex2f(-250, 450);
	glEnd();

	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex2f(-250, 550);
	glVertex2f(250, 550);
	glVertex2f(250, 700);
	glVertex2f(-250, 700);
	glEnd();
}

void drawBricks() {
	glColor3f(0.2f, 0.2f, 0.8f);
	glBegin(GL_QUADS);
	for (auto& b : bricks) {
		if (!b.alive) continue;
		glVertex2f(b.x, b.y);
		glVertex2f(b.x + b.w, b.y);
		glVertex2f(b.x + b.w, b.y + b.h);
		glVertex2f(b.x, b.y + b.h);
	}
	glEnd();
}

void brickss()
{

	bricks.clear();
	for (float i = -200.0f; i < 200.0f; i += 60.0f) {
		for (float j = 500.0f; j < 850.0f; j += 45.0f) {
			Brick b;
			b.x = i;
			b.y = j - 10.0f;
			b.w = 50.0f;
			b.h = 35.0f;
			b.alive = true;
			bricks.push_back(b);
		}
	}


}

void stopIcon()
{
	glColor3f(0.2f, 1.0f, 0.2f);
	glLineWidth(8);
	glBegin(GL_LINES);
	glVertex2f(460, 950);
	glVertex2f(460, 980);

	glVertex2f(480, 950);
	glVertex2f(480, 980);
	glEnd();

}

void playIcon()
{
	glColor3f(0.2f, 1.0f, 0.2f);
	glBegin(GL_TRIANGLES);
	glVertex2f(460, 950);
	glVertex2f(460, 980);
	glVertex2f(480, 965);
	glEnd();
}

void rocket(float x1, float y1, float x2, float y2)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(10);
	glBegin(GL_LINES);
	x1 += offsetRocket;
	x2 += offsetRocket;
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}

void ball(float r)
{
	glColor3f(1.0f, 0.5f, 0.2f);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i <= 360; i++)
	{
		float angle = 2.0f * p * (i / 360.0f);
		float x = r * cos(angle);
		float y = r * sin(angle);
		glVertex2f(x + offsetX, y + offsetY);
	}
	glEnd();
}

void restartGame()
{
	isAlive = true;
	won = false;
	score = 0;
	offsetX = 0.0f;
	offsetY = 100.0f;
	offsetRocket = 0.0f;
	velocityX = speed * jahatVahedX;
	velocityY = speed * jahatVahedY;
	brickss();
	entered = false;
}

void drawScene()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawText(scoreText + to_string(score), -480, 960, 1.0f, 0.0f, 0.0f);
	if (isAlive and not won)
	{
		
		rocket(-rocketWidth / 2, rocketY + 20, rocketWidth / 2, rocketY + 20);
		ball(radius);
		drawBricks();
	}
	else if (!isAlive and not won)
	{
		drawText("YOU LOSE :(", -100, 800, 1.0f, 0.2f, 0.3f);
		menu();
		int selected = id % 2;

		if (selected == 0)
			drawText(menuR, -40, 620, 1.0f, 0.2f, 0.3f);
		else
			drawText(menuR, -40, 620, 1.0f, 1.0f, 0.3f);

		if (selected == 1)
			drawText(menuQ, -30, 370, 1.0f, 0.2f, 0.3f);
		else
			drawText(menuQ, -30, 370, 1.0f, 1.0f, 0.3f);
	}

	if (isStopped) {
		playIcon();
		/*celebrate();*/
		//celebratePayeFeshfeshe();
		//animFesh(0);
	}
	else
	{
		stopIcon();
	}

	if (score >= (int)bricks.size())
	{
		drawText("YOU WIN :)", -100, 800, 0.2f, 1.0f, 0.3f);
		won = true;
		menu();
		int selected = id % 2;
		if (selected == 0)
			drawText(menuR, -40, 620, 1.0f, 0.2f, 0.3f);
		else
			drawText(menuR, -40, 620, 1.0f, 1.0f, 0.3f);
		if (selected == 1)
			drawText(menuQ, -30, 370, 1.0f, 0.2f, 0.3f);
		else
			drawText(menuQ, -30, 370, 1.0f, 1.0f, 0.3f);
	}
	glutSwapBuffers();
}

void ballAndBricks()
{
	for (auto& b : bricks)
	{
		if (!b.alive)
			continue;
		float closestbX = clamp(offsetX, b.x, b.x + b.w);
		float closestbY = clamp(offsetY, b.y, b.y + b.h);
		float dx = offsetX - closestbX;
		float dy = offsetY - closestbY;
		float dis = hypot(dx, dy);
		if (dis <= (radius))
		{
			b.alive = false;
			if (fabsf(dx) > fabsf(dy))
				velocityX = -velocityX;
			else
				velocityY = -velocityY;
			score++;

		}
	}
}

void ballAndRocketUpdateCode()
{
	offsetX += velocityX;
	offsetY += velocityY;
	// wall
	if (offsetX - radius < -500)
	{
		velocityX = -velocityX;
	}
	if (offsetX + radius > 500)
	{
		velocityX = -velocityX;
	}
	if (offsetY - radius < 0)
	{
		velocityY = -velocityY;
	}
	if (offsetY + radius > 1000)
	{
		velocityY = -velocityY;
	}
	// rocket 
	float closestX = clamp(offsetX, -rocketWidth / 2 + offsetRocket, rocketWidth / 2 + offsetRocket);
	float closestY = clamp(offsetY, rocketY + 20, rocketY + 20);
	float distanceX = offsetX - closestX;
	float distanceY = offsetY - closestY;
	float dis = hypot(distanceX, distanceY);

	if (dis < radius && velocityY < 0.0f)
	{
		float paddleCenterX = offsetRocket;
		float rel = (offsetX - paddleCenterX) / (rocketWidth * 0.5f);
		rel = clamp(rel, -1.0f, 1.0f);

		float currentSpeed = hypot(velocityX, velocityY);
		if (currentSpeed <= 0.0f) currentSpeed = speed;

	    float maxBounceAngle = 75.0f * (p / 180.0f);
		float angle = rel * maxBounceAngle;

		velocityX = currentSpeed * sinf(angle);
		velocityY = currentSpeed * cosf(angle);

		offsetY = rocketY + 20 + radius + 0.1f;
	}

	if (offsetY + radius < rocketY) {
		isAlive = false;
	}

	ballAndBricks();
}

void update(int v)
{
	//if (isStopped)
	//{
	//	celebratePayeFeshfeshe();
	//}
	if (isAlive && !isStopped) {
		ballAndRocketUpdateCode();
		glutPostRedisplay();
	}
	if (payefesh <= 600) {
		payefesh += 10;
	}
	glutTimerFunc(16, update, 0);
}

void keyBoard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 13:
		if (!isAlive or won)
		{
			int selected = id % 2;
			if (selected == 0)
				restartGame();
			else
				exit(0);
		}
		 break;
	case 'p':
	case 'P':
		if (!isAlive) break;
		if (!isStopped)
		{
			isStopped = true;
			savedVelocityX = velocityX;
			savedVelocityY = velocityY;
			velocityX = 0.0f;
			velocityY = 0.0f;
			
		}
		else if (isStopped)
		{
			isStopped = false;
			velocityX = savedVelocityX;
			velocityY = savedVelocityY;
		}
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		offsetRocket -= 20;
		break;
	case 'd':
	case 'D':
		offsetRocket += 20;
		break;
	default:
		break;
	}
	float minX = -500.0f + rocketWidth / 2.0f;
	float maxX = 500.0f - rocketWidth / 2.0f;
	offsetRocket = clamp(offsetRocket, minX, maxX);
	glutPostRedisplay();
	
}

void specialKeyboard(int key, int x, int y)
{
	if (!isAlive or won)
	{
		switch (key)
		{
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			id++; 
			break;
		default:
			break;
		}
		glutPostRedisplay();
		return;
	}

	if (isStopped or won ) return;

	switch (key)
	{
	case GLUT_KEY_LEFT:
		offsetRocket -= 20;
		break;
	case GLUT_KEY_RIGHT:
		offsetRocket += 20;
		break;
	default:
		break;
	}
	float minX = -500.0f + rocketWidth / 2.0f;
	float maxX = 500.0f - rocketWidth / 2.0f;
	offsetRocket = clamp(offsetRocket, minX, maxX);
	glutPostRedisplay();
}

void setup()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	velocityX = speed * jahatVahedX;
	velocityY = speed * jahatVahedY;
	brickss();

}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-500, 500, 0, 1000, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(800, 650);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Pong");
	glewInit();
	
	setup();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(keyBoard);
	glutSpecialFunc(specialKeyboard);
	glutReshapeFunc(resize);
	glutTimerFunc(0, update, 0);
	//glutTimerFunc(0, animFesh, 0);
	glutMainLoop();
	return 0;

}



