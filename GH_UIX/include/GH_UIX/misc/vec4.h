#pragma once
template <class T>
struct vec4
{
	T x, y, z, w;
	vec4();
	vec4( T i );
	vec4( T x, T y, T z );


	void operator=( const vec4<T>& rhs );
	vec4<T> operator+( const vec4<T>& rhs ) const;
	void operator+=( const vec4<T>& rhs );
};

template<class T>
inline vec4<T>::vec4()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

template<class T>
inline vec4<T>::vec4( T i )
{
	x = y = z = w = i;
}

template<class T>
inline vec4<T>::vec4( T x, T y, T z )
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

template<class T>
inline void vec4<T>::operator=( const vec4<T> & rhs )
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
}

template<class T>
inline vec4<T> vec4<T>::operator+( const vec4<T> & rhs ) const
{
	vec4<T> v;
	v.x = this->x + rhs.x;
	v.y = this->y + rhs.y;
	v.z = this->z + rhs.z;
	v.w = this->w + rhs.w;
	return v;
}

template<class T>
inline void vec4<T>::operator+=( const vec4<T> & rhs )
{
	this = *this + rhs;
}