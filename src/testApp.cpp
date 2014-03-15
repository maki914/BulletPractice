#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofEnableDepthTest();
	ofEnableSmoothing();
	ofBackground(255, 255, 255);

	//カメラ設定
	camera.setDistance(30);
	//camera.setPosition(ofVec3f(0, -7.f, -10.f));
	//camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	//camera.setFov(60.f);

	//ライティング設定
	light.enable();
	light.setSpotlight();
	light.setPosition(0, 0, 0);
	light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5, 1.0));
	light.setDiffuseColor(ofFloatColor(0.5, 0.5, 1.0));
	light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));

	world.setup();
	//world.broadphase();
	world.enableGrabbing();
	world.setGravity(ofVec3f(0.f, -9.8f, 0.f));
	world.enableDebugDraw();
	world.setCamera(&camera);
	

	sphere = new ofxBulletSphere();
	sphere->create(world.world, ofVec3f(0, 10, 0), 0.1, 1.25);
	sphere->add();

	box = new ofxBulletBox();
	box->create(world.world, ofVec3f(7, 10, 0), .05, .5, .5, .5);
	box->add();

	cone = new ofxBulletCone();
	cone->create(world.world, ofVec3f(-1, 1, .2), .2, .4, 1.);
	cone->add();

	capsule = new ofxBulletCapsule();
	capsule->create(world.world, ofVec3f(1, 2, -.2), .4, .8, 1.2);
	capsule->add();

	cylinder = new ofxBulletCylinder();
	cylinder->create(world.world, ofVec3f(0, 2.4, 0), .8, .9, 1.8);
	cylinder->add();

	ground.create(world.world, ofVec3f(0., 0., 0.), 0., 100.f, 1.f, 100.f);
	ground.setProperties(.25, .95);
	ground.add();
}


//--------------------------------------------------------------
void testApp::update() {
	world.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
}

//--------------------------------------------------------------
void testApp::draw() {
	glEnable(GL_DEPTH_TEST);
	camera.begin();
	ofRotateX(15);

	//地面描画
	//ofSetLineWidth(1.5f);
	//ofSetColor(255, 0, 0);
	//ofLine(-100, 5, 0, 100, 5, 0);
	//ofSetColor(0, 0, 255);
	//ofLine(0, 5, -100, 0, 5, 100);
	//ofSetColor(0, 255, 0);
	//ofLine(0, -100, 0, 0, 100, 0);
	//ofSetColor(200);

	//ofSetLineWidth(1.f);
	//for (int i = -50; i <= 50; i++) {
	//	ofLine(-50, 5, i, 50, 5, i);
	//	ofLine(i, 5, -50, i, 5, 50);
	//}

	ofDrawGrid(50, 10, true, true, true, true);


	ofSetLineWidth(1.f);
	ofSetColor(255, 0, 200);
	world.drawDebug();

	//ofSetColor(100, 100, 100);
	//ground.draw();

	ofSetColor(225, 225, 225);
	sphere->draw();

	ofSetColor(225, 225, 225);
	box->draw();
	if (ofGetFrameNum() % 30 == 0){
		box = new ofxBulletBox();
		box->create(world.world, ofVec3f(7, 0, 0), .05, .5, .5, .5);
		box->add();
	}

	ofSetColor(225, 225, 225);
	cylinder->draw();

	ofSetColor(225, 225, 225);
	capsule->draw();

	ofSetColor(225, 225, 225);
	cone->draw();

	camera.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo) {

}