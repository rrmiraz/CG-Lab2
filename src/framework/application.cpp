#include "application.h"
#include "utils.h"
#include "image.h"
//
Application::Application(const char* caption, int width, int height)
{
	this->window = createWindow(caption, width, height);

	// initialize attributes
	// Warning: DO NOT CREATE STUFF HERE, USE THE INIT 
	// things create here cannot access opengl
	int w,h;
	SDL_GetWindowSize(window,&w,&h);

	this->window_width = w;
	this->window_height = h;
	this->keystate = SDL_GetKeyboardState(NULL);
    this->framebuffer = new Image(window_width,window_height);
    this->key = 0;
    this->c = Color(255,255,255); //Initialized as white by default
    this->rad = 10;
    this->size = 10;
    this->ux = 0;
    this->uy = 0;
    this->lineDDL = false;
    this->lineB = false;
    this->circle = false;
    this->rectangle = false;
    this->im = new Image(window_width, window_height);
}

//Here we have already GL working, so we can create meshes and textures
void Application::init(void)
{
	std::cout << "initiating app..." << std::endl;

	//here add your init stuff
    key=0;
}

//render one frame
void Application::render(void)
{

    //send image to screen*/
    showImage( framebuffer );
}

//called after render
void Application::update(double seconds_elapsed)
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
    if (keystate[SDL_SCANCODE_0]) //if key 0 is pressed access initial image
	{
        key = 0;
        framebuffer->clearImage();
    }
    else if (keystate[SDL_SCANCODE_1]) //if key 1 is pressed access x10 image
	{
        key = 1;
        framebuffer->clearImage();
	}
    else if (keystate[SDL_SCANCODE_2]) //if key 2 is pressed access the painting tool
    {
        key = 2;
        framebuffer->clearImage();
    }
    else if (keystate[SDL_SCANCODE_3]) //if key 3 is pressed access the painting tool
    {
        key = 3;
        framebuffer->clearImage();
    }
    else if(keystate[SDL_SCANCODE_4])
    {
        c = Color(255,255,0);
        //rad = 10;
    }
    else if(keystate[SDL_SCANCODE_5])
    {
        c = Color(0,0,255);
        //rad = 30;
    }
    else if(keystate[SDL_SCANCODE_6])
    {
        c = Color(51,204,51);
        //rad = 50;
    }
    else if(keystate[SDL_SCANCODE_7])
    {
        c = Color(255,0,0);
        //rad = 70;
    }
    else if (keystate[SDL_SCANCODE_B]) 
    {
        framebuffer->fill(Color(0,0,0));
    }
    else if (keystate[SDL_SCANCODE_O])
    {
        framebuffer->fill(Color(255,165,0));
    }
    else if (keystate[SDL_SCANCODE_R])
    {
        framebuffer->fill(Color(255,0,0));
    }
    else if (keystate[SDL_SCANCODE_G])
    {
        framebuffer->fill(Color(50,205,50));
    }
    else if (keystate[SDL_SCANCODE_W])
    {
        framebuffer->fill(Color(255,255,255));
    }
    if (key == 3){
        if(keystate[SDL_SCANCODE_S]){ 
            size = 2;
        }
        if(keystate[SDL_SCANCODE_M]){ 
            size = 5;
        }
		if (keystate[SDL_SCANCODE_G]) {
			size = 15;
		}
        if(keystate[SDL_SCANCODE_E]){ 
            size = 30;
        }
        if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT)){
            if((mouse_position.x > 20) && (mouse_position.y > 20)){
                for(int i=0; i < size; i++){
                    for(int j=0; j < size; j++){
                        framebuffer->setPixel(mouse_position.x - size/2 + i, mouse_position.y - size/2 - j, this->c);
                    }
                }
            }
        }
    }
}

//keyboard press event 
void Application::onKeyDown( SDL_KeyboardEvent event )
{
	//to see all the keycodes: https://wiki.libsdl.org/SDL_Keycode
    switch(event.keysym.scancode)
    {
        case SDL_SCANCODE_ESCAPE: //if key 0 is pressed access main menu
            exit(0);
            break;
    }
}

//keyboard key up event 
void Application::onKeyUp(SDL_KeyboardEvent event)
{
	//...
}

//mouse button event
void Application::onMouseButtonDown( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse pressed
	{
        if (key == 0){
            if(keystate[SDL_SCANCODE_X])
            {
                lineDDL = true;
                lineB = false;
                circle = false;
                rectangle = false;
                ux = mouse_position.x;
                uy = mouse_position.y;
            }
            else if (keystate[SDL_SCANCODE_C])
            {
                lineB = true;
                circle = false;
                lineDDL = false;
                rectangle = false;
                ux = mouse_position.x;
                uy = mouse_position.y;
            }
            else if (keystate[SDL_SCANCODE_V])
            {
                circle = true;
                lineDDL = false;
                lineB = false;
                rectangle = false;
                ux = mouse_position.x;
                uy = mouse_position.y;
            }
            else
            {
                lineDDL = false;
                lineB = false;
                circle = false;
                rectangle = false;
                framebuffer->setPixel(mouse_position.x, mouse_position.y, Color(0,255,0));
            }
        }
	}
    
}

void Application::onMouseButtonUp( SDL_MouseButtonEvent event )
{
	if (event.button == SDL_BUTTON_LEFT) //left mouse unpressed
	{
        if (key == 0){
            framebuffer->setPixel(mouse_position.x, mouse_position.y, Color(255,0,0));
            
            if((ux!=mouse_position.x || uy != mouse_position.y)&&(lineDDL == true)){
                framebuffer->drawLineDDL(ux, uy, mouse_position.x, mouse_position.y, c);
            }

            if((ux!=mouse_position.x || uy != mouse_position.y)&&(lineB == true)){
                framebuffer->drawLineB(ux, uy, mouse_position.x, mouse_position.y, c);
            }
                
            if((ux!=mouse_position.x || uy != mouse_position.y)&&(circle == true))
            {
                rad = sqrt((ux-mouse_position.x)*(ux-mouse_position.x)+(uy-mouse_position.y)*(uy-mouse_position.y));
                framebuffer->drawCircle(ux, uy, rad, c);
            }
            if((ux!=mouse_position.x || uy != mouse_position.y)&&(rectangle == true)){
                int w = mouse_position.x - ux;
                int h = mouse_position.y - uy;
                framebuffer->drawRectangle(ux, uy, w, h, c);
            }
        }
    }
}

//when the app starts
void Application::start()
{
	std::cout << "launching loop..." << std::endl;
	launchLoop(this);
}
