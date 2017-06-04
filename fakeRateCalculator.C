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

void fakeRateCalculator(){
    bool verbose = false;
    TChain * tData  = new TChain("Events");
    tData->Add("data/TauRun*.root");
    const TTree *tDataTree = (TTree*)tData->GetTree();
       
    bool pass_trig,badcharged_filter,badmuon_filter,pv_filter,
    beamhalo_filter,hbhe_filter,hbheiso_filter,ecaltp_filter,eebadsc_filter,
    lep1_matchtrig,lep2_matchtrig,lep1_loose,lep2_loose,lep1_med,lep2_med,
    lep1_tight,lep2_tight,lep1_vtight,lep2_vtight;
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

    Double_t binsMT[] = {0,50,100,125,175};
    TH1F * hMTLooseMode0     = new TH1F("hMTLooseMode0","hMTLooseMode0",4,binsMT)  ;
    TH1F * hMTMedMode0       = new TH1F("hMTMedMode0","hMTMedMode0",4,binsMT)  ;
    TH1F * hMTTightMode0     = new TH1F("hMTTightMode0","hMTTightMode0",4,binsMT)  ;
    TH1F * hMTVTightMode0    = new TH1F("hMTVTightMode0","hMTVTightMode0",4,binsMT)  ;
    
    TH1F * hMTLooseMode1     = new TH1F("hMTLooseMode1","hMTLooseMode1",4,binsMT)  ;
    TH1F * hMTMedMode1       = new TH1F("hMTMedMode1","hMTMedMode1",4,binsMT)  ;
    TH1F * hMTTightMode1     = new TH1F("hMTTightMode1","hMTTightMode1",4,binsMT)  ;
    TH1F * hMTVTightMode1    = new TH1F("hMTVTightMode1","hMTVTightMode1",4,binsMT)  ;

    TH1F * hMTLooseMode10    = new TH1F("hMTLooseMode10","hMTLooseMode10",4,binsMT)  ;
    TH1F * hMTMedMode10      = new TH1F("hMTMedMode10","hMTMedMode10",4,binsMT)  ;
    TH1F * hMTTightMode10    = new TH1F("hMTTightMode10","hMTTightMode10",4,binsMT)  ;
    TH1F * hMTVTightMode10   = new TH1F("hMTVTightMode10","hMTVTightMode10",4,binsMT)  ;
 
    hPTLooseMode0->Sumw2();     hPTMedMode0->Sumw2();   hPTTightMode0->Sumw2();      hPTVTightMode0->Sumw2();
    hPTLooseMode1->Sumw2();     hPTMedMode1->Sumw2();   hPTTightMode1->Sumw2();      hPTVTightMode1->Sumw2();
    hPTLooseMode10->Sumw2();    hPTMedMode10->Sumw2();  hPTTightMode10->Sumw2();     hPTVTightMode10->Sumw2();

    hMTLooseMode0->Sumw2();     hMTMedMode0->Sumw2();   hMTTightMode0->Sumw2();      hMTVTightMode0->Sumw2();
    hMTLooseMode1->Sumw2();     hMTMedMode1->Sumw2();   hMTTightMode1->Sumw2();      hMTVTightMode1->Sumw2();
    hMTLooseMode10->Sumw2();    hMTMedMode10->Sumw2();  hMTTightMode10->Sumw2();     hMTVTightMode10->Sumw2();

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

        if (mt2 > 40){
            if(verbose)std::cout << "MT2 CUT FAILED" << std::endl;
            continue;
        }

        if (lep1_pdgid == -lep2_pdgid){
            if (verbose) std::cout << "OPPOSITE SIGNED TAU LEPTON CUT FAILED" << std::endl;
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
        float bin1PTCut = 80;
        if (lep1_decaymode == 0){
            hPTLooseMode0->Fill(lep1_pt);
            if (lep1_pt < bin1PTCut) hMTLooseMode0->Fill(mt_max);
            if (lep1_med)  { 
                if (lep1_pt < bin1PTCut) hMTMedMode0->Fill(mt_max);
                hPTMedMode0->Fill(lep1_pt); 
            }

            if (lep1_tight)  {
                if (lep1_pt < bin1PTCut) hMTTightMode0->Fill(mt_max);
                hPTTightMode0->Fill(lep1_pt);
            }

            if (lep1_vtight)  {
                if (lep1_pt < bin1PTCut) hMTVTightMode0->Fill(mt_max);
                hPTVTightMode0->Fill(lep1_pt);
            }                         
        }
        if (lep2_decaymode == 0){
            hPTLooseMode0->Fill(lep2_pt);
            if (lep2_pt < bin1PTCut) hMTLooseMode0->Fill(mt_max);
            if (lep2_med)  { 
                if (lep2_pt < bin1PTCut) hMTMedMode0->Fill(mt_max);
                hPTMedMode0->Fill(lep2_pt); 
            }        
            if (lep2_tight)  {
                if (lep2_pt < bin1PTCut) hMTTightMode0->Fill(mt_max);
                hPTTightMode0->Fill(lep2_pt);
            }
            if (lep2_vtight)  {
                if (lep2_pt < bin1PTCut)  hMTVTightMode0->Fill(mt_max);
                hPTVTightMode0->Fill(lep2_pt);
            }
        }
        
        if (lep1_decaymode == 1){
             hPTLooseMode1->Fill(lep1_pt);
             if (lep1_pt < bin1PTCut) hMTLooseMode1->Fill(mt_max);
             if (lep1_med)  { 
                 if (lep1_pt < bin1PTCut) hMTMedMode1->Fill(mt_max);
                 hPTMedMode1->Fill(lep1_pt); 
             }

             if (lep1_tight)  {
                 if (lep1_pt < bin1PTCut) hMTTightMode1->Fill(mt_max);
                 hPTTightMode1->Fill(lep1_pt);
             }

             if (lep1_vtight)  {
                 if (lep1_pt < bin1PTCut) hMTVTightMode1->Fill(mt_max);
                 hPTVTightMode1->Fill(lep1_pt);
             }                           
         }
         if (lep2_decaymode == 1){
             hPTLooseMode1->Fill(lep2_pt);
             if (lep2_pt < bin1PTCut) hMTLooseMode1->Fill(mt_max);
             if (lep2_med)  { 
                 if (lep2_pt < bin1PTCut) hMTMedMode1->Fill(mt_max);
                 hPTMedMode1->Fill(lep2_pt); 
             }        
             if (lep2_tight)  {
                 if (lep2_pt < bin1PTCut) hMTTightMode1->Fill(mt_max);
                 hPTTightMode1->Fill(lep2_pt);
             }
             if (lep2_vtight)  {
                 if (lep2_pt < bin1PTCut) hMTVTightMode1->Fill(mt_max);
                 hPTVTightMode1->Fill(lep2_pt);
             }
         }
         
         if (lep1_decaymode == 10){
              hPTLooseMode10->Fill(lep1_pt);
              if (lep1_pt < bin1PTCut) hMTLooseMode10->Fill(mt_max);
              if (lep1_med)  { 
                  if (lep1_pt < bin1PTCut) hMTMedMode10->Fill(mt_max);
                  hPTMedMode10->Fill(lep1_pt); 
              }

              if (lep1_tight)  {
                  if (lep1_pt < bin1PTCut) hMTTightMode10->Fill(mt_max);
                  hPTTightMode10->Fill(lep1_pt);
              }

              if (lep1_vtight)  {
                  if (lep1_pt < bin1PTCut) hMTVTightMode10->Fill(mt_max);
                  hPTVTightMode10->Fill(lep1_pt);
              }                            
          }
          if (lep2_decaymode == 10){
              hPTLooseMode10->Fill(lep2_pt);
              if (lep2_pt < bin1PTCut) hMTLooseMode10->Fill(mt_max);
              if (lep2_med)  { 
                  if (lep2_pt < bin1PTCut) hMTMedMode10->Fill(mt_max);
                  hPTMedMode10->Fill(lep2_pt); 
              }        
              if (lep2_tight)  {
                  if (lep2_pt < bin1PTCut) hMTTightMode10->Fill(mt_max);
                  hPTTightMode10->Fill(lep2_pt);
              }
              if (lep2_vtight)  {
                  if (lep2_pt < bin1PTCut) hMTVTightMode10->Fill(mt_max);
                  hPTVTightMode10->Fill(lep2_pt);
              }
          }
    }
        
    TFile *outFile = new TFile("weights/calculatedFakeRates.root", "RECREATE");


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

    
    hMTMedMode0->Divide(hMTLooseMode0);
    hMTMedMode0->SetName("MT_loose_med_mode0");
    hMTMedMode0->Write();
    hPTMedMode0->Draw();

    hMTTightMode0->Divide(hMTLooseMode0);
    hMTTightMode0->SetName("MT_loose_tight_mode0");
    hMTTightMode0->Write();

    hMTVTightMode0->Divide(hMTLooseMode0);
    hMTVTightMode0->SetName("MT_loose_vtight_mode0");
    hMTVTightMode0->Write();

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

    
    hMTMedMode1->Divide(hMTLooseMode1);
    hMTMedMode1->SetName("MT_loose_med_mode1");
    hMTMedMode1->Write();
    
    hMTTightMode1->Divide(hMTLooseMode1);
    hMTTightMode1->SetName("MT_loose_tight_mode1");
    hMTTightMode1->Write();

    hMTVTightMode1->Divide(hMTLooseMode1);
    hMTVTightMode1->SetName("MT_loose_vtight_mode1");
    hMTVTightMode1->Write();
    
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

    
    hMTMedMode10->Divide(hMTLooseMode10);
    hMTMedMode10->SetName("MT_loose_med_mode10");
    hMTMedMode10->Write();
    
    hMTTightMode10->Divide(hMTLooseMode10);
    hMTTightMode10->SetName("MT_loose_tight_mode10");
    hMTTightMode10->Write();

    hMTVTightMode10->Divide(hMTLooseMode10);
    hMTVTightMode10->SetName("MT_loose_vtight_mode10");
    hMTVTightMode10->Write();
   
    outFile->Close();
            
}
