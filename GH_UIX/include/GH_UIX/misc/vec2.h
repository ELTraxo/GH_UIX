#pragma once
template <class T>
struct vec2
{
	T x, y;
	vec2();
	vec2( T i );
	vec2( T x, T y );
	
	
	void operator=( const vec2<T>& rhs );
	vec2<T> operator+( const vec2<T>& rhs ) const;
	void operator+=( vec2<T>& rhs );
	vec2<T> operator/( const vec2<T>& rhs ) const;
	void operator/=( vec2<T>& rhs );
	vec2<T> operator*( const vec2<T>& rhs ) const;
	void operator*=( vec2<T>& rhs );

	bool operator==( T rhs );
	bool operator==( vec2<T> rhs );

	D3DXVECTOR2 ToDX9Vector();
};

template<class T>
inline vec2<T>::vec2()
{
	x = 0;
	y = 0;
}

template<class T>
inline vec2<T>::vec2( T i )
{
	x = y = i;
}

template<class T>
inline vec2<T>::vec2( T x, T y )
{
	this->x = x;
	this->y = y;
}

template<class T>
inline void vec2<T>::operator=( const vec2<T> & rhs )
{
	this->x = rhs.x;
	this->y = rhs.y;
}

template<class T>
inline vec2<T> vec2<T>::operator+( const vec2<T> & rhs ) const
{
	vec2<T> v;
	v.x = this->x + rhs.x;
	v.y = this->y + rhs.y;
	return v;
}

template<class T>
inline void vec2<T>::operator+=( vec2<T> & rhs )
{	
	this->x = this->x + rhs.x;
	this->y = this->y + rhs.y;
}

template<class T>
inline vec2<T> vec2<T>::operator/( const vec2<T>& rhs ) const
{
	vec2<T> v;
	v.x = this->x / rhs.x;
	v.y = this->y / rhs.y;
	return v;
}

template<class T>
inline void vec2<T>::operator/=( vec2<T>& rhs )
{
	this->x = this->x / rhs.x;
	this->y = this->y / rhs.y;
}

template<class T>
inline vec2<T> vec2<T>::operator*( const vec2<T>& rhs ) const
{
	vec2<T> v;
	v.x = this->x * rhs.x;
	v.y = this->y * rhs.y;
	return v;
}

template<class T>
inline void vec2<T>::operator*=( vec2<T>& rhs )
{
	this->x = this->x * rhs.x;
	this->y = this->y * rhs.y;
}

template<class T>
inline bool vec2<T>::operator==( T rhs )
{
	return (this->x == rhs && this->y == rhs);
}

template<class T>
inline bool vec2<T>::operator==( vec2<T> rhs )
{
	return (this->x == rhs.x && this->y == rhs.y);
}

template<class T>
inline D3DXVECTOR2 vec2<T>::ToDX9Vector()
{
	return D3DXVECTOR2(x,y);
}


