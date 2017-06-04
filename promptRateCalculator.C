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

void promptRateCalculator(){
    bool verbose = false;
    TChain * tData  = new TChain("Events");
    tData->Add("MC/DY*.root");
    const TTree *tDataTree = (TTree*)tData->GetTree();
       
    bool pass_trig,badcharged_filter,badmuon_filter,pv_filter,
    beamhalo_filter,hbhe_filter,hbheiso_filter,ecaltp_filter,eebadsc_filter,
    lep1_matchtrig,lep2_matchtrig,lep1_loose,lep2_loose,lep1_med,lep2_med,
    lep1_tight,lep2_tight,lep1_vtight,lep2_vtight,lep1_match,lep2_match;
    Int_t nbjetsloose,nvetoele,nvetomu,lep1_decaymode,lep2_decaymode;

    Float_t lep1_mt,lep1_iso,lep2_mt,lep2_iso,lep1_pt,lep2_pt,lep1_eta,lep2_eta,lep1_pdgid,lep2_pdgid,mt2,mt_sum,ht,dR_l1l2,dphi_l1l2;
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
    tData->SetBranchAddress("lep1_mt",&lep1_mt);
    tData->SetBranchAddress("lep2_mt",&lep2_mt);
    tData->SetBranchAddress("lep1_iso",&lep1_iso);
    tData->SetBranchAddress("lep2_iso",&lep2_iso);
    tData->SetBranchAddress("lep1_pt",&lep1_pt);
    tData->SetBranchAddress("lep2_pt",&lep2_pt);
    tData->SetBranchAddress("lep1_eta",&lep1_eta);
    tData->SetBranchAddress("lep2_eta",&lep2_eta);
    tData->SetBranchAddress("lep1_match",&lep1_match);
    tData->SetBranchAddress("lep2_match",&lep2_match);
    tData->SetBranchAddress("lep1_matchtrig",&lep1_matchtrig);
    tData->SetBranchAddress("lep2_matchtrig",&lep2_matchtrig);
    tData->SetBranchAddress("lep1_pdgid",&lep1_pdgid);
    tData->SetBranchAddress("lep2_pdgid",&lep2_pdgid);
    tData->SetBranchAddress("lep1_decaymode",&lep1_decaymode);
    tData->SetBranchAddress("lep2_decaymode",&lep2_decaymode);
    tData->SetBranchAddress("mt2",&mt2);
    tData->SetBranchAddress("ht",&ht);
    tData->SetBranchAddress("mt_sum",&mt_sum);
    tData->SetBranchAddress("dR_l1l2",&dR_l1l2);
    tData->SetBranchAddress("dphi_l1l2",&dphi_l1l2);

    Double_t binsPT[] = {40,80,120,160,200};
    TH1F * hPTLooseMode0     = new TH1F("hPTLooseMode0","hPTLooseMode0",4,binsPT)  ;
    TH1F * hPTMedMode0       = new TH1F("hPTMedMode0","hPTMedMode0",4,binsPT)  ;
    TH1F * hPTTightMode0     = new TH1F("hPTTightMode0","hPTTightMode0",4,binsPT)  ;
    TH1F * hPTVTightMode0    = new TH1F("hPTVTightMode0","hPTVTightMode0",4,binsPT)  ;
    
    TH1F * hPTLooseMode1     = new TH1F("hPTLooseMode1","hPTLooseMode1",4,binsPT)  ;
    TH1F * hPTMedMode1       = new TH1F("hPTMedMode1","hPTMedMode1",4,binsPT)  ;
    TH1F * hPTTightMode1     = new TH1F("hPTTightMode1","hPTTightMode1",4,binsPT)  ;
    TH1F * hPTVTightMode1    = new TH1F("hPTVTightMode1","hPTVTightMode1",4,binsPT)  ;

    TH1F * hPTLooseMode10    = new TH1F("hPTLooseMode10","hPTLooseMode10",4,binsPT)  ;
    TH1F * hPTMedMode10      = new TH1F("hPTMedMode10","hPTMedMode10",4,binsPT)  ;
    TH1F * hPTTightMode10    = new TH1F("hPTTightMode10","hPTTightMode10",4,binsPT)  ;
    TH1F * hPTVTightMode10   = new TH1F("hPTVTightMode10","hPTVTightMode10",4,binsPT)  ;

    
    Double_t binsIso[] = {.5,.7,.8,.9,1};
    TH1F * hIsoLooseMode0     = new TH1F("hIsoLooseMode0","hIsoLooseMode0",4,binsIso)  ;
    TH1F * hIsoMedMode0       = new TH1F("hIsoMedMode0","hIsoMedMode0",4,binsIso)  ;
    TH1F * hIsoTightMode0     = new TH1F("hIsoTightMode0","hIsoTightMode0",4,binsIso)  ;
    TH1F * hIsoVTightMode0    = new TH1F("hIsoVTightMode0","hIsoVTightMode0",4,binsIso)  ;
    
    TH1F * hIsoLooseMode1     = new TH1F("hIsoLooseMode1","hIsoLooseMode1",4,binsIso)  ;
    TH1F * hIsoMedMode1       = new TH1F("hIsoMedMode1","hIsoMedMode1",4,binsIso)  ;
    TH1F * hIsoTightMode1     = new TH1F("hIsoTightMode1","hIsoTightMode1",4,binsIso)  ;
    TH1F * hIsoVTightMode1    = new TH1F("hIsoVTightMode1","hIsoVTightMode1",4,binsIso)  ;

    TH1F * hIsoLooseMode10    = new TH1F("hIsoLooseMode10","hIsoLooseMode10",4,binsIso)  ;
    TH1F * hIsoMedMode10      = new TH1F("hIsoMedMode10","hIsoMedMode10",4,binsIso)  ;
    TH1F * hIsoTightMode10    = new TH1F("hIsoTightMode10","hIsoTightMode10",4,binsIso)  ;
    TH1F * hIsoVTightMode10   = new TH1F("hIsoVTightMode10","hIsoVTightMode10",4,binsIso)  ;

 
    hIsoLooseMode0->Sumw2();     hIsoMedMode0->Sumw2();   hIsoTightMode0->Sumw2();      hIsoVTightMode0->Sumw2();
    hIsoLooseMode1->Sumw2();     hIsoMedMode1->Sumw2();   hIsoTightMode1->Sumw2();      hIsoVTightMode1->Sumw2();
    hIsoLooseMode10->Sumw2();    hIsoMedMode10->Sumw2();  hIsoTightMode10->Sumw2();     hIsoVTightMode10->Sumw2();

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
        if (lep1_pdgid == lep2_pdgid){
            if (verbose) std::cout << "SAME SIGNED TAU LEPTON CUT FAILED" << std::endl;
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

        if (lep1_pt < 40 || lep2_pt < 40 || abs(lep1_eta) > 2.1 || abs(lep2_eta) > 2.1){
            if(verbose)std::cout << "TAU KINEMATICS FAILED" << std::endl;      
            continue;
        }                
        //std::cout << "Event weight = " << evtWeight << std::endl;
        bool lep1_pt_cut = lep1_pt < 80  &&  abs(lep1_eta) < 2.1 && lep1_matchtrig;
        bool lep2_pt_cut = lep2_pt < 80   && abs(lep2_eta) < 2.1 && lep2_matchtrig;
        float mt_max = TMath::Max(lep1_mt,lep2_mt);
        //std::cout << "lep1_mt = " << lep1_mt <<  " mt_max = " << mt_max << std::endl;

        if (mt_sum >= 225) mt_sum = 224;
        if (mt_max >= 175) mt_max = 174;
        float bin1PTCut = 1e6;
        if (lep1_decaymode == 0 and lep1_match){
            hPTLooseMode0->Fill(lep1_pt);
            if (lep1_pt < bin1PTCut) hIsoLooseMode0->Fill(lep2_iso);
            if (lep1_med)  { 
                if (lep1_pt < bin1PTCut) hIsoMedMode0->Fill(lep2_iso);
                hPTMedMode0->Fill(lep1_pt); 
            }

            if (lep1_tight)  {
                if (lep1_pt < bin1PTCut) hIsoTightMode0->Fill(lep2_iso);
                hPTTightMode0->Fill(lep1_pt);
            }

            if (lep1_vtight)  {
                if (lep1_pt < bin1PTCut) hIsoVTightMode0->Fill(lep2_iso);
                hPTVTightMode0->Fill(lep1_pt);
            }                         
        }
        if (lep2_decaymode == 0 and lep2_match){
            hPTLooseMode0->Fill(lep2_pt);
            if (lep2_pt < bin1PTCut) hIsoLooseMode0->Fill(lep1_iso);
            if (lep2_med)  { 
                if (lep2_pt < bin1PTCut) hIsoMedMode0->Fill(lep1_iso);
                hPTMedMode0->Fill(lep2_pt); 
            }        
            if (lep2_tight)  {
                if (lep2_pt < bin1PTCut) hIsoTightMode0->Fill(lep1_iso);
                hPTTightMode0->Fill(lep2_pt);
            }
            if (lep2_vtight)  {
                if (lep2_pt < bin1PTCut)  hIsoVTightMode0->Fill(lep1_iso);
                hPTVTightMode0->Fill(lep2_pt);
            }
        }
        
        if (lep1_decaymode == 1 and lep1_match){
             hPTLooseMode1->Fill(lep1_pt);
             if (lep1_pt < bin1PTCut) hIsoLooseMode1->Fill(lep2_iso);
             if (lep1_med)  { 
                 if (lep1_pt < bin1PTCut) hIsoMedMode1->Fill(lep2_iso);
                 hPTMedMode1->Fill(lep1_pt); 
             }

             if (lep1_tight)  {
                 if (lep1_pt < bin1PTCut) hIsoTightMode1->Fill(lep2_iso);
                 hPTTightMode1->Fill(lep1_pt);
             }

             if (lep1_vtight)  {
                 if (lep1_pt < bin1PTCut) hIsoVTightMode1->Fill(lep2_iso);
                 hPTVTightMode1->Fill(lep1_pt);
             }                           
         }
         if (lep2_decaymode == 1 and lep2_match){
             hPTLooseMode1->Fill(lep2_pt);
             if (lep2_pt < bin1PTCut) hIsoLooseMode1->Fill(lep1_iso);
             if (lep2_med)  { 
                 if (lep2_pt < bin1PTCut) hIsoMedMode1->Fill(lep1_iso);
                 hPTMedMode1->Fill(lep2_pt); 
             }        
             if (lep2_tight)  {
                 if (lep2_pt < bin1PTCut) hIsoTightMode1->Fill(lep1_iso);
                 hPTTightMode1->Fill(lep2_pt);
             }
             if (lep2_vtight)  {
                 if (lep2_pt < bin1PTCut) hIsoVTightMode1->Fill(lep1_iso);
                 hPTVTightMode1->Fill(lep2_pt);
             }
         }
         
         if (lep1_decaymode == 10 and lep1_match){
              hPTLooseMode10->Fill(lep1_pt);
              if (lep1_pt < bin1PTCut) hIsoLooseMode10->Fill(lep2_iso);
              if (lep1_med)  { 
                  if (lep1_pt < bin1PTCut) hIsoMedMode10->Fill(lep2_iso);
                  hPTMedMode10->Fill(lep1_pt); 
              }

              if (lep1_tight)  {
                  if (lep1_pt < bin1PTCut) hIsoTightMode10->Fill(lep2_iso);
                  hPTTightMode10->Fill(lep1_pt);
              }

              if (lep1_vtight)  {
                  if (lep1_pt < bin1PTCut) hIsoVTightMode10->Fill(lep2_iso);
                  hPTVTightMode10->Fill(lep1_pt);
              }                            
          }
          if (lep2_decaymode == 10 and lep2_match){
              hPTLooseMode10->Fill(lep2_pt);
              if (lep2_pt < bin1PTCut) hIsoLooseMode10->Fill(lep1_iso);
              if (lep2_med)  { 
                  if (lep2_pt < bin1PTCut) hIsoMedMode10->Fill(lep1_iso);
                  hPTMedMode10->Fill(lep2_pt); 
              }        
              if (lep2_tight)  {
                  if (lep2_pt < bin1PTCut) hIsoTightMode10->Fill(lep1_iso);
                  hPTTightMode10->Fill(lep2_pt);
              }
              if (lep2_vtight)  {
                  if (lep2_pt < bin1PTCut) hIsoVTightMode10->Fill(lep1_iso);
                  hPTVTightMode10->Fill(lep2_pt);
              }
          }
    }
        
    TFile *outFile = new TFile("weights/calculatedPromptRates.root", "RECREATE");


    /* Mode 0 */
    hPTMedMode0->Divide(hPTLooseMode0);
    hPTMedMode0->SetName("PT_loose_med_mode0");
    hPTMedMode0->Write();
    
    hPTTightMode0->Divide(hPTLooseMode0);
    hPTTightMode0->SetName("PT_loose_tight_mode0");
    hPTTightMode0->Write();

    hPTVTightMode0->Divide(hPTLooseMode0);
    hPTVTightMode0->SetName("PT_loose_vtight_mode0");
    hPTVTightMode0->Write();


    /* Mode 1 */
    hPTMedMode1->Divide(hPTLooseMode1);
    hPTMedMode1->SetName("PT_loose_med_mode1");
    hPTMedMode1->Write();
    
    hPTTightMode1->Divide(hPTLooseMode1);
    hPTTightMode1->SetName("PT_loose_tight_mode1");
    hPTTightMode1->Write();

    hPTVTightMode1->Divide(hPTLooseMode1);
    hPTVTightMode1->SetName("PT_loose_vtight_mode1");
    hPTVTightMode1->Write();

    /* Mode 10 */

    hPTMedMode10->Divide(hPTLooseMode10);
    hPTMedMode10->SetName("PT_loose_med_mode10");
    hPTMedMode10->Write();
    
    hPTTightMode10->Divide(hPTLooseMode10);
    hPTTightMode10->SetName("PT_loose_tight_mode10");
    hPTTightMode10->Write();

    hPTVTightMode10->Divide(hPTLooseMode10);
    hPTVTightMode10->SetName("PT_loose_vtight_mode10");
    hPTVTightMode10->Write();

    /* Mode 0 */
    hIsoMedMode0->Divide(hIsoLooseMode0);
    hIsoMedMode0->SetName("Iso_loose_med_mode0");
    hIsoMedMode0->Write();
    
    hIsoTightMode0->Divide(hIsoLooseMode0);
    hIsoTightMode0->SetName("Iso_loose_tight_mode0");
    hIsoTightMode0->Write();

    hIsoVTightMode0->Divide(hIsoLooseMode0);
    hIsoVTightMode0->SetName("Iso_loose_vtight_mode0");
    hIsoVTightMode0->Write();
    
   /* Mode 1 */
   hIsoMedMode1->Divide(hIsoLooseMode1);
   hIsoMedMode1->SetName("Iso_loose_med_mode1");
   hIsoMedMode1->Write();
   
   hIsoTightMode1->Divide(hIsoLooseMode1);
   hIsoTightMode1->SetName("Iso_loose_tight_mode1");
   hIsoTightMode1->Write();

   hIsoVTightMode1->Divide(hIsoLooseMode1);
   hIsoVTightMode1->SetName("Iso_loose_vtight_mode1");
   hIsoVTightMode1->Write();

   /* Mode 10 */

   hIsoMedMode10->Divide(hIsoLooseMode10);
   hIsoMedMode10->SetName("Iso_loose_med_mode10");
   hIsoMedMode10->Write();
   
   hIsoTightMode10->Divide(hIsoLooseMode10);
   hIsoTightMode10->SetName("Iso_loose_tight_mode10");
   hIsoTightMode10->Write();

   hIsoVTightMode10->Divide(hIsoLooseMode10);
   hIsoVTightMode10->SetName("Iso_loose_vtight_mode10");
   hIsoVTightMode10->Write();
    outFile->Close();
            
}
