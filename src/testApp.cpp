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
	camera.setPosition(ofVec3f(20, 10, 20));
	//camera.setPosition(ofVec3f(0, -7.f, -10.f));
	//camera.lookAt(ofVec3f(0, 0, 0), ofVec3f(0, 1, 0));
	camera.setTarget(ofVec3f(0, 0, 0));
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
	world.disableMousePickingEvents();
	world.setCamera(&camera);
	world.setGravity(ofVec3f(0.f, -9.8f, 0.f));	//d—Í‰Á‘¬“x

	//ƒfƒoƒbƒO•\Ž¦‚ðoff
	bDrawDebug = false;


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

	//‹…‚ð•\Ž¦
	for (int i = -3; i < 3; i++){
		for (int j = -3; j < 3; j++){
			for (int k = 5; k < 15; k += 2){
				shapes.push_back(new ofxBulletSphere());
				//(btDiscreteDynamicsWorld*, ˆÊ’u, Ž¿—Ê, ”¼Œa)
				((ofxBulletSphere*)shapes[shapes.size() - 1])->create(world.world, ofVec3f(i, k, j), 10., .5);
				//((ofxBulletBox*)shapes[shapes.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
				//”½”­ŒW”A–€ŽCŒW”‚ð’Ç‰Á
				((ofxBulletSphere*)shapes[shapes.size() - 1])->setProperties(0.5, 0.9);
				shapes[shapes.size() - 1]->add();
			}
		}
	}

	//” ‚ð•\Ž¦
	for (int i = -3; i < 3; i++){
		for (int j = -3; j < 3; j++){
			for (int k = 20; k < 30; k++){
				shapes.push_back(new ofxBulletBox());
				//(btDiscreteDynamicsWorld*, ˆÊ’u, Ž¿—Ê, ”¼Œa)
				((ofxBulletBox*)shapes[shapes.size() - 1])->create(world.world, ofVec3f(i, k, j), 10., 1., 1., 1.);
				//((ofxBulletBox*)shapes[shapes.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
				//”½”­ŒW”A–€ŽCŒW”‚ð’Ç‰Á
				((ofxBulletBox*)shapes[shapes.size() - 1])->setProperties(0.5, 0.9);
				shapes[shapes.size() - 1]->add();
			}
		}
	}

	//joint—p‚Ì” ‚ð•\Ž¦
	jBox.push_back(new ofxBulletBox());
	((ofxBulletBox*)jBox[jBox.size() - 1])->create(world.world, ofVec3f(10, 5, 5), 10., 2., 2., 2.);
	jBox[jBox.size() - 1]->add();

	jBox.push_back(new ofxBulletBox());
	((ofxBulletBox*)jBox[jBox.size() - 1])->create(world.world, ofVec3f(15, 5, 5), 10., 3., 3., 3.);
	jBox[jBox.size() - 1]->add();

	//” ‚Éjoint‚ð’Ç‰Á
	joints.push_back(new ofxBulletJoint());
	joints[joints.size() - 1]->create(world.world, jBox[0], ofVec3f(jBox[1]->getPosition()));
	joints[joints.size() - 1]->add();


	ground.create(world.world, ofVec3f(0., 0., 0.), 0., 50.f, 0., 50.f);
	ground.setProperties(1., 1.); //(Restitution:”½”­ŒW”, Friction:–€ŽCŒW”)
	ground.add();
}


//--------------------------------------------------------------
void testApp::update() {
	world.update();
	ofVec3f mousePos = camera.screenToWorld(ofVec3f((float)ofGetMouseX(), (float)ofGetMouseY(), 0));

	joints[joints.size() - 1]->updatePivotPos(ofVec3f(jBox[1]->getPosition()), 1.f);
	//ofSetWindowTitle(ofToString(ofGetFrameRate(), 0));
}

