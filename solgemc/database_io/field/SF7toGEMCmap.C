#include <iomanip>
#include <iostream>
using namespace std;

void SF7toGEMCmap(string input_filename){

// TCanvas *c_gflux = new TCanvas("gflux","gflux",20,10,800,1200);
// c_gflux->Divide(1,2);
// c_gflux->cd(1);
// TH1F* hgflux = new TH1F("gflux","gflux",80,1.5,5.5);

ifstream input(input_filename.c_str());
if (input.good()) cout << "open SF7 file " << input_filename << " OK" <<endl;
else {cout << "can't open the file" << endl; return;}

int Num_R,Num_Z;
char textline[200];

  // reads and discard the first 27 lines of text
for (int k = 0; k<27; k++) input.getline(textline,200);
//readin R and Z info
input.getline(textline,200);
cout << textline << endl; 
input.getline(textline,200);
cout << textline << endl;
input >> textline >> textline >> textline >> textline >> Num_R >> Num_Z; //reads the line like "R and Z increments:   300   775"
cout << "R and Z increments:\t" << Num_R << "\t" << Num_Z << endl;
cout << "put these info into database" << endl;

// reads and discard the next 3 lines of text  
for (int k = 0; k<4; k++) input.getline(textline,200);

// reads in R Z Br Bz (R increase first when Z fixed)
const int constNum_R=Num_R+1,constNum_Z=Num_Z+1;
string R[constNum_R][constNum_Z],Z[constNum_R][constNum_Z],Br[constNum_R][constNum_Z],Bz[constNum_R][constNum_Z];
for (int j = 0; j<constNum_Z; j++) {
  for (int i = 0; i<constNum_R; i++) {
	input >> R[i][j] >> Z[i][j] >> Br[i][j] >> Bz[i][j];
	input.getline(textline,200); //get the rest of line
//       cout.width(10);
//       cout.setf(0,ios::floatfield);
//       cout.setf(ios::fixed,ios::floatfield);
//     cout.precision(6);
//     cout << scientific << 
//     cout << R[i][j] << "\t" <<  Z[i][j] <<  "\t" <<  Br[i][j] <<  "\t" <<  Bz[i][j] << endl;  
  }
}

input.close();

//write  R Z Br Bz (Z increase first when R fixed)
string output_filename=input_filename+".GEMCmap";
// string output_filename="GEMCmap";
ofstream output(output_filename.c_str(),ios::trunc);
for (int i = 0; i<constNum_R; i++) {
  for (int j = 0; j<constNum_Z; j++) {
    output << R[i][j] << "\t" <<  Z[i][j] <<  "\t" <<  Br[i][j] <<  "\t" <<  Bz[i][j] << endl; 
  }
}
// output.write();
output.close();
cout << "covert to GEMC map file " <<  output_filename << " OK" << endl;

}