#ifndef Object3D_h
#define Object3D_h

#include "src/Common/GlFramework.h"
#include "AbstractFramework.h"


class Object3D
{

protected:
	public:
        static void setFramework( AbstractFramework* );

	public:
		void draw();

	protected:
		virtual void drawShape() = 0;


	protected:
		static AbstractFramework* m_Framework;
};


#endif
