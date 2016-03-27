#include <SDL.h>

void SDL::initializeDevice() {
    SDL_Init(SDL_INIT_EVERYTHING);

    int config = SDL_HWSURFACE;
    
    if (_type & Fullscreen) {
        config |= SDL_FULLSCREEN;
    }

    if (_type & Doublebuffer) {
        config |= SDL_DOUBLEBUF;
    }

	const SDL_VideoInfo* info = SDL_GetVideoInfo();
	if (_width == 0) {
		_width = info->current_w;
	}
	if (_height == 0) {
		_height = info->current_h;
	}
    
    _display = SDL_SetVideoMode(_width, _height, 16, config);
	atexit(SDL_Quit);
	_min_x = _width;
	_min_y = _height;
	_max_x = 0;
	_max_y = 0;
}

void SDL::setPixel(int x, int y, color_t c) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return;
    }

	setBound(x, y);

    if (SDL_MUSTLOCK(_display)) 
        if (SDL_LockSurface(_display) < 0) 
            return;

    color_t *_buffer = (color_t *)_display->pixels;

    _buffer[y * _width + x] = c;

    if (SDL_MUSTLOCK(_display)) 
        SDL_UnlockSurface(_display);

    if (!_buffered) {
        SDL_UpdateRect(_display, x, y, 1, 1);
    }
}

void SDL::startBuffer() {
    _buffered++;
}

void SDL::endBuffer() {
    _buffered--;
    if (_buffered <= 0) {
	if (_min_x <= _max_x && _min_y <= _max_y) {
		SDL_UpdateRect(_display, _min_x, _min_y, _max_x - _min_x + 1, _max_y - _min_y + 1);
	}
	_min_x = _width;
	_min_y = _height;
	_max_x = 0;
	_max_y = 0;
	
        _buffered = 0;
    }
}

color_t SDL::colorAt(int x, int y) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return 0;
    }

    if (SDL_MUSTLOCK(_display))
        if (SDL_LockSurface(_display) < 0)
            return 0;

    color_t *_buffer = (color_t *)_display->pixels;

    color_t c = _buffer[y * _width + x];

    if (SDL_MUSTLOCK(_display))
        SDL_UnlockSurface(_display);


    return c;
}

int SDL::getWidth() {
    return _width;
}

int SDL::getHeight() {
    return _height;
}

boolean SDLTouch::isPressed() {
    return _pressed;
}

int SDLTouch::x() {
	return _x;
    return (int)((float)_x * _scale_x) + _offset_x;
}

int SDLTouch::y() {
	return _y;
    return (int)((float)_y * _scale_y) + _offset_y;
}

void SDLTouch::sample() {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
//        SDL_Quit();
        exit(0);
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        _x = event.button.x;
        _y = event.button.y;
        _pressed = true;
    }

    if (event.type == SDL_MOUSEBUTTONUP) {
        _x = event.button.x;
        _y = event.button.y;
        _pressed = false;
    }

    if (event.type == SDL_MOUSEMOTION) {
        _x = event.motion.x;
        _y = event.motion.y;
    }
}

void SDL::fillScreen(color_t c) {
    SDL_FillRect(_display, NULL, c);
}

void SDL::fillRectangle(int x, int y, int w, int h, color_t color) {
    SDL_Rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;

	setBound(x, y);
	setBound(x + w, y + h);

    SDL_FillRect(_display, &r, color);
}

void SDL::flip() {
	SDL_Flip(_display);
}

void SDL::setBound(int x, int y) {
	if (x < _min_x) _min_x = x;
	if (x > _max_x) _max_x = x;
	if (y < _min_y) _min_y = y;
	if (y > _max_y) _max_y = y;
}


void SDL::hideCursor() {
	SDL_ShowCursor(0);
}

void SDL::showCursor() {
	SDL_ShowCursor(1);
}

void SDL::openWindow(int x0, int y0, int x1, int y1) {
    _winx = x0;
    _winy = y0;
    _winw = x1;
    _winh = y1;
    _blitSfc = SDL_CreateRGBSurface(0, _winw, _winh, 16, 0b1111100000000000, 0b11111100000, 0b11111, 0);
    _win_ptr = 0;
    _win_px = 0;
    _win_py = 0;
}

void SDL::windowData(color_t d) {
    SDL_Rect r;
    r.x = _win_px;
    r.y = _win_py;
    r.w = 1;
    r.h = 1;
    SDL_FillRect(_blitSfc, &r, d);
    _win_px++;
    if (_win_px == _winw) {
        _win_py++;
        _win_px = 0;
    }
    if (_win_py == _winh) {
        _winh = 0;
    }
}

void SDL::windowData(color_t *d, int l) {
    SDL_Surface *s = SDL_CreateRGBSurfaceFrom(d, _winw, _winh, 16, _winw*2, 0b1111100000000000, 0b11111100000, 0b11111, 0);
    SDL_Rect r = {0, 0, (uint16_t)_winw, (uint16_t)_winh };
    SDL_BlitSurface(s, NULL, _blitSfc, &r);
    SDL_FreeSurface(s);
}

void SDL::closeWindow() {
    SDL_Rect r = {(int16_t)_winx, (int16_t)_winy, (uint16_t)_winw, (uint16_t)_winh };
    SDL_BlitSurface(_blitSfc, NULL, _display, &r);
    SDL_FreeSurface(_blitSfc);
}
