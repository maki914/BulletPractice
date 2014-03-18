#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	//ofEnableSmoothing();
	ofBackground(255, 255, 255);

	//�J�����ݒ�
	camera.setDistance(20);
	camera.setPosition(ofVec3f(20, 10, 20));
	camera.setTarget(ofVec3f(0, 0, 0));

	//���C�e�B���O�ݒ�
	ofEnableLighting();
	light.enable();
	light.setSpotlight();
	light.setPointLight();
	light.setPosition(0, 0, 0);
	light.setAmbientColor(ofFloatColor(0.5, 0.5, 0.5, 1.0));
	light.setDiffuseColor(ofFloatColor(0.5, 0.5, 0.5));
	light.setSpecularColor(ofFloatColor(1.0, 1.0, 1.0));

	//ofxBullet�̐ݒ�
	world.setup();
	world.enableGrabbing();
	world.enableDebugDraw();
	world.disableMousePickingEvents();
	world.setCamera(&camera);
	world.setGravity(ofVec3f(0.f, -9.8f, 0.f));	//�d�͉����x�̐ݒ�

	//�f�o�b�O�\����off
	bDrawDebug = false;

	//����\��
	for (int i = -3; i < 3; i++){
		for (int j = -3; j < 3; j++){
			for (int k = 5; k < 15; k += 2){
				shapes.push_back(new ofxBulletSphere());
				//�����ʒu, ����, ���a�̐ݒ�
				((ofxBulletSphere*)shapes[shapes.size() - 1])->create(world.world, ofVec3f(i, k, j), 10., .5);
				//�����W���A���C�W����ǉ�
				((ofxBulletSphere*)shapes[shapes.size() - 1])->setProperties(0.5, 0.9);
				shapes[shapes.size() - 1]->add();
			}
		}
	}

	//����\��
	for (int i = -3; i < 3; i++){
		for (int j = -3; j < 3; j++){
			for (int k = 20; k < 30; k++){
				shapes.push_back(new ofxBulletBox());
				//�����ʒu, ����, �傫���̐ݒ�
				((ofxBulletBox*)shapes[shapes.size() - 1])->create(world.world, ofVec3f(i, k, j), 10., 1., 1., 1.);
				//�����W���A���C�W����ǉ�
				((ofxBulletBox*)shapes[shapes.size() - 1])->setProperties(0.5, 0.9);
				shapes[shapes.size() - 1]->add();
			}
		}
	}

	//�n�ʂ̐ݒ�
	ground.create(world.world, ofVec3f(0., 0., 0.), 0., 50.f, 0., 50.f);
	ground.setProperties(1., 1.); //(Restitution:�����W��, Friction:���C�W��)
	ground.add();
}


//--------------------------------------------------------------
void testApp::update() {
	world.update();
}

//--------------------------------------------------------------
void testApp::draw() {
	glEnable(GL_DEPTH_TEST);
	camera.begin();

	//�f�o�b�O�\���؂�ւ�
	if (bDrawDebug) world.drawDebug();

	//5�t���[�����ɏォ�甠�𗎂Ƃ�
	if (ofGetFrameNum() % 5 == 0){
		shapes.push_back(new ofxBulletBox());
		((ofxBulletBox*)shapes[shapes.size() - 1])->create(world.world, ofVec3f(0, 30, 0), .05, .5, .5, .5);
		//������ǉ�
		((ofxBulletBox*)shapes[shapes.size() - 1])
			->applyCentralForce(btVector3(ofRandom(-10, 10), ofRandom(-10, 10), ofRandom(-10, 10)));
		shapes[shapes.size() - 1]->add();
	}

	//�I�u�W�F�N�g�̕`��
	ofSetColor(220, 220, 220);
	for (int i = 0; i < shapes.size(); i++){			
		shapes[i]->draw(); 
	}
	
	//�n�ʕ`��
	ofSetLineWidth(1.f);
	ofSetColor(225, 225, 225);
	for (int i = -25; i <= 25; i++) {
		ofLine(-25, 0, i, 25, 0, i);
		ofLine(i, 0, -25, i, 0, 25);
	}

	glDisable(GL_DEPTH_TEST);
	camera.end();

	//�e�L�X�g�\��
	int shapesNum  = shapes.size();
	ofVec3f camPos = camera.getGlobalPosition();
	
	stringstream ss;
	ss << "FPS: " << ofToString(ofGetFrameRate(), 0) << endl;
	ss << "Shapes: " << shapesNum << endl;
	ss << "camPos: " << camPos.x << ", " << camPos.y << ", " << camPos.z << endl;
	ofSetColor(50);
	ofDrawBitmapString(ss.str().c_str(), 20, 20);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	ofVec3f mouseLoc = camera.screenToWorld(ofVec3f((float)ofGetMouseX(), (float)ofGetMouseY(), 0));
	ofVec3f camPos = camera.getGlobalPosition();
	
	switch (key){
		case 'b':
			shapes.push_back(new ofxBulletBox());
			//�����ʒu, ����, �傫����ݒ�
			((ofxBulletBox*)shapes[shapes.size() - 1])->create(world.world, mouseLoc, 1., .5, .5, .5);
			//�����W���A���C�W����ǉ�
			((ofxBulletBox*)shapes[shapes.size() - 1])->setProperties(0.5, 0.8);
			shapes[shapes.size() - 1]->add();
			break;
		case 's':
			shapes.push_back(new ofxBulletSphere());
			//(btDiscreteDynamicsWorld*, �ʒu, ����, ���a)
			((ofxBulletSphere*)shapes[shapes.size() - 1])->create(world.world, mouseLoc, 0.05, .5);
			//�����W���A���C�W����ǉ�
			((ofxBulletBox*)shapes[shapes.size() - 1])->setProperties(0.5, 0.8);
			shapes[shapes.size() - 1]->add();
			break;
		case ' ':
			shapes.push_back(new ofxBulletSphere());
			//(btDiscreteDynamicsWorld*, �ʒu, ����, ���a)
			((ofxBulletSphere*)shapes[shapes.size() - 1])->create(world.world, mouseLoc, 5., .5);
			//�����W���A���C�W����ǉ�
			((ofxBulletBox*)shapes[shapes.size() - 1])->setProperties(0.5, 0.8);
			//������ǉ�
			((ofxBulletBox*)shapes[shapes.size() - 1])->applyCentralForce(btVector3(camPos.x * -500, camPos.y * -500, camPos.z * -500 ));
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