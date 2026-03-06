#include "drawBlock.h"

//TODO : 카메라 거리 자동 조절, 

void drawObject::setup() {
	ofFbo::Settings s;
	s.width = width;
	s.height = height;
	s.internalformat = GL_RGBA;
	s.useDepth = true;
	s.useStencil = true;
	s.depthStencilAsTexture = false;
	s.numSamples = 4;
	fbo.allocate(s);

	light.setup();
	light.setDirectional();
	light.setDiffuseColor(ofFloatColor(1.0));
	light.setSpecularColor(ofFloatColor(0.3));
	light.setOrientation(glm::vec3(light_degree_h, 270 + light_degree_xz, 0));

	ofSetGlobalAmbientColor(ofColor(35, 35, 35));
}

void drawObject::drawBlocks() {
	int max_r = data->getMaxRow();
	int max_c = data->getMaxCol();

	for (int r = 0; r < max_r; r++) {
		for (int c = 0; c < max_c; c++) {
			int height = data->getHeightData(r, c);

			for (int h = 0; h < height; h++)
				ofDrawBox(r * block_size, h * block_size, -c * block_size, block_size);
		}
	}
}

void drawObject::drawOutline() {
	//TODO : implement function
	int max_r = data->getMaxRow();
	int max_c = data->getMaxCol();

	ofSetColor(0, 0, 0, 255);

	for (int r = 0; r < max_r; r++) {
		for (int c = 0; c < max_c; c++) {
			int height = data->getHeightData(r, c);

			for (int h = 0; h < height; h++)
				drawSingleOutline(r, c, h);
		}
	}
}

void drawObject::drawSingleOutline(int r, int c, int h) {
	int mul_a[4] = { 1, 1, -1, -1 };
	int mul_b[4] = { 1, -1, 1, -1 };
	float bias = 0.01;
	glm::vec3 block_center = { r * block_size, h * block_size, -c * block_size };

	for (int i = 0; i < 4; i++) {
		glm::vec3 mul = { mul_a[i], mul_b[i], 0 }; //z fixed
		glm::vec3 edge_center = block_center + (float)block_size / 2 * mul;
		ofDrawBox(edge_center, thickness, thickness, block_size);
	}
	for (int i = 0; i < 4; i++) {
		glm::vec3 mul = { 0, mul_b[i], mul_a[i] }; //x fixed
		glm::vec3 edge_center = block_center + (float)block_size / 2 * mul;
		ofDrawBox(edge_center, block_size, thickness, thickness);
	}
	for (int i = 0; i < 4; i++) {
		glm::vec3 mul = { mul_a[i], 0, mul_b[i] }; //y fixed
		glm::vec3 edge_center = block_center + (float)block_size / 2 * mul;
		ofDrawBox(edge_center, thickness, block_size, thickness);
	}
}

void drawObject::setCamera() {
	std::cout << "degree_xz = " << degree_xz << "\ndegree_h = " << degree_h << "\n";
	int dist = 500;
	float rad_xz = -degree_xz * std::numbers::pi / 180;
	float rad_h = degree_h * std::numbers::pi / 180;

	cam_center = {
		(data->getMaxRow() - 1) * block_size * 0.5f,
		(data->getMaxHeight() - 1) * block_size * 0.5f,
		-(data->getMaxCol() - 1) * block_size * 0.5f
	};

	cam.enableOrtho();
	cam.orbitDeg(90 + degree_xz, -degree_h, dist, cam_center);
	cam.lookAt(cam_center, {0, 1, 0});

	cam_position = cam.getPosition();
}

void drawObject::render() {
	if (!data)
		return;

	fbo.begin();
	ofClear(255, 255, 255, 255);

	setCamera();

	ofEnableLighting();
	light.enable();

	ofEnableDepthTest();

	cam.begin();
	ofSetColor(draw_color, 255);
	drawBlocks();
	cam.end();

	light.disable();
	ofDisableLighting();

	cam.begin();
	ofSetColor(0, 0, 0, 255);
	drawOutline();
	cam.end();

	ofDisableDepthTest();

	fbo.end();
}

void drawObject::saveImage(std::string filename) {
	ofPixels pixels;
	fbo.readToPixels(pixels);
	ofSaveImage(pixels, filename);
};
