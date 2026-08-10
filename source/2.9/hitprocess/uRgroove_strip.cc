// gemc headers
#include "uRgroove_strip.h"
#include "Randomize.hh"
#include "G4Poisson.hh"
#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES

vector<uRgroove_strip_found> uRgroove_strip::FindStrip(G4ThreeVector xyz , double Edep, uRgrooveConstants uRgroovec, double time, bool isProto)
{
    vector<uRgroove_strip_found> strip_found;
    uRgroove_strip_found ThisStrip;

    // Convert deposited energy to the number of primary electrons.
    int N_el = 1e6*Edep/uRgroovec.w_i;

    if (N_el == 0) {
        ThisStrip.numberID = -15000;
        ThisStrip.weight   = 1;
        ThisStrip.time     = -1;
        strip_found.push_back(ThisStrip);
        return strip_found;
    }

    N_el = G4Poisson(N_el*uRgroovec.gain);

    // Transform the hit position into the strip coordinate frame.
    // y_real is the coordinate perpendicular to the strip direction.
    double x_real = xyz.x()*cos(M_PI*uRgroovec.get_stereo_angle()/180) + xyz.y()*sin(M_PI*uRgroovec.get_stereo_angle()/180);
    double y_real = xyz.y()*cos(M_PI*uRgroovec.get_stereo_angle()/180) - xyz.x()*sin(M_PI*uRgroovec.get_stereo_angle()/180);
    double z_real = xyz.z();

    // HallC2026 local strip numbering, following the corrected uRwell scheme:
    // component = 1 ... number_of_strip for each sector and U/V readout layer.
    // With Yhalf = 5.12 cm and number_of_strip = 512, pitch = 0.2 mm.
    // This replaces the old cluster-centered renumbering that could produce component 0.
    double pitch = 2.0*uRgroovec.Yhalf/uRgroovec.number_of_strip;
    int stripID = (int) floor((y_real + uRgroovec.Yhalf)/pitch) + 1;

    // Reject hits outside the active strip range.
    if (stripID < 1 || stripID > uRgroovec.number_of_strip) {
        ThisStrip.numberID = -15000;
        ThisStrip.weight   = 1;
        ThisStrip.time     = -1;
        strip_found.push_back(ThisStrip);
        return strip_found;
    }

    // Drift-time contribution.
    double time_dz = fabs(-uRgroovec.Zhalf/cm + z_real/cm)/uRgroovec.v_drift;

    ThisStrip.numberID = stripID;
    ThisStrip.weight   = N_el;
    ThisStrip.time     = time + time_dz + G4RandGauss::shoot(0., uRgroovec.sigma_time);

    strip_found.push_back(ThisStrip);
    return strip_found;
}

double uRgroove_strip::Weight_td(int strip, double x, double y, double z, uRgrooveConstants uRgroovec, bool isProto){
	double wght;
	if(Build_strip(strip, uRgroovec)){
	 wght=( erf((strip_y+uRgroovec.get_strip_width(strip, isProto)/2.-y)/uRgroovec.sigma_td/sqrt(2))-erf((strip_y-uRgroovec.get_strip_width(strip, isProto)/2.-y)/uRgroovec.sigma_td/sqrt(2)))*
			 (erf((strip_x+strip_length/2.-x)/uRgroovec.sigma_td/sqrt(2))-erf((strip_x-strip_length/2.-x)/uRgroovec.sigma_td/sqrt(2)))/2./2.;
	 if (wght<0) wght=-wght;
	}else{
		wght =-1;
	}
	return wght;
}

