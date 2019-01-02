#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(0);
	ofEnableDepthTest();

	this->fbo1.allocate(ofGetWidth(), ofGetHeight());
	this->fbo2.allocate(ofGetWidth(), ofGetHeight());
	this->shader.load("shader/shader.vert", "shader/shader.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

	this->fbo1.begin();
	ofClear(0);

	float radius = 300;
	ofBeginShape();
	for (int deg = 0; deg < 360; deg += 3) {

		glm::vec2 noise_point = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
		float noise_radius = ofMap(ofNoise(noise_point.x * 0.003, noise_point.y * 0.003, ofGetFrameNum() * 0.005), 0, 1, radius * 0.5, radius);

		ofVertex(noise_radius * cos(deg * DEG_TO_RAD) + ofGetWidth() * 0.5, noise_radius * sin(deg * DEG_TO_RAD) + ofGetHeight() * 0.5);
	}
	ofEndShape();

	this->fbo1.end();

	this->fbo2.begin();
	ofClear(0);

	for (int x = 0; x < ofGetWidth(); x += 120) {

		ofDrawRectangle(x, 0, 60, ofGetHeight());
	}

	this->fbo2.end();
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofFill();
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniformTexture("tex1", this->fbo1.getTexture(), 1);
	this->shader.setUniformTexture("tex2", this->fbo2.getTexture(), 2);

	ofDrawRectangle(glm::vec2(0, 0), ofGetWidth(), ofGetHeight());

	this->shader.end();
}

//--------------------------------------------------------------
int main() {

	ofGLWindowSettings settings;
	settings.setGLVersion(3, 2);
	settings.setSize(720, 720);
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}