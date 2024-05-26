//
//last updated@06 Apr,2024
//Z.Chen
//

#ifndef _ZCHEN_CC_
#define _ZCHEN_CC_

#include <iostream>
#include "../../inc/users/zchen.hh"
#include "../lisa_febex.cc"
#include "../lisa_settings.cc"
#include "../lisa_vis.cc"

zchen_ana::zchen_ana(TTree *tree)
{
    if (tree == NULL) {
        std::cout << "***Error_zchen_cc_000:zchen_ana::zchen_ana(tree==0)" << std::endl;
        return;
    }
    Init(tree);//from lisa_ucesb
    setTree(tree);//deliver tree to ftree;from lisa_febex
    //loadSettings(settings);//from lisa_febex
}

zchen_ana::~zchen_ana()
{
    std::cout << "zchen_ana::~zchen_ana()" << std::endl;
}

void zchen_ana::Show(lisa_febex *ipt)
{
    if (ipt == 0) {
        std::cout << "***Error_zchen_cc_001:zchen_ana::Show(tree==0)" << std::endl;
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

void zchen_ana::Test(TTree *tree)
{
    std::cout << "***zchen_ana::Test()" << std::endl;
    //setJentry(22);
    //setCh(0);
    TCanvas *c = new TCanvas();
    c->Divide(2, 2);
    //raw trace
    c->cd(1);
    getSingleTrace(tree);
    int flen0 = getFebexTraceL();
    int *fxx0 = (int*)getRawTraceI();
    int *fyy0 = (int*)getRawTraceV();
    TGraph *gr0 = new TGraph( flen0, fxx0, fyy0 );
    gr0->Draw("AP*");

    //correct trace
    c->cd(2);
    getCorrectTrace();
    int *fxx = (int*)getCorrectTraceI();
    int *fyy = (int*)getCorrectTraceV();
    TGraph *gr1 = new TGraph( flen0, fxx, fyy );
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

void zchen_ana::TestSingleTrace(lisa_febex *ffebex)
{
    if (ffebex == 0) {
        std::cout << "***Error_zchen_cc_002:zchen_ana::TestSingleTrace(ffebex==0)" << std::endl;
        return;
    }
    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis(ffebex);
    std::cout<<"vis done"<<std::endl;
    vis1->anaFebex4_checkSingleTrace(ffebex);
}

void zchen_ana::TestCheckMWD(lisa_febex *ffebex)
{
    if (ffebex == 0) {
        std::cout << "***Error_zchen_cc_003:zchen_ana::TestCheckMWD(ffebex==0)" << std::endl;
        return;
    }
    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis(ffebex);
    std::cout<<"vis done"<<std::endl;
    vis1->checkMWD(ffebex);
}

//no display
void zchen_ana::TestTraces(lisa_febex *ffebex)
{
    std::cout << "***zchen_ana::TestTraces()" << std::endl;
    if (ffebex == 0) {
        std::cout << "***Error_zchen_cc_004:zchen_ana::TestTraces(ffebex==0)" << std::endl;
        return;
    }

    ffebex->getTraces(ffebex->getTree());
}

//with display

void zchen_ana::TestanaFebex4_checkTraces(lisa_febex *ffebex)
{
    if (ffebex == 0) {
        std::cout << "***Error_zchen_cc_005:zchen_ana::TestanaFebex4_checkTraces(ffebex==0)" << std::endl;
        return;
    }
    ffebex->getTraces(ffebex->getTree());
    //*** for visualization ***//
    std::cout<<"vis start"<<std::endl;
    lisa_vis *vis1 = new lisa_vis(ffebex);
    std::cout<<"vis done"<<std::endl;
    vis1->anaFebex4_checkTraces(ffebex);
}

#endif