bool uRgroove_strip::Build_strip(int strip, uRgrooveConstants uRgroovec ){
	
	//strip straight line -> y = mx +c;
	double m = tan(M_PI*uRgroovec.get_stereo_angle()/180);
	double c = strip*uRgroovec.get_strip_pitch()/cos(M_PI*uRgroovec.get_stereo_angle()/180);

   // Trapezoid coordinates
	G4ThreeVector A = {-uRgroovec.Xhalf_base, -uRgroovec.Yhalf, uRgroovec.Zhalf};
	G4ThreeVector B =  {uRgroovec.Xhalf_base, -uRgroovec.Yhalf, uRgroovec.Zhalf};
	G4ThreeVector C = {-uRgroovec.Xhalf_Largebase, uRgroovec.Yhalf, uRgroovec.Zhalf};
	G4ThreeVector D =  {uRgroovec.Xhalf_Largebase, uRgroovec.Yhalf, uRgroovec.Zhalf};
	


	// C-------------D //
	//  -------------  //
	//   -----------   //
	//    A-------B   //
	// Intersection points between strip straight line and Trapezoid straight lines
	
	G4ThreeVector AB_strip = intersectionPoint(m,c,A,B);
	G4ThreeVector BD_strip = intersectionPoint(m,c,B,D);
	G4ThreeVector CD_strip = intersectionPoint(m,c,C,D);
	G4ThreeVector AC_strip = intersectionPoint(m,c,A,C);
	
	vector< G4ThreeVector> strip_points ; // intersection point between strip and the trapezoid sides;
	
	// geometrical characteristic
	double length_strip=0;
	G4ThreeVector first_point;
	G4ThreeVector second_point;
	
	// check if the intersection point is on the segment defined by two points (i.e A and B)
	
	 if(uRgroovec.get_strip_kind()=="strip_v"){

		if(pointOnsegment(AC_strip, A, C)) {
			first_point=AC_strip;
			if(pointOnsegment(BD_strip, B, D)) second_point = BD_strip;
			if(pointOnsegment(CD_strip, C, D)) second_point = CD_strip;
			
		}else if(pointOnsegment(AB_strip, A, B)){
			first_point=AB_strip;
			
			if(pointOnsegment(BD_strip, B, D)) second_point = BD_strip;
			if(pointOnsegment(CD_strip, C, D)) second_point = CD_strip;
			
		}else{
			return false;
		}
	}
	
	
	
	 if(uRgroovec.get_strip_kind()=="strip_u"){

		if(pointOnsegment(BD_strip, B, D)){
			first_point=BD_strip;
			
			if(pointOnsegment(AC_strip, A, C)) second_point = AC_strip;
			if(pointOnsegment(CD_strip, C, D)) second_point = CD_strip;
		}else if (pointOnsegment(AB_strip, A, B)){
			first_point=AB_strip;
			if(pointOnsegment(AC_strip, A, C)) second_point = AC_strip;
			if(pointOnsegment(CD_strip, C, D)) second_point = CD_strip;
		}else{
			return false;
		}
		
	}
	
	length_strip = cal_length(first_point, second_point);
	
	strip_length = length_strip;
	strip_endpoint1 = first_point;
	strip_endpoint2 = second_point;


	G4ThreeVector strip_endpoint1_stripFrame = change_of_coordinates(strip_endpoint1, uRgroovec );
	G4ThreeVector strip_endpoint2_stripFrame = change_of_coordinates(strip_endpoint2, uRgroovec );
	
	strip_y = strip_endpoint1_stripFrame.y();
	strip_x = (strip_endpoint1_stripFrame.x() + strip_endpoint2_stripFrame.x())/2;
	
/*
	cout << "strip: "<<strip<< endl;
	cout << strip_endpoint1.x()<< " "<< strip_endpoint1.y()<<" "<<endl;
	cout << strip_endpoint2.x()<< " "<< strip_endpoint2.y()<<" "<<endl;
	cout <<"done"<<endl;
*/

	return true;
}

G4ThreeVector uRgroove_strip::change_of_coordinates( G4ThreeVector A, uRgrooveConstants uRgroovec){
	
	G4ThreeVector XYZ;
	XYZ.setX(A.x()*cos(M_PI*uRgroovec.get_stereo_angle()/180) + A.y()*sin(M_PI*uRgroovec.get_stereo_angle()/180));
    XYZ.setY(A.y()*cos(M_PI*uRgroovec.get_stereo_angle()/180) - A.x()*sin(M_PI*uRgroovec.get_stereo_angle()/180));
	XYZ.setZ(A.z());
	
	return XYZ;
}

G4ThreeVector uRgroove_strip::intersectionPoint(double m, double c, G4ThreeVector A, G4ThreeVector B){
	
	G4ThreeVector XY;
	double mT = (B.y()-A.y())/(B.x()-A.x());
	double cT = -mT*A.x()+A.y();
	
	XY.setX((cT-c)/(m-mT));
	XY.setY( m*XY.x() +c);
	XY.setZ(A.z());
	


	return XY;
	
}

bool uRgroove_strip::pointOnsegment(G4ThreeVector X, G4ThreeVector A, G4ThreeVector B){
	
	
	if((X.x()>= fmin(A.x(), B.x())) && (X.x()<=fmax(A.x(), B.x()))&&(X.y()>=fmin(A.y(), B.y())) && (X.y()<=fmax(A.y(), B.y()))){
		
		return true;
	}else{
		return false;
	}
}

double uRgroove_strip::cal_length(G4ThreeVector A, G4ThreeVector B){
	double length=0;
	length = sqrt(pow((A.x()-B.x()),2) + pow((A.y()-B.y()),2)) ;
	return length;
}

double uRgroove_strip::GetBinomial(double n, double p){
	double answer;
	answer=CLHEP::RandBinomial::shoot(n,p);
	//Very bad method when n=0 or p close to 0 or 1... return easily -1 in these case.
	//So need to help in the limit condition
	if (answer==-1){
		answer=n;
		if (p==0) answer=0;
	}
	return answer;
}

int uRgroove_strip::Number_of_strip(uRgrooveConstants uRgroovec){
	
	int N;
	// C-------------D //
	//  -------------  //
	//   -----------   //
	//    A-------B   //
	
	/*** number of strip in AB***/
	
	int n_AB = abs(2*uRgroovec.Xhalf_base/(uRgroovec.stripU_pitch/sin(M_PI*uRgroovec.get_stereo_angle()/180)));

	/** number of strip in CA **/
	double AC = sqrt((pow((uRgroovec.Xhalf_base-uRgroovec.Xhalf_Largebase),2) + pow((uRgroovec.Yhalf+uRgroovec.Yhalf),2)));
    double theta = acos(2*uRgroovec.Yhalf/(AC));
	int n_AC = AC/(uRgroovec.stripU_pitch/cos(theta-abs(M_PI*uRgroovec.get_stereo_angle())/180));

	N = n_AB + n_AC+1;
    return N;
}

int uRgroove_strip::strip_id(int i, uRgrooveConstants uRgroove ){
	int ID = 0;
	
	ID = Number_of_strip(uRgroove)/2+i;
	
	return ID;
	
}


