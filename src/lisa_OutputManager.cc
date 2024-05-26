//
//last updated@26 May,2024
//Z.Chen
//


#include <iostream>
#include <TTree.h>
#include <TFile.h>
#include <vector>
#include "../inc/lisa_OutputManager.hh"
#include "../inc/lisa_scope.hh"
#include "../inc/lisa_vis.hh"

//#include "lisa_febex.cc"
//#include "lisa_scope.cc"
//#include "lisa_settings.cc"

lisa_optManager::lisa_optManager(TTree *tree)
{
    if (tree == NULL) {
        std::cout << "***Error_zchen_cc_000:lisa_optManager::lisa_optManager(tree==0)" << std::endl;
        return;
    }
    Init(tree);//from lisa_ucesb
    setTree(tree);//deliver tree to ftree;from lisa_febex
                  //loadSettings(settings);//from lisa_febex
}

lisa_optManager::lisa_optManager(){}

lisa_optManager::~lisa_optManager()
{
    std::cout << "lisa_optManager::~lisa_optManager()" << std::endl;
}

void lisa_optManager::Show(lisa_febex *ipt)
{
    if (ipt == 0) {
        std::cout << "***Error_zchen_cc_001:lisa_optManager::Show(tree==0)" << std::endl;
        return;
    }
    //tree->Draw("lisa_data1traces1v:lisa_data1traces1I");

    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis(ipt);
    std::cout<<"vis done"<<std::endl;
    TCanvas *cc = (TCanvas*)vis1->createCanvas(2,2);//this is a 2x2 canvas
    cc->cd(1);

    std::cout<<"length = "<<ipt->getFebexTraceL()<<std::endl;
    std::cout<<"Jentry = "<<ipt->getJentry()<<std::endl;
    vis1->showSingleRawTrace(ipt);
    cc->cd(2);
    vis1->showSingleCorrectTrace(ipt);
    std::cout<<"length = "<<ipt->getFebexTraceL()<<std::endl;
    cc->cd(3);
    vis1->showMWDTrace(ipt);
    ipt->calcEnergy();
    cc->cd(4);
    vis1->showCFDTrace(ipt);
}

void lisa_optManager::Test(TTree *tree)
{
    std::cout << "***lisa_optManager::Test()" << std::endl;
    //setJentry(22);
    //setCh(0);
    TCanvas *c = new TCanvas();
    c->Divide(2, 2);
    //raw trace
    c->cd(1);
    getSingleTrace(tree);
    int flen0 = getFebexTraceL();
    std::vector<Int_t> fxx0 = getRawTraceI();
    std::vector<Int_t> fyy0 = getRawTraceV();
    TGraph *gr0 = new TGraph( fxx0.size(), fxx0.data(), fyy0.data() );
    gr0->Draw("AP*");

    //correct trace
    c->cd(2);
    getCorrectTrace();
    std::vector<float> fxx = getCorrectTraceI();
    std::vector<float> fyy = getCorrectTraceV();
    TGraph *gr1 = new TGraph( fxx.size(), fxx.data(), fyy.data() );
    gr1->Draw("AP*");

    c->cd(3);
    getMWDTrace();
    TGraph *gr2 = new TGraph(getMWDTraceLength(), getMWDTraceI().data(), getMWDTraceV().data() );//Length:size of array
    gr2->Draw("AP*");

    c->cd(4);
    getCFDTrace();
    TGraph *gr3 = new TGraph(getCFDTraceLength(), getCFDTraceI().data(), getCFDTraceV().data() );//Length:size of array
    gr3->Draw("AP*");
    std::cout<<"CFDtime = "<<getCFDtime()<<std::endl;
}

void lisa_optManager::anaFebex4_checkSingleTrace(lisa_febex *ffebex)
{
    std::cout << "***lisa_optManager::anaFebex4_checkSingleTrace()"<<std::endl;
    std::cout << "Verbose = " << lisa_settings::getVerbose() << std::endl;
    if (ffebex == 0) {
        std::cout << "***Error_zchen_cc_002:lisa_optManager::anaFebex4_checkSingleTrace(ffebex==0)" << std::endl;
        return;
    }
    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis(ffebex);
    vis1->setVisVerbose(lisa_settings::getVerbose());
    std::cout<<"vis done"<<std::endl;
    vis1->anaFebex4_checkSingleTrace(ffebex);
}

//...oooOO0OOooo......oooOO0OOooo.....oooOO0OOooo......oooOO0OOooo......//
void lisa_optManager::anaScope_checkSingleTrace(TString iptFileName, TString fsett, TString optfile)
{
    std::cout << "***lisa_optManager::anaScope_checkSingleTrace()"<<std::endl;
    lisa_scope *fscope = new lisa_scope();
    fscope->loadSettings(fsett);//from class lisa_settings
    fscope->setInputFilePathScope(iptFileName);
	fscope->setOptRootFileName(optfile);
    std::cout<<"input file path = "<<fscope->getInputFilePathScope()<<std::endl;
    std::cout<<"load settings done"<<std::endl;
    std::cout << "Verbose = " << fscope->getVerbose() << std::endl;
    if (fscope == 0) {
        std::cout << "***Error_lisa_optManager_002:lisa_optManager::anaFebex4_checkSingleTrace(fscope==0)" << std::endl;
        return;
    }
    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis();
    vis1->setVisVerbose(lisa_settings::getVerbose());
    std::cout<<"vis done"<<std::endl;
    std::cout<<"---> test input path "<<fscope->getInputFilePathScope()<<std::endl;
    vis1->anaScope_checkSingleTrace(fscope);
}

