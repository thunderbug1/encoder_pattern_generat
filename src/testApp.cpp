#include "testApp.h"

//////////////////////////////////////////// DEFINE SWITCHES

#define poti
//#define encoder

#define radial

//#define grid

//////////////////////////////////////////// GENERAL SETTINGS

#define cm *37.70842744             //Pixel per cm (23"Display)        95.78 dpi
#define mm *3.770842744

float left_border   = 1.5 cm;         //-> Querformat
float top_border    = 1 cm;
float right_border  = 1.5 cm;
float bottom_border = 1 cm;

int width        = 21 * sqrt(2) cm;
int heigth       = 21 cm;                 //-> DIN A4
int barThickness = 1 cm;
int barLength    = width-right_border-left_border;         // = 26.6518 cm

int desired_dpi    = 400;                              //400 dpi -> 15.7 Pixel/mm
float scale_factor = desired_dpi / (1 cm * 2.54);
string Title = "Encoder Test 1";

//////////////////////////////////////////// ENCODER SETTINGS

float stripe_thickness = 1 mm;

//////////////////////////////////////////// POTI SETTINGS

int number_of_printing_layers = 1;
long double min_color = 0;
long double max_color = 22850;                      //max 65535
long double a = 0.00998285795977539;                // a,b,c are values to compensate the nonlinear relationship between colorvalue and opacity of the paper for IR-light
long double b = 0.191395321326135;
long double c = 0.000000000000001;

/////////////////////////////////////////// RADIAL SETTINGS

float outer_diameter = 37 mm;
float inner_diameter = 20 mm;

///////////////////////////////////////////

//--------------------------------------------------------------
void testApp::setup(){

    ofSetWindowTitle("Optical - Encoder/Potentiometer Wheel generator");
    //ofBackground(125,125,125,125);
    ofBackground(255,255,255,0);
    ofSetWindowShape(width,heigth);
    ofSetFrameRate(40);



#ifndef radial
    cout<<"entering not radial"<<endl;
    img.allocate(barLength * scale_factor+2,barThickness * scale_factor+2,OF_IMAGE_GRAYSCALE);                                          //->    65535 different Colours
    for(int x= 1;x < barLength * scale_factor;x++)
    {
        for(int y= 1;y < barThickness * scale_factor;y++)
        {
            img.setColor(x,y,65535);
        }
    }
    cout<<"leaving not radial"<<endl;
#else
    cout<<"entering radial"<<endl;
    //ofSetBackgroundAuto(false);
    img.allocate(outer_diameter*scale_factor+2,outer_diameter*scale_factor+2,OF_IMAGE_GRAYSCALE);
    for(int x= 1;x < outer_diameter * scale_factor;x++)
    {
        for(int y= 1;y < outer_diameter * scale_factor;y++)
        {
            img.setColor(x,y,65535);
        }
    }
    cout<<"leaving radial"<<endl;
#endif

#ifdef poti
#ifndef radial
    cout<<"entering poti"<<endl;
    for(int x=0; x < barLength * scale_factor-1; x++)           // x is the position or the opacity
    {

        long double opacity     = ofMap(x,0,barLength*scale_factor,0,100,true);        // = %of light comming through
        long double color_value = sqrt(opacity/a+b*b/4-c)-b/2;                  //% of color
        //if(color_value<0){color_value=0;}else if(color_value>100){color_value=100;}
        long double final_color = ofMap(color_value,0,100,min_color,max_color-1);
        ofShortColor c = final_color;
        //if(!(x%10)){cout<<(int)color_value<<endl;}

        for(int y=0;y < barThickness * scale_factor-1;y++)
        {
           img.setColor(x,y,c);
           //if(opacity >= 76.8 && opacity <= 77.2){cout<<ofMap(color_value,0,100,min_color,max_color)<<endl;}
        }
    }
    cout<<"leaving poti"<<endl;
#else
    cout<<"entering radial poti"<<endl;
    float x,y;
	float angle;
	// Use smaller steps on big circles
	float angleSteps = 0.5/inner_diameter ;

	//mesh.setMode(ofPrimitive)

	mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
	//meshOutline.setMode(OF_PRIMITIVE_LINE_LOOP);

	//mesh.setMode(OF_TRIANGLE_STRIP_MODE);
	//meshOutline.setMode(OF_LINE_LOOP_MODE);

	int index = 0;
	long double color = min_color;
	long double colorSteps = (max_color - min_color) / (360/angleSteps);
    //cout<<"angleSteps: "<<angleSteps<<" colorSteps: "<<colorSteps<<endl;
    int counter = 0;

	for (float angle = 0; angle < 90; angle+=angleSteps){
	    //if(counter==0){ counter=800; cout<<color<<endl;}else{ counter--;}
		color += colorSteps;
        //cout<<color<<endl;
		x = outer_diameter/2 * cos(angle);
		y = outer_diameter/2 * sin(angle);
		mesh.addVertex(ofVec3f(x,y,0));
		mesh.addColor(ofColor(color));

		x = inner_diameter/2 * cos(angle);
		y = inner_diameter/2 * sin(angle);
		mesh.addVertex(ofVec3f(x,y,0));
		mesh.addColor(ofColor(color));

	}

    cout<<"leaving radial poti"<<endl;

#endif
#endif

#ifdef encoder
#ifndef radial
    cout<<"entering encoder"<<endl;
    ofShortColor color;
    color = color.limit();
    int length = stripe_thickness * scale_factor;
    int offset = 0;

    for(int barcount = 0;barcount<1;barcount++)
    {

        for(int x=1; x < barLength * scale_factor-1; x++)
        {
            if(length==0)
            {
                length=stripe_thickness * scale_factor;
                if(color==0){color = color.limit();}else{color = 0;}
            }
            else
            {
                length--;
            }

            for(int y=0+offset;y < barThickness * scale_factor+offset-1;y++)
            {
                img.setColor(x,y,color);
            }
        }
        stripe_thickness *= 1.20;
        offset +=barThickness+1 cm;
    }
    cout<<"leaving encoder"<<endl;
#else
    cout<<"entering radial encoder"<<endl;
//    ofShortColor color;
//    color = color.limit();
//    int length = stripe_thickness * scale_factor;
//    float step_angle = 0.1;
//    float circumference = outer_diameter * PI * scale_factor;
//    float stripe_thickness_angle = 360 * length / circumference;
//    float stripe_angle = stripe_thickness_angle;
//    cout<<"length: "<<length<<" circumference: "<<circumference<<" stripe_thickness: "<<stripe_thickness<<endl;
//
//    for(float r=0;r<=360;r+=step_angle)
//    {
//        if(stripe_angle==0)
//        {
//            stripe_angle = stripe_thickness_angle;
//            if(color==0){color = color.limit();}else{color = 0;}
//        }
//        else
//        {
//            stripe_angle-=r;
//        }
//        //for(float l=inner_diameter;l<outer_diameter * scale_factor -1;l+=0.1)
//        //{
//            //cout<<"x: "<<(int)outer_diameter/2+l*cos(r)<<" y: "<<(int)outer_diameter/2+l*sin(r)<<endl;
//            img.setColor(outer_diameter/2+cos(r),outer_diameter/2+sin(r),color);
//        //}
//    }





    cout<<"leaving radial encoder"<<endl;
#endif
#endif
    img.update();

#ifdef radial

#endif
}


