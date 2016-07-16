#include <DisplayCore.h>
#include <stdarg.h>

Form::Form(int num...) {
    va_list args;
    _size = num;
    _list = (Widget **)malloc(sizeof(Widget) * _size);
    va_start(args, num);
    for (int i = 0; i < _size; i++) {
        _list[i] = va_arg(args, Widget *);
    }

}

Form::~Form() {
    free(_list);
}

void Form::render() {
    for (int i = 0; i < _size; i++) {
        _list[i]->render();
    }
}

void Form::redraw() {
    for (int i = 0; i < _size; i++) {
        _list[i]->redraw();
    }
}

void Form::onPress(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onPress(func);
    }
}

void Form::onRelease(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onRelease(func);
    }
}

void Form::onTap(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onTap(func);
    }
}

void Form::onDrag(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onDrag(func);
    }
}

void Form::onRepeat(void (*func)(Event *)) {
    for (int i = 0; i < _size; i++) {
        _list[i]->onRepeat(func);
    }
}

