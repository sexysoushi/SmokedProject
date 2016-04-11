#ifndef Object3D_h
#define Object3D_h

#include "Common/GlFramework.h"
#include "AbstractFramework.h"


class Object3D
{

private:
    vec3   rotation; // rotation de la particule
    vec3   position; // position de la particule
    vec3   size; // taille de la particule


	public:
        static void setFramework( AbstractFramework* );

	public:

        void translate(vec3 t);
        void rotate(vec3 r);
        void setSize(vec3 s);

		void draw();

	protected:
		virtual void drawShape() = 0;


	protected:
		static AbstractFramework* m_Framework;
};


#endif
