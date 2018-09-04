#pragma once
template <class T>
struct vec3
{
	T x, y, z;
	vec3();
	vec3( T i );
	vec3( T x, T y, T z );


	void operator=( const vec3<T>& rhs );
	vec3<T> operator+( const vec3<T>& rhs ) const;
	void operator+=( const vec3<T>& rhs );

	T DistanceTo( const vec3<T>& rhs );

	D3DXVECTOR3 ToDX9Vector();
};

template<class T>
inline vec3<T>::vec3()
{
	x = 0;
	y = 0;
	z = 0;
}

template<class T>
inline vec3<T>::vec3( T i )
{
	x = y = z = i;
}

template<class T>
inline vec3<T>::vec3( T x, T y, T z )
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<class T>
inline void vec3<T>::operator=( const vec3<T> & rhs )
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
}

template<class T>
inline vec3<T> vec3<T>::operator+( const vec3<T> & rhs ) const
{
	vec3<T> v;
	v.x = this->x + rhs.x;
	v.y = this->y + rhs.y;
	v.z = this->z + rhs.z;
	return v;
}

template<class T>
inline void vec3<T>::operator+=( const vec3<T> & rhs )
{
	this = *this + rhs;
}

template<class T>
inline T vec3<T>::DistanceTo( const vec3<T>& rhs )
{
	auto dx = ( rhs.x - x ) * ( rhs.x - x );
	auto dy = ( rhs.y - y ) * ( rhs.y - y );
	auto dz = ( rhs.z - z ) * ( rhs.z - z );
	return sqrt( dx + dy + dz );
}

template<class T>
inline D3DXVECTOR3 vec3<T>::ToDX9Vector()
{
	return D3DXVECTOR3( x, y, z );
}


