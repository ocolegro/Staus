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

class FRCalculator {
    public:
    FRCalculator() {
        fakeRateHistograms = new TFile("weights/calculatedFakeRates.root", "READ");
        promptRateHistograms = new TFile("weights/calculatedPromptRates.root", "READ");
    };

    double fakeRate(double taupt,int tau_decaymode, float mt_sum, TString selection = "_vtight"){
        TH1F * reWeighter;
        TString prefix,suffix;
        if (taupt > 80 )  {
            prefix = "PT_loose";
        }
        else{
            prefix = "MT_loose";
        }
        if (tau_decaymode == 0){
            suffix = "_mode0;1";
        }
        else if (tau_decaymode == 1){
            suffix = "_mode1;1";
        }
        else{
            suffix = "_mode10;1";
        }
        reWeighter = (TH1F*) fakeRateHistograms->Get(prefix + selection + suffix);

        //std::cout << "reWeighter->GetBinContent(4); = " << reWeighter->GetBinContent(4) << std::endl;
        if (taupt > 160){ return reWeighter->GetBinContent(4);}                 
        else if (taupt >= 120 && taupt < 160){ return reWeighter->GetBinContent(3); }
        else if (taupt >= 80 && taupt < 120) { return reWeighter->GetBinContent(2); }
        else   {
            if (mt_sum < 50) return reWeighter->GetBinContent(1);
            else if (mt_sum < 100) return reWeighter->GetBinContent(2);
            else if (mt_sum < 150) return reWeighter->GetBinContent(3);
            else   { return reWeighter->GetBinContent(4);}
        }
    };
    
    double promptRate(double taupt,int tau_decaymode, float iso, TString selection = "_vtight"){
        TH1F * reWeighter;
        TString prefix,suffix;
        prefix = "Iso_loose";

        if (tau_decaymode == 0){
            suffix = "_mode0;1";
        }
        else if (tau_decaymode == 1){
            suffix = "_mode1;1";
        }
        else{
            suffix = "_mode10;1";
        }

        //std::cout << "Getting histogram = " << prefix + "_vtight" + suffix << std::endl;
        reWeighter = (TH1F*) promptRateHistograms->Get(prefix + selection + suffix);

        if (iso < .8) return reWeighter->GetBinContent(1);
            else if (iso < .9) return reWeighter->GetBinContent(2);
            else if (iso < .95) return reWeighter->GetBinContent(3);
            else  return reWeighter->GetBinContent(4);

    };
    
    double getFREventWeight(double taupt1, bool tau1_vtight, int tau1_decaymode, double tau1_iso,
                            double taupt2, bool tau2_vtight,int tau2_decaymode, double tau2_iso, float mt_sum, TString selection){
        
      double fr1 = fakeRate(taupt1,tau1_decaymode,mt_sum,selection),fr2 = fakeRate(taupt2,tau2_decaymode,mt_sum,selection);
      
      double pr1 = promptRate(taupt1,tau1_decaymode,tau2_iso,selection), pr2 = promptRate(taupt2,tau2_decaymode,tau1_iso,selection);
     //std::cout << "fr1 = " << fr1 << " pr1 = " << pr1 << std::endl;
      double fakeFake     = 0;
      double promptFake   = 0;
      double fakePrompt   = 0;
      double promptPrompt = 0;
      double pr_h1 = 1 - pr1,pr_h2 = 1 - pr2,fr_h1 = 1 - fr1,fr_h2 = 1 - fr2; 

      if          (tau1_vtight && tau2_vtight)   {
          fakeFake   = pr_h1 * pr_h2;
          fakePrompt = -1 *  (pr_h1 * fr_h2);
          promptFake = -1 *  (fr_h1 * pr_h2);                    
      } 
      else if     (tau1_vtight && !tau2_vtight)  { 
          fakeFake   = -1 * pr_h1 * pr2;
          fakePrompt =  pr_h1 * fr2;
          promptFake =  fr_h1 * pr2;
      } 
      else if     (!tau1_vtight && tau2_vtight)  {  
          fakeFake   = -1 * pr1 * pr_h2;
          fakePrompt =  pr1 * fr_h2;
          promptFake =  fr1 * pr_h2;
      }
      else if     (!tau1_vtight && !tau2_vtight) {  
          fakeFake   =  pr1 * pr2;
          fakePrompt = -pr1 * fr2;
          promptFake = -fr1 * pr2;
      }
      float denom      = ((pr1-fr1) * (pr2-fr2));
      return fakeFake  * (fr1 * fr2 / denom )  + fakePrompt * (fr1 * pr2 / denom ) + promptFake * (fr2 * pr1  / denom );

    };
    TFile *fakeRateHistograms,*promptRateHistograms;

};

