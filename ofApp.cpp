#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetCircleResolution(60);
	ofNoFill();

	this->radius = 250;
	ofColor color;
	for (int deg = 0; deg < 360; deg += 1) {

		auto location = glm::vec2(this->radius * cos(deg * DEG_TO_RAD), this->radius * sin(deg * DEG_TO_RAD));
		this->base_location_list.push_back(location);
		color.setHsb(ofMap((deg * 2) % 360, 0, 360, 0, 255), 255, 255);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->log_list.clear();

	for (int i = 0; i < this->base_location_list.size(); i++) {

		vector<glm::vec2> log;
		log.push_back(this->base_location_list[i]);
		this->log_list.push_back(log);
	}

	int step = 1;
	for (int i = 0; i < this->log_list.size(); i++) {

		int k = 0;
		while (true) {

			auto deg = ofMap(ofNoise(glm::vec3(this->log_list[i].back() * 0.015, ofGetFrameNum() * 0.008 + k * 0.001)), 0, 1, -720, 720);
			auto next = this->log_list[i].back() + glm::vec2(step * cos(deg * DEG_TO_RAD), step * sin(deg * DEG_TO_RAD));

			if (glm::distance(glm::vec2(0, 0), next) > this->radius - 50 && glm::distance(glm::vec2(0, 0), next) < this->radius + 50) {

				this->log_list[i].push_back(next);
			}
			else {

				break;
			}

			k++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	ofSetLineWidth(2);
	for (int i = 0; i < this->log_list.size(); i++) {

		ofSetColor(this->color_list[i]);

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();
	}

	ofSetLineWidth(1);
	ofSetColor(0, 64);
	ofDrawCircle(glm::vec2(), this->radius - 50);
	ofDrawCircle(glm::vec2(), this->radius);
	ofDrawCircle(glm::vec2(), this->radius + 50);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}