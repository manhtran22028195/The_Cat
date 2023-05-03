#include "mainfunction.h"

    void init(SDL_Window*& window, SDL_Renderer*& render, TTF_Font*& font)
	{
		SDL_Init(SDL_INIT_VIDEO);
		SDL_Init(SDL_INIT_AUDIO);
		SDL_Init(MIX_INIT_MP3);
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		}
		TTF_Init();
		window = SDL_CreateWindow("the cat", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 700, SDL_WINDOW_SHOWN);
		render = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED);
		font = TTF_OpenFont("data//font//font2.ttf", 16);
	}

	void load_icon(SDL_Window* window, string path) {
		SDL_Surface* icon{};
		icon=IMG_Load(path.c_str());
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}

 	void loadtext(TTF_Font* font, SDL_Texture*& texture,SDL_Renderer *render,string s,SDL_Color color) {
		SDL_DestroyTexture(texture);
		SDL_Surface* tmp;
		tmp=TTF_RenderText_Solid(font, s.c_str(),color);
		if (tmp == NULL) {
			std::cout << "Failed to render text: " << TTF_GetError() << endl;
		}
		texture = SDL_CreateTextureFromSurface(render, tmp);
		SDL_FreeSurface(tmp);
	}

	void loadtexture(SDL_Renderer* render, SDL_Texture*& texture, string path)
	{
		texture = IMG_LoadTexture(render, path.c_str());
		if (texture == NULL)
			std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
	}

	void quit(SDL_Window* window, SDL_Renderer* render)
	{
		if(SDL_PollEvent(&e))
		if(e.type==SDL_QUIT)
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(render);
	}
	bool check_collision(SDL_Rect a, SDL_Rect b) {
		bool overlap_x = (a.x < (b.x + b.w)) && ((a.x + a.w) > b.x);
		bool overlap_y = (a.y < (b.y + b.h)) && ((a.y + a.h) > b.y);
		return overlap_x && overlap_y;
	}

	bool check_bullet_collision(SDL_Rect k, SDL_Rect h,float step_x,float step_y) {
		newrect a = { k.x,k.y,k.w,k.h };
		newrect b = { h.x,h.y,h.w,h.h };
		for (int i = 0; i < 5; i++) {
			bool overlap_x = (a.x < (b.x + b.w)) && ((a.x + a.w) > b.x);
			bool overlap_y = (a.y < (b.y + b.h)) && ((a.y + a.h) > b.y);
			return overlap_x && overlap_y;
			b.x+=step_x / 5; b.y += step_y / 5;
		}
		return 0;
	}

	void e_move(SDL_Rect get_c_pos, int delta_c_pos, SDL_Rect& e_pos, int vel_x,int distance) {
		if (abs(delta_c_pos) > 12)
			delta_c_pos = 0;
		if (get_c_pos.x> 570 && get_c_pos.x < map_w - 630) {
			{
				if (600+distance < e_pos.x +e_pos.w/2) {
					e_pos.x -= vel_x;
				}
				else if (600-distance > e_pos.x +e_pos.w/2)
				{
					e_pos.x += vel_x;
				}
				e_pos.x += delta_c_pos;
			}
		}
		else if (get_c_pos.x <= 570) {
			if (get_c_pos.x+get_c_pos.w/2 + distance < e_pos.x +e_pos.w/2) {
				e_pos.x -= vel_x;
			}
			else if (get_c_pos.x+get_c_pos.w/2 - distance > e_pos.x +e_pos.w/2)
			{
				e_pos.x += vel_x;
			}
		}
		else
		{
			if ((get_c_pos.x+get_c_pos.w/2 - (map_w - 1200)) + distance < e_pos.x +e_pos.w/2) {
				e_pos.x -= vel_x;
			}
			else if (get_c_pos.x+get_c_pos.w/2 - (map_w - 1200) - distance > e_pos.x +e_pos.w/2)
			{
				e_pos.x += vel_x;
			}
		}
	}
	void pause_screen(SDL_Renderer* render, SDL_Texture*& texture) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
		SDL_Surface* surface = SDL_CreateRGBSurface(0, window_w, window_h, 32, 0, 0, 0, 0);
		SDL_RenderReadPixels(render, NULL, surface->format->format, surface->pixels, surface->pitch);
		texture = SDL_CreateTextureFromSurface(render, surface);
		SDL_FreeSurface(surface);
	}
	bool cooldown(int previuos_time, unsigned int delay_time,Timer *&time) {
		return int(time->getTicks()) > previuos_time + delay_time;
	}