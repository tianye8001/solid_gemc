Here is a quick introduction about how to make SIDIS projection

#1, Genereate the SIDIS events:
   The code locates in ./generator/. It randomly generates events within a slightly wider phase-space 
   and some SIDIS cuts will select particular events which will be saved into the ROOT files. Hence,
   few factors are important for study in next step: the total simualted events and accepted events, 
   and the phase-space that the code randomly genereates events. Unless you change the code, the phase-
   space is like:
      Theta_ele: min = 7 degrees, max = 30 degrees
      Phi_ele:   min = 0 degrees, max = 360 degrees
      Mom_ele:   min = 0.5 GeV/c, max = E0 GeV/c, where E0 is up to 11GeV for 12GeV-JLAB
      Theta_had: min = 7 degrees, max = 30 degrees
      Phi_had:   min = 0 degrees, max = 360 degrees
      Mom_had:   min = 0.5 GeV/c, max = 6 GeV/c
      Phase_Space = (cos(Theta_ele_min)-cos(Theta_ele_max))*2*PI*(E0-0.5)
                   *(cos(Theta_had_min)-cos(Theta_had_max))*2*PI*(6-0.5)

#2, Calculate the weight-factor and insert into the ROOT file: in rate_coverage/generate_weight.C
      The weight-factor will be used for rate, coverage and events evaluation, and it is calucalted by:
       weight_hp = dxs_hp*Phase_Space/N_simulate;
       weight_hm = dxs_hm*Phase_Space/N_simulate;
    where dxs_hp/hm is the SIDIS cross section calculated in the generator, N_smualate is the total simulated
    events before the SIDIS cut, so it is not the total #events in the ROOT file but stored in the brach "nsim". 

#3, Apply the SoLID CLEO acceptance, estimate the rate and make some plots:
    getrate_he3.C --> calculate He3 rate
    getrate_nh3.C --> calculate NH3 rate
    generate_rate.C --> calcualte He3 rate and make plotsa

    The SoLID acceptance files locate at: /w/work6501/zwzhao/solid/work/solid_acceptance

#4, Chain the root files with E0=8.8&11GeV settings, and then split them into smaller root files with different Q2&Z bins:
    It will be more efficient to split the files since we don't have to loop whole events each time we do the binning (>1000 bins).
    The code locates at ./skim/skim.C. The bin-ranges&size of each Q2&Z bin is determined in the code. You can enlarge the
    bin-sizes and hence change the total number of smaller root files.

    Note that the SoLID acceptance, Luminosity, Beam-Time are included into the weight-factor at this step.

#5, Make (Q2,Z,pt,x) bins:
    Codes locate at ./makebin/:
    makebin_pt.C --> For each (Q2,z) bin (and hence each root-file), further bin the data into 
    (pt,x) bins. The target polarization, dilution, and efficiencies are applied here to get the final projected number of event
    in each bin.
    get_results.C --> Read data in in each (Q2, Z, pt, x) bin and calculate the corrections for the azumuthal coverages of Sivers,
    Collins and Pretzelocity.

#6, Make projection plots in ./plot/:

#7, The Pretzelocity projection is binned in one dimentional so the codes starting from step#5 are slightly different.
    I put them in ./pretzelocity/
    
