#import "TFile.h"
#import "TTree.h"
#import "THStack.h"
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
#include <vector>
#define PI 3.14159


void plotClosure(){
    TCanvas * c1 = new TCanvas("c1","Canvas");
    bool verbose = false;
    TChain * tData  = new TChain("Events");

    tData->Add("data/TauDataFRWeighted.root");
    const TTree *tDataTree = (TTree*)tData->GetTree();

    TChain * tDY  = new TChain("Events");
    tDY->Add("MC/DYNJets_xSecWgted_tree.root");


    TChain * tC_RARE  = new TChain("Events");
    tC_RARE->Add("MC/ZZ*xSecWgted*.root");
    tC_RARE->Add("MC/WZ*xSecWgted*.root");
    tC_RARE->Add("MC/WW*xSecWgted*.root");
    tC_RARE->Add("MC/Wminus*xSecWgted*.root");
    tC_RARE->Add("MC/Wplus*xSecWgted*.root");
    tC_RARE->Add("MC/VBF*xSecWgted*.root");
    tC_RARE->Add("MC/Glu*xSecWgted*.root");
    tC_RARE->Add("MC/TTGJets_xSecWgted_tree.root");
    tC_RARE->Add("MC/TTW_xSecWgted_tree.root");
    tC_RARE->Add("MC/TTZ_xSecWgted_tree.root");
    tC_RARE->Add("MC/TTto1L_xSecWgted_tree.root");
    tC_RARE->Add("MC/TTto2L_xSecWgted_tree.root");
    tC_RARE->Add("MC/TW_xSecWgted_tree.root");
    tC_RARE->Add("MC/TbarW_xSecWgted_tree.root");

    TH1F* hMT2Test  = new TH1F("hMT2Test","hMT2Test",20,0,100)  ;
    TH1F* hMT2Train = new TH1F("hMT2Train","hMT2Train",20,0,100)  ;
    TH1F* hMT2TrainMC = new TH1F("hMT2TrainMC","hMT2TrainMC",20,0,100)  ;
    TH1F* hMT2TrainMC_2 = new TH1F("hMT2TrainMC_2","hMT2TrainMC_2",20,0,100)  ;

    TH1F* hMT2TrainErrors = new TH1F("hMT2TrainErrors","hMT2TrainErrors",20,0,100)  ;

    hMT2TrainMC->SetFillColor(kBlue);
    hMT2TrainMC_2->SetFillColor(kYellow);
    hMT2Train->SetMarkerColor(kRed);
    hMT2TrainErrors->SetMarkerColor(kBlack);
    hMT2Test->SetMarkerColor(kBlack);

    hMT2Train->SetFillColor(kRed);
    hMT2TrainErrors->SetFillColor(kBlack);
    hMT2Test->SetFillColor(kBlack);

    hMT2TrainErrors->SetFillStyle(3001);
    hMT2Test->SetMarkerStyle(23);
    hMT2Test->Sumw2();
    hMT2TrainErrors->Sumw2();

    TString cutStringData = "(1==1)";
    cutStringData += "&& (pass_trig == 1)";
    cutStringData += "&& (nbjetsloose == 0)";
    cutStringData += "&& (nvetoele == 0)";
    cutStringData += "&& (nvetomu == 0)";
    cutStringData += "&& (badcharged_filter == 0 && badmuon_filter == 0 && pv_filter == 0 && beamhalo_filter == 0 && hbhe_filter == 0 && hbheiso_filter == 0 && ecaltp_filter == 0 && eebadsc_filter == 0)";
    cutStringData += "&& (abs(lep1_pdgid) == 15 && abs(lep2_pdgid) == 15)";
    cutStringData += "&& (abs(lep1_eta) <= 2.1 && abs(lep2_eta) <= 2.1)";
    cutStringData += "&& (lep1_matchtrig == 1 && lep2_matchtrig == 1)";
    cutStringData += "&& (lep1_loose == 1 && lep1_loose == 1)";
    cutStringData += "&& (mt2 < 80)";
    cutStringData += "&& (mt_sum < 300)";
    cutStringData += "&& (lep1_pt >= 40 && lep2_pt >= 40)";

    TString cutStringDataSS             = cutStringData + "&& (lep1_pdgid == lep2_pdgid)";
    TString cutStringDataSSVTightTrain  =  "fakeWeightVTight*(" + cutStringDataSS + ")";
    TString cutStringDataSSTightTrain   =  "fakeWeightTight*(" + cutStringDataSS + ")";
    TString cutStringDataSSMedTrain     =  "fakeWeightMedium*(" + cutStringDataSS + ")";

    TString cutStringDataOS             = cutStringData + "&& (lep1_pdgid == -1*lep2_pdgid)";
    TString cutStringDataOSVTightTrain  =  "fakeWeightVTight*(" + cutStringDataOS + ")";
    TString cutStringDataOSTightTrain   =  "fakeWeightTight*(" + cutStringDataOS + ")";
    TString cutStringDataOSMedTrain     =  "fakeWeightMedium*(" + cutStringDataOS + ")";

    TString cutStringDataSSVTightTest   = "(" + cutStringData + "&& (lep1_pdgid == lep2_pdgid)" + " && (lep1_vtight == 1 && lep2_vtight == 1)" + ")";
    TString cutStringDataSSTightTest   = "(" + cutStringData + "&& (lep1_pdgid == lep2_pdgid)" + " && (lep1_tight == 1 && lep2_tight == 1)" + ")";
    TString cutStringDataSSMedTest   = "(" + cutStringData + "&& (lep1_pdgid == lep2_pdgid)" + " && (lep1_medium == 1 && lep2_medium == 1)" + ")";

    TString cutStringDataOSVTightTest   = "(" + cutStringData + "&& (lep1_pdgid == -1 * lep2_pdgid)" + " && (lep1_vtight == 1 && lep2_vtight == 1)" + ")";
    TString cutStringDataOSTightTest   = "(" + cutStringData + "&& (lep1_pdgid == -1 * lep2_pdgid)" + " && (lep1_tight == 1 && lep2_tight == 1)" + ")";
    TString cutStringDataOSMedTest   = "(" + cutStringData + "&& (lep1_pdgid == -1*lep2_pdgid)" + " && (lep1_medium == 1 && lep2_medium == 1)" + ")";

    TString cutStringDataOSVTightMC   = "36*xSecEvtWgt*tau_sf*trigger_sf*btag_sf*pu_central*(" + cutStringData + "&& (lep1_pdgid == -1 * lep2_pdgid)" + " && (lep1_vtight == 1 && lep2_vtight == 1)" + ")";
    TString cutStringDataOSTightMC    = "36*xSecEvtWgt*tau_sf*trigger_sf*btag_sf*pu_central*(" + cutStringData + "&& (lep1_pdgid == -1 * lep2_pdgid)" + " && (lep1_tight == 1 && lep2_tight == 1)" + ")";
    TString cutStringDataOSMedMC       = "36*xSecEvtWgt*tau_sf*trigger_sf*btag_sf*pu_central*(" + cutStringData + "&& (lep1_pdgid == -1*lep2_pdgid)" + " && (lep1_medium == 1 && lep2_medium == 1)" + ")";


    tData->Draw("mt2>>hMT2Train",cutStringDataSSVTightTrain);
    tData->Draw("mt2>>hMT2TrainErrors",cutStringDataSSVTightTrain);
    tData->Draw("mt2>>hMT2Test",cutStringDataSSVTightTest);
    hMT2Test->Draw();
    hMT2Train->Draw("same");
    hMT2TrainErrors->Draw("sameE2");
    c1->Print("plots/SSVTight.pdf");
    c1->SetLogy();
    c1->Print("plots/SSVTight_log.pdf");
    c1->SetLogy(false);


    tData->Draw("mt2>>hMT2Train",cutStringDataSSTightTrain);
    tData->Draw("mt2>>hMT2TrainErrors",cutStringDataSSTightTrain);
    tData->Draw("mt2>>hMT2Test",cutStringDataSSTightTest);
    hMT2Test->Draw();
    hMT2Train->Draw("same");
    hMT2TrainErrors->Draw("sameE2");
    c1->Print("plots/SSTight.pdf");
    c1->SetLogy();
    c1->Print("plots/SSTight_log.pdf");
    c1->SetLogy(false);

    tData->Draw("mt2>>hMT2Train",cutStringDataSSMedTrain);
    tData->Draw("mt2>>hMT2TrainErrors",cutStringDataSSMedTrain);
    tData->Draw("mt2>>hMT2Test",cutStringDataSSMedTest);
    hMT2Test->Draw();
    hMT2Train->Draw("same");
    hMT2TrainErrors->Draw("sameE2");
    c1->Print("plots/SSMed.pdf");
    c1->SetLogy();
    c1->Print("plots/SSMed_log.pdf");
    c1->SetLogy(false);

    tData->Draw("mt2>>hMT2Train",cutStringDataOSVTightTrain);
    tDY->Draw("mt2>>hMT2TrainMC",cutStringDataOSVTightMC);
    tData->Draw("mt2>>hMT2TrainErrors",cutStringDataOSVTightTrain);
    tData->Draw("mt2>>hMT2Test",cutStringDataOSVTightTest);

    THStack *hStack = new THStack("hs","");
    hStack->Add(hMT2Train);
    hStack->Add(hMT2TrainMC);
    hStack->Draw();
    hMT2Test->Draw("same");

    c1->Print("plots/OSVTight.pdf");
    c1->SetLogy();
    c1->Print("plots/OSVTight_log.pdf");
    c1->SetLogy(false);

    hStack = new THStack("hs","");
    tData->Draw("mt2>>hMT2Train",cutStringDataOSTightTrain);
    tDY->Draw("mt2>>hMT2TrainMC",cutStringDataOSTightMC);
    tData->Draw("mt2>>hMT2TrainErrors",cutStringDataOSTightTrain);
    tData->Draw("mt2>>hMT2Test",cutStringDataOSTightTest);
    hStack->Add(hMT2Train);
    hStack->Add(hMT2TrainMC);
    hStack->Draw();
    hMT2Test->Draw("same");
    c1->Print("plots/OSTight.pdf");
    c1->SetLogy();
    c1->Print("plots/OSTight_log.pdf");
    c1->SetLogy(false);

    hStack = new THStack("hs","");
    tData->Draw("mt2>>hMT2Train",cutStringDataOSMedTrain);
    tDY->Draw("mt2>>hMT2TrainMC",cutStringDataOSMedMC);
    tC_RARE->Draw("mt2>>hMT2TrainMC_2",cutStringDataOSMedMC);
    tData->Draw("mt2>>hMT2TrainErrors",cutStringDataOSMedTrain);
    tData->Draw("mt2>>hMT2Test",cutStringDataOSMedTest);
    hStack->Add(hMT2Train);
    hStack->Add(hMT2TrainMC);
    hStack->Add(hMT2TrainMC_2);
    hStack->Draw();
    hMT2Test->Draw("same");
    c1->Print("plots/OSMed.pdf");
    c1->SetLogy();
    c1->Print("plots/OSMed_log.pdf");
    c1->SetLogy(false);




}
