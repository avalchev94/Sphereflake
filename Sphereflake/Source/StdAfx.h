#pragma once

///////////////////////////////////////////////////////////////////////
// Built-in headers include
#include <stdint.h>
#include <string.h>

///////////////////////////////////////////////////////////////////////
// Plug-in specific includes
#include "Math/MathUtils.h"
#include "Math/Point3D.h"
#include "Math/Point2D.h"
#include "Math/Matrix.h"


///////////////////////////////////////////////////////////////////////
// Data types
typedef uint8_t		Uint8;
typedef	uint16_t	Uint16;
typedef	uint32_t	Uint32;
typedef uint64_t	Uint64;

typedef char		Sint8;	
typedef	int16_t		Sint16;
typedef	int32_t		Sint32;
typedef int64_t		Sint64;


///////////////////////////////////////////////////////////////////////
// Defines
#define DISALLOW_COPY(TypeName) \
private: \
	TypeName(const TypeName&); \
	TypeName& operator=(const TypeName&);

#define SINGELTON(SingletonClass) \
public: \
	static SingletonClass& GetInstance() \
	{ \
		static SingletonClass singletonInstance; \
		return singletonInstance; \
	} \
private: \
	SingletonClass(); \
	SingletonClass(const SingletonClass&); \
	SingletonClass& operator=(const SingletonClass&);
