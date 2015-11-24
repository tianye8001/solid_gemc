#include<iostream>
#include<fstream>

using namespace std;

void EC_map(string option,double hit_x=0,double hit_y=0){

	if (option != "find" && option != "convert") {cout << "wrong option" << endl; return;}
	
	//________________________________construct map_____________________________________________________
		
	ifstream INPUT_file;
	INPUT_file.open("map_FAEC_ANL_20130628.txt");
	if(!INPUT_file)cout<<"ERROR!!! Can't open map_FAEC_ANL_20130628.txt"<<endl;	

	int num_module_in_row[54]={0};    //54 layers in y direction
	double y_bak[54]={100000};
	double x[54][50]={100000};           
	double y[54][50]={100000}; 
	
	
	double total_module=0;
	for(int i=0;i<54;i++){ //54 rows
		INPUT_file>>num_module_in_row[i];
		num_module_in_row[i]=num_module_in_row[i]-1;  //first one is y coordinate
		total_module+=num_module_in_row[i];
		double tmp_y;
		INPUT_file>>tmp_y;
		y_bak[i]=tmp_y;       //make a backup in order to judge which row a certain particle hits the EC
		for(int j=0;j<num_module_in_row[i];j++){
			INPUT_file>>x[i][j];
			y[i][j]=tmp_y;     // in each row , y coordinate is the same
		}
		//cout<<num_module_in_row[i]<<"	"<<y[i][0]<<endl;

	}
	
	//__________deal with id______________________________________________________
	int id[54][50]={100000};    //the structure is the same as x[54][50], y[54][50]   54 is the number of y rows
	int counter_id=0;
	for(int i=0;i<54;i++){
		for(int j=0;j<num_module_in_row[i];j++){
			counter_id++;
			id[i][j]=counter_id;			
// 			cout << id[i][j] << endl;
		}
	}	
	//__________id is finished________________________
	
	//__________deal with separating EC into 30 sectors________________________
	int sector[54][50]={100000};    //the structure is the same as x[54][50], y[54][50]   54 is the number of y rows
	for(int i=0;i<54;i++){
		for(int j=0;j<num_module_in_row[i];j++){
			TVector2 vec(x[i][j],y[i][j]);
			double phi_module=vec.Phi();
			for(int k=0;k<30;k++){   //30 sectors
				if(phi_module>=k*12.0/180.0*3.141592 && phi_module<(k+1.0)*12.0/180.0*3.141592){  //sector k
					sector[i][j]=k+1;
// 				    cout << sector[i][j] << endl;				
				}
			}
		}
	}

	//_______sector map is finished___________________________________________	
	
	int total_module_active=0;
	int status[54][50]={100000};    //the structure is the same as x[54][50], y[54][50]   54 is the number of y rows
	for(int i=0;i<54;i++){
		for(int j=0;j<num_module_in_row[i];j++){
		  status[i][j]=1; //all active for PVDIS FAEC
		  if (status[i][j]==1) total_module_active++;
		}
	}

	if (option == "convert") {
	  
	  ofstream OUTPUT_file;
	  OUTPUT_file.open("map_FAEC_ANL_20130628_PVDIS_parameters.txt");

	  OUTPUT_file << "total_module" << "\t" << "| " << total_module << "\t| counts | - | - |  - | - | - | - | - " << endl;	  
	  OUTPUT_file << "total_module_active" << "\t" << "| " << total_module_active << "\t| counts | - | - |  - | - | - | - | - " << endl;   
	  
// 	  OUTPUT_file << "idymax" << "\t" << "| " << 54 << "\t| - | - | - |  - | - | - | - | - " << endl;	  	  
// 	  
// 	  for(int i=0;i<54;i++){
// 	      OUTPUT_file << Form("idxmax_idy%i",i+1) << "\t" << "| " << num_module_in_row[i] << "\t| - | - | - |  - | - | - | - | - " << endl;
// 	      OUTPUT_file << Form("y_idy%i",i+1) << "\t" << "| " << tmp_y << "\t| cm | - |  - | - | - | - | - | - " << endl;
// 		  
// 		  for(int j=0;j<num_module_in_row[i];j++){
// 		    OUTPUT_file << Form("status_idy%i_idx%i_id%i_sector%i",i+1,j+1,id[i][j],sector[i][j]) << "\t" << "| " << status[i][j] << "\t| - | - |  - | - | - | - | - | - " << endl;		    
// 		    OUTPUT_file << Form("x_idy%i_idx%i_id%i_sector%i",i+1,j+1,id[i][j],sector[i][j]) << "\t" << "| " << x[i][j] << "\t| cm | - |  - | - | - | - | - | - " << endl;		    
// 		  }		  			
// 	  }	
	  
	  for(int i=0;i<54;i++){	  
	    for(int j=0;j<num_module_in_row[i];j++){
	      OUTPUT_file << Form("id%i_status",id[i][j]) << "\t" << "| " << status[i][j] << "\t| counts | - | - |  - | - | - | - | - " << endl;
	      OUTPUT_file << Form("id%i_idy",id[i][j]) << "\t" << "| " << i+1 << "\t| counts | - | - |  - | - | - | - | - " << endl;
	      OUTPUT_file << Form("id%i_idx",id[i][j]) << "\t" << "| " << j+1 << "\t| counts | - | - |  - | - | - | - | - " << endl;
	      OUTPUT_file << Form("id%i_y",id[i][j]) << "\t" << "| " << y[i][j] << "\t| cm | - | - |  - | - | - | - | - " << endl;
	      OUTPUT_file << Form("id%i_x",id[i][j]) << "\t" << "| " << x[i][j] << "\t| cm | - | - |  - | - | - | - | - " << endl;	      
	      OUTPUT_file << Form("id%i_sector",id[i][j]) << "\t" << "| " << sector[i][j] << "\t| counts | - | - |  - | - | - | - | - " << endl;
	    }		  			
	  }	
	  
	  OUTPUT_file.close();
	}
	
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
	int hit_idx;                   //once we get hit id, we can easily locate the hitted module coordinate
	int hit_idy;
	int hit_around_idx[6]={100000};      //around 6 modules, a variable label indicates how many surrounded modules are around the hitted module
	int hit_around_idy[6]={100000};
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
		hit_idy=first_y;                                 //found y id
	}else{
		hit_idy=last_y;
	}

	//then go and find x id
	int first_x=0;
	int last_x=num_module_in_row[hit_idy]-1;   //last depends on which row the hit it is on
	while( last_x!=first_x+1 ){
		int mid_x=(int)(first_x+last_x)/2;
		if(hit_x>x[hit_idy][mid_x]){
			first_x=mid_x;
		}else if(hit_x<x[hit_idy][mid_x]){
			last_x=mid_x;
		}else{
			first_x=mid_x;
			last_x=first_x+1;
		}
	}
	if( fabs(hit_x-x[hit_idy][first_x])<=fabs(hit_x-x[hit_idy][last_x]) ){
		hit_idx=first_x;            //found x id
	}else{
		hit_idx=last_x;
	}