//...oooOO0OOooo......oooOO0OOooo.....oooOO0OOooo......oooOO0OOooo......//
void lisa_optManager::anaFebex4_checkMWD(lisa_febex *ffebex)
{
    std::cout << "***lisa_optManager::anaFebex4_checkMWD()"<<std::endl;
    std::cout << "Verbose = " << lisa_settings::getVerbose() << std::endl;
    if (ffebex == 0) {
        std::cout << "***Error_zchen_cc_003:lisa_optManager::anaFebex4_checkMWD(ffebex==0)" << std::endl;
        return;
    }
    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis(ffebex);
    vis1->setVisVerbose(lisa_settings::getVerbose());
    std::cout<<"vis done"<<std::endl;
    vis1->checkMWD(ffebex);
}
//...oooOO0OOooo......oooOO0OOooo.....oooOO0OOooo......oooOO0OOooo......//
void lisa_optManager::anaScope_checkMWD(TString iptFileName, TString fsett, TString optfile)
{
    std::cout << "***lisa_optManager::anaScope_checkMWD()"<<std::endl;
    lisa_scope *fscope = new lisa_scope();
    fscope->loadSettings(fsett);//from class lisa_settings
    fscope->setInputFilePathScope(iptFileName);
	fscope->setOptRootFileName(optfile);
    std::cout << "Verbose = " << fscope->getVerbose() << std::endl;
    if (fscope == 0) {
        std::cout << "***Error_lisa_optManager_005:lisa_optManager::anaFebex4_checkMWD(fscope==0)" << std::endl;
        return;
    }
    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis();
    vis1->setVisVerbose(lisa_settings::getVerbose());
    std::cout<<"vis done"<<std::endl;
    vis1->checkMWD_Scope(fscope);
}

//...oooOO0OOooo......oooOO0OOooo.....oooOO0OOooo......oooOO0OOooo......//
//no display
void lisa_optManager::anaFebex4_traces(lisa_febex *ffebex)
{
    std::cout << "***lisa_optManager::anaFebex4_traces()" << std::endl;
    if (ffebex == 0) {
        std::cout << "***Error_zchen_cc_004:lisa_optManager::anaFebex4_traces(ffebex==0)" << std::endl;
        return;
    }

    ffebex->getTraces(ffebex->getTree());
}

//...oooOO0OOooo......oooOO0OOooo.....oooOO0OOooo......oooOO0OOooo......//
void lisa_optManager::anaScope_traces(TString iptFileName, TString fsett, TString optfile)
{
    std::cout<<"***lisa_optManager::anaScope_traces()"<<std::endl;
    lisa_scope *fscope = new lisa_scope();
    fscope->loadSettings(fsett);//from class lisa_settings
    fscope->setInputFilePathScope(iptFileName);
	fscope->setOptRootFileName(optfile);
    std::cout << "Verbose = " << fscope->getVerbose() << std::endl;
    if (fscope == 0) {
        std::cout << "***Error_lisa_optManager_007:lisa_optManager::anaScope_traces(fscope==0)" << std::endl;
        return;
    }
    fscope->getScopeTraces();
}

//...oooOO0OOooo......oooOO0OOooo.....oooOO0OOooo......oooOO0OOooo......//
//with display
void lisa_optManager::anaFebex4_checkTraces(lisa_febex *ffebex)
{
    std::cout<<"***lisa_optManager::anaFebex4_checkTraces()"<<std::endl;
    std::cout << "Verbose = " << lisa_settings::getVerbose() << std::endl;
    if (ffebex == 0) {
        std::cout << "***Error_zchen_cc_005:lisa_optManager::anaFebex4_checkTraces(ffebex==0)" << std::endl;
        return;
    }
    ffebex->getTraces(ffebex->getTree());
    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis(ffebex);
    vis1->setVisVerbose(lisa_settings::getVerbose());
    std::cout<<"vis done"<<std::endl;
    vis1->anaFebex4_checkTraces(ffebex);
}

//...oooOO0OOooo......oooOO0OOooo.....oooOO0OOooo......oooOO0OOooo......//
//with display
void lisa_optManager::anaScope_checkTraces(TString iptFileName, TString fsett, TString optfile)
{
    std::cout<<"***lisa_optManager::anaScope_checkTraces()"<<std::endl;
    lisa_scope *fscope = new lisa_scope();
    fscope->loadSettings(fsett);//from class lisa_settings
    fscope->setInputFilePathScope(iptFileName);
	fscope->setOptRootFileName(optfile);
    std::cout << "Verbose = " << fscope->getVerbose() << std::endl;
    if (fscope == 0) {
        std::cout << "***Error_lisa_optManager_006:lisa_optManager::anaScope_checkTraces(fscope==0)" << std::endl;
        return;
    }
    fscope->getScopeTraces();
    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis();
    vis1->setVisVerbose(fscope->getVerbose());
    std::cout<<"vis done"<<std::endl;
    vis1->anaScope_checkTraces(fscope);
}

