	#pragma once

	#include "blockGenerator.h"
	#include "ofMain.h"

	class drawObject {

		private:
			int block_size = 100;
			int width;
			int height;

			float degree_xz = -15;
			float degree_h = 50;

			blockData * data = nullptr;

			ofColor draw_color = ofColor(220, 185, 154);
			ofFbo fbo;
			ofEasyCam cam;

			void setup();

			void drawBlocks(); //draw blocks on fbo
			void drawSingleBlock(int r, int c, int h);

			void setCameraPosition();

		public:
			drawObject(blockData* _d, int _w, int _h)
				: data(_d), width(_w), height(_h) {
					setup();
				}

			void render(); //draw and render blocks on fbo
			void getPixels(ofPixels& pixels);
			void saveImage(std::string filename); //save PNG

			void degreeUpdate(float deg_xz, float deg_h) {
				degree_xz = deg_xz;
				degree_h = deg_h;
			}
	};
