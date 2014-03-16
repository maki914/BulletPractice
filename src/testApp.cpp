#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	//ofEnableDepthTest();
	//ofEnableSmoothing();
	ofBackground(255, 255, 255);

	//ƒJƒƒ‰Ý’è
	camera.setDistance(20);
	//camera.setPosition(ofVec3f(0, -7.f, -10.f));
	//camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, -1, 0));
	//camera.setFov(60.f);

	//ƒ‰ƒCƒeƒBƒ“ƒOÝ’è
	ofEnableLighting();
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
	world.enableDebugDraw();
	world.setCamera(&camera);
	world.setGravity(ofVec3f(0.f, -9.8f, 0.f));	//d—Í‰Á‘¬“x
	

	//sphere = new ofxBulletSphere();
	////create‚ÍofQuoternion‚ð‘æŽOˆø”‚ÉÝ’è‰Â
	//sphere->create(world.world, ofVec3f(0, 10, 0), 0.1, 1.25);	//(btDiscreteDynamicsWorld*, ˆÊ’u, Ž¿—Ê, ”¼Œa)
	//sphere->setProperties(0.5, 0.5);
	////sphere->applyForce(1.0, 0.0, 0.0);
	//sphere->add();

	//box = new ofxBulletBox();
	//box->create(world.world, ofVec3f(7, 10, 0), .05, .5, .5, .5);
	//box->add();

	//cone = new ofxBulletCone();
	//cone->create(world.world, ofVec3f(-1, 1, .2), .2, .4, 1.);
	//cone->add();

	//cylinder = new ofxBulletCylinder();
	//cylinder->create(world.world, ofVec3f(0, 2.4, 0), .8, .9, 1.8);
	//cylinder->add();

	ground.create(world.world, ofVec3f(0., 0., 0.), 0., 50.f, 0., 50.f);
	ground.setProperties(1., 1.); //(Restitution:”½”­ŒW”, Friction:–€ŽCŒW”)
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
	ofDisableAlphaBlending();
	ofDisableBlendMode();


	//ofDrawGrid(50, 25, false, false, true, false);
	//ofEnableLighting();
	//light.enable();
	


	ofSetLineWidth(1.f);
	ofSetColor(255, 0, 200);
	world.drawDebug();

	//ofSetColor(100, 100, 100);
	//ground.draw();

	ofSetColor(225, 225, 225);
	//sphere->draw();

	ofSetColor(225, 225, 225);

	//if (ofGetFrameNum() % 30 == 0){
	//	vectorBox.push_back(new ofxBulletBox());
	//	((ofxBulletBox*)vectorBox[vectorBox.size() - 1])->create(world.world, ofVec3f(5, 50, 0), .05, .5, .5, .5);
	//	((ofxBulletBox*)vectorBox[vectorBox.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
	//	vectorBox[vectorBox.size() - 1]->add();
	//}

	//box•`‰æ
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
	//cylinder->draw();



	ofSetColor(225, 225, 225);
	//cone->draw();


	//’n–Ê•`‰æ
	ofSetLineWidth(1.5f);
	ofSetColor(255, 0, 0);
	ofLine(-50, 0, 0, 50, 0, 0);
	ofSetColor(0, 0, 255);
	ofLine(0, 0, -50, 0, 0, 50);
	ofSetColor(0, 255, 0);
	ofLine(0, -50, 0, 0, 50, 0);
	ofSetColor(200);

	ofSetLineWidth(1.f);
	for (int i = -25; i <= 25; i++) {
		ofLine(-25, 0, i, 25, 0, i);
		ofLine(i, 0, -25, i, 0, 25);
	}


	glDisable(GL_DEPTH_TEST);
	camera.end();

	//ƒeƒLƒXƒg•\Ž¦
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
			((ofxBulletBox*)vectorBox[vectorBox.size() - 1])->create(world.world, ofVec3f(0, 10, 0), .05, .5, .5, .5);
			((ofxBulletBox*)vectorBox[vectorBox.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
			//”½”­ŒW”A–€ŽCŒW”‚ð’Ç‰Á
			((ofxBulletBox*)vectorBox[vectorBox.size() - 1])->setProperties(0.5, 0.8);

			//‰‘¬‚ð’Ç‰Á
			((ofxBulletBox*)vectorBox[vectorBox.size() - 1])
				->applyCentralForce(btVector3(ofRandom(-10., 10.), ofRandom(-10., 10.), ofRandom(-10., 10.)));

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