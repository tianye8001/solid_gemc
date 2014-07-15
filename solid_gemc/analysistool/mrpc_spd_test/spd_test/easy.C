void easy(){

 TString name, dum;
 TString id;

 ifstream inf("job.dat");
 ofstream outf("job_kill.sh");

 inf >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum;
 while(!(inf.eof()))
 {
	inf >> id >>dum>>dum>>dum>>dum>>name>>dum>>dum>>dum>>dum>>dum>>dum;
    if(name.Contains("VZ75"))
		outf <<"jkill "<<id<<endl;

 }
 inf.close();
 outf.close();

}
