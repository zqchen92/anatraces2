//
//last updated@26 May,2024
//Z.Chen
//***  for visualization  ***//
//


#include "../inc/lisa_vis.hh"

#include <vector>
#include <iostream>
#include <TGraph.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TMultiGraph.h>
#include <TSystem.h>
#include <TStyle.h>

lisa_vis::lisa_vis()
{
    std::cout << "lisa_vis::lisa_vis()" << std::endl;
    gVisCanvasCNT = 0;//reset the number of canvas
    gVisCanvas.clear();//reset the canvas
    setEnv();
}

lisa_vis::lisa_vis(lisa_febex *ffebex)
{
    if(ffebex == NULL){
        if(getVisVerbose() == 3)std::cout<<"***Error_lisa_vis_cc_001: lisa_vis(lisa_febex *ffebex=0)"<<std::endl;
    }
    gVisCanvasCNT = 0;//reset the number of canvas
    gVisCanvas.clear();//reset the canvas
    setEnv();
    std::cout << "lisa_vis::lisa_vis()" << std::endl;
}

lisa_vis::~lisa_vis()
{
    std::cout << "lisa_vis::~lisa_vis()" << std::endl;
}

TCanvas* lisa_vis::createCanvas(Int_t xx, Int_t yy)
{
    if(getVisVerbose() == 1)std::cout<<"debug_lisa_vis::createCanvas()"<<std::endl;
    TString cname = Form("lisa_canvas_%d",gVisCanvasCNT);
    gVisCanvas.push_back( new TCanvas(cname,cname,10,10,1500,900) );

    if(getVisVerbose() == 1)std::cout<<"debug2_lisa_vis::createCanvas()"<<std::endl;
    gVisCanvas[gVisCanvasCNT]->Divide(xx, yy);
    //gVisCanvas[gVisCanvasCNT]->Divide(xx, yy, -1, 0.001);//narrow margin
    gVisCanvasCNT++;
    return gVisCanvas[gVisCanvasCNT-1];
}

