#pragma once

#include <tuple>
#include <functional>

/////////////////// Lazy vizitor implementation ///////////////////
template<typename T>
class VizitorComponent
{
public:
	bool tryVisit(T *shape)
	{
		if (m_callback)
		{
			m_callback(shape);
			return true;
		}
		return false;
	}

	void setCallback(const std::function<void(T*)>& callback)
	{
		m_callback = callback;
	}
private:
	std::function<void(T*)> m_callback;
};


template<typename Ttuple>
class LazyVisitor
{
public:
	template<typename T>
	bool tryVisit(T *shape)
	{
		VizitorComponent<T>& component = std::get<VizitorComponent<T>>(m_tuple);
		return component.tryVisit(shape);
	}

	template<typename T>
	void setCallback(const std::function<void(T*)>& callback)
	{
		VizitorComponent<T>& component = std::get<VizitorComponent<T>>(m_tuple);
		return component.setCallback(callback);
	}

private:

	Ttuple m_tuple;
};

typedef LazyVisitor<std::tuple<
	VizitorComponent<class Circle>,
	VizitorComponent<class Square>
> > TVisitor;

/////////////////// Downcast implementation ///////////////////
template<typename TDerived, typename TBase>
TDerived* Downcast(TBase* shape)
{
	TDerived* retObject = nullptr;
	TVisitor lazyVisitor;
	lazyVisitor.setCallback<TDerived>([&](TDerived* shapeDerived)
	{
		retObject = shapeDerived;
	});

	shape->tryAccept(lazyVisitor);

	return retObject;
}