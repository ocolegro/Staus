


#import "TFile.h"
#import "TTree.h"
#import "TChain.h"
#import "TH2F.h"
#import "TString.h"
#import "TLegend.h"
#import "TCanvas.h"
#import "TLatex.h"
#import "TStyle.h"
#import "TMath.h"
#import "TF1.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#define PI 3.14159

void yieldMaker(){
    TCanvas * c1    = new TCanvas("c1","Graph Example",200,10,500,500);


    
    TChain * tC_DY  = new TChain("Events");
    tC_DY->Add("MC/DY1Jets_xSecWgted_tree.root");
    tC_DY->Add("MC/DY2Jets_xSecWgted_tree.root");
    tC_DY->Add("MC/DY3Jets_xSecWgted_tree.root");
    tC_DY->Add("MC/DY4Jets_xSecWgted_tree.root");
    TH1F * hYields = new TH1F("hYields","hYields",1,0,1)  ;
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    TChain * tC_TT  = new TChain("Events");
    tC_TT->Add("MC/TTGJets_xSecWgted_tree.root");
    tC_TT->Add("MC/TTW_xSecWgted_tree.root");
    tC_TT->Add("MC/TTZ_xSecWgted_tree.root");
    tC_TT->Add("MC/TTto1L_xSecWgted_tree.root");
    tC_TT->Add("MC/TTto2L_xSecWgted_tree.root");
    tC_TT->Add("MC/TW_xSecWgted_tree.root");
    tC_TT->Add("MC/TbarW_xSecWgted_tree.root");

    TChain * tC_RARE  = new TChain("Events");
    tC_RARE->Add("MC/ZZ*xSecWgted*.root");
    tC_RARE->Add("MC/WZ*xSecWgted*.root");
    tC_RARE->Add("MC/WW*xSecWgted*.root");
    tC_RARE->Add("MC/Wminus*xSecWgted*.root");
    tC_RARE->Add("MC/Wplus*xSecWgted*.root");
    tC_RARE->Add("MC/VBF*xSecWgted*.root");
    tC_RARE->Add("MC/Glu*xSecWgted*.root");

    TChain * tC_LHStau_150_1  = new TChain("Events");
    tC_LHStau_150_1->Add("signal/LHStau_150_1.root");

    TChain * tC_RHStau_150_1  = new TChain("Events");
    tC_RHStau_150_1->Add("signal/RHStau_150_1.root");
    
    TChain * tC_MixedStau_150_1 = new TChain("Events");
    tC_MixedStau_150_1->Add("signal/MixedStau_150_1.root");
    
    TChain * tC_DATA  = new TChain("Events");
    tC_DATA->Add("data/TauDataFRWeighted.root");

    TString cutString = "(1==1)";
    
    cutString += "&& (pass_trig == 1)";

    cutString += "&& (nbjetsloose == 0)";
    cutString += "&& (nvetoele == 0)";
    cutString += "&& (nvetomu == 0)";
    cutString += "&& (badcharged_filter == 0 && badmuon_filter == 0 && pv_filter == 0 && beamhalo_filter == 0 && hbhe_filter == 0 && hbheiso_filter == 0 && ecaltp_filter == 0 && eebadsc_filter == 0)";
    cutString += "&& (lep1_pdgid == -1*lep2_pdgid)";
    cutString += "&& (abs(lep1_pdgid) == 15)";
    cutString += "&& (lep1_pt >= 40 && lep2_pt >= 40)";
    cutString += "&& (abs(lep1_eta) <= 2.1 && abs(lep2_eta) <= 2.1)";
    cutString += "&& (TMath::Max(lep1_mt,lep2_mt) > 200)";

    cutString += "&& (lep1_matchtrig == 1 && lep2_matchtrig == 1)";
    cutString += "&& (lep1_loose == 1 && lep2_loose == 1)";

    TString cutStringQCD = cutString;
    cutString += "&& (lep1_medium == 1 && lep2_medium == 1)";

    TString looseCut =   "&& (abs(dphi_l1l2) >= 1.25) && ( mt2 >= 80 ) && (pfmet > 125) ";//&& (TMath::Min(abs(dphi_l1met),abs(dphi_l2met)) >= .5)";

    TString medCut =   " && (abs(dphi_l1l2) >= 2.5) && ( mt2 < 80 && mt2 >= 40)  && mvis > 250   && (lep1_tight == 1 && lep2_tight == 1)";

    TString tightCut =   " && (abs(dphi_l1l2) >=  1.25) && ( mt2 < 80 && mt2 >= 40)  && mvis < 250 && (lep1_vtight == 1 && lep2_vtight == 1)     ";


    TString cutStringSR1 = "36*xSecEvtWgt*tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString +  looseCut + ")";
    TString cutStringSR2 = "36*xSecEvtWgt*tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString +  medCut + ")";
    TString cutStringSR3 = "36*xSecEvtWgt*tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString  + tightCut + ")";

    TString cutStringRHStauSR1 = "36*1/90848.*23.32**tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString + looseCut+ ")";
    TString cutStringRHStauSR2 = "36*1/90848.*23.32**tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString  + medCut + ")";
    TString cutStringRHStauSR3 = "36*1/90848.*23.32**tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString  + tightCut + ")";

    TString cutStringMixedStauSR1 = "36*1/97386.*25.53**tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString + looseCut + ")";
    TString cutStringMixedStauSR2 = "36*1/97386.*25.53**tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString  + medCut + ")";
    TString cutStringMixedStauSR3 = "36*1/97386.*25.53**tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString  + tightCut + ")";

    TString cutStringLHStauSR1 = "36*1/87172.*63.34**tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString + looseCut + ")";
    TString cutStringLHStauSR2 = "36*1/87172.*63.34**tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString + medCut + ")";
    TString cutStringLHStauSR3 = "36*1/87172.*63.34**tau_sf*trigger_sf*btag_sf*pu_central*(" + cutString  + tightCut + ")";


    TString cutStringQCDSR1 = "fakeWeightMedium * (" + cutStringQCD + looseCut + ")";
    TString cutStringQCDSR2 = "fakeWeightTight * (" + cutStringQCD + medCut + ")";
    TString cutStringQCDSR3 = "fakeWeightVTight * (" + cutStringQCD  + tightCut + ")";

    /**DODODODODODODODODOODO*/
    tC_DY->Draw("nbjetsloose*0>>hYields",cutStringSR1);
    std::cout << "The DY Yields in SR1 = " << hYields->Integral() << std::endl;
    
    tC_TT->Draw("nbjetsloose*0>>hYields",cutStringSR1);
    std::cout << "The Top Yields in SR1 = " << hYields->Integral() << std::endl;
    
    tC_RARE->Draw("nbjetsloose*0>>hYields",cutStringSR1);
    std::cout << "The Rare Yields in SR1 = " << hYields->Integral() << std::endl;
    
    tC_LHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringLHStauSR1);
    std::cout << "The LHStau_150_1 Yields in SR1 = " << hYields->Integral() << std::endl;
    
    tC_RHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringRHStauSR1);
    std::cout << "The RHStau_150_1 Yields in SR1 = " << hYields->Integral() << std::endl;
        
    tC_MixedStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringMixedStauSR1);
    std::cout << "The Mixed_Stau_150_1 Yields in SR1 = " << hYields->Integral() << std::endl;
            
    /**DODODODODODODODODOODO*/
    tC_DY->Draw("nbjetsloose*0>>hYields",cutStringSR2);
    std::cout << "The DY Yields in SR2 = " << hYields->Integral() << std::endl;
   
    tC_TT->Draw("nbjetsloose*0>>hYields",cutStringSR2);
    std::cout << "The Top Yields in SR2 = " << hYields->Integral() << std::endl;
    
    tC_RARE->Draw("nbjetsloose*0>>hYields",cutStringSR2);
    std::cout << "The Rare Yields in SR2 = " << hYields->Integral() << std::endl;
        
    tC_LHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringLHStauSR2);
    std::cout << "The LHStau_150_1 Yields in SR2 = " << hYields->Integral() << std::endl;
    
    tC_RHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringRHStauSR2);
    std::cout << "The RHStau_150_1 Yields in SR2 = " << hYields->Integral() << std::endl;
        
    tC_MixedStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringMixedStauSR2);
    std::cout << "The Mixed_Stau_150_1 Yields in SR2 = " << hYields->Integral() << std::endl;
    /**DODODODODODODODODOODO*/
    tC_TT->Draw("nbjetsloose*0>>hYields",cutStringSR3);
    std::cout << "The Top Yields in SR3 = " << hYields->Integral() << std::endl;
    
    tC_DY->Draw("nbjetsloose*0>>hYields",cutStringSR3);
    std::cout << "The DY Yields in SR3 = " << hYields->Integral() << std::endl;

    tC_RARE->Draw("nbjetsloose*0>>hYields",cutStringSR3);
    std::cout << "The Rare Yields in SR3 = " << hYields->Integral() << std::endl;
    
    tC_LHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringLHStauSR3);
    std::cout << "The LHStau_150_1 Yields in SR3 = " << hYields->Integral() << std::endl;
    
    tC_RHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringRHStauSR3);
    std::cout << "The RHStau_150_1 Yields in SR3 = " << hYields->Integral() << std::endl;

    tC_MixedStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringMixedStauSR3);
    std::cout << "The Mixed_Stau_150_1 Yields in SR3 = " << hYields->Integral() << std::endl;
    
    ofstream myfile;
    myfile.open ("yields.txt");
    myfile << std::fixed << std::setprecision(2);

    double QCDSR1Error,QCDSR2Error,QCDSR3Error;
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_DATA->Draw("nbjetsloose*0>>hYields",cutStringQCDSR1);
    double QCDSR1 = hYields->IntegralAndError(-1,1e6,QCDSR1Error);

    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_DATA->Draw("nbjetsloose*0>>hYields",cutStringQCDSR2);
    double QCDSR2 = hYields->IntegralAndError(-1,1e6,QCDSR2Error);

    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_DATA->Draw("nbjetsloose*0>>hYields",cutStringQCDSR3);
    double QCDSR3 = hYields->IntegralAndError(-1,1e6,QCDSR3Error);
    myfile << "QCD and W+Jets " << " & " << QCDSR1 << " $\\pm$ " << QCDSR1Error 
            << " & " << QCDSR2 << " $\\pm$ " << QCDSR2Error
            << " & " << QCDSR3 << " $\\pm$ " << QCDSR3Error << "\\\\" << std::endl;

    
    
    double DYSR1Error,DYSR2Error,DYSR3Error;
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_DY->Draw("nbjetsloose*0>>hYields",cutStringSR1);
    double DYSR1 = hYields->IntegralAndError(-1,1e6,DYSR1Error);

    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_DY->Draw("nbjetsloose*0>>hYields",cutStringSR2);
    double DYSR2 = hYields->IntegralAndError(-1,1e6,DYSR2Error);

    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_DY->Draw("nbjetsloose*0>>hYields",cutStringSR3);
    double DYSR3 = hYields->IntegralAndError(-1,1e6,DYSR3Error);
    myfile << "Drell-Yan " << " & " << DYSR1 << " $\\pm$ " << DYSR1Error 
            << " & " << DYSR2 << " $\\pm$ " << DYSR2Error
            << " & " << DYSR3 << " $\\pm$ " << DYSR3Error << "\\\\" << std::endl;

    double TTSR1Error,TTSR2Error,TTSR3Error;
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_TT->Draw("nbjetsloose*0>>hYields",cutStringSR1);
    double TTSR1 = hYields->IntegralAndError(-1,1e6,TTSR1Error);

    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_TT->Draw("nbjetsloose*0>>hYields",cutStringSR2);
    double TTSR2 = hYields->IntegralAndError(-1,1e6,TTSR2Error);

    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_TT->Draw("nbjetsloose*0>>hYields",cutStringSR3);
    double TTSR3 = hYields->IntegralAndError(-1,1e6,TTSR3Error);
    myfile << "Top " << " & " << TTSR1 << " $\\pm$ " << TTSR1Error 
            << " & " << TTSR2 << " $\\pm$ " << TTSR2Error
            << " & " << TTSR3 << " $\\pm$ " << TTSR3Error << "\\\\" << std::endl;

    double RARESR1Error,RARESR2Error,RARESR3Error;
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_RARE->Draw("nbjetsloose*0>>hYields",cutStringSR1);
    double RARESR1 = hYields->IntegralAndError(-1,1e6,RARESR1Error);

    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_RARE->Draw("nbjetsloose*0>>hYields",cutStringSR2);
    double RARESR2 = hYields->IntegralAndError(-1,1e6,RARESR2Error);

    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_RARE->Draw("nbjetsloose*0>>hYields",cutStringSR3);
    double RARESR3 = hYields->IntegralAndError(-1,1e6,RARESR3Error);

    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    myfile << "Rare " << " & " << RARESR1 << " $\\pm$ " << RARESR1Error 
            << " & " << RARESR2 << " $\\pm$ " << RARESR2Error
            << " & " << RARESR3 << " $\\pm$ " << RARESR3Error << "\\\\" << std::endl;
    myfile << "\\hline" << std::endl;
    
    double LHStau_150_1SR1Error,LHStau_150_1SR2Error,LHStau_150_1SR3Error;
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_LHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringLHStauSR1);
    double LHStau_150_1SR1 = hYields->IntegralAndError(-1,1e6,LHStau_150_1SR1Error);
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_LHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringLHStauSR2);
    double LHStau_150_1SR2 = hYields->IntegralAndError(-1,1e6,LHStau_150_1SR2Error);
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_LHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringLHStauSR3);
    double LHStau_150_1SR3 = hYields->IntegralAndError(-1,1e6,LHStau_150_1SR3Error);
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    myfile << "LHStau(150,1) " << " & " << LHStau_150_1SR1 << " $\\pm$ " << LHStau_150_1SR1Error 
            << " & " << LHStau_150_1SR2 << " $\\pm$ " << LHStau_150_1SR2Error
            << " & " << LHStau_150_1SR3 << " $\\pm$ " << LHStau_150_1SR3Error << "\\\\" << std::endl;
    myfile << "\\hline" << std::endl;
    
    double RHStau_150_1SR1Error,RHStau_150_1SR2Error,RHStau_150_1SR3Error;
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_RHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringRHStauSR1);
    double RHStau_150_1SR1 = hYields->IntegralAndError(-1,1e6,RHStau_150_1SR1Error);
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_RHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringRHStauSR2);
    double RHStau_150_1SR2 = hYields->IntegralAndError(-1,1e6,RHStau_150_1SR2Error);
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_RHStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringRHStauSR3);
    double RHStau_150_1SR3 = hYields->IntegralAndError(-1,1e6,RHStau_150_1SR3Error);
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    myfile << "RHStau(150,1) " << " & " << RHStau_150_1SR1 << " $\\pm$ " << RHStau_150_1SR1Error 
            << " & " << RHStau_150_1SR2 << " $\\pm$ " << RHStau_150_1SR2Error
            << " & " << RHStau_150_1SR3 << " $\\pm$ " << RHStau_150_1SR3Error << "\\\\" << std::endl;
    myfile << "\\hline" << std::endl;
    
    double MixedStau_150_1SR1Error,MixedStau_150_1SR2Error,MixedStau_150_1SR3Error;
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_MixedStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringMixedStauSR1);
    double MixedStau_150_1SR1 = hYields->IntegralAndError(-1,1e6,MixedStau_150_1SR1Error);
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_MixedStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringMixedStauSR2);
    double MixedStau_150_1SR2 = hYields->IntegralAndError(-1,1e6,MixedStau_150_1SR2Error);
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    tC_MixedStau_150_1->Draw("nbjetsloose*0>>hYields",cutStringMixedStauSR3);
    double MixedStau_150_1SR3 = hYields->IntegralAndError(-1,1e6,MixedStau_150_1SR3Error);
    hYields = new TH1F("hYields","hYields",1,0,1)  ; hYields->Sumw2();
    myfile << "MixedStau(150,1) " << " & " << MixedStau_150_1SR1 << " $\\pm$ " << MixedStau_150_1SR1Error 
            << " & " << MixedStau_150_1SR2 << " $\\pm$ " << MixedStau_150_1SR2Error
            << " & " << MixedStau_150_1SR3 << " $\\pm$ " << RHStau_150_1SR3Error << "\\\\" << std::endl;
    myfile << "\\hline" << std::endl;
    
    myfile.close();

}
//cutString = "36*xSecEvtWgt*(" + cutString + ")";


