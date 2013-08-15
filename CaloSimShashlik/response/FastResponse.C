/*
 * FastResponse.C
 *
 *  Created on: Aug 15, 2013
 *      Author: jinhuang
 */

#include <iostream>
#include <cassert>
#include <TFile.h>
#include <TROOT.h>
#include <TString.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TMath.h>

using namespace std;

//! Get a quick response model for Shashlik calorimeter for a particle before entering shower + preshwoer
//! \param[in] particle names, pi, p, e, gamma
//! \param[in] E_Kine kinematic in GeV
//! \return Energy deposition in shower. Stocastically generated shower response
double FastResponse(const TString & particle, const double E_Kine)
{
	// from G4 simulation of Shashlik configuration of 0.5mm Pb+1.5mm Scint.
	static const double E_calibration = 3.88271;

	const char * data_file = NULL;

	double mass = 0;

	if (particle == "e")
	{
		data_file =
		        "Elec.10.11.12.root_DrawLowEBgd_EDepShowerOverE_Dist_Read.root";
		mass = 0.510998928e-3;
	}
	else if (particle == "pi")
	{
		data_file =
		        "Pion.run10x.root_DrawLowEBgd_EDepShowerOverE_Dist_Read.root";
		mass = 139.570e-3;
	}
	else if (particle == "p")
	{
		data_file =
		        "Proton.run10x.root_DrawLowEBgd_EDepShowerOverE_Dist_Read.root";
		mass = 938.27204e-3;
	}
	else if (particle == "gamma")
	{
		data_file =
		        "Gamma.run10x.root_DrawLowEBgd_EDepShowerOverE_Dist_Read.root";
		mass = 0;
	}
	else
	{
		cout << "FastResponse - Error - " << "unsupported particle " << particle
		        << endl;

	}

	TFile * file = (TFile *) gROOT->GetListOfFiles()->FindObject(data_file);

	if (!file)
	{
		file = new TFile(data_file);

		assert(file);

		cout <<"FastResponse - INFO - openned "<<data_file<<endl;
	}

	TH2F * h2 = (TH2F *) file->GetObjectChecked("EDepShowerOverE_Dist", "TH2F");
	assert(h2);

	const double log_Ek = TMath::Log10(E_Kine);
	const double E_total = TMath::Sqrt(E_Kine * E_Kine + mass * mass);
	const int bin = h2->GetYaxis()->FindBin(log_Ek);

	TH1D* h1 = h2->ProjectionX("proj", bin, bin);

	const double scintillator_e_dep = h1->GetRandom() * E_total;
	const double shower_E_calibrated = scintillator_e_dep * E_calibration;

	return shower_E_calibrated;

}

