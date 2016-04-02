#pragma once

#include "lazy_visitor.h"

/////////////////// Test data implementation ///////////////////
class Shape
{
public:
	Shape(int x, int y);

	int getX();

	int getY();

	virtual ~Shape();

	virtual void draw() = 0;

	virtual bool tryAccept(TVisitor &v) = 0;

protected:
	int m_x;
	int m_y;
};

class Circle : public Shape
{
public:
	Circle(int x, int y, int radius);

	virtual void draw() override;

	virtual bool tryAccept(TVisitor &visitor) override;

	int getRadius();

private:

	int m_radius;
};

class Square : public Shape
{
public:
	Square(int x, int y, int width, int height);

	virtual void draw() override;

	virtual bool tryAccept(TVisitor &visitor) override;

	int getWidth();

	int getHeight();

private:

	int m_width;
	int m_height;
};

void DataGetter(Shape* shape);

void Test();