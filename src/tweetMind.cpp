#include "tweetMind.h"

//--------------------------------------------------------------
void tweetMind::setup() {
    twitter = new ofxTwitter();
    twitter->setup();
    ofSetBackgroundAuto(false);
    ofSetFrameRate(30);

    // Range of printable ASCII characters
    double minInstance[1] = { 36 };
    double maxInstance[1] = { 126 };

    som = new ofxSelfOrganizingMap();
    som->setFeaturesRange(1, minInstance, maxInstance);
    som->setMapSize(160,160);
    som->setNumIterations(10000);
    som->setup();

    somString = string(160, ' ');
}

//--------------------------------------------------------------
void tweetMind::update(){
    twitter->startTwitterQuery("news", 10);
    tweets = twitter->getLatestResponse();

    // cout << tweets.begin()->print() << endl << "Begin update call" << endl;

    if (tweets.begin()->title.size() > 10) {

        for(vector<Tweet>::iterator it = tweets.begin(); it != tweets.end(); ++it) {

            if(it->title.size() <= 10) break;

            // Take a random character from the tweet
            char c = it->title[ofRandom(it->title.size())];
            double instance[1] = { (double) c};

            som->updateMap(instance);
        }

        cout << "Map: [ ";

        for (int i=0; i < 160; i++) {
            double* somChar = som->getMapAt(i,i);
            char c = (char) fabs(somChar[0]);
            if (c < 32)
                c = 32;
            else if (c > 126)
                c = 126;
            somString[i] = c;
            cout << ofToString(somChar[0]) << " ";
        }

        cout << "]" << endl;

        // Fisher-Yates shuffle the string
//        for(int i=somString.size()-1; i>0; i--) {
//            int j = ofRandom(i);
//            char tmp = somString[j];
//            somString[j] = somString[i];
//            somString[i] = tmp;
//        }

        genStrings.push_back(somString);
    }
}

//--------------------------------------------------------------
void tweetMind::draw(){
    cout << "Generated Tweet: " << somString << endl;

    ofEnableAlphaBlending();
    ofSetColor(0,0,0,32);
    ofRect(0,0,ofGetWidth(),ofGetHeight());
    ofDisableAlphaBlending();
    ofSetColor(255,255,255);

    while(tweets.size() > 0) {
        string name = tweets.begin()->author.name;
        string t = "@"+name+"\n    "+tweets.begin()->title;
        int xcoord = (((int)name[0])*((int)name[1])*((int)name[2]))%799;
        int ycoord = (((int)name[3])*((int)name[4])*((int)name[5]))%601;
        ofDrawBitmapString(t, xcoord, ycoord);
        tweets.erase(tweets.begin());
    }

    ofEnableAlphaBlending();
    ofSetColor(255,0,0, 64);
    for(int i=genStrings.size()-1; i > 0; i--) {
        ofDrawBitmapString((genStrings.at(i)), 0, 16*(genStrings.size()-i));
    }

    ofDisableAlphaBlending();
}

//--------------------------------------------------------------
void tweetMind::keyPressed(int key){

}

//--------------------------------------------------------------
void tweetMind::keyReleased(int key){

}

//--------------------------------------------------------------
void tweetMind::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void tweetMind::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void tweetMind::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void tweetMind::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void tweetMind::windowResized(int w, int h){

}

//--------------------------------------------------------------
void tweetMind::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void tweetMind::dragEvent(ofDragInfo dragInfo){

}