//--------------------------------------------------------------
void testApp::draw() {
	glEnable(GL_DEPTH_TEST);
	camera.begin();
	//ofRotateX(45);
	//ofRotateY(-45);
	//light.disable();
	ofDisableAlphaBlending();
	ofDisableBlendMode();

	//joints[joints.size()-1]


	//ofDrawGrid(50, 25, false, false, true, false);
	//ofEnableLighting();
	//light.enable();



	ofSetLineWidth(1.f);
	ofSetColor(255, 0, 200);

	//ƒfƒoƒbƒO•\Ž¦Ø‚è‘Ö‚¦
	if (bDrawDebug) {
		world.drawDebug();
		ofSetLineWidth(1.5f);
		ofSetColor(255, 0, 0);
		ofLine(-50, 0, 0, 50, 0, 0);	//xŽ²
		ofSetColor(0, 0, 255);
		ofLine(0, 0, -50, 0, 0, 50);	//yŽ²
		ofSetColor(0, 255, 0);
		ofLine(0, -50, 0, 0, 50, 0);	//zŽ²
		ofSetColor(200);
	}
	//ofSetColor(100, 100, 100);
	//ground.draw();

	ofSetColor(225, 225, 225);
	//sphere->draw();



	//if (ofGetFrameNum() % 30 == 0){
	//	shapes.push_back(new ofxBulletBox());
	//	((ofxBulletBox*)shapes[shapes.size() - 1])->create(world.world, ofVec3f(5, 50, 0), .05, .5, .5, .5);
	//	((ofxBulletBox*)shapes[shapes.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
	//	shapes[shapes.size() - 1]->add();
	//}

	//•`‰æ
	ofSetColor(225, 225, 225);
	for (int i = 0; i < shapes.size(); i++){
		shapes[i]->draw();
	}

	ofSetColor(255, 100, 100);
	for (int i = 0; i < jBox.size(); i++){
		jBox[i]->draw();
	}
	//ofPushStyle();
	//shapesMat.begin();
	//for (int i = 0; i < shapes.size(); i++) {
	//	shapes[i]->draw();
	//}
	//shapesMat.end();
	//ofPopStyle();



	//’n–Ê•`‰æ
	ofSetLineWidth(1.f);
	ofSetColor(225, 225, 225);
	for (int i = -25; i <= 25; i++) {
		ofLine(-25, 0, i, 25, 0, i);
		ofLine(i, 0, -25, i, 0, 25);
	}


	glDisable(GL_DEPTH_TEST);
	camera.end();

	//ƒeƒLƒXƒg•\Ž¦
	int shapesNum = shapes.size();
	ofVec3f mouseLoc = camera.screenToWorld(ofVec3f((float)ofGetMouseX(), (float)ofGetMouseY(), 0));
	ofVec3f camEuler = camera.getOrientationEuler();
	ofVec3f camPos = camera.getGlobalPosition();
	ofVec3f camLook = camera.getLookAtDir();
	//camera.get
	//ofVec3f v1(1, 0, 0);
	//ofVec3f v2 = v1.getRotated(45, 45, 90);
	//ofVec3f v3 = v2.getRotated(45, 0, 0);
	//ofVec3f v4 = v3.getRotated(0, 45, 0);

	ofNode	camTar = camera.getTarget();
	//ofNode camTar = camera.getTarget();
	stringstream ss;
	//ss << "v2: " << v2.x << ", " << v2.y << ", " << v2.z << endl;
	//ss << "v3: " << v3.x << ", " << v3.y << ", " << v3.z << endl;
	//ss << "v4: " << v4.x << ", " << v4.y << ", " << v4.z << endl;
	ss << "FPS: " << ofToString(ofGetFrameRate(), 0) << endl;
	ss << "Shapes: " << shapesNum << endl;
	ss << "camPos: " << camPos.x << ", " << camPos.y << ", " << camPos.z << endl;
	//ss << "camTar: " << camTar.getX() << ", " << camTar.getY() << ", " << camTar.getZ() << endl;
	//ss << "camEuler: " << camEuler.x << ", " << camEuler.y << ", " << camEuler.z << endl;
	//ss << "camTar: " << camera.getTarget().getX() << endl;
	//ss << "mouseLoc: " << mouseLoc.x << ", " << mouseLoc.y << ", " << mouseLoc.z << endl;
	//ss << "distance: " << camera.getDistance() << endl;
	//ss << "diff: " << camPos.x - mouseLoc.x << ", " << camPos.y - mouseLoc.y << ", " << (camPos.z - mouseLoc.z) * -1 << endl;
	ofSetColor(50);
	ofDrawBitmapString(ss.str().c_str(), 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	ofVec3f mouseLoc = camera.screenToWorld(ofVec3f((float)ofGetMouseX(), (float)ofGetMouseY(), 0));
	float camPosX = camera.getGlobalPosition().x;
	float camPosY = camera.getGlobalPosition().y;
	float camPosZ = camera.getGlobalPosition().z;


	switch (key){
	case 'b':
		shapes.push_back(new ofxBulletBox());
		//(btDiscreteDynamicsWorld*, ˆÊ’u, Ž¿—Ê, ”¼Œa)
		((ofxBulletBox*)shapes[shapes.size() - 1])->create(world.world, mouseLoc, 1., .5, .5, .5);
		((ofxBulletBox*)shapes[shapes.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
		//”½”­ŒW”A–€ŽCŒW”‚ð’Ç‰Á
		((ofxBulletBox*)shapes[shapes.size() - 1])->setProperties(0.5, 0.8);

		//‰‘¬‚ð’Ç‰Á
		((ofxBulletBox*)shapes[shapes.size() - 1])
			->applyCentralForce(btVector3(ofRandom(-10., 10.), ofRandom(-10., 10.), ofRandom(-10., 10.)));

		shapes[shapes.size() - 1]->add();
		break;
	case 's':
		shapes.push_back(new ofxBulletSphere());
		//(btDiscreteDynamicsWorld*, ˆÊ’u, Ž¿—Ê, ”¼Œa)
		((ofxBulletSphere*)shapes[shapes.size() - 1])->create(world.world, mouseLoc, 0.05, .5);
		((ofxBulletSphere*)shapes[shapes.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
		//”½”­ŒW”A–€ŽCŒW”‚ð’Ç‰Á
		((ofxBulletBox*)shapes[shapes.size() - 1])->setProperties(0.5, 0.8);

		//‰‘¬‚ð’Ç‰Á
		((ofxBulletSphere*)shapes[shapes.size() - 1])
			->applyCentralForce(btVector3(ofRandom(-10., 10.), ofRandom(-10., 10.), ofRandom(-10., 10.)));

		shapes[shapes.size() - 1]->add();
		break;
	case ' ':
		shapes.push_back(new ofxBulletSphere());
		//(btDiscreteDynamicsWorld*, ˆÊ’u, Ž¿—Ê, ”¼Œa)
		((ofxBulletSphere*)shapes[shapes.size() - 1])->create(world.world, mouseLoc, 5., .5);
		((ofxBulletSphere*)shapes[shapes.size() - 1])->setActivationState(DISABLE_DEACTIVATION);
		//”½”­ŒW”A–€ŽCŒW”‚ð’Ç‰Á
		((ofxBulletBox*)shapes[shapes.size() - 1])->setProperties(0.5, 0.8);

		//‰‘¬‚ð’Ç‰Á
		((ofxBulletBox*)shapes[shapes.size() - 1])
			->applyCentralForce(btVector3(camPosX * -500, camPosY * -500, camPosZ * -500));


		shapes[shapes.size() - 1]->add();
		break;
	case 'd':
		bDrawDebug = !bDrawDebug;
		break;
	case 'r':
		camera.setPosition(ofVec3f(20, 10, 20));
		camera.setTarget(ofVec3f(0, 0, 0));
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