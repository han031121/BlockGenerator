#pragma once

#include "blockGenerator.h"
#include "ofMain.h"

class drawObject {

	private:
		int block_size = 1;

		blockData * data = nullptr;

		ofColor draw_color = ofColor(220, 185, 154);
		ofFbo fbo;
		ofEasyCam cam;

		void drawBlocks(); //draw blocks on fbo
		void drawSingleBlock(int r, int c, int h);

	public:
		drawObject(blockData* _d)
			: data(_d) {

			}

		void drawSetup(int width, int height); //setup fbo

		void render(); //draw and render blocks on fbo
		void saveImage(std::string file_name); //save PNG
};
