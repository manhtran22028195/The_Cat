#include "background.h"
#include "meo.h"

void backgroundd::loadbackground(SDL_Renderer*&render) {
	loadtexture(render, layer1, "data//image//background.png");
	loadtexture(render, layer2, "data//image//middleground.png");
	loadtexture(render, ground_a, "data//image//ground.png");
	loadtexture(render, ground_b, "data//image//ground-b.png");
	loadtexture(render, house_a, "data//image//house-a.png");
	loadtexture(render, house_b, "data//image//house-b.png");
	loadtexture(render, house_c, "data//image//house-c.png");
	loadtexture(render, street_lamp, "data//image//street-lamp.png");
	loadtexture(render, wagon, "data//image//wagon.png");
	loadtexture(render, well, "data//image//well.png");
}

void backgroundd::reset() {
	vel = 0;
	getpos = { 0,420,240,240 };
	rect_house_a = { 0,248,336,366 };
	rect_house_b = { 400,126,420,488 };
	rect_house_c = { 800,248,442,366 };

	rect_street_lamp = { 0,398,70,216 };
	rect_wagon = { 0,464,186,150 };
	rect_well = { 0,490,130,130 };
	rectground_a = { 0,590,39,117 };
	rectground_b = { 39,590,39,117 };
}

void backgroundd::backgroundupdate(SDL_Renderer*&render)
{
	if (rect1.x >= 1200)
		rect1.x = rect11.x-background_w;
	if (rect11.x >= 1200)
		rect11.x = rect111.x - background_w;
	if (rect111.x >= 1200)
		rect111.x = rect1.x - background_w;
	if (!timer->isPaused())
	{
		rect1.x += 1;
		rect11.x += 1;
		rect111.x += 1;
	}
	SDL_RenderCopy(render, layer1, 0, &rect1);
	SDL_RenderCopy(render, layer1, 0, &rect11);
	SDL_RenderCopy(render, layer1, 0, &rect111);

	//set map follow chacracter

	if (getpos.x > 570 && getpos.x < map_w - 630) {
		vel = -(getpos.x - 570);
	}

	for (int i = 0; i < 4; i++)
	{
		rect2.x =vel/2+i*background_w;
		SDL_RenderCopy(render, layer2, 0, &rect2);
	}

	rect_house_a.x = vel + 0;
	rect_house_b.x = vel + 1500;
	rect_house_c.x = vel + 2500;
	rect_well.x = vel+400;
	rect_wagon.x = vel+700;
	rect_street_lamp.x = vel + 300;
	SDL_RenderCopy(render, house_a, NULL, &rect_house_a);
	SDL_RenderCopy(render, house_b, NULL, &rect_house_b);
	SDL_RenderCopy(render, house_c, NULL, &rect_house_c);
	SDL_RenderCopy(render, street_lamp, NULL, &rect_street_lamp);
	SDL_RenderCopy(render, well, NULL, &rect_well);
	SDL_RenderCopy(render, wagon, NULL, &rect_wagon);

	for (int i = 0; i < 65; i++)
	{
		rectground_a.x = vel + (i * 2) * 39;
		rectground_b.x = vel + (i * 2+1) * 39;
		SDL_RenderCopy(render, ground_a, 0, &rectground_a);
		SDL_RenderCopy(render, ground_b, 0, &rectground_b);
	}
}