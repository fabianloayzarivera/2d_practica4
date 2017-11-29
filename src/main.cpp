#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION


#include <glfw3.h>
#include <stb_image.h>
//#include <font.h>
#include <Vec2.h>
#include <list>
//#include <random>
#include <sprite.h>
using namespace std;

ltex_t *createTexture(const char *filename, int *width, int *height);

int main() {

	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);
	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, false);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}
	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);
	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

	int widthBee		= 640;
	int heightBee		= 92;
	Sprite beeSprite	= Sprite(createTexture("./data/bee_anim.png", &widthBee, &heightBee), 8, 1);
	beeSprite.setPosition(Vec2(0, 0));
	beeSprite.setBlend(BLEND_ALPHA);
	beeSprite.setFps(8);
	int beeFrame;
	float frame = 0;
	double lastTime = glfwGetTime();
	double xposMouse = 0;
	double yposMouse = 0;
	double xposDelayed = 0;
	double yposDelayed = 0;
	Vec2 updatedPos;
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);
		lgfx_clearcolorbuffer(0, 0, 0);

		//ltex_drawrotsized(beeSprite->getTexture(), 0, 0, 0, 0, 0, widthBee, heightBee, 0, 0, 1, 1);		
		//ltex_draw(beeSprite->getTexture(), 0, 0);

		glfwGetCursorPos(window, &xposMouse, &yposMouse);
		Vec2 mousePos = Vec2(xposMouse, yposMouse);
		/*xposDelayed += xposMouse * 128 * deltaTime;
		yposDelayed += yposMouse * 128 * deltaTime;*/
		/*xposDelayed += beeSprite.getPosition().x;
		yposDelayed += beeSprite.getPosition().y;*/
		updatedPos = Vec2(xposDelayed, yposDelayed);
		beeSprite.setPosition(mousePos);
		
		beeSprite.update(deltaTime);
		beeSprite.draw();
		
		
		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();


	}

	return 0;
}

ltex_t* createTexture(const char *filename, int *width, int *height) {

	unsigned char* buffer = stbi_load(filename, width, height, nullptr, 4);

	if (buffer != NULL) {
	}
	else {
		cout << "buffer empty";
	}

	ltex_t* tex = ltex_alloc(*width, *height, 0);

	ltex_setpixels(tex, buffer);

	stbi_image_free(buffer);

	return tex;
	//ltex_free(ltex_t* tex);

}

