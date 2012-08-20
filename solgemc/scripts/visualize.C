#include "TGLClip.h"

/* 
    Example 2D visualization with grid to visualize SoLID's
    geometry setup.  Reads in the GDML file named solgemc_example.gdml
    and draws it accordingly.

    Seamus Riordan
    riordan@jlab.org
    August 20, 2012
*/

// Kludge... not sure the namespace this actually lives in
enum EClipType { kClipNone = 0, kClipPlane, kClipBox };

void visualize(){
    gSystem->Load("libGeom");
    TGeoManager *geo = new TGeoManager("World", "My geometry");
    geo->Import("solgemc_example.gdml");

    geo->GetMasterVolume()->Draw("ogl");

    TGLViewer *v = (TGLViewer *)gPad->GetViewer3D();

    v->SetCurrentCamera(TGLViewer::kCameraOrthoZOY);
    v->SetStyle(TGLRnrCtx::kWireFrame);

    Double_t boxdata[6] = {0.0, 0.0, 0.0, 20.0, 10000.0, 10000.0};

    v->SetClipAutoUpdate(kFALSE);

    v->GetClipSet()->SetClipType(kClipBox);
    v->GetClipSet()->GetCurrentClip()->Setup(TGLVector3(0.0, 0.0, 0.0), 
	                                     TGLVector3(1.0, 1.0, 1.0));
    v->GetClipSet()->SetClipState(kClipBox, boxdata);

    const TGLBoundingBox & box = v->GetClipSet()->GetCurrentClip()->BoundingBox();
    TGLVector3 scale = v->GetClipSet()->GetCurrentClip()->GetScale();

    v->GetClipSet()->GetCurrentClip()->SetMode(TGLClip::kOutside);


    TGLCameraOverlay *co = v->GetCameraOverlay();
    co->SetShowOrthographic(kTRUE);
    co->SetOrthographicMode(TGLCameraOverlay::kGridBack);


}
