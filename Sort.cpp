#include "include/Sort.h"

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList) {
    shapeList->sort([](const Shape *firstShape, const Shape *secondShape) {
        return firstShape->perimeter() < secondShape->perimeter();
    });
}

void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList) {
    shapeList->sort([](const Shape *firstShape, const Shape *secondShape) {
        return firstShape->perimeter() > secondShape->perimeter();
    });
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList) {
    shapeList->sort([](const Shape *firstShape, const Shape *secondShape) {
        return firstShape->area() < secondShape->area();
    });
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList) {
    shapeList->sort([](const Shape *firstShape, const Shape *secondShape) {
        return firstShape->area() > secondShape->area();
    });
}
  
void Sort::sortByIncreasingCompactness(std::list<Shape *> * shapeList) {
    shapeList->sort([](const Shape *firstShape, const Shape *secondShape) {
        return (firstShape->area() / firstShape->perimeter()) < (secondShape->area() / secondShape->perimeter());
    });
}
