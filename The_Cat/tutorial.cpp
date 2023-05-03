#include "tutorial.h"
void tutorial::load_doc(SDL_Renderer*render,TTF_Font*font,SDL_Color color) {
	char* line= &s[0];
	while (line < &s[s.size() - 1]) {
		SDL_DestroyTexture(doc);
		SDL_Surface* tmp;
		tmp = TTF_RenderText_Solid(font, line, color);
		if (!tmp) {
			cout << "Failed to render text: " << TTF_GetError() << endl;
		}
		doc = SDL_CreateTextureFromSurface(render, tmp);
		rect_doc.w = strlen(line)*size_w;
		SDL_RenderCopy(render,doc, NULL, &rect_doc);
		SDL_FreeSurface(tmp);
		line = line+strlen(line)+1;
		rect_doc.y += size_h;
	}
	rect_doc = { 350,125,0,size_h };
}
tutorial::tutorial() {
	char* line = &s[0];
	char* endl{};
	while (line < &s[s.size() - 1]) {
		endl = min(&s[s.size() - 1], line + 50);
		if (*endl != '\0') {
			endl = find(line, endl, '\n');
			while (*endl != ' ' && *endl != '\n') {
				endl--;
			}
			*endl = '\0';
		}
		line = endl + 1;
	}
}