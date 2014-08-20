/*
This script is used to get the fired module and its surrounded 6 module ID

inputs are hit_x hit_y unit is cm
module ID is given by column and row number of the module and the sector number(30 sectors in total).

coordinate definition is in readme.txt

written by Yuxiang Zhao (yxzhao@jlab.org)

*/

#include<iostream>
#include<fstream>

using namespace std;

void EC_map(string option,double hit_x=0,double hit_y=0){

	if (option != "find" && option != "convert") {cout << "wrong option" << endl; return;}
	
	//________________________________construct map_____________________________________________________
	
	ofstream OUTPUT_file;
	if (option == "convert") {OUTPUT_file.open("EC_map_parameters.txt");}
	
	ifstream INPUT_file;
	INPUT_file.open("EC_map_final.txt");
	if(!INPUT_file)cout<<"ERROR!!! Can't open EC_map_final.txt"<<endl;

	int num_module_in_row[54]={0};    //54 layers in y direction
	double y_bak[54]={100000};
	double x[54][50]={100000};           
	double y[54][50]={100000}; 
	
	double total_EC_module=0;
	for(int i=0;i<54;i++){ //54 rows
		INPUT_file>>num_module_in_row[i];
		num_module_in_row[i]=num_module_in_row[i]-1;  //first one is y coordinate
		total_EC_module+=num_module_in_row[i];
		double tmp_y;
		INPUT_file>>tmp_y;
		y_bak[i]=tmp_y;       //make a backup in order to judge which row a certain particle hits the EC
		if (option == "convert") {
		  OUTPUT_file << Form("num_y%i",i) << "\t" << "| " << num_module_in_row[i] << "\t| - | - | - |  - | - | - | - | - " << endl;
		  OUTPUT_file << Form("y%i",i) << "\t" << "| " << tmp_y << "\t| cm | - |  - | - | - | - | - | - " << endl;
		}		  
		for(int j=0;j<num_module_in_row[i];j++){
			INPUT_file>>x[i][j];
			y[i][j]=tmp_y;     // in each row , y coordinate is the same
			if (option == "convert") {
			  OUTPUT_file << Form("y%i_x%i",i,j) << "\t" << "| " << x[i][j] << "\t| cm | - |  - | - | - | - | - | - " << endl;
			}		  			
		}
		//cout<<num_module_in_row[i]<<"	"<<y[i][0]<<endl;

	}
	
	if (option == "convert") OUTPUT_file.close();
/*
	//check map here
	int check_row=0;
	for(int k=0;k<num_module_in_row[check_row];k++){
		cout<<x[check_row][k]<<"	"<<y[check_row][k]<<endl;
	}

*/
	//map construction finished here!!!
	
	//___________________________________find hit id ___________________________________________________
	if (option != "find") {return;}
	//input: x, y coordinate unit in cm
// 	double hit_x=100;  //unit: cm
// 	double hit_y=4.8;
	
	//outputs: fired module ID and its surrounded 6 modules ID
	//total number of EC modules will be printed out
	int hit_x_id;                   //once we get hit id, we can easily locate the hitted module coordinate
	int hit_y_id;
	int hit_around_x_id[6]={100000};      //around 6 modules, a variable label indicates how many surrounded modules are around the hitted module
	int hit_around_y_id[6]={100000};
	//___________________________________
	
	int first_y=0;
	int last_y=54-1;
	while( last_y!=first_y+1 ){
		int mid_y=(int)(first_y+last_y)/2;
		if(hit_y>y_bak[mid_y]){
			first_y=mid_y;
		}else if(hit_y<y_bak[mid_y]){
			last_y=mid_y;
		}else{
			first_y=mid_y;
			last_y=first_y+1;
		}
	}
	if( fabs(hit_y-y_bak[first_y])<=fabs(hit_y-y_bak[last_y]) ){
		hit_y_id=first_y;                                 //found y id
	}else{
		hit_y_id=last_y;
	}

	//then go and find x id
	int first_x=0;
	int last_x=num_module_in_row[hit_y_id]-1;   //last depends on which row the hit it is on
	while( last_x!=first_x+1 ){
		int mid_x=(int)(first_x+last_x)/2;
		if(hit_x>x[hit_y_id][mid_x]){
			first_x=mid_x;
		}else if(hit_x<x[hit_y_id][mid_x]){
			last_x=mid_x;
		}else{
			first_x=mid_x;
			last_x=first_x+1;
		}
	}
	if( fabs(hit_x-x[hit_y_id][first_x])<=fabs(hit_x-x[hit_y_id][last_x]) ){
		hit_x_id=first_x;            //found x id
	}else{
		hit_x_id=last_x;
	}

/*
	//check hit id here
	cout<<"hit_x_id "<<hit_x_id<<endl;
	cout<<"hit_y_id "<<hit_y_id<<endl;
*/
	//__________________________________find the surrounded other 6 modules________________________
	int tmp_x_id[15]={hit_x_id-7, hit_x_id-6, hit_x_id-5, hit_x_id-4, hit_x_id-3, hit_x_id-2, hit_x_id-1, hit_x_id, hit_x_id+1, hit_x_id+2, hit_x_id+3, hit_x_id+4, hit_x_id+5, hit_x_id+6, hit_x_id+7};
	int tmp_y_id[3]={hit_y_id-1, hit_y_id, hit_y_id+1};
	int label=0;
	for(int i=0;i<15;i++){// x scan
		for(int j=0;j<3;j++){  //y scan
			if(tmp_y_id[j]>=0&&tmp_y_id[j]<54&&tmp_x_id[i]>=0&&tmp_x_id[i]<num_module_in_row[tmp_y_id[j]]&&(tmp_x_id[i]!=hit_x_id || tmp_y_id[j]!=hit_y_id) ){ // in range
				if(sqrt( pow( (x[tmp_y_id[j]][tmp_x_id[i]]-x[hit_y_id][hit_x_id]),2 )+ pow((y[tmp_y_id[j]][tmp_x_id[i]]-y[hit_y_id][hit_x_id]),2 ))<15.0){
					hit_around_x_id[label]=tmp_x_id[i];
					hit_around_y_id[label]=tmp_y_id[j];
					label++;
				}
			}
		}
	}
/*
	cout<<"find  "<<label<<" around the hitted module"<<endl;
	cout<<"x_id	y_id"<<endl;
	cout<<hit_x_id<<"	"<<hit_y_id<<endl;
	for(int l=0;l<label;l++){
		cout<<hit_around_x_id[l]<<"	"<<hit_around_y_id[l]<<endl;
	}

*/
	//______________________________________module search is finished ____________________________________________________________________
	
	
	//__________deal with separating EC into 30 sectors______________________________________________________
	double sector_id[54][50]={100000};    //the structure is the same as x[54][50], y[54][50]   54 is the number of y rows
	for(int i=0;i<54;i++){
		for(int j=0;j<num_module_in_row[i];j++){
			TVector2 vec(x[i][j],y[i][j]);
			double phi_module=vec.Phi();
			for(int k=0;k<30;k++){   //30 sectors
				if(phi_module>=k*12.0/180.0*3.141592 && phi_module<(k+1.0)*12.0/180.0*3.141592){  //sector k
					sector_id[i][j]=k;
				}
			}
		}
	}

	//_______sector map is finished_______________________________________________________________________________
	cout<<"________total EC module: "<<total_EC_module<<endl;
	cout<<"find  "<<label<<" around the hitted module"<<endl;
	cout<<"x_id	y_id	sector_id"<<endl;
	cout<<hit_x_id<<"	"<<hit_y_id<<"	"<<sector_id[hit_y_id][hit_x_id]<<" ----> this module is hitted!"<<endl;
	for(int l=0;l<label;l++){
		cout<<hit_around_x_id[l]<<"	"<<hit_around_y_id[l]<<"	"<<sector_id[hit_around_y_id[l]][hit_around_x_id[l]]<<endl;
	}



}


