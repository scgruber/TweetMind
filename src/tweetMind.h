#pragma once

#include "ofMain.h"
#include "ofxTwitter.h"
#include "ofxSelfOrganizingMap.h"

class tweetMind : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxTwitter* twitter;
		vector<Tweet> tweets;

		ofxSelfOrganizingMap* som;
		string somString;
		vector<string> genStrings;

};
