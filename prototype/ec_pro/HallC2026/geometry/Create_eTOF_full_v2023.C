/********************************************************************************
 *    Copyright (C) 2019 Quark Matter Research Center, IMP,CAS			*
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Author: Botan Wang (THU)

// Modified on Jun 13, 2021
// The eTOF detectors middle coordinate: 234 cm
// The front panel of eTOF: 225 cm

#include "TSystem.h"
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoMaterial.h"
#include "TGeoMedium.h"
#include "TGeoPgon.h"
#include "TGeoMatrix.h"
#include "TGeoCompositeShape.h"
#include "TFile.h"
#include "TString.h"
#include "TList.h"
#include "TROOT.h"



#include <iostream>

using namespace TMath;
const double pi=TMath::Pi();
double RtoD(double a){return a*180/pi;} // Rad to Degree.
//geometry of MRPC
const double thickness_gap=0.025;//centimeter
const double thickness_readoutstrip=0.0035;
const double thickness_glass=0.07; //glass2
const double thickness_innerglass=0.05; //glass1
const double thickness_PCB=0.08;
const double thickness_mylar=0.025;
const double thickness_electrode=0.0005;
const double thickness_honeycomb=0.5;
const double thickness_MRPC=thickness_gap*10+thickness_readoutstrip*3+thickness_glass*8+thickness_innerglass*4+thickness_PCB*4+thickness_mylar*4+thickness_electrode*4+thickness_honeycomb*2;
const double length_gap=48; //in x direction
const double length_glass1=48;
const double length_glass2=50.5;  
const double length_readoutstrip=48;
const double length_PCB=56.9;
const double length_mylar=50.5;
const double length_electrode=48;
const double length_honeycomb=50.5;
const double length_MRPC=length_PCB;
const double width_readoutstrip=1.5;
const double width_stripgap=0.2;
//geometry of MRPC1
const double width_gap1=56; //in y direction
const double width_glass11=56;
const double width_glass21=58.5;  
const double width_PCB1=62.9;
const double width_mylar1=58.5;
const double width_electrode1=56;
const double width_honeycomb1=58.5;
const double n_channel1=32;
//geometry of MRPC2
const double width_MRPC1=width_PCB1;
const double width_gap2=28.5;
const double width_glass12=28.5;
const double width_glass22=31;
const double width_PCB2=35.4;
const double width_mylar2=31;
const double width_electrode2=28.5;
const double width_honeycomb2=31;
const double n_channel2=16;

// Settings

const double z4=246; //the z coordinate for the front panel of the eTOF box.
const double x4=0; //the x coordinate, change to fit with beamspot.
const int modMov[3] =  {0, 1, 0}; // Set the moved column to 1
const double modBias[7] = {0., 0., 0., 0., 0., 0., 0.}; // For better coverage
const double yMov = 10; // Y distance to move
int geover=4;
Bool_t bDrawTOF=kFALSE; // set to kTRUE to display

// Name of geometry version and output file
const TString geoVersion = "etof";
const TString FileName = geoVersion + Form("_v%d.root",geover);
const TString FileName1 = geoVersion + Form("_geomanager_v%d.root",geover);

// Names of the different used materials which are used to build the modules
// The materials are defined in the global media.geo file

const TString gapmedium = "RPCgas";
const TString glassmedium = "RPCglass";
const TString readoutmedium = "copper";
const TString electrodemedium = "carbon";
const TString mylarmedium = "mylar";
const TString PCBmedium = "pcbmvd";
const TString honeycombmedium = "honeycomb";

int i; int j; int k;

// some global variables
TGeoManager* gGeoMan = NULL;  // Pointer to TGeoManager instance
// Forward declarations
void create_materials_from_media_file();

void Create_eTOF_full_v2023(){
    create_materials_from_media_file();
    gGeoMan=(TGeoManager*)gROOT->FindObject("FAIRGeom");
    gGeoMan->SetVisLevel(7);


    TGeoVolume* topeTOF= new TGeoVolumeAssembly("TOPETOF");
    gGeoMan->SetTopVolume(topeTOF);

    TGeoVolume* etof= new TGeoVolumeAssembly(geoVersion);
    topeTOF->AddNode(etof, 1);
    //TGeoMedium* TOFVolMed   = gGeoMan->GetMedium(TOFVolumeMedium);

   // TGeoVolume *MRPC = gGeoMan->MakeBox("MRPC",TOFVolMed, 13, 76, 1.435);
    TGeoVolume *MRPC1 = new TGeoVolumeAssembly("MRPC1");
    TGeoVolume *MRPC2 = new TGeoVolumeAssembly("MRPC2");

    /****** MRPC1 component geometry ******/
    TGeoBBox* PCB_geo = new TGeoBBox("PCB_geo", length_PCB/2, width_PCB1/2,thickness_PCB/2);
    TGeoMedium* PCBMed = gGeoMan->GetMedium(PCBmedium);
    TGeoVolume* PCB = new TGeoVolume("PCB", PCB_geo, PCBMed);
    PCB->SetLineColor(kGreen-2);
    double position_PCB1=4*thickness_innerglass+2*thickness_glass+5*thickness_gap+2*(thickness_mylar+thickness_electrode)+3*thickness_PCB/2+3*thickness_readoutstrip/2;
    double position_PCB2=thickness_PCB/2+thickness_readoutstrip/2;
    TGeoTranslation *PCB_tr1=new TGeoTranslation(0, 0, position_PCB1);
    TGeoTranslation *PCB_tr2=new TGeoTranslation(0, 0, position_PCB2);
    TGeoTranslation *PCB_tr3=new TGeoTranslation(0, 0, -1*position_PCB2);
    TGeoTranslation *PCB_tr4=new TGeoTranslation(0, 0, -1*position_PCB1);
    MRPC1->AddNode(PCB, 1, PCB_tr1);
    MRPC1->AddNode(PCB, 2, PCB_tr2);
    MRPC1->AddNode(PCB, 3, PCB_tr3);
    MRPC1->AddNode(PCB, 4, PCB_tr4);

    TGeoBBox* mylar_geo = new TGeoBBox("mylar_geo", length_mylar/2, width_mylar1/2,thickness_mylar/2);
    TGeoMedium* mylarMed = gGeoMan->GetMedium(mylarmedium);
    TGeoVolume* mylar = new TGeoVolume("mylar", mylar_geo, mylarMed);
    mylar->SetLineColor(kMagenta+2);
    double position_mylar1=thickness_PCB+0.5*thickness_readoutstrip+0.5*thickness_mylar;
    double position_mylar2=0.5*thickness_PCB+thickness_readoutstrip+0.5*thickness_mylar;
    TGeoTranslation *mylar_tr1=new TGeoTranslation(0, 0, position_mylar1);
    TGeoTranslation *mylar_tr2=new TGeoTranslation(0, 0, -1*position_mylar1);
    TGeoTranslation *mylar_tr3=new TGeoTranslation(0, 0, position_PCB1-position_mylar2);
    TGeoTranslation *mylar_tr4=new TGeoTranslation(0, 0, position_mylar2-position_PCB1);
    MRPC1->AddNode(mylar, 1, mylar_tr1);
    MRPC1->AddNode(mylar, 2, mylar_tr2);
    MRPC1->AddNode(mylar, 3, mylar_tr3);
    MRPC1->AddNode(mylar, 4, mylar_tr4);

    TGeoBBox* electrode_geo = new TGeoBBox("electrode_geo", length_electrode/2, width_electrode1/2,thickness_electrode/2);
    TGeoMedium* electrodeMed = gGeoMan->GetMedium(electrodemedium);
    TGeoVolume* electrode = new TGeoVolume("electrode", electrode_geo, electrodeMed);
    electrode->SetLineColor(kBlack);
    double position_electrode1=position_mylar1+0.5*thickness_mylar+0.5*thickness_electrode;
    double position_electrode2=position_mylar2+0.5*thickness_mylar+0.5*thickness_electrode;
    TGeoTranslation *electrode_tr1=new TGeoTranslation(0, 0, position_electrode1);
    TGeoTranslation *electrode_tr2=new TGeoTranslation(0, 0, -1*position_electrode1);
    TGeoTranslation *electrode_tr3=new TGeoTranslation(0, 0, position_PCB1-position_electrode2);
    TGeoTranslation *electrode_tr4=new TGeoTranslation(0, 0, position_electrode2-position_PCB1);
    MRPC1->AddNode(electrode, 1, electrode_tr1);
    MRPC1->AddNode(electrode, 2, electrode_tr2);
    MRPC1->AddNode(electrode, 3, electrode_tr3);
    MRPC1->AddNode(electrode, 4, electrode_tr4);

    TGeoBBox* readout_geo = new TGeoBBox("readout_geo", length_readoutstrip/2, width_readoutstrip/2,thickness_readoutstrip/2);
    TGeoMedium* readoutMed = gGeoMan->GetMedium(readoutmedium);
    TGeoVolume* readout = new TGeoVolume("readout", readout_geo, readoutMed);
    double position_readout=0.5*(thickness_PCB+thickness_readoutstrip);
    double start_readout=-width_gap1/2+(width_gap1 - n_channel1*(width_readoutstrip+width_stripgap))/2+width_readoutstrip/2;
    readout->SetLineColor(kPink+7);
    for(j=1; j<=2; j++)
    {
        for(i=1; i<=n_channel1; i++)
        {
            MRPC1->AddNode(readout, i+n_channel1*(j-1), new TGeoTranslation(0, start_readout+(width_readoutstrip+width_stripgap)*(i-1), (position_PCB1 - position_readout)*pow(-1,j)));
        }
    }

        for(i=1; i<=n_channel1; i++)
        {
            MRPC1->AddNode(readout, i+2*n_channel1, new TGeoTranslation(0, start_readout+(width_stripgap+width_readoutstrip)*(i-1), 0));
        }


    TGeoBBox* honeycomb_geo = new TGeoBBox("honetcomb_geo", length_honeycomb/2, width_honeycomb1/2,thickness_honeycomb/2);
    TGeoMedium* honeycombMed = gGeoMan->GetMedium(honeycombmedium);
    TGeoVolume* honeycomb = new TGeoVolume("honeycomb", honeycomb_geo, honeycombMed);
    honeycomb->SetLineColor(kOrange-3);
    double position_honeycomb=position_PCB1+0.5*(thickness_PCB+thickness_honeycomb);
    TGeoTranslation *honeycomb_tr1=new TGeoTranslation(0, 0, position_honeycomb);
    TGeoTranslation *honeycomb_tr2=new TGeoTranslation(0, 0, -1*position_honeycomb);
    MRPC1->AddNode(honeycomb, 1, honeycomb_tr1);
    MRPC1->AddNode(honeycomb, 2, honeycomb_tr2);

    TGeoBBox* gap_geo = new TGeoBBox("gap_geo", length_gap/2, width_gap1/2,thickness_gap/2);
    TGeoMedium* gapMed = gGeoMan->GetMedium(gapmedium);
    TGeoVolume* gap = new TGeoVolume("etof_gap", gap_geo, gapMed);
    gap->SetLineColor(kWhite);
    double position_gap=position_electrode1+0.5*(thickness_electrode+thickness_gap)+thickness_glass;
    for(j=1; j<=2; j++)
    {
        for (i=1; i<=5; i++)
        {
            MRPC1->AddNode(gap, i+5*(j-1), new TGeoTranslation(0, 0, (position_gap+(thickness_gap+thickness_innerglass)*(i-1))*pow(-1,j)));
        }
    }

    TGeoBBox* glass1_geo = new TGeoBBox("glass1_geo", length_glass1/2, width_glass11/2,thickness_innerglass/2);
    TGeoBBox* glass2_geo = new TGeoBBox("glass2_geo", length_glass2/2, width_glass21/2,thickness_glass/2);
    TGeoMedium* glassMed = gGeoMan->GetMedium(glassmedium);
    TGeoVolume* glass1 = new TGeoVolume("glass1", glass1_geo, glassMed);
    TGeoVolume* glass2 = new TGeoVolume("glass2", glass2_geo, glassMed);
    glass1->SetLineColor(kBlue-9);
    glass2->SetLineColor(kBlue-9);
    double position_glass2=0.5*(thickness_glass+thickness_electrode);
    double position_glass2o=position_mylar2+thickness_mylar/2+thickness_glass/2;
    TGeoTranslation *glass2_tr1=new TGeoTranslation(0, 0, position_electrode1+position_glass2);
    TGeoTranslation *glass2_tr2=new TGeoTranslation(0, 0, -(position_electrode1+position_glass2));
    TGeoTranslation *glass2_tr3=new TGeoTranslation(0, 0, position_PCB1 - position_glass2o);
    TGeoTranslation *glass2_tr4=new TGeoTranslation(0, 0, position_glass2o - position_PCB1);
    MRPC1->AddNode(glass2, 1, glass2_tr1);
    MRPC1->AddNode(glass2, 2, glass2_tr2);
    MRPC1->AddNode(glass2, 3, glass2_tr3);
    MRPC1->AddNode(glass2, 4, glass2_tr4);
    for(j=1; j<=2; j++)
    {
        for (i=1; i<=4; i++)
        {
            MRPC1->AddNode(glass1, i+4*(j-1), new TGeoTranslation(0, 0, (position_glass2+position_electrode1-thickness_innerglass/2+thickness_glass/2+i*(thickness_innerglass+thickness_gap))*pow(-1,j)));
        }
    }


    /****** MRPC2 component geometry ******/
    PCB_geo = new TGeoBBox("PCB_geo", length_PCB/2, width_PCB2/2,thickness_PCB/2);
    PCBMed = gGeoMan->GetMedium(PCBmedium);
    PCB = new TGeoVolume("PCB", PCB_geo, PCBMed);
    PCB->SetLineColor(kGreen-2);
    position_PCB1=4*thickness_innerglass+2*thickness_glass+5*thickness_gap+2*(thickness_mylar+thickness_electrode)+3*thickness_PCB/2+3*thickness_readoutstrip/2;
    position_PCB2=thickness_PCB/2+thickness_readoutstrip/2;
    PCB_tr1=new TGeoTranslation(0, 0, position_PCB1);
    PCB_tr2=new TGeoTranslation(0, 0, position_PCB2);
    PCB_tr3=new TGeoTranslation(0, 0, -1*position_PCB2);
    PCB_tr4=new TGeoTranslation(0, 0, -1*position_PCB1);
    MRPC2->AddNode(PCB, 1, PCB_tr1);
    MRPC2->AddNode(PCB, 2, PCB_tr2);
    MRPC2->AddNode(PCB, 3, PCB_tr3);
    MRPC2->AddNode(PCB, 4, PCB_tr4);

    mylar_geo = new TGeoBBox("mylar_geo", length_mylar/2, width_mylar2/2,thickness_mylar/2);
    mylarMed = gGeoMan->GetMedium(mylarmedium);
    mylar = new TGeoVolume("mylar", mylar_geo, mylarMed);
    mylar->SetLineColor(kMagenta+2);
    position_mylar1=thickness_PCB+0.5*thickness_readoutstrip+0.5*thickness_mylar;
    position_mylar2=0.5*thickness_PCB+thickness_readoutstrip+0.5*thickness_mylar;
    mylar_tr1=new TGeoTranslation(0, 0, position_mylar1);
    mylar_tr2=new TGeoTranslation(0, 0, -1*position_mylar1);
    mylar_tr3=new TGeoTranslation(0, 0, position_PCB1-position_mylar2);
    mylar_tr4=new TGeoTranslation(0, 0, position_mylar2-position_PCB1);
    MRPC2->AddNode(mylar, 1, mylar_tr1);
    MRPC2->AddNode(mylar, 2, mylar_tr2);
    MRPC2->AddNode(mylar, 3, mylar_tr3);
    MRPC2->AddNode(mylar, 4, mylar_tr4);

    electrode_geo = new TGeoBBox("electrode_geo", length_electrode/2, width_electrode2/2,thickness_electrode/2);
    electrodeMed = gGeoMan->GetMedium(electrodemedium);
    electrode = new TGeoVolume("electrode", electrode_geo, electrodeMed);
    electrode->SetLineColor(kBlack);
    position_electrode1=position_mylar1+0.5*thickness_mylar+0.5*thickness_electrode;
    position_electrode2=position_mylar2+0.5*thickness_mylar+0.5*thickness_electrode;
    electrode_tr1=new TGeoTranslation(0, 0, position_electrode1);
    electrode_tr2=new TGeoTranslation(0, 0, -1*position_electrode1);
    electrode_tr3=new TGeoTranslation(0, 0, position_PCB1-position_electrode2);
    electrode_tr4=new TGeoTranslation(0, 0, position_electrode2-position_PCB1);
    MRPC2->AddNode(electrode, 1, electrode_tr1);
    MRPC2->AddNode(electrode, 2, electrode_tr2);
    MRPC2->AddNode(electrode, 3, electrode_tr3);
    MRPC2->AddNode(electrode, 4, electrode_tr4);

    readout_geo = new TGeoBBox("readout_geo", length_readoutstrip/2, width_readoutstrip/2,thickness_readoutstrip/2);
    readoutMed = gGeoMan->GetMedium(readoutmedium);
    readout = new TGeoVolume("readout", readout_geo, readoutMed);
    position_readout=0.5*(thickness_PCB+thickness_readoutstrip);
    start_readout=-width_gap2/2+(width_gap2 - n_channel2*(width_readoutstrip+width_stripgap))/2+width_readoutstrip/2;
    readout->SetLineColor(kPink+7);
    for(j=1; j<=2; j++)
    {
        for(i=1; i<=n_channel2; i++)
        {
            MRPC2->AddNode(readout, i+n_channel2*(j-1), new TGeoTranslation(0, start_readout+(width_readoutstrip+width_stripgap)*(i-1), (position_PCB1 - position_readout)*pow(-1,j)));
        }
    }

    for(i=1; i<=n_channel2; i++)
    {
        MRPC2->AddNode(readout, i+2*n_channel2, new TGeoTranslation(0, start_readout+(width_stripgap+width_readoutstrip)*(i-1), 0));
    }


    honeycomb_geo = new TGeoBBox("honetcomb_geo", length_honeycomb/2, width_honeycomb2/2,thickness_honeycomb/2);
    honeycombMed = gGeoMan->GetMedium(honeycombmedium);
    honeycomb = new TGeoVolume("honeycomb", honeycomb_geo, honeycombMed);
    honeycomb->SetLineColor(kOrange-3);
    position_honeycomb=position_PCB1+0.5*(thickness_PCB+thickness_honeycomb);
    honeycomb_tr1=new TGeoTranslation(0, 0, position_honeycomb);
    honeycomb_tr2=new TGeoTranslation(0, 0, -1*position_honeycomb);
    MRPC2->AddNode(honeycomb, 1, honeycomb_tr1);
    MRPC2->AddNode(honeycomb, 2, honeycomb_tr2);

    gap_geo = new TGeoBBox("gap_geo", length_gap/2, width_gap2/2,thickness_gap/2);
    gapMed = gGeoMan->GetMedium(gapmedium);
    gap = new TGeoVolume("etof_gap", gap_geo, gapMed);
    gap->SetLineColor(kWhite);
    position_gap=position_electrode1+0.5*(thickness_electrode+thickness_gap)+thickness_glass;
    for(j=1; j<=2; j++)
    {
        for (i=1; i<=5; i++)
        {
            MRPC2->AddNode(gap, i+5*(j-1), new TGeoTranslation(0, 0, (position_gap+(thickness_gap+thickness_innerglass)*(i-1))*pow(-1,j)));
        }
    }

    glass1_geo = new TGeoBBox("glass1_geo", length_glass1/2, width_glass12/2,thickness_innerglass/2);
    glass2_geo = new TGeoBBox("glass2_geo", length_glass2/2, width_glass22/2,thickness_glass/2);
    glassMed = gGeoMan->GetMedium(glassmedium);
    glass1 = new TGeoVolume("glass1", glass1_geo, glassMed);
    glass2 = new TGeoVolume("glass2", glass2_geo, glassMed);
    glass1->SetLineColor(kBlue-9);
    glass2->SetLineColor(kBlue-9);
    position_glass2=0.5*(thickness_glass+thickness_electrode);
    position_glass2o=position_mylar2+thickness_mylar/2+thickness_glass/2;
    glass2_tr1=new TGeoTranslation(0, 0, position_electrode1+position_glass2);
    glass2_tr2=new TGeoTranslation(0, 0, -(position_electrode1+position_glass2));
    glass2_tr3=new TGeoTranslation(0, 0, position_PCB1 - position_glass2o);
    glass2_tr4=new TGeoTranslation(0, 0, position_glass2o - position_PCB1);
    MRPC2->AddNode(glass2, 1, glass2_tr1);
    MRPC2->AddNode(glass2, 2, glass2_tr2);
    MRPC2->AddNode(glass2, 3, glass2_tr3);
    MRPC2->AddNode(glass2, 4, glass2_tr4);
    for(j=1; j<=2; j++)
    {
        for (i=1; i<=4; i++)
        {
            MRPC2->AddNode(glass1, i+4*(j-1), new TGeoTranslation(0, 0, (position_glass2+position_electrode1-thickness_innerglass/2+thickness_glass/2+i*(thickness_innerglass+thickness_gap))*pow(-1,j)));
        }
    }

    // Module assembly

    double y_out = 31*(width_readoutstrip+width_stripgap);
    double z_over = thickness_MRPC/2+1;

    TGeoVolume *M1 = new TGeoVolumeAssembly("M1");
    TGeoVolume *M1_1 = new TGeoVolumeAssembly("M1_1");
    TGeoVolume *M2 = new TGeoVolumeAssembly("M2");
    M1->AddNode(MRPC1,0,new TGeoTranslation(0, y_out, -z_over));
    M1->AddNode(MRPC2,1,new TGeoTranslation(0, 7.5*(width_readoutstrip+width_stripgap), z_over));
    M1->AddNode(MRPC2,2,new TGeoTranslation(0, -7.5*(width_readoutstrip+width_stripgap), -z_over));
    M1->AddNode(MRPC1,3,new TGeoTranslation(0, -y_out, z_over));
    M1_1->AddNode(MRPC1,0,new TGeoTranslation(0, y_out, -z_over));
    M1_1->AddNode(MRPC2,1,new TGeoTranslation(0, 7.5*(width_readoutstrip+width_stripgap)+yMov, z_over));
    M1_1->AddNode(MRPC2,2,new TGeoTranslation(0, -7.5*(width_readoutstrip+width_stripgap)-yMov, -z_over));
    M1_1->AddNode(MRPC1,3,new TGeoTranslation(0, -y_out, z_over));
    M2->AddNode(MRPC1,0,new TGeoTranslation(0, y_out, -z_over));
    M2->AddNode(MRPC1,1,new TGeoTranslation(0, 0, z_over));
    M2->AddNode(MRPC1,2,new TGeoTranslation(0, -y_out, -z_over));

    /****** eTOF geometry ******/

    double x_place = -6*(0.5*length_gap-1);
    double zm_over = 10;
    // double z_place = z4+thickness_MRPC/2+zm_over+z_over;
    double z_place = z4;
    int m=0;
    for (i=0;i<7;i++){
        if (i<2 || i>4){
            m++;
            etof->AddNode(M2,m,new TGeoTranslation(x_place+x4+modBias[i], 0, pow(-1,i)*zm_over+z_place));
            x_place += 2*(0.5*length_gap-1);
        }
        else if(modMov[i-2]==0){
            m++;
            etof->AddNode(M1,m,new TGeoTranslation(x_place+x4+modBias[i], 0, pow(-1,i)*zm_over+z_place));
            x_place += 2*(0.5*length_gap-1);
        }
        else{
            cout<<"modMov[i-2]="<< modMov[i-2] <<endl;
            m++;
            etof->AddNode(M1_1,m,new TGeoTranslation(x_place+x4+modBias[i], 0, pow(-1,i)*zm_over+z_place));
            x_place += 2*(0.5*length_gap-1);
        }
    }
    cout<<"Total modules m="<< m <<endl;
    cout<<"The centeral point of eTOF locates: "<<z_place<<endl;
    cout<<"Voxelizing."<<endl;
    topeTOF->SetTransparency(10);
    topeTOF->Voxelize("");
    gGeoMan->CloseGeometry();
    gGeoMan->CheckOverlaps(0.001);
    gGeoMan->PrintOverlaps();
    gGeoMan->Test();

    TFile* outfile = TFile::Open(FileName,"RECREATE");
    topeTOF->Write();
    outfile->Close();

    TFile* outfile1 = TFile::Open(FileName1,"RECREATE");
    gGeoMan->Write();
    outfile1->Close();

    if (bDrawTOF) topeTOF->Draw("ogl");
    //MRPC->Draw("ogl");
    //topeTOF->Draw("ogl");
}

