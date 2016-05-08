#include "rubiks.h"
#include "GlWindow.h"

Rubiks::Rubiks(int dim, float s)
{
    dimension = dim;
    cube = new Cube(1.0f);
    angle = 0;
    spacing = s;
}

//Rubiks::drawShape(){

//    for(int i=0; i<dimension; i++){
//        for(int j=0; j<dimension; j++){
//            for(int k=0; k<dimension; k++){
//                m_Framework->pushMatrix();
//                m_Framework->translate(i,j,k);
//            }
//        }
//    }


//}