//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw(){

        test = true;
    ofPoint last;
    int r = 4 cm;
    ofTranslate(10 cm, 10 cm, 0);
    ofSetLineWidth(0.01);
    ofSetColor(125,126,125,255);
    ofSetBackgroundAuto(false);

        for(int i=0;i<360;i++)
    {
        //cout<<"sin("<<i<<"): "<<sin(i)<<"cos("<<i<<"): "<<cos(i)<<endl;
        last.set(r*sin(i),r*cos(i),0);
        ofLine(last.x,last.y,r*sin(i+1),r*cos(i+1));
    }


    //bar_border.
#ifndef radial
    img.draw(left_border,top_border,barLength,barThickness);
#else
   //img.draw(left_border,top_border,outer_diameter,outer_diameter);
   //if(test)
   //{
    glPushMatrix();

	//ofSetLineWidth(1);
	//ofSetColor(0, 60, 60);
	//meshOutline.drawFaces();
    ofTranslate(left_border+outer_diameter/2,top_border+outer_diameter/2,0);
	ofSetLineWidth(0);
	mesh.drawFaces();

	glPopMatrix();
	test = false;
   //}
#endif

    //////////////////////////////////////////////////////draw the grid
#ifdef grid
#ifndef radial
    ofSetColor(0,0,0,255);
    float y = barThickness+top_border;
    bool thick_line = true;

    for(float x=0;x<barLength + 0.2 cm;x += 0.5 cm)
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
    ofDrawBitmapString(Title,left_border+2 mm,barThickness+top_border + 15 mm);
#else

#endif
#endif
    ////////////////////////////////////////////////////
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
