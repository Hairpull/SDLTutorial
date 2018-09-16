#include "Graphics.h"

Graphics* Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;


Graphics* Graphics::Instance() {
	if(sInstance == NULL)
		sInstance = new Graphics();
	

	return sInstance;
}


void Graphics::Release(){
	delete sInstance;
	sInstance = NULL;
	
	sInitialized = false;

}


bool Graphics::Initialized() {
	return sInitialized;
}

Graphics::Graphics() {
	
	mBackBuffer = NULL;
	
	sInitialized = Init();
	
}

Graphics::~Graphics(){
	
	
	SDL_DestroyWindow(mWindow);
	mWindow = NULL;
	
	SDL_DestroyRenderer(mRenderer);
	mRenderer = NULL;
	
	IMG_Quit();
	SDL_Quit();
	
}




bool Graphics::Init(){
	
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Initialization error: %s\n", SDL_GetError());
		return false;
	}
	
	
	mWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Graphics::SCREEN_WIDTH, Graphics::SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if(mWindow == NULL) {
		printf("Window creation error: %s\n", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	
	if(mRenderer == NULL) {
		printf("Renderer creation error: %s\n", SDL_GetError());
		return false;
	}
	
	SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);
	
	int flags = IMG_INIT_PNG;
	if(!(IMG_Init(flags) & flags)) {
		
		printf("Image initialization error: %s\n", IMG_GetError());
		return false;
	}
	
	mBackBuffer = SDL_GetWindowSurface(mWindow);
	
	return true;
}


SDL_Texture* Graphics::LoadTexture(std::string path) {
	
	SDL_Texture* tex = NULL;
	
	SDL_Surface* surface = IMG_Load(path.c_str());
	if(surface == NULL ) {
		
		printf("Image load error path:(%s) Error(%s)\n", path.c_str(), IMG_GetError());
		return tex;
	}
	
	tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	if(tex == NULL) {
		
		printf("Create texture error: %s\n", SDL_GetError());
		return tex;
	}
	
	SDL_FreeSurface(surface);
	
	return tex;
	
}


void Graphics::ClearBackBuffer() {
	
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex) {
	
	SDL_RenderCopy(mRenderer, tex, NULL, NULL);
}



void Graphics::Render() {
	
	SDL_RenderPresent(mRenderer);
}


