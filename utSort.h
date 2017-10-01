#ifndef EXP_H
#define EXP_H
#include "include/Shapes.h"
#include "include/Sort.h"
#include <vector>

const double abs_error = 0.000001;

TEST (Sort, sortByIncreasingPerimeter) {
	Rectangle rectangle(0, 0, 3, 4);
	Circle circle(0, 0, 3);
	vertex v1 = {0, 0};
	vertex v2 = {1, 2};
	vertex v3 = {2, 0};
	Triangle triangle(v1, v2, v3);
	std::list<Shape *> shapeList;
	shapeList.push_back(&rectangle);
	shapeList.push_back(&circle);
	shapeList.push_back(&triangle);
	Sort::sortByIncreasingPerimeter(&shapeList);
    
    std::vector<Shape *> shapes;
    for (Shape *shape : shapeList) {
        shapes.push_back(shape);
    }
    // t < r < c
	EXPECT_EQ(&triangle, shapes[0]);
    EXPECT_EQ(&rectangle, shapes[1]);
	EXPECT_EQ(&circle, shapes[2]);
}

TEST (Sort, sortByDecreasingPerimeter) {
    Rectangle rectangle(0, 0, 3, 4);
    Circle circle(0, 0, 3);
    vertex v1 = {0, 0};
    vertex v2 = {1, 2};
    vertex v3 = {2, 0};
    Triangle triangle(v1, v2, v3);
    std::list<Shape *> shapeList;
    shapeList.push_back(&rectangle);
    shapeList.push_back(&circle);
    shapeList.push_back(&triangle);
    Sort::sortByDecreasingPerimeter(&shapeList);
    
    std::vector<Shape *> shapes;
    for (Shape *shape : shapeList) {
        shapes.push_back(shape);
    }
    // c > r > t
    EXPECT_EQ(&circle, shapes[0]);
    EXPECT_EQ(&rectangle, shapes[1]);
    EXPECT_EQ(&triangle, shapes[2]);
}

TEST (Sort, sortByIncreasingArea) {
    Rectangle rectangle(0, 0, 3, 4);
    Circle circle(0, 0, 3);
    vertex v1 = {0, 0};
    vertex v2 = {1, 2};
    vertex v3 = {2, 0};
    Triangle triangle(v1, v2, v3);
    std::list<Shape *> shapeList;
    shapeList.push_back(&rectangle);
    shapeList.push_back(&circle);
    shapeList.push_back(&triangle);
    Sort::sortByIncreasingArea(&shapeList);
    
    std::vector<Shape *> shapes;
    for (Shape *shape : shapeList) {
        shapes.push_back(shape);
    }
    // t < r < c
    ASSERT_EQ(&triangle, shapes[0]);
    ASSERT_EQ(&rectangle, shapes[1]);
    ASSERT_EQ(&circle, shapes[2]);
}

TEST (Sort, sortByDecreasingArea) {
    Rectangle rectangle(0, 0, 3, 4);
    Circle circle(0, 0, 3);
    vertex v1 = {0, 0};
    vertex v2 = {1, 2};
    vertex v3 = {2, 0};
    Triangle triangle(v1, v2, v3);
    std::list<Shape *> shapeList;
    shapeList.push_back(&rectangle);
    shapeList.push_back(&circle);
    shapeList.push_back(&triangle);
    Sort::sortByDecreasingArea(&shapeList);
    
    std::vector<Shape *> shapes;
    for (Shape *shape : shapeList) {
        shapes.push_back(shape);
    }
    // c > r > t
    ASSERT_EQ(&circle, shapes[0]);
    ASSERT_EQ(&rectangle, shapes[1]);
    ASSERT_EQ(&triangle, shapes[2]);
}

TEST (Sort, sortByIncreasingCompactness) {
    Rectangle rectangle(0, 0, 3, 4);
    Circle circle(0, 0, 3);
    vertex v1 = {0, 0};
    vertex v2 = {1, 2};
    vertex v3 = {2, 0};
    Triangle triangle(v1, v2, v3);
    std::list<Shape *> shapeList;
    shapeList.push_back(&rectangle);
    shapeList.push_back(&circle);
    shapeList.push_back(&triangle);
    Sort::sortByIncreasingCompactness(&shapeList);
    
    std::vector<Shape *> shapes;
    for (Shape *shape : shapeList) {
        shapes.push_back(shape);
    }
    // t < r < c
    ASSERT_EQ(&triangle, shapes[0]);
    ASSERT_EQ(&rectangle, shapes[1]);
    ASSERT_EQ(&circle, shapes[2]);
}

#endif
