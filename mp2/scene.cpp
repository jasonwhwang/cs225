#include <iostream>
#include "scene.h"
#include "image.h"
using namespace std;

Scene::Scene(int max):max(max)
{
    layers = new Image*[max];
    xval = new int[max];
    yval = new int[max];
    for(int i = 0; i < max; i++){
        layers[i] = NULL;
        xval[i] = yval[i] = 0;
    }
}

Scene::~Scene()
{
    clear();
}


Scene::Scene(const Scene &source)
{
    copy(source);
}

const Scene & Scene::operator=(const Scene &source)
{
    if(this != &source){
        clear();
        copy(source);
    }
    return *this;
}

void Scene::changemaxlayers(int newmax)
{
    if(newmax < max){
        for(int i = newmax; i < max; i++){
            if(layers[i] != NULL){
                cout << "invalid newmax" << endl;
                return;
            }
        }
    }

    Image** newlayers = new Image*[newmax];
    int* newx = new int[newmax];
    int* newy = new int[newmax];
    int index = min(max, newmax);

    for(int i = 0; i < index; i++){
        *newlayers[i] = *layers[i];
        newx[i] = xval[i];
        newy[i] = yval[i];
    }
    if(index == max){
        for(int i = max; i < newmax; i++){
            newlayers[i] = NULL;
            newx[i] = 0;
            newy[i] = 0;
        }
    }
    
    clear();
    layers = newlayers;
    xval = newx;
    yval = newy;
    max = newmax;
}

void Scene::addpicture(const char *FileName, int index, int x, int y)
{
    if(index >= max || index < 0){
        cout << "index out of bounds" << endl;
        return;
    }

    xval[index] = x;
    yval[index] = y;

    Image* newimage = new Image();
    newimage->readFromFile(FileName);

    if(layers[index] != NULL){
        delete layers[index];
    }

    layers[index] = newimage;
}

void Scene::changelayer(int index, int newindex)
{
    if((index >= max || index < 0) || (newindex >= max || newindex < 0)){
        cout << "invalid index" << endl;
        return;
    }
    if(index == newindex){
        return;
    }

    if(layers[newindex] != NULL){
        delete layers[newindex];
    }
    layers[newindex] = layers[index];
    delete layers[index];
    layers[index] = NULL;

    xval[newindex] = xval[index];
    yval[newindex] = yval[index];
    xval[index] = yval[index] = 0;
}

void Scene::translate(int index, int xcoord, int ycoord)
{
    if(index >= max || index < 0 || layers[index] == NULL){
        cout << "invalid index" << endl;
        return;
    }

    xval[index] = xcoord;
    yval[index] = ycoord;
}

void Scene::deletepicture(int index)
{
    if(index >= max || index < 0 || layers[index] == NULL){
        cout << "invalid index" << endl;
        return;
    }

    delete layers[index];
    layers[index] = NULL;
    xval[index] = yval[index] = 0;
}

Image* Scene::getpicture(int index) const
{
    if(index >= max || index < 0 || layers[index] == NULL){
        cout << "invalid index" << endl;
        return NULL;
    }
    return layers[index];
}

Image Scene::drawscene() const
{
    int width = 0, height = 0;
    for(int i = 0; i < max; i++){
        if(layers[i] != NULL){
            width = std::max((int)layers[i]->width()+xval[i],width);
            height = std::max((int)layers[i]->height()+yval[i],height);
        }
    }

    Image img;
    img.resize(width, height);
    cout << width << endl;
    cout << height << endl;
    for(int i = 0; i < max; i++){
        if(layers[i] != NULL){
            for(size_t x = 0; x < layers[i]->width(); x++){
                for(size_t y = 0; y < layers[i]->height(); y++){
                    *img(x, y) = *(*layers[i])(x,y);
                }
            }
        }
    }
    return img;
}

void Scene::copy(const Scene &other)
{
    max = other.max;
    layers = new Image*[max];
    xval = new int[max];
    yval = new int[max];
    for(int i = 0; i < max; i++){
        if(other.layers[i] != NULL){
            layers[i] = new Image(*(other.layers[i]));
        }
        else{
            layers[i] = NULL;
        }
        xval[i] = other.xval[i];
        yval[i] = other.yval[i];
    }
}

void Scene::clear()
{
    for(int i = 0; i < max; i++){
        delete layers[i];
    }
    delete[] layers;
    delete[] xval;
    delete[] yval;
}
