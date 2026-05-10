#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tools/stb_image.h"
#include "tools/stb_image_write.h"
#include "rendering.hpp"

/***************************************************************************/
/*   FONCTION DE GESTION GL : NE PAS LIRE (rendez-vous en Master 1 & 2)    */
/***************************************************************************/
void resetProjMatrix() {
	projMatrix = Matrix4D::perspective(45.0,ratio,0.1f,2000.0f);
}

void updateMvMatrix(int ids) {
	glUniformMatrix4fv(glGetUniformLocation(idShader[ids],"modelviewMat"),1,GL_FALSE,modelviewStack.getTopGLMatrix());
}

void setFlatColor(float r,float g,float b) {
	glVertexAttrib3f(glGetAttribLocation(idShader[0],"vx_col"),r,g,b);
}

void createSkyBox() {
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &idTexSkybox);
	glBindTexture(GL_TEXTURE_CUBE_MAP,idTexSkybox);

	std::vector<std::string> faces
	{
    	"../images/rainbow_rt.png",
    	"../images/rainbow_lf.png",
    	"../images/rainbow_up.png",
    	"../images/rainbow_dn.png",
    	"../images/rainbow_bk.png",
    	"../images/rainbow_ft.png"
	};

	// Loading 6 images
	int w,h,nbc;
	unsigned char* the_image = NULL;
	// Right texture
    for (unsigned int i = 0; i < faces.size(); i++)
    {
		the_image = stbi_load(faces[i].c_str(),&w,&h,&nbc,0);
		if (!the_image)
		{
			std::cerr<<"We got something wrong in loading "<<faces[i]<<std::endl;
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
					0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, the_image);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_WRAP_R,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

	glBindTexture(GL_TEXTURE_CUBE_MAP,0);
}

void drawSky() {
	glDepthMask(GL_FALSE);
	glUseProgram(idShader[1]);
	glUniform1i(glGetUniformLocation(idShader[1],"u_tex"),0);
	glBindTexture(GL_TEXTURE_CUBE_MAP,idTexSkybox);

	Matrix4D sky_v_matrix;
	Vector3D vis_pt = Vector3D(cos(deg2rad(-angle_theta+180))*cos(deg2rad(angle_phy+180)),
							 sin(deg2rad(angle_phy+180)),
							 sin(deg2rad(-angle_theta+180))*cos(deg2rad(angle_phy+180)));

	sky_v_matrix = Matrix4D::lookAt(Vector3D(0.0,0.0,0.0),
							vis_pt,
							Vector3D(0.0,1.0,0.0));
	glUniformMatrix4fv(glGetUniformLocation(idShader[1],"modelviewMat"),1,GL_FALSE,sky_v_matrix.mat);
	
	a_basic_wolf->draw();

	glDepthMask(GL_TRUE);
	glUseProgram(idShader[0]);
}

void makeSnapshot(std::string filename,int size_w,int size_h) {
	// Create an image buffer
	GLubyte* pixels = new GLubyte[4 * size_w * size_h];
	glReadBuffer(GL_BACK);

	// Read the pixel data from the framebuffer
	glReadPixels(0, 0, size_w, size_h, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	stbi_flip_vertically_on_write(1);
	// Save the image to a file
	stbi_write_png(filename.c_str(), size_w, size_h, 4, pixels, size_w * 4);
	{
		std::cout << "screenshot saved to " << filename << std::endl;
	}
}