void fillFakeWeightsData(){
    bool verbose = false;
    TChain * tData  = new TChain("Events");
    tData->Add("data/TauRun*.root");
    const TTree *tDataTree = (TTree*)tData->GetTree();
       
    bool pass_trig,badcharged_filter,badmuon_filter,pv_filter,
    beamhalo_filter,hbhe_filter,hbheiso_filter,ecaltp_filter,eebadsc_filter,
    lep1_matchtrig,lep2_matchtrig,lep1_loose,lep2_loose,lep1_med,lep2_med,
    lep1_tight,lep2_tight,lep1_vtight,lep2_vtight;
    Int_t nbjetsloose,nvetoele,nvetomu,lep1_decaymode,lep2_decaymode;

    Float_t lep1_iso,lep2_iso,lep1_pt,lep2_pt,lep1_eta,lep2_eta,lep1_pdgid,lep2_pdgid,mt2,mt_sum,dphi_l1l2,pfmet;
    tData->SetBranchAddress("pass_trig",&pass_trig);
    tData->SetBranchAddress("badcharged_filter",&badcharged_filter);
    tData->SetBranchAddress("badmuon_filter",&badmuon_filter);
    tData->SetBranchAddress("pv_filter",&pv_filter);
    tData->SetBranchAddress("beamhalo_filter",&beamhalo_filter);
    tData->SetBranchAddress("hbhe_filter",&hbhe_filter);
    tData->SetBranchAddress("hbheiso_filter",&hbheiso_filter);
    tData->SetBranchAddress("ecaltp_filter",&ecaltp_filter);
    tData->SetBranchAddress("eebadsc_filter",&eebadsc_filter);
    tData->SetBranchAddress("nbjetsloose",&nbjetsloose);
    tData->SetBranchAddress("nvetomu",&nvetomu);
    tData->SetBranchAddress("nvetoele",&nvetoele);
    tData->SetBranchAddress("lep1_loose",&lep1_loose);
    tData->SetBranchAddress("lep2_loose",&lep2_loose);
    tData->SetBranchAddress("lep1_medium",&lep1_med);
    tData->SetBranchAddress("lep2_medium",&lep2_med);
    tData->SetBranchAddress("lep1_tight",&lep1_tight);
    tData->SetBranchAddress("lep2_tight",&lep2_tight);
    tData->SetBranchAddress("lep1_vtight",&lep1_vtight);
    tData->SetBranchAddress("lep2_vtight",&lep2_vtight);
    tData->SetBranchAddress("lep1_pt",&lep1_pt);
    tData->SetBranchAddress("lep2_pt",&lep2_pt);
    tData->SetBranchAddress("lep1_eta",&lep1_eta);
    tData->SetBranchAddress("lep2_eta",&lep2_eta);
    tData->SetBranchAddress("lep1_matchtrig",&lep1_matchtrig);
    tData->SetBranchAddress("lep2_matchtrig",&lep2_matchtrig);
    tData->SetBranchAddress("lep1_pdgid",&lep1_pdgid);
    tData->SetBranchAddress("lep2_pdgid",&lep2_pdgid);
    tData->SetBranchAddress("lep1_decaymode",&lep1_decaymode);
    tData->SetBranchAddress("lep2_decaymode",&lep2_decaymode);
    tData->SetBranchAddress("lep1_iso",&lep1_iso);
    tData->SetBranchAddress("lep2_iso",&lep2_iso);
    tData->SetBranchAddress("mt2",&mt2);
    tData->SetBranchAddress("mt_sum",&mt_sum);
    tData->SetBranchAddress("dphi_l1l2",&dphi_l1l2);
    tData->SetBranchAddress("pfmet",&pfmet);

    
    FRCalculator * eventWeighter = new FRCalculator();
    

    TH1F * hSR1 = new TH1F("hSR1","hSR1",1,0,1)  ;
    TH1F * hSR2 = new TH1F("hSR2","hSR2",1,0,1)  ;
    TH1F * hSR3 = new TH1F("hSR3","hSR3",1,0,1)  ;

    hSR1->Sumw2();hSR2->Sumw2();hSR3->Sumw2();


    TString outFile = "data/TauDataFRWeighted.root";
    TFile * fOut = new TFile(outFile, "RECREATE");
    TTree * tOut = tData->CloneTree(0);
    float fakeWeightMedium = 0;
    float fakeWeightTight = 0;
    float fakeWeightVTight = 0 ;
    tOut->Branch("fakeWeightVTight", &fakeWeightVTight, "fakeWeightVTight/F");
    tOut->Branch("fakeWeightTight", &fakeWeightTight, "fakeWeightTight/F");
    tOut->Branch("fakeWeightMedium", &fakeWeightMedium, "fakeWeightMedium/F");



    //read all entries and fill the histograms
    Long64_t nEntries = tData->GetEntries();
    for (Long64_t iEntry=0; iEntry < nEntries; iEntry++) {
        if ((iEntry%100000) == 0) std::cout << "iEntry = " << iEntry << std::endl;
        tData->GetEntry(iEntry);
        if (pass_trig != 1){
            if(verbose)std::cout << "TRIGGER FAILED" << std::endl;      
            continue;
        }
        if (nbjetsloose != 0 || nvetomu != 0 || nvetoele != 0){
            if(verbose)std::cout << "LEPTON and B FILTER FAILED" << std::endl;  
            continue;
        }
        if (!(badcharged_filter == 0 && badmuon_filter == 0 && 
                pv_filter == 0 && beamhalo_filter == 0 && hbhe_filter == 0 && 
                hbheiso_filter == 0 && ecaltp_filter == 0 && eebadsc_filter == 0)){
            if(verbose)std::cout << "MET FILTER FAILED" << std::endl;
            continue;
        }
        if ( abs(lep1_pdgid) != 15 || abs(lep2_pdgid) != 15){
            if(verbose)std::cout << "REQUIRING TWO TAUS FAILED" << std::endl;
            continue;
        }
        if (lep1_pt < 40 || lep2_pt < 40 || abs(lep1_eta) > 2.1 || abs(lep2_eta) > 2.1){
            if(verbose)std::cout << "TAU KINEMATICS FAILED" << std::endl;      
            continue;
        }
        if (lep1_matchtrig != 1 || lep2_matchtrig != 1){
            if(verbose)std::cout << "TAU TRIGGER MATCH FAILED" << std::endl;      
            continue;
        }
        if (lep1_loose != 1 || lep2_loose != 1){
            if(verbose)std::cout << "LOOSE TAUS FAILED" << std::endl;      
            continue;
        }

                
        fakeWeightVTight = eventWeighter->getFREventWeight(lep1_pt,lep1_vtight,lep1_decaymode,lep1_iso,
                                                           lep2_pt,lep2_vtight,lep2_decaymode,lep2_iso,mt_sum,"_vtight");


        fakeWeightTight = eventWeighter->getFREventWeight(lep1_pt,lep1_tight,lep1_decaymode,lep1_iso,
                                                           lep2_pt,lep2_tight,lep2_decaymode,lep2_iso,mt_sum,"_tight");
        //std::cout << "fakeWeightTight = " << fakeWeightTight << std::endl;
        fakeWeightMedium = eventWeighter->getFREventWeight(lep1_pt,lep1_med,lep1_decaymode,lep1_iso,
                                                               lep2_pt,lep2_med,lep2_decaymode,lep2_iso,mt_sum,"_med");

        tOut->Fill();
    }
    tOut->Write();
    fOut->Close();

}

