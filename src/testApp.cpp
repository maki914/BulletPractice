#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofEnableDepthTest();
	ofEnableSmoothing();
	ofBackground(255, 255, 255);

	//カメラ設定
	camera.setDistance(20);
	//camera.setPosition(ofVec3f(0, -7.f, -10.f));
	//camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	//camera.setFov(60.f);

	//ライティング設定
	light.enable();
	light.setSpotlight();
	light.setPointLight();
	light.setPosition(0, 0, 0);
	light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5, 1.0));
	light.setDiffuseColor(ofFloatColor(0.5, 0.5, 0.5));
	light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));

	world.setup();
	//world.broadphase();
	world.enableGrabbing();
	world.setGravity(ofVec3f(0.f, -9.8f, 0.f));	//重力加速度
	world.enableDebugDraw();
	world.setCamera(&camera);
	

	sphere = new ofxBulletSphere();
	//createはofQuoternionを第三引数に設定可
	sphere->create(world.world, ofVec3f(0, 10, 0), 0.1, 1.25);	//(btDiscreteDynamicsWorld*, 位置, 質量, 半径)
	sphere->setProperties(0.5, 0.5);
	sphere->add();

	box = new ofxBulletBox();
	box->create(world.world, ofVec3f(7, 10, 0), .05, .5, .5, .5);
	box->add();

	cone = new ofxBulletCone();
	cone->create(world.world, ofVec3f(-1, 1, .2), .2, .4, 1.);
	cone->add();

	cylinder = new ofxBulletCylinder();
	cylinder->create(world.world, ofVec3f(0, 2.4, 0), .8, .9, 1.8);
	cylinder->add();

	ground.create(world.world, ofVec3f(0., 0., 0.), 0., 50.f, 0., 50.f);
	ground.setProperties(1., 1.); //(Restitution:反発係数, Friction:摩擦係数)
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
	ofRotateX(45);
	ofRotateY(-45);
	//light.disable();



	//ofDrawGrid(50, 25, false, false, true, false);
	//ofEnableLighting();
	//light.enable();
	


	ofSetLineWidth(1.f);
	ofSetColor(255, 0, 200);
	world.drawDebug();

	//ofSetColor(100, 100, 100);
	//ground.draw();

	ofSetColor(225, 225, 225);
	sphere->draw();

	ofSetColor(225, 225, 225);

	//if (ofGetFrameNum() % 30 == 0){
	//	vectorBox.push_back(new ofxBulletBox());
	//	((ofxBulletBox*)vectorBox[vectorBox.size() - 1])->create(world.world, ofVec3f(5, 50, 0), .05, .5, .5, .5);
	//	((ofxBulletBox*)vectorBox[vectorBox.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
	//	vectorBox[vectorBox.size() - 1]->add();
	//}

	for (int i = 0; i < vectorBox.size(); i++){
		vectorBox[i]->draw();
	}

	//ofPushStyle();
	//shapesMat.begin();
	//for (int i = 0; i < shapes.size(); i++) {
	//	shapes[i]->draw();
	//}
	//shapesMat.end();
	//ofPopStyle();
	

	ofSetColor(225, 225, 225);
	cylinder->draw();



	ofSetColor(225, 225, 225);
	cone->draw();


	//地面描画
	ofSetLineWidth(1.5f);
	ofSetColor(255, 0, 0);
	ofLine(-100, 0, 0, 100, 0, 0);
	ofSetColor(0, 0, 255);
	ofLine(0, 0, -100, 0, 0, 100);
	ofSetColor(0, 255, 0);
	ofLine(0, -100, 0, 0, 100, 0);
	ofSetColor(200);

	ofSetLineWidth(1.f);
	for (int i = -50; i <= 50; i++) {
		ofLine(-50, 0, i, 50, 0, i);
		ofLine(i, 0, -50, i, 0, 50);
	}

	camera.end();

	//テキスト表示
	int shapes = vectorBox.size();
	stringstream ss;
	ss << "Box Num: " << shapes << endl;
	ofSetColor(50);
	ofDrawBitmapString(ss.str().c_str(), 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	switch (key){
		case 'b':
			vectorBox.push_back(new ofxBulletBox());
			((ofxBulletBox*)vectorBox[vectorBox.size() - 1])->create(world.world, ofVec3f(5, 50, 0), .05, .5, .5, .5);
			((ofxBulletBox*)vectorBox[vectorBox.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
			vectorBox[vectorBox.size() - 1]->add();
			break;
		default:
			break;
	}

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