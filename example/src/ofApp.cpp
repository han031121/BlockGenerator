#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	std::cout << "[ ofApp ] : generate new block data\n";
	consoleInput();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	if (img.isAllocated())
		img.draw(30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'g') {
		std::cout << "[ ofApp ] : set block data and generate draw object\n";
		if (draw_object)
			delete draw_object;

		block_data->generateBlock();
		block_data->printHeightData();
		draw_object = new drawObject(block_data, 1000, 1000);
	}
	else if (key == 'd') {
		std::cout << "[ ofApp ] : modify cam degree\n";

		float a, b;
		std::cout << "cam degree_xz : ";
		std::cin >> a;
		std::cout << "cam degree_h : ";
		std::cin >> b;
		draw_object->camDegreeUpdate(a, b);
	}
	else if (key == 'l') {
		std::cout << "[ ofApp ] : modify cam degree\n";

		float a, b;
		std::cout << "light degree_xz : ";
		std::cin >> a;
		std::cout << "light degree_h : ";
		std::cin >> b;
		draw_object->lightDegreeUpdate(a, b);
	}
	else if (key == 'r') {
		std::cout << "[ ofApp ] : render blocks\n";

		draw_object->render();
		draw_object->getPixels(pix);
		//std::cout << "[ ofApp ] : pixel created\n";
		std::cout << pix.getWidth() << "x" << pix.getHeight()
				  << " ch=" << pix.getNumChannels()
				  << " size=" << pix.size() << "\n";

		img.setFromPixels(pix);
		//std::cout << "[ ofApp ] : image created\n";
	}
	else if (key == 'n') {
		cout << "[ ofApp ] : regenerate block data\n";
		consoleInput();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::consoleInput() {
	if (block_data)
		delete block_data;

	int i1, i2, i3, i4, i5, i6;
	std::cout << "block count 1 : ";
	std::cin >> i1;
	std::cout << "block count 2 : ";
	std::cin >> i2;
	std::cout << "max row : ";
	std::cin >> i3;
	std::cout << "max column : ";
	std::cin >> i4;
	std::cout << "max height : ";
	std::cin >> i5;
	std::cout << "density : ";
	std::cin >> i6;
	block_data = new blockData(i1, i2, i3, i4, i5, (double)i6);
}
