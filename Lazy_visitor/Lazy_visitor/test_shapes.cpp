#include "test_shapes.h"

#include <vector>
#include <iostream>

Shape::Shape(int x, int y)
	: m_x(x)
	, m_y(y)
{}

int Shape::getX()
{
	return m_x;
}

int Shape::getY()
{
	return m_y;
}

Shape::~Shape()
{
}


Circle::Circle(int x, int y, int radius)
	: Shape(x, y)
	, m_radius(radius)
{}

void Circle::draw()
{
	std::cout << "Circle   X=" << m_x << " Y=" << m_y << " Radius=" << m_radius << std::endl;
}

bool Circle::tryAccept(TVisitor &visitor)
{
	return visitor.tryVisit(this);
}

int Circle::getRadius()
{
	return m_radius;
}

Square::Square(int x, int y, int width, int height)
	: Shape(x, y)
	, m_width(width)
	, m_height(height)
{}

void Square::draw()
{
	std::cout << "Square   X=" << m_x << " Y=" << m_y << " Width=" << m_width << " Height=" << m_height << std::endl;
}

bool Square::tryAccept(TVisitor &visitor)
{
	return visitor.tryVisit(this);
}

int Square::getWidth()
{
	return m_width;
}

int Square::getHeight()
{
	return m_height;
}

void DataGetter(Shape* shape)
{
	int radius = 0;
	int width = 0;
	int height = 0;
	std::string additionalInfo;
	TVisitor lazyVisitor;
	lazyVisitor.setCallback<Circle>([&](Circle* shape)
	{
		radius = shape->getRadius();
		additionalInfo = "Circle";
	});
	lazyVisitor.setCallback<Square>([&](Square* shape)
	{
		width = shape->getWidth();
		height = shape->getHeight();
		additionalInfo = "Square";
	});

	if (shape->tryAccept(lazyVisitor))
	{
		std::cout << "Obtained from: " << additionalInfo.c_str() << " Radius:" << radius << " Width:" << width << " Height:" << height << std::endl;
	}
}

void Test()
{
	std::vector<Shape*> shapes = { new Circle(4, 6, 80), new Square(5, 8, 20, 25) };

	for (Shape* shape : shapes)
	{
		DataGetter(shape);
	}

	// Downcasting.
	std::cout << "Downcasting." << std::endl;

	Square* square1 = Downcast<Square>(shapes[0]); // shapes[0] == Circle. Must return nullptr.
	std::cout << "Casting from Shape ( real type is Circle ) to Square " << (square1 ? "possible." : "impossible.") << std::endl;

	Square* square2 = Downcast<Square>(shapes[1]); // shapes[1] == Square. Must return square.
	std::cout << "Casting from Shape ( real type is Square ) to Square " << (square2 ? "possible." : "impossible.") << std::endl;

	Circle* circle1 = Downcast<Circle>(shapes[0]); // shapes[0] == Circle. Must return circle.
	std::cout << "Casting from Shape ( real type is Circle ) to Circle " << (circle1 ? "possible." : "impossible.") << std::endl;

	Circle* circle2 = Downcast<Circle>(shapes[1]); // shapes[1] == Square. Must return nullptr.
	std::cout << "Casting from Shape ( real type is Square ) to Circle " << (circle2 ? "possible." : "impossible.") << std::endl;

	for (Shape* shape : shapes)
	{
		delete shape;
	}
}