#ifndef GlFrame_h
#define GlFrame_h


#include "GlWindow.h"


class GlFrame : public GlWindow
{
	public:
        GlFrame();
        ~GlFrame();

		/*!
		*\brief Initialization des objets.
		*/
		bool initializeObjects();

		/*!
		*\brief Rendu de la scène.
		*/
		void render();

		void keyPressEvent(QKeyEvent *);
};


#endif