void lisa_vis::showSingleRawTrace(lisa_febex *ffebex)
{
    std::cout << "lisa_vis::showSingleRawTrace()" << std::endl;

    if(ffebex->getTree() == NULL){
        if(getVisVerbose() == 3)std::cout<<"***Error_lisa_vis_cc_002: empty tree. Please check your input file."<<std::endl;
    }
    //debug
    //TTree *ftree11 = ffebex->getTree();
    //ftree11->Draw("lisa_data1traces1v:lisa_data1traces1I");
    //return;

    ffebex->getSingleTrace( ffebex->getTree() );
    setVisJentry(ffebex->getJentry());
    int flen0 = ffebex->getFebexTraceL();
    std::vector<Int_t> fS_xx = ffebex->getRawTraceI();
    std::vector<Int_t> fS_yy = ffebex->getRawTraceV();

    if(flen0==0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_003: empty graph; trace length = 0."<<std::endl;
        return;
    }

    if(getVisVerbose() == 1){
        std::cout<<"flen0 = "<<flen0<<std::endl;
        std::cout<<"fS_xx = "<<fS_xx[0]<<std::endl;
        std::cout<<"fS_yy = "<<fS_yy[0]<<std::endl;
    }

    TGraph *gr0 = new TGraph( fS_xx.size(), fS_xx.data(), fS_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("Raw trace");
    gr0->GetXaxis()->SetTitle("Time [pts]");
    gr0->GetYaxis()->SetTitle("Energy [arb.]");
    //set format//
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    std::cout << "lisa_vis::showSingleRawTrace() end" << std::endl;
}

void lisa_vis::showSingleRawTrace(std::vector<Double_t> &tr_xx, std::vector<Double_t> &tr_yy)
{
    std::cout<<"lisa_vis::showSingleRawTrace()"<<std::endl;
    if(tr_xx.size() == 0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_011: empty graph; trace length = 0."<<std::endl;
        return;
    }

    TGraph *gr0 = new TGraph( tr_xx.size(), tr_xx.data(), tr_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("Raw trace");
    gr0->GetXaxis()->SetTitle("Time [ns]");
    gr0->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    std::cout<<"lisa_vis::showSingleRawTrace() end"<<std::endl;
}

void lisa_vis::showSingleCorrectTrace(lisa_febex *ffebex)
{
    std::cout << "lisa_vis::showSingleCorrectTrace()" << std::endl;

    int flen0 = ffebex->getFebexTraceL();

    if(flen0==0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_004: empty graph; trace length = 0."<<std::endl;
        return;
    }

    //debug
    //TTree *ftree11 = ffebex->getTree();
    //ftree11->Draw("lisa_data1traces1v:lisa_data1traces1I");
    //return;

    ffebex->getCorrectTrace();
    setVisJentry(ffebex->getJentry());
    std::vector<float> fC_xx = ffebex->getCorrectTraceI();
    std::vector<float> fC_yy = ffebex->getCorrectTraceV();

    if(getVisVerbose() == 1){
        std::cout<<"flen0 = "<<flen0<<std::endl;
        std::cout<<"fC_xx = "<<fC_xx[0]<<std::endl;
        std::cout<<"fC_yy = "<<fC_yy[0]<<std::endl;
    }
    TGraph *gr0 = new TGraph( fC_xx.size(), fC_xx.data(), fC_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("Corrected trace");
    gr0->GetXaxis()->SetTitle("Time [ns]");
    gr0->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    gr0->SetMarkerColor(kBlue);
    std::cout << "lisa_vis::showSingleCorrectTrace() end" << std::endl;
}

void lisa_vis::showSingleCorrectTrace(std::vector<Double_t> &tr_xx, std::vector<Double_t> &tr_yy){
    std::cout<<"lisa_vis::showSingleCorrectTrace()"<<std::endl;
    if(tr_xx.size() == 0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_012: empty graph; trace length = 0."<<std::endl;
        return;
    }
    TGraph *gr0 = new TGraph( tr_xx.size(), tr_xx.data(), tr_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("Corrected trace");
    gr0->GetXaxis()->SetTitle("Time [us]");
    gr0->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    gr0->SetMarkerColor(kBlue);
    std::cout << "lisa_vis::showSingleCorrectTrace() end" << std::endl;
}

void lisa_vis::showMWDTrace(lisa_febex *ffebex)
{
    std::cout << "lisa_vis::showMWDTrace()" << std::endl;

    ffebex->getMWDTrace();
    setVisJentry(ffebex->getJentry());
    int flen0 = ffebex->getMWDTraceLength();

    if(flen0==0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_005: empty graph; trace length = 0."<<std::endl;
        return;
    }

    std::vector<float> fMWD_xx = ffebex->getMWDTraceI();
    std::vector<float> fMWD_yy = ffebex->getMWDTraceV();
    if( fMWD_xx[0] < 0.5 ){//to check e-310
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_006: e-310 error. fMWD_xx[0] = "<<fMWD_xx[0]<<""<<std::endl;
    }

    if(getVisVerbose() == 1){
        //to check if we have e-310
        std::cout<<"flen0 = "<<flen0<<std::endl;
        for(int ii=0;ii<10;ii++){
            std::cout<<"fMWD_xx = "<<fMWD_xx[ii]<<"          fMWD_yy = "<<fMWD_yy[ii]<<std::endl;
        }
    }

    TGraph *gr0 = new TGraph( fMWD_xx.size(), fMWD_xx.data(), fMWD_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("MWD trace");
    gr0->GetXaxis()->SetTitle("Time [ns]");
    gr0->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    gr0->SetMarkerColor(kRed);
    //calculate energy//
    ffebex->calcEnergy();
    std::cout << "lisa_vis::showMWDTrace() end" << std::endl;
}

void lisa_vis::showMWDTrace(std::vector<Double_t> &tr_xx, std::vector<Double_t> &tr_yy){
    std::cout<<"lisa_vis::showMWDTrace()"<<std::endl;
    if(tr_xx.size() == 0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_005: empty graph; trace length = 0."<<std::endl;
        return;
    }
    TGraph *gr0 = new TGraph( tr_xx.size(), tr_xx.data(), tr_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("MWD trace");
    gr0->GetXaxis()->SetTitle("Time [ns]");
    gr0->GetYaxis()->SetTitle("Energy [mV]");
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    gr0->SetMarkerColor(kRed);

    std::cout << "lisa_vis::showMWDTrace() end" << std::endl;

}

void lisa_vis::showMWDTrace2(lisa_febex *ffebex){

    std::cout << "lisa_vis::showMWDTrace()" << std::endl;

    //***load MWD trace***//
    ffebex->getMWDTrace();
    setVisJentry(ffebex->getJentry());
    int flen0 = ffebex->getMWDTraceLength();

    if(flen0==0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_005: empty graph; trace length = 0."<<std::endl;
        return;
    }

    std::vector<float> fMWD_xx = ffebex->getMWDTraceI();
    std::vector<float> fMWD_yy = ffebex->getMWDTraceV();
    if( fMWD_xx[0] < 0.5 ){//to check e-310
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_006: e-310 error. fMWD_xx[0] = "<<fMWD_xx[0]<<""<<std::endl;
    }

    if(getVisVerbose() == 1){
        //to check if we have e-310
        std::cout<<"flen0 = "<<flen0<<std::endl;
        for(int ii=0;ii<10;ii++){
            std::cout<<"fMWD_xx = "<<fMWD_xx[ii]<<"          fMWD_yy = "<<fMWD_yy[ii]<<std::endl;
        }
    }

    TGraph *gr0 = new TGraph( fMWD_xx.size(), fMWD_xx.data(), fMWD_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("MWD trace");
    gr0->GetXaxis()->SetTitle("Time [ns]");
    gr0->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    gr0->SetMarkerColor(kRed);
    //...oooOO0OOooo......oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...//
    //load Corrected trace
    ffebex->getCorrectTrace();
    int flen1 = ffebex->getFebexTraceL();
    std::vector<float> fCorr_xx = ffebex->getCorrectTraceI();
    std::vector<float> fCorr_yy = ffebex->getCorrectTraceV();
    TGraph *gr1 = new TGraph( fCorr_xx.size(), fCorr_xx.data(), fCorr_yy.data() );
    gr1->Draw("AP*");
    gr1->SetTitle("Corrected trace");
    gr1->GetXaxis()->SetTitle("Time [ns]");
    gr1->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr1->GetXaxis()->SetTitleOffset(0.85);
    gr1->GetXaxis()->SetLabelOffset(0.001);

    gr1->GetYaxis()->SetTitleOffset(0.65);
    gr1->GetYaxis()->SetLabelOffset(0.001);
    gr1->SetMarkerColor(kBlue);
    //...oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo......//
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(gr0);
    mg->Add(gr1);
    mg->Draw("AP*");
    mg->SetTitle("MWD trace");
    mg->GetXaxis()->SetTitle("Time [ns]");
    mg->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    mg->GetXaxis()->SetTitleOffset(0.85);
    mg->GetXaxis()->SetLabelOffset(0.001);

    mg->GetYaxis()->SetTitleOffset(0.65);
    mg->GetYaxis()->SetLabelOffset(0.001);
    //...oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo......//
    //calculate energy//
    ffebex->calcEnergy();
    std::cout << "lisa_vis::showMWDTrace2() end" << std::endl;
}

void lisa_vis::showCFDTrace(lisa_febex *ffebex)
{
    std::cout << "lisa_vis::showCFDTrace()" << std::endl;
    ffebex->getCFDTrace();

    int flen0 = ffebex->getCFDTraceLength();
    if(flen0==0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_007: empty graph; trace length = 0."<<std::endl;
        return;
    }
    std::vector<float> fCFD_xx = ffebex->getCFDTraceI();
    std::vector<float> fCFD_yy = ffebex->getCFDTraceV();
    if( fCFD_xx[0] < 0.5 ){//to check e-310
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_008: e-310 error. fCFD_xx[0] = "<<fCFD_xx[0]<<""<<std::endl;
    }

    if(getVisVerbose() == 1){
        //to check if we have e-310
        std::cout<<"flen0 = "<<flen0<<std::endl;
        for(int ii=0;ii<10;ii++){
            std::cout<<"fCFD_xx = "<<fCFD_xx[ii]<<"          fCFD_yy = "<<fCFD_yy[ii]<<std::endl;
        }
    }

    TGraph *gr0 = new TGraph( fCFD_xx.size(), fCFD_xx.data(), fCFD_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("CFD trace");
    gr0->GetXaxis()->SetTitle("Time [ns]");
    gr0->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    gr0->SetMarkerColor(kRed);
    //std::cout<<"***CFD time = "<<ffebex->getCFDtime()<<" [ns] ***"<<std::endl;
    std::cout << "lisa_vis::showCFDTrace() end" << std::endl;
}

void lisa_vis::showCFDTrace(std::vector<Double_t> &fCFD_xx, std::vector<Double_t> &fCFD_yy)
{

    std::cout<<"lisa_vis::showCFDTrace()"<<std::endl;
    if(fCFD_xx.size() == 0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_013: empty graph; trace length = 0."<<std::endl;
        return;
    }
    TGraph *gr0 = new TGraph( fCFD_xx.size(), fCFD_xx.data(), fCFD_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("CFD trace");
    gr0->GetXaxis()->SetTitle("Time [ns]");
    gr0->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    gr0->SetMarkerColor(kRed);
    std::cout << "lisa_vis::showCFDTrace() end" << std::endl;

}




//***show CFD trace overlaped with corrected trace***//
void lisa_vis::showCFDTrace2(lisa_febex *ffebex)
{
    std::cout << "lisa_vis::showCFDTrace2()" << std::endl;
    //load CFD trace
    ffebex->getCFDTrace();
    int flen0 = ffebex->getCFDTraceLength();
    if(flen0==0) {
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_007: empty graph; trace length = 0."<<std::endl;
        return;
    }
    std::vector<float> fCFD_xx = ffebex->getCFDTraceI();
    std::vector<float> fCFD_yy = ffebex->getCFDTraceV();
    if( fCFD_xx[0] < 0.5 ){//to check e-310
        if(getVisVerbose() == 3)std::cout<<"Error_lisa_vis_cc_008: e-310 error. fCFD_xx[0] = "<<fCFD_xx[0]<<""<<std::endl;
    }

    if(getVisVerbose() == 1){
        //to check if we have e-310
        std::cout<<"flen0 = "<<flen0<<std::endl;
		std::cout<<" fCFD_xx.size() "<<fCFD_xx.size()<<std::endl;
        for(int ii=0;ii<flen0;ii++){
            std::cout<<"fCFD_xx = "<<fCFD_xx[ii]<<"          fCFD_yy = "<<fCFD_yy[ii]<<std::endl;
        }
    }
    TGraph *gr0 = new TGraph( fCFD_xx.size(), fCFD_xx.data(), fCFD_yy.data() );
    gr0->Draw("AP*");
    gr0->SetTitle("CFD trace");
    gr0->GetXaxis()->SetTitle("Time [ns]");
    gr0->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr0->GetXaxis()->SetTitleOffset(0.85);
    gr0->GetXaxis()->SetLabelOffset(0.001);

    gr0->GetYaxis()->SetTitleOffset(0.65);
    gr0->GetYaxis()->SetLabelOffset(0.001);
    gr0->SetMarkerColor(kRed);
    //...oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo......//
    //load Corrected trace
    ffebex->getCorrectTrace();
    int flen1 = ffebex->getFebexTraceL();
    std::vector <float> fCorr_xx = ffebex->getCorrectTraceI();
    std::vector <float> fCorr_yy = ffebex->getCorrectTraceV();
    TGraph *gr1 = new TGraph( fCorr_xx.size(), fCorr_xx.data(), fCorr_yy.data() );
    gr1->Draw("AP*");
    gr1->SetTitle("Corrected trace");
    gr1->GetXaxis()->SetTitle("Time [ns]");
    gr1->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    gr1->GetXaxis()->SetTitleOffset(0.85);
    gr1->GetXaxis()->SetLabelOffset(0.001);

    gr1->GetYaxis()->SetTitleOffset(0.65);
    gr1->GetYaxis()->SetLabelOffset(0.001);
    gr1->SetMarkerColor(kBlue);
    //...oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo......//
    TMultiGraph *mg = new TMultiGraph();
    mg->Add(gr0);
    mg->Add(gr1);
    mg->Draw("AP*");
    mg->SetTitle("CFD trace");
    mg->GetXaxis()->SetTitle("Time [ns]");
    mg->GetYaxis()->SetTitle("Energy [mV]");
    //set format//
    mg->GetXaxis()->SetTitleOffset(0.85);
    mg->GetXaxis()->SetLabelOffset(0.001);

    mg->GetYaxis()->SetTitleOffset(0.65);
    mg->GetYaxis()->SetLabelOffset(0.001);
    //...oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo......//
    std::cout<<"***CFD time = "<<ffebex->getCFDtime()<<" [ns] ***"<<std::endl;

    std::cout << "lisa_vis::showCFDTrace2() end" << std::endl;
}

void lisa_vis::anaFebex4_checkSingleTrace(lisa_febex *ffebex)
{
    std::cout << "lisa_vis::anaFebex4_checkSingleTrace()" << std::endl;
    std::cout<<"verbose = "<<getVisVerbose()<<std::endl;
    TCanvas *cSingle = (TCanvas*)createCanvas(2,2);//this is a 2x2 canvas
    cSingle->cd(1);
    showSingleRawTrace(ffebex);
    cSingle->cd(2);
    showSingleCorrectTrace(ffebex);
    cSingle->cd(3);
    showCFDTrace2(ffebex);
    cSingle->cd(4);
    showMWDTrace(ffebex);
    std::cout << "Current entry = " << getVisJentry() << std::endl;
}

void lisa_vis::anaScope_checkSingleTrace(lisa_scope *ipt){
    std::cout<<"lisa_vis::anaScope_checkSingleTrace()"<<std::endl;
    setVisJentry( ipt->getJentryScope() );
    setVisVerbose( ipt->getVerbose() );
    std::cout<<"verbose = "<<getVisVerbose()<<std::endl;
    TCanvas *cSingle = (TCanvas*)createCanvas(2,2);//this is a 2x1 canvas
                                                   
    cSingle->cd(1);
    ipt->getSingleScopeTrace();
    std::vector<Double_t> scopeTrace_xx = ipt->getScopeTraceI();
    std::vector<Double_t> scopeTrace_yy = ipt->getScopeTraceV();
    showSingleRawTrace(scopeTrace_xx, scopeTrace_yy);

    cSingle->cd(2);
    ipt->getCorrectScopeTrace();
    std::vector<Double_t> scopeCorrTrace_xx = ipt->getScopeTraceI_corr();
    std::vector<Double_t> scopeCorrTrace_yy = ipt->getScopeTraceV_corr();
    showSingleCorrectTrace(scopeCorrTrace_xx, scopeCorrTrace_yy);

    cSingle->cd(3);
    ipt->getCFDScopeTrace();
    std::vector<Double_t> scopeCFDTrace_xx = ipt->getScopeTraceI_cfd();
    std::vector<Double_t> scopeCFDTrace_yy = ipt->getScopeTraceV_cfd();
    showCFDTrace(scopeCFDTrace_xx, scopeCFDTrace_yy);
    std::cout<<"***CFD time = "<<ipt->getScopeTime_cfd()<<" [ns] ***"<<std::endl;
    std::cout << "Current entry = " << getVisJentry() << std::endl;
}

void lisa_vis::anaFebex4_checkTraces(lisa_febex *ffebex)
{
    std::cout << "lisa_vis::anaFebex4_checkTraces()" << std::endl;
    std::cout<<"verbose = "<<getVisVerbose()<<std::endl;

    //***load data***//
    auto febex_data_tem = ffebex->getFebexDataV();
    UInt_t nentries = febex_data_tem.size();
    if(nentries==0){
        if(getVisVerbose() == 3)std::cout<<"***Error_lisa_vis_cc_009: febex_data is empty."<<std::endl;
        return;
    }
    std::cout<<"***nentries = "<<nentries<<std::endl;

    //***debug***//
    /*
       for(int ii=0;ii<nentries;ii++){
       std::cout<<"***Debug9:  ii = "<<ii<<std::endl;
       if(febex_data_tem[ii].flength!=0){
       for(int jj=0;jj<10;jj++){
    //std::cout<<"***Debug10: febex_data_tem[ii].fCorrTrace_x = "<<febex_data_tem[ii].fCorrTrace_x[jj]<<std::endl;
    std::cout<<"***Debug10: febex_data_tem[ii].fCorrTrace_y = "<<febex_data_tem[ii].fCorrTrace_y[jj]<<std::endl;
    }
    }
    }
    */
    //...oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo......//
    std::vector<TGraph*>v_graphs_corr;//graphs of corrected traces, temporary container; used for display
    v_graphs_corr.clear();
    std::vector<TGraph*>v_graphs_MWD;//graphs of MWD traces, temporary container; used for display
    v_graphs_MWD.clear();
    TGraph *corr_graph = NULL;
    TGraph *MWD_graph = NULL;

    auto *fhist_time = new TH1F("fhist_time","fhist_time",ffebex->getHistoNBins(),ffebex->getTimeHistRange()[0],ffebex->getTimeHistRange()[1]);//0,5000
    auto *fhist_energy = new TH1F("fhist_energy","fhist_energy",ffebex->getHistoNBins(),ffebex->getEnergyHistRange()[0],ffebex->getEnergyHistRange()[1]);//10,1010
    //auto *fhist_time = new TH1F("fhist_time","fhist_time",fscope->getHistoNBins(),fscope->getTimeHistRange()[0],fscope->getTimeHistRange()[1]);
    //auto *fhist_energy = new TH1F("fhist_energy","fhist_energy",fscope->getHistoNBins(),fscope->getEnergyHistRange()[0],fscope->getEnergyHistRange()[1]);

    TCanvas *cTraces = (TCanvas*)createCanvas(2,2);//this is a 2x2 canvas
    std::cout<<"*** start to loop ***"<<std::endl;
    for(int ii=0;ii<nentries;ii++){

        //TGraph *corr_graph(febex_data_tem[ii].flength,febex_data_tem[ii].fCorrTrace_x,febex_data_tem[ii].fCorrTrace_y);
        //if(corr_graph != NULL) {delete corr_graph; corr_graph = NULL;}
        //corr_graph = new TGraph(febex_data_tem[ii].flength,febex_data_tem[ii].fCorrTrace_x.data(),febex_data_tem[ii].fCorrTrace_y.data());
        //***debug***//
        /*
           std::cout<<"***Debug9:  ii = "<<ii<<std::endl;
           std::cout<<"***Debug10: febex_data_tem[ii].flength = "<<febex_data_tem[ii].flength<<std::endl;
           if(febex_data_tem[ii].flength!=0){
           for(int jj=0;jj<10;jj++){
           std::cout<<"***Debug10: febex_data_tem[ii].fMWDTrace_y = "<<febex_data_tem[ii].fMWDTrace_y[jj]<<std::endl;
           }
           }
           */
        //std::cout<<"***febex_data_tem[ii].fCorrTrace_x.size() = "<<febex_data_tem[ii].fCorrTrace_x.size()<<std::endl;
        if(febex_data_tem[ii].fCorrTrace_x.size()==0){
            if(getVisVerbose() == 3)std::cout<<"***Error_lisa_vis_cc_010: febex_data_tem[ii].fCorrTrace_x.size() = "<<febex_data_tem[ii].fCorrTrace_x.size()<<std::endl;
            continue;
        }
        corr_graph = getGraph(febex_data_tem[ii].fCorrTrace_x,febex_data_tem[ii].fCorrTrace_y);
        v_graphs_corr.push_back(corr_graph);//corrected traces
        fhist_time->Fill(febex_data_tem[ii].ftime_cfd);//time histogram
                                                       //if(MWD_graph != NULL) {delete MWD_graph; MWD_graph = NULL;}
                                                       //MWD_graph = new TGraph(febex_data_tem[ii].fMWDTrace_x.size(),febex_data_tem[ii].fMWDTrace_x.data(),febex_data_tem[ii].fMWDTrace_y.data());

        MWD_graph = getGraph(febex_data_tem[ii].fMWDTrace_x,febex_data_tem[ii].fMWDTrace_y);
        //std::cout<<"***Debug11: febex_data_tem[ii].fMWDTrace_x.size() = "<<febex_data_tem[ii].fMWDTrace_x.size()<<std::endl;
        v_graphs_MWD.push_back(MWD_graph);//MWD tracesd
        fhist_energy->Fill(febex_data_tem[ii].fenergy_raw);//energy histogram

    }
    std::cout<<"*** end of loop ***"<<std::endl;
    //std::cout<<"debug11: v_graphs_corr.size() = "<<v_graphs_corr.size()<<std::endl;
    cTraces->cd(1);
    //***display***//
    if(v_graphs_corr.size()>0){
        v_graphs_corr.at(0)->Draw("APL");
        v_graphs_corr.at(0)->SetTitle("Febex Traces: 10ns/Sample");
        v_graphs_corr.at(0)->GetXaxis()->SetTitle("Time[ns]");
        v_graphs_corr.at(0)->GetYaxis()->SetTitle("Amplitude[mV]");
        v_graphs_corr.at(0)->SetMaximum(ffebex->getTraceAmpRange()[1]);
        v_graphs_corr.at(0)->SetMinimum(ffebex->getTraceAmpRange()[0]);
        //v_graphs_corr.at(0)->SetMaximum(1000);
        //v_graphs_corr.at(0)->SetMinimum(-1000);
        for(int i=0;i<v_graphs_corr.size();i++){
            v_graphs_corr.at(i)->SetLineColor(1+i%40);
            v_graphs_corr.at(i)->Draw("PL");
        }
    }
    cTraces->cd(2);
    fhist_time->Draw();
	fhist_time->GetXaxis()->SetRangeUser(ffebex->getTimeSpecRange()[0],ffebex->getTimeSpecRange()[1]);
	//fhist_time->GetXaxis()->SetRangeUser(fscope->getTimeSpecRange()[0],fscope->getTimeSpecRange()[1]);
    cTraces->cd(3);
    fhist_energy->Draw();
	fhist_energy->GetXaxis()->SetRangeUser(ffebex->getEnergySpecRange()[0],ffebex->getEnergySpecRange()[1]);
    cTraces->cd(4);
    //std::cout<<"debug12: v_graphs_MWD.size() = "<<v_graphs_MWD.size()<<std::endl;
    if(v_graphs_MWD.size()>0){
        v_graphs_MWD.at(0)->Draw("APL");
        v_graphs_MWD.at(0)->SetTitle("MWD Traces: 10ns/Sample");
        v_graphs_MWD.at(0)->GetXaxis()->SetTitle("Time[ns]");
        v_graphs_MWD.at(0)->GetYaxis()->SetTitle("Amplitude[mV]");
        v_graphs_MWD.at(0)->SetMaximum(ffebex->getTraceAmpRange()[1]);
        v_graphs_MWD.at(0)->SetMinimum(ffebex->getTraceAmpRange()[0]);
        //v_graphs_MWD.at(0)->SetMaximum(1000);
        //v_graphs_MWD.at(0)->SetMinimum(-1000);
        for(int i=0;i<v_graphs_MWD.size();i++){
            v_graphs_MWD.at(i)->SetLineColor(1+i%40);
            v_graphs_MWD.at(i)->Draw("PL");
        }
    }
}

void lisa_vis::anaScope_checkTraces(lisa_scope *fscope){

    std::cout << "lisa_vis::anaScope_checkTraces()" << std::endl;
    setVisJentry( fscope->getJentryScope() );
    setVisVerbose( fscope->getVerbose() );
    std::cout<<"verbose = "<<getVisVerbose()<<std::endl;
    //***load data***//
    auto scope_data_tem = fscope->getScopeDataV();
    UInt_t nentries = scope_data_tem.size();
    if(nentries==0){
        if(getVisVerbose() == 3)std::cout<<"***Error_lisa_vis_cc_014: scope_data is empty."<<std::endl;
        return;
    }
    std::cout<<"***nentries = "<<nentries<<std::endl;

    //***debug***//
    /*
       for(int ii=0;ii<nentries;ii++){
       std::cout<<"***Debug9:  ii = "<<ii<<std::endl;
       if(febex_data_tem[ii].flength!=0){
       for(int jj=0;jj<10;jj++){
    //std::cout<<"***Debug10: febex_data_tem[ii].fCorrTrace_x = "<<febex_data_tem[ii].fCorrTrace_x[jj]<<std::endl;
    std::cout<<"***Debug10: febex_data_tem[ii].fCorrTrace_y = "<<febex_data_tem[ii].fCorrTrace_y[jj]<<std::endl;
    }
    }
    }
    */
    //...oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo........oooOOO0OOOooo......//
    std::vector<TGraph*>v_graphs_corr;//graphs of corrected traces, temporary container; used for display
    v_graphs_corr.clear();
    std::vector<TGraph*>v_graphs_MWD;//graphs of MWD traces, temporary container; used for display
    v_graphs_MWD.clear();
    TGraph *corr_graph = NULL;
    TGraph *MWD_graph = NULL;

    auto *fhist_time = new TH1F("fhist_time","fhist_time",fscope->getHistoNBins(),fscope->getTimeHistRange()[0],fscope->getTimeHistRange()[1]);
    auto *fhist_energy = new TH1F("fhist_energy","fhist_energy",fscope->getHistoNBins(),fscope->getEnergyHistRange()[0],fscope->getEnergyHistRange()[1]);

    TCanvas *cTraces = (TCanvas*)createCanvas(2,2);//this is a 2x2 canvas
    std::cout<<"*** start to loop ***"<<std::endl;
    for(int ii=0;ii<nentries;ii++){

        //TGraph *corr_graph(febex_data_tem[ii].flength,febex_data_tem[ii].fCorrTrace_x,febex_data_tem[ii].fCorrTrace_y);
        //if(corr_graph != NULL) {delete corr_graph; corr_graph = NULL;}
        //corr_graph = new TGraph(febex_data_tem[ii].flength,febex_data_tem[ii].fCorrTrace_x.data(),febex_data_tem[ii].fCorrTrace_y.data());
        //***debug***//
        /*
           std::cout<<"***Debug9:  ii = "<<ii<<std::endl;
           std::cout<<"***Debug10: febex_data_tem[ii].flength = "<<febex_data_tem[ii].flength<<std::endl;
           if(febex_data_tem[ii].flength!=0){
           for(int jj=0;jj<10;jj++){
           std::cout<<"***Debug10: febex_data_tem[ii].fMWDTrace_y = "<<febex_data_tem[ii].fMWDTrace_y[jj]<<std::endl;
           }
           }
           */
        //std::cout<<"***febex_data_tem[ii].fCorrTrace_x.size() = "<<febex_data_tem[ii].fCorrTrace_x.size()<<std::endl;
        if(scope_data_tem[ii].fCorrTrace_x.size()==0){
            if(getVisVerbose() == 3)std::cout<<"***Error_lisa_vis_cc_015: scope_data_tem[ii].fCorrTrace_x.size() = "<<scope_data_tem[ii].fCorrTrace_x.size()<<std::endl;
            continue;
        }
        corr_graph = getGraph(scope_data_tem[ii].fCorrTrace_x,scope_data_tem[ii].fCorrTrace_y);
        v_graphs_corr.push_back(corr_graph);//corrected traces
        fhist_time->Fill(scope_data_tem[ii].ftime_cfd);//time histogram
                                                       //if(MWD_graph != NULL) {delete MWD_graph; MWD_graph = NULL;}
                                                       //MWD_graph = new TGraph(febex_data_tem[ii].fMWDTrace_x.size(),febex_data_tem[ii].fMWDTrace_x.data(),febex_data_tem[ii].fMWDTrace_y.data());

        MWD_graph = getGraph(scope_data_tem[ii].fMWDTrace_x,scope_data_tem[ii].fMWDTrace_y);
        //std::cout<<"***Debug11: febex_data_tem[ii].fMWDTrace_x.size() = "<<febex_data_tem[ii].fMWDTrace_x.size()<<std::endl;
        v_graphs_MWD.push_back(MWD_graph);//MWD tracesd
        fhist_energy->Fill(scope_data_tem[ii].fenergy_raw);//energy histogram

    }
    std::cout<<"*** end of loop ***"<<std::endl;
    //std::cout<<"debug11: v_graphs_corr.size() = "<<v_graphs_corr.size()<<std::endl;
    cTraces->cd(1);
    //***display***//
    if(v_graphs_corr.size()>0){
        v_graphs_corr.at(0)->Draw("APL");
        v_graphs_corr.at(0)->SetTitle("Scope Traces:");
        v_graphs_corr.at(0)->GetXaxis()->SetTitle("Time[ns]");
        v_graphs_corr.at(0)->GetYaxis()->SetTitle("Amplitude[mV]");
        v_graphs_corr.at(0)->SetMaximum(fscope->getTraceAmpRange()[1]);
        v_graphs_corr.at(0)->SetMinimum(fscope->getTraceAmpRange()[0]);
        //v_graphs_corr.at(0)->SetMaximum(30);
        //v_graphs_corr.at(0)->SetMinimum(-30);
        for(int i=0;i<v_graphs_corr.size();i++){
            v_graphs_corr.at(i)->SetLineColor(1+i%40);
            v_graphs_corr.at(i)->Draw("PL");
        }
    }
    cTraces->cd(2);
    fhist_time->Draw();
	fhist_time->GetXaxis()->SetRangeUser(fscope->getTimeSpecRange()[0],fscope->getTimeSpecRange()[1]);
    cTraces->cd(3);
    fhist_energy->Draw();
	fhist_energy->GetXaxis()->SetRangeUser(fscope->getEnergySpecRange()[0],fscope->getEnergySpecRange()[1]);
    cTraces->cd(4);
    //std::cout<<"debug12: v_graphs_MWD.size() = "<<v_graphs_MWD.size()<<std::endl;
    if(v_graphs_MWD.size()>0){
        v_graphs_MWD.at(0)->Draw("APL");
        v_graphs_MWD.at(0)->SetTitle("MWD Traces: 10ns/Sample");
        v_graphs_MWD.at(0)->GetXaxis()->SetTitle("Time[ns]");
        v_graphs_MWD.at(0)->GetYaxis()->SetTitle("Amplitude[arb.]");
        v_graphs_MWD.at(0)->SetMaximum(fscope->getTraceAmpRange()[1]);
        v_graphs_MWD.at(0)->SetMinimum(fscope->getTraceAmpRange()[0]);
        //v_graphs_MWD.at(0)->SetMaximum(30);
        //v_graphs_MWD.at(0)->SetMinimum(-30);
        for(int i=0;i<v_graphs_MWD.size();i++){
            v_graphs_MWD.at(i)->SetLineColor(1+i%40);
            v_graphs_MWD.at(i)->Draw("PL");
        }
    }

}

void lisa_vis::checkMWD(lisa_febex *ffebex)
{
    std::cout << "lisa_vis::checkMWD()" << std::endl;
    std::cout<<"verbose = "<<getVisVerbose()<<std::endl;
    TCanvas *cMWD = (TCanvas*)createCanvas(2,2);//this is a 2x2 canvas
    cMWD->cd(1);
    showSingleRawTrace(ffebex);
    showSingleCorrectTrace(ffebex);
    cMWD->cd(2);
    showMWDTrace(ffebex);
    cMWD->cd(3);
    showMWDTrace2(ffebex);
    std::cout << "Current entry = " << getVisJentry() << std::endl;
    std::cout<<"***Amplitude = "<<ffebex->getMWDenergy()<<"***"<<std::endl;
}

void lisa_vis::checkMWD_Scope(lisa_scope *ipt)
{
    std::cout << "lisa_vis::checkMWD()" << std::endl;
    setVisJentry( ipt->getJentryScope() );
    setVisVerbose( ipt->getVerbose() );
    std::cout<<"--->verbose = "<<getVisVerbose()<<std::endl;
    std::cout<<"--->entry = "<<ipt->getJentryScope()<<std::endl;
    TCanvas *cMWD = (TCanvas*)createCanvas(2,2);//this is a 2x2 canvas
                                                
    cMWD->cd(1);
    ipt->getSingleScopeTrace();
    std::vector<Double_t> scopeTrace_xx = ipt->getScopeTraceI();
    std::vector<Double_t> scopeTrace_yy = ipt->getScopeTraceV();
    showSingleRawTrace(scopeTrace_xx, scopeTrace_yy);

    cMWD->cd(2);
    ipt->getCorrectScopeTrace();
    std::vector<Double_t> scopeCorrTrace_xx = ipt->getScopeTraceI_corr();
    std::vector<Double_t> scopeCorrTrace_yy = ipt->getScopeTraceV_corr();
    showSingleCorrectTrace(scopeCorrTrace_xx, scopeCorrTrace_yy);

    cMWD->cd(3);
    ipt->getMWDScopeTrace();
    std::vector<Double_t> scopeMWDTrace_xx = ipt->getScopeTraceI_mwd();
    std::vector<Double_t> scopeMWDTrace_yy = ipt->getScopeTraceV_mwd();
    showMWDTrace(scopeMWDTrace_xx, scopeMWDTrace_yy);

    std::cout << "Current entry = " << getVisJentry() << std::endl;
    ipt->calcEnergy();
    std::cout<<"*** Amplitude = "<<ipt->getScopeEnergy_mwd()<<" ***"<<std::endl;
}

void lisa_vis::setEnv()
{
    std::cout << "lisa_vis::setEnv()" << std::endl;
    gROOT->SetStyle("Modern");
    //gStyle->SetHistFillColor(7);
    //gStyle->SetHistFillStyle(3002);
    //gStyle->SetHistLineColor(kBlue);
    //*** FAIR style ***//
    gStyle->SetHistFillColor(796);
    gStyle->SetHistFillStyle(1001);
    gStyle->SetHistLineColor(kBlack);
    gStyle->SetFuncColor(kRed);
    gStyle->SetFrameLineWidth(2);
    gStyle->SetCanvasColor(0);
    gStyle->SetTitleFillColor(0);
    gStyle->SetTitleStyle(0);
    gStyle->SetStatColor(0);
    gStyle->SetStatStyle(0);
    gStyle->SetStatX(0.9);  
    gStyle->SetStatY(0.9);  
    gStyle->SetPalette(1);
    //gStyle->SetOptLogz(1);
    //  gStyle->SetOptTitle(0);
    //gStyle->SetOptFit(1);
    gStyle->SetOptStat(1111111);
    //gStyle->SetOptStat(0);
    //gStyle->SetPadBorderMode(1);
    //  gStyle->SetOptDate(1);
    gStyle->SetLabelFont(132,"XYZ");
    gStyle->SetLabelSize(0.06,"X");
    gStyle->SetLabelSize(0.06,"Y");
    gStyle->SetLabelOffset(0.004);
    gStyle->SetTitleOffset(1.05);
    gStyle->SetTitleFont(132,"XYZ");
    gStyle->SetTitleSize(0.06,"X");
    gStyle->SetTitleSize(0.06,"Y");
    //gStyle->SetTitleFont(132,"");
    gStyle->SetTextFont(132);
    gStyle->SetStatFont(132);
}

TGraph* lisa_vis::getGraph(std::vector<float> &fgr_x, std::vector<float> &fgr_y)
{
    TGraph *fgraph = new TGraph(fgr_x.size(),fgr_x.data(),fgr_y.data());
    return fgraph;
}

TGraph* lisa_vis::getGraph(std::vector<Int_t> &fgr_x, std::vector<Int_t> &fgr_y)
{
    TGraph *fgraph = new TGraph(fgr_x.size(),fgr_x.data(),fgr_y.data());
    return fgraph;
}

TGraph* lisa_vis::getGraph(std::vector<Double_t> &fgr_x, std::vector<Double_t> &fgr_y)
{
    TGraph *fgraph = new TGraph(fgr_x.size(),fgr_x.data(),fgr_y.data());
    return fgraph;
}

