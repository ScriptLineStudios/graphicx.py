#include <Python.h>
#include <assert.h>

int WIDTH;
int HEIGHT; 

#define CHANNELS 1

static PyObject *surf_clear(PyObject *self, PyObject *args) {
    PyObject *bufobj;
    if(!PyArg_ParseTuple(args, "O", &bufobj))
        return NULL;

    char *bytebuffer = PyBytes_AsString(bufobj);
    for (int i = 0; i < WIDTH * HEIGHT * CHANNELS; i++) {
        bytebuffer[i] = 1;
    }
    PyObject *pbo = PyBytes_FromString(bytebuffer);
    return pbo;
}

static PyObject *surf_load(PyObject *self, PyObject *args) {
    int width;
    int height;

    if(!PyArg_ParseTuple(args, "(ii)", &width, &height))
        return NULL;

    WIDTH = width;
    HEIGHT = height;

    PyObject *pbo = PyBytes_FromStringAndSize(NULL, WIDTH * HEIGHT * CHANNELS);
    char *bytebuffer = PyBytes_AsString(pbo);
    for (int i = 0; i < WIDTH * HEIGHT * CHANNELS; i++) {
        bytebuffer[i] = 1;
    }
    pbo = PyBytes_FromString(bytebuffer);
    return pbo;
}

char *_set_pixel(char *bytebuffer, int pos, int r, int g, int b) {
    bytebuffer[pos] = r;
    bytebuffer[pos+1] = g;
    bytebuffer[pos+2] = b;
}

static PyObject *set_pixel(PyObject *self, PyObject *args) {
    PyObject *bufobj;
    int x;
    int y;
    int r;
    int g;
    int b;

    if(!PyArg_ParseTuple(args, "O(ii)(iii)", &bufobj, &x, &y, &r, &g, &b))
        return NULL;
    
    x *= CHANNELS;
    y *= CHANNELS;

    int pos = y * WIDTH + x;

    char *bytebuffer = PyBytes_AsString(bufobj);
    bufobj = PyBytes_FromString(_set_pixel(bytebuffer, pos, r, g, b));
    return bufobj;
}

void memory_set(char *buffer, int val, int end_pos, int stride) {
    for (int i = 0; i < end_pos; i+=stride) {
        buffer[i] = val;
    }
}

void *my_memset(void *s, int c,  unsigned int len)
{
    unsigned char* p=s;
    while(len--)
    {
        *p++ = (unsigned char)c;
    }
    return s;
}

char *_draw_line(char *bytebuffer, int pos, int end_pos, int r, int g, int b) {
    memory_set(bytebuffer+pos, r, end_pos, 3);
    memory_set(bytebuffer+pos, g, end_pos, 3);
    memory_set(bytebuffer+pos, b, end_pos, 3);

    //memset(bytebuffer+pos, r, end_pos);
    //memset(bytebuffer+pos, g, end_pos+3);
    //memset(bytebuffer+pos, b, end_pos+6);

}

static PyObject *draw_rect(PyObject *self, PyObject *args) {
    PyObject *bufobj;
    int x;
    int y;
    int w;
    int h;

    int r;
    int g;
    int b;

    if(!PyArg_ParseTuple(args, "O(iiii)(iii)", &bufobj, &x, &y, &w, &h, &r, &g, &b))
        return NULL;
    
    char *bytebuffer = PyBytes_AsString(bufobj);
    x *= CHANNELS;
    y *= CHANNELS;
    

    int start_pos = y * WIDTH + x;
    int end_pos =   ((y) + (h * CHANNELS) - CHANNELS) * WIDTH + ((x) + (w * CHANNELS) - CHANNELS);

    int start_pos2 = (y + 3) * WIDTH + x;
    int end_pos2 =  (y + 3) * WIDTH + ((x) + (w * CHANNELS) - CHANNELS);

    int count = 1;
    int offbeats = 0;
    for (int i = start_pos; i <= end_pos; i+=CHANNELS) {
        if (count <= w) _set_pixel(bytebuffer, i, r, g, b);
        else offbeats++;
        if (offbeats >= (WIDTH - w)) {offbeats = 0; count = 0;}
        count++;
    }

    // for (int i = 0; i < h*6; i+=6) {
    //     _draw_line(bytebuffer, i*300, 1000, r, g, b);
    // }
    //_draw_line(bytebuffer, 6*300, 1000, 0, 100, 100);
    //_draw_line(bytebuffer, 12*300, 1000, 0, 100, 100);

      //  _draw_line(bytebuffer, 1800, 1000, 300, 100, 100);
      //  _draw_line(bytebuffer, 3600, 1000, 300, 100, 100);
    //} 

    //TODO: Instead of 2 for loops (slow) calculate the pointer range that needs modifying
    // for (int _y = 0; _y < h; _y++) {
    //     for (int i = 0; i < w; i++) {
    //         int pos = y * WIDTH + x;

    //         _set_pixel(bytebuffer, pos, r, g, b);
    //         x+=CHANNELS;
    //     }
    //     x -= w*CHANNELS;
    //     y+=CHANNELS;
    // }
    return Py_BuildValue("O", bufobj);
}

static PyObject *test_meth(PyObject *self, PyObject *args) {
    PyObject *bufobj;
    if(!PyArg_ParseTuple(args, "O", &bufobj))
        return NULL;
    char *bytebuffer = PyBytes_AsString(bufobj);
    
    int x = 0;
    int y = 0;
    int w = 100;
    int h = 100;

    x *= CHANNELS;
    y *= CHANNELS;
    
    int start_pos = y * WIDTH + x;
    int end_pos = ((y) + (h * CHANNELS) - CHANNELS) * WIDTH + ((x) + (w * CHANNELS) - CHANNELS);

    int count = 1;
    int offbeats = 0;
    for (int i = start_pos; i <= end_pos; i+=CHANNELS) {
        if (count <= w) bytebuffer = _set_pixel(bytebuffer, i, 100, 100, 100 );
        else offbeats++;
        if (offbeats >= (WIDTH - w)) {offbeats = 0; count = 0;}
        count++;
    }
    
    return Py_BuildValue("O", bufobj);
}

static PyMethodDef methods[] = {
  {"Surface", surf_load, METH_VARARGS, "Creates a surface"},
  {"set_pixel", set_pixel, METH_VARARGS, "sets pixel"},
  {"draw_rect", draw_rect, METH_VARARGS, "draws rect"},
  {"test", test_meth, METH_VARARGS, "draws rect"},
  {"clear", surf_clear, METH_VARARGS, "clears the display"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef graphicx = {
    PyModuleDef_HEAD_INIT,
    "graphicx",
    "base module",
    -1,
    methods
};

PyMODINIT_FUNC PyInit_graphicx(void) {
    PyObject *base = PyModule_Create(&graphicx);
    return base;
}