void create_materials_from_media_file()
{
    // Use the FairRoot geometry interface to load the media which are already defined
    FairGeoLoader* geoLoad = new FairGeoLoader("TGeo", "FairGeoLoader");
    FairGeoInterface* geoFace = geoLoad->getGeoInterface();
    TString geoPath = gSystem->Getenv("VMCWORKDIR");
    TString geoFile = geoPath + "/geometry/media.geo";
    geoFace->setMediaFile(geoFile);
    geoFace->readMedia();

    // Read the required media and create them in the GeoManager
    FairGeoMedia* geoMedia = geoFace->getMedia();
    FairGeoBuilder* geoBuild = geoLoad->getGeoBuilder();

    FairGeoMedium* air              = geoMedia->getMedium("air");
    FairGeoMedium* silicon          = geoMedia->getMedium("silicon");
    FairGeoMedium* scintillator = geoMedia->getMedium("FscScint");

    FairGeoMedium* Air = geoMedia->getMedium("RPCgas");
    FairGeoMedium* Glass = geoMedia->getMedium("RPCglass");
    FairGeoMedium* readout = geoMedia->getMedium("copper");
    FairGeoMedium* electrode = geoMedia->getMedium("carbon");
    FairGeoMedium* mylar = geoMedia->getMedium("mylar");
    FairGeoMedium* PCB = geoMedia->getMedium("pcbmvd");
    FairGeoMedium* honeycomb = geoMedia->getMedium("honeycomb");
    // include check if all media are found

    geoBuild->createMedium(air);
    geoBuild->createMedium(silicon);
    geoBuild->createMedium(scintillator);
    geoBuild->createMedium(Air);
    geoBuild->createMedium(Glass);
    geoBuild->createMedium(readout);
    geoBuild->createMedium(electrode);
    geoBuild->createMedium(mylar);
    geoBuild->createMedium(PCB);
    geoBuild->createMedium(honeycomb);

}