/*
	//check hit id here
	cout<<"hit_idx "<<hit_idx<<endl;
	cout<<"hit_idy "<<hit_idy<<endl;
*/
	//__________________________________find the surrounded other 6 modules________________________
	int tmp_idx[15]={hit_idx-7, hit_idx-6, hit_idx-5, hit_idx-4, hit_idx-3, hit_idx-2, hit_idx-1, hit_idx, hit_idx+1, hit_idx+2, hit_idx+3, hit_idx+4, hit_idx+5, hit_idx+6, hit_idx+7};
	int tmp_idy[3]={hit_idy-1, hit_idy, hit_idy+1};
	int label=0;
	for(int i=0;i<15;i++){// x scan
		for(int j=0;j<3;j++){  //y scan
			if(tmp_idy[j]>=0&&tmp_idy[j]<54&&tmp_idx[i]>=0&&tmp_idx[i]<num_module_in_row[tmp_idy[j]]&&(tmp_idx[i]!=hit_idx || tmp_idy[j]!=hit_idy) ){ // in range
				if(sqrt( pow( (x[tmp_idy[j]][tmp_idx[i]]-x[hit_idy][hit_idx]),2 )+ pow((y[tmp_idy[j]][tmp_idx[i]]-y[hit_idy][hit_idx]),2 ))<15.0){
					hit_around_idx[label]=tmp_idx[i];
					hit_around_idy[label]=tmp_idy[j];
					label++;
				}
			}
		}
	}
/*
	cout<<"find  "<<label<<" around the hitted module"<<endl;
	cout<<"idx	idy"<<endl;
	cout<<hit_idx<<"	"<<hit_idy<<endl;
	for(int l=0;l<label;l++){
		cout<<hit_around_idx[l]<<"	"<<hit_around_idy[l]<<endl;
	}

*/
	//______________________________________module search is finished ____________________________________________________________________

	
	cout<<"________total EC module: "<<total_module<<endl;
	cout<<"find  "<<label<<" around the hitted module"<<endl;
	cout<<"idy\tidx\tid\tsector"<<endl;
	cout<<hit_idy+1<<"\t"<<hit_idx+1<<"\t"<<id[hit_idy][hit_idx]<<"\t"<<sector[hit_idy][hit_idx]<<" ----> this module is hitted!"<<endl;
	for(int l=0;l<label;l++){
	  cout<<hit_around_idy[l]+1<<"\t"<<hit_around_idx[l]+1<<"\t"<<id[hit_around_idy[l]][hit_around_idx[l]]<< "\t"<<sector[hit_around_idy[l]][hit_around_idx[l]]<<endl;
	}

}


