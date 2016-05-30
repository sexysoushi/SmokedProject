#version 130

in vec4 color;
in vec2 texCoord;
uniform sampler2D texId;


out vec4 fColor;

void main()
{
   int n = 0;
   //Lidentifiant de l'unite de texture n (avec n = 0, 1, NBR_TEXTURES-1)
   glUniform1i( glGetUniformLocation( 0, "texId" ), n ) ;
   fColor = color;
}
