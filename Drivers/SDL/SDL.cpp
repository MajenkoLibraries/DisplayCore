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
    
    _display = SDL_SetVideoMode(_width, _height, 16, config);
	atexit(SDL_Quit);
	_min_x = _width;
	_min_y = _height;
	_max_x = 0;
	_max_y = 0;
}

void SDL::setPixel(int16_t x, int16_t y, uint16_t c) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return;
    }

	setBound(x, y);

    if (SDL_MUSTLOCK(_display)) 
        if (SDL_LockSurface(_display) < 0) 
            return;

    uint16_t *_buffer = (uint16_t *)_display->pixels;

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

uint16_t SDL::colorAt(int16_t x, int16_t y) {
    if (x < 0 || y < 0 || x >= _width || y >= _height) {
        return 0;
    }

    if (SDL_MUSTLOCK(_display))
        if (SDL_LockSurface(_display) < 0)
            return 0;

    uint16_t *_buffer = (uint16_t *)_display->pixels;

    uint16_t c = _buffer[y * _width + x];

    if (SDL_MUSTLOCK(_display))
        SDL_UnlockSurface(_display);


    return c;
}

uint16_t SDL::getWidth() {
    return _width;
}

uint16_t SDL::getHeight() {
    return _height;
}

boolean SDLTouch::isPressed() {
    return _pressed;
}

uint16_t SDLTouch::x() {
	return _x;
    return (uint16_t)((float)_x * _scale_x) + _offset_x;
}

uint16_t SDLTouch::y() {
	return _y;
    return (uint16_t)((float)_y * _scale_y) + _offset_y;
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

void SDL::fillScreen(uint16_t c) {
    SDL_FillRect(_display, NULL, c);
}

void SDL::fillRectangle(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
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
