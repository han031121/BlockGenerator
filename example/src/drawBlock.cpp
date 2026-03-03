#include "drawBlock.h"

void drawObject::setup() {
	ofFbo::Settings s;
	s.width = width;
	s.height = height;
	s.internalformat = GL_RGBA;
	s.useDepth = true;
	s.useStencil = true;
	s.depthStencilAsTexture = false;
	s.numSamples = 0;
	fbo.allocate(s);
}

void drawObject::drawBlocks() {
	int max_r = data->getMaxRow();
	int max_c = data->getMaxCol();

	for (int r = 0; r < max_r; r++) {
		for (int c = 0; c < max_c; c++) {
			int height = data->getHeightData(r, c);

			for (int h = 0; h < height; h++) {
				drawSingleBlock(r, c, h);
			}
		}
	}
}

void drawObject::drawSingleBlock(int r, int c, int h) {
	std::cout << "[ drawSingleBlock ] : " << r << ", " << c << ", " << h << "\n";

	ofFill();
	ofSetColor(draw_color, 255);
	ofDrawBox(r * block_size, h * block_size, -c * block_size, block_size);

	ofNoFill();
	ofSetColor(0, 0, 0, 255);
	ofDrawBox(r * block_size, h * block_size, -c * block_size, block_size);
}

void drawObject::setCameraPosition() {
	//TODO : implement setCamarePosition
	std::cout << "degree_xz = " << degree_xz << "\ndegree_h = " << degree_h << "\n";
	int dist = 500;
	float rad_xz = degree_xz * std::numbers::pi / 180;
	float rad_h = degree_h * std::numbers::pi / 180;

	glm::vec3 cam_center = {
		(data->getMaxRow() - 1) * block_size * 0.5f,
		(data->getMaxHeight() - 1) * block_size * 0.5f,
		-(data->getMaxCol() - 1) * block_size * 0.5f
	};

	glm::vec3 cam_position = {
		dist * std::cos(rad_xz),
		dist * std::sin(rad_h),
		dist * std::sin(rad_xz)
	};
	cam_position += cam_center;

	cam.setPosition(cam_position);
	cam.lookAt(cam_center);
}

void drawObject::render() {
	if (!data)
		return;

	fbo.begin();
	ofClear(255, 255, 255, 255);

	setCameraPosition();

	ofEnableDepthTest();
	cam.begin();
	drawBlocks();
	cam.end();
	ofDisableDepthTest();

	fbo.end();
}

void drawObject::getPixels(ofPixels& pixels) {
	fbo.readToPixels(pixels);
}

void drawObject::saveImage(std::string filename) {
	ofPixels pixels;
	fbo.readToPixels(pixels);
	ofSaveImage(pixels, filename);
}
