#include "testApp.h"

#define cm *37.70842744             //Pixel per cm (monitor)         95.78 dpi
#define mm *3.770842744

float left_border = 1.5 cm;         //-> Querformat
float top_border = 1 cm;
float right_border = 1.5 cm;
float bottom_border = 1 cm;

int width = 21 * sqrt(2) cm;
int heigth = 21 cm;                 //-> DIN A4
int barThickness = 1 cm;
int barLength = width-right_border-left_border;         // = 26.6518 cm

int desired_dpi = 400;                              //400 dpi -> 15.7 Pixel/mm
float scale_factor = desired_dpi / (1 cm * 2.54);

long double min_color = 1852;
long double max_color = 24546;                      //->from experiments


//--------------------------------------------------------------
void testApp::setup(){

    ofSetWindowTitle("Optical - Encoder/Potentiometer Wheel generator");
    ofBackground(255,255,255,125);
    ofSetWindowShape(width,heigth);
    ofSetFrameRate(40);
    //ofSetColor(255,255,255,0);


    //img.allocate(2481,3507,OF_IMAGE_GRAYSCALE);             //-> 1cm = 37.70842744 pixel  (23"Display)
    img.allocate(barLength * scale_factor,1 cm * scale_factor,OF_IMAGE_GRAYSCALE);
    ofShortColor c;                                             //->    65535 different Colours
    cout<<barLength<<endl;

    for(int x=0; x < barLength * scale_factor-1; x++)           // x is the position or the opacity
    {
        ////////////////////////////////////////////////////Test1

        //c.set(ofMap(x,0,barLength*scale_factor,0,65535,true));

        ////////////////////////////////////////////////////Test2

        //c.set(ofMap(x,0,barLength*scale_factor,0,24546,true));

        ///////////////////////////////////////////////////Test3

//        long double gradient = ofMap(x,0,barLength*scale_factor,1852,24546,true);
//        long double regression = 0.000028818272528*x*x + 0.176412980911001*x + 1523.589885546850000;     // regression:      y = 0.000028818272528*x*x + 0.176412980911001*x + 1523.589885546850000;        (x in cm)
//        long double linear_approximation = x*0.962655677441282;                                // lineare näherung:    y = x*0.962655677441282
//        long double difference = regression - linear_approximation;
//        c.set(gradient + difference);

        ///////////////////////////////////////////////////Test4

//        long double gradient = ofMap(x,0,barLength*scale_factor,1852,24546,true);
//        long double regression1 = 0.000028818272528*x*x + 0.176412980911001*x + 1523.589885546850000;     // regression1:      y = 0.000028818272528*x*x + 0.176412980911001*x + 1523.589885546850000;        (x in cm)
//        long double regression2 = 0.000023953166946*x*x + 0.135438706518793*x + 3379.09520090785;         // regression2: y = 0.000023953166946x2 + 0.135438706518793x + 3379.095200907850000
//        long double linear_approximation = x*0.962655677441282;                                // lineare näherung:    y = x*0.962655677441282
//        long double difference = regression1 + regression2 - linear_approximation;
//        c.set(gradient + difference);

        //////////////////////////////////////////////////Tets5

//        long double gradient = ofMap(x,0,barLength*scale_factor,1852,24546,true);
//        long double regression = 0.000028818272528*x*x + 0.176412980911001*x + 1523.589885546850000;     // regression:      y = 0.000028818272528*x*x + 0.176412980911001*x + 1523.589885546850000;        (x in cm)
//        long double linear_approximation = x*0.962655677441282;                                // lineare näherung:    y = x*0.962655677441282
//        long double difference = linear_approximation - regression;
//        c.set(gradient + difference);

        ///////////////////////////////////////////////////Test6

//        long double gradient = ofMap(x,0,barLength*scale_factor,1852,24546,true);
//        long double regression1 = 0.000028818272528*x*x + 0.176412980911001*x + 1523.589885546850000;     // regression:      y = 0.000028818272528*x*x + 0.176412980911001*x + 1523.589885546850000;        (x in cm)
//        long double regression2 = 0.000000000000197*x*x*x*x - 0.000000009564970*x*x*x + 0.000122502879241*x*x - 0.159912440583735*x - 3861.98157911452000;       //y = 0.000000000000197*x*x*x*x - 0.000000009564970*x*x*x + 0.000122502879241*x*x - 0.159912440583735*x - 3861.98157911452000
//
//        long double linear_approximation = x*0.962655677441282;                                // lineare näherung:    y = x*0.962655677441282
//        long double difference = linear_approximation - regression1 - regression2;
//        c.set(gradient + difference);

        //////////////////////////////////////////////////

        long double opacity= ofMap(x,0,barLength*scale_factor,0,100,true);        // = %of light comming through
        long double a = 0.008326265045988;
        long double b = 0.191395321326135;
        long double c = 6.207080117114610;
        long double color_value = sqrt(opacity/a+b^2/4-c)-b/2;                  //% of color

        for(int y=0;y < barThickness * scale_factor-1;y++)
        {
           img.setColor(x,y,ofMap(color_value,0,100,min_color,max_color);
        }
    }
    img.update();

    bar_border.set(left_border,top_border,barLength,barThickness);

}


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

    //bar_border.

    img.draw(left_border,top_border,barLength,barThickness);

    //////////////////////////////////////////////////////draw the grid
    ofPushStyle();
    ofSetColor(0,0,0,255);
    float y = barThickness+top_border;
    bool thick_line = true;

    for(float x=0;x<barLength + 0.5 cm;x += 0.5 cm)
    {
        if(thick_line)
        {
            ofLine(x+left_border,y,x+left_border,y + 5 mm);
            ofDrawBitmapString(ofToString((int)(x / (1 cm)+0.5)),x+left_border,y + 10 mm);
        }
        else
        {
            ofLine(x+left_border,y,x+left_border,y + 2 mm);
        }
        thick_line = !thick_line;
    }
    ////////////////////////////////////////////////////
    ofPopStyle();

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

    if(key == 's')
    {
        ofImage save;
        save.grabScreen(0,0,ofGetWidth(),ofGetHeight());
        save.saveImage("export.png");
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
