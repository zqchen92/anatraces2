//
//last updated@26 May,2024
//Z.Chen
//
//Error_scope_cc_xxx.
//


#include "../inc/lisa_scope.hh"

#include <vector>
#include <iostream>
#include <cstdio>
#include <fstream>
#include <TTree.h>
#include <TFile.h>
#include <TMath.h>
#include <TStopwatch.h>
#include <TRandom3.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TAxis.h>
#include <TMultiGraph.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TH1.h>
#include <TEnv.h>
#include <functional>

lisa_scope::lisa_scope()
{
    std::cout << "lisa_scope::lisa_scope()" << std::endl;
}

lisa_scope::~lisa_scope()
{
    std::cout << "lisa_scope::~lisa_scope()" << std::endl;
}

void lisa_scope::getSingleScopeTrace()
{

    std::cout<<"lisa_scope::getSingleScopeTrace()"<<std::endl;

    std::ifstream fFile;
    Int_t fjentry = getJentryScope();
    TString fTxtDir = getInputFilePathScope();
    TString fName = Form("%d.txt",fjentry);
    std::vector<Double_t> time_ns;
    std::vector<Double_t> amplitude;
    Int_t *fScopeDataLoading = getEntryScope(); 

    fName = fTxtDir + fName;
    if(lisa_settings::getVerbose() == 1)std::cout<<"Load data from "<<fName<<std::endl;
    fFile.open(fName);
    if(!fFile.is_open()){
        std::cout<<"***Error_scope_cc_001: Can not open file "<<fName<<std::endl;
        return;
    }
    time_ns.clear();
    amplitude.clear();
    int cnt = 0;
    while(!fFile.eof()){
        double t, a;
        fFile >> t >> a;
        if(lisa_settings::getVerbose() == 1 && cnt<10)std::cout<<"t = "<<t<<" a = "<<a<<std::endl;
        if(lisa_settings::getVerbose() == 1 && cnt<1 )std::cout<<"read from pts = "<<fScopeSampleWindow[0]<<" to = "<<fScopeSampleWindow[1]<<std::endl;
        cnt++;
        fFile.ignore(100,'\n');
        //if(cnt>gScopeDataLoading[1])break;
        if(cnt<fScopeSampleWindow[0] || cnt>fScopeSampleWindow[1])continue;
        //if( cnt>gtrapezSampleWindow[1]+1000)break;
        time_ns.push_back(t*1e9);//ns
        amplitude.push_back(a*1000);//mV
    }
    if(lisa_settings::getVerbose() == 1)std::cout<<"test: size = "<<time_ns.size()<<" xx = "<<time_ns.back()<<" yy = "<<amplitude.back()<<std::endl;
    setScopeTraceI(time_ns);
    setScopeTraceV(amplitude);
    setScopeTraceLength(time_ns.size());
    if(lisa_settings::getVerbose() == 1)std::cout<<"lisa_scope::getSingleScopeTrace() end"<<std::endl;
}


void lisa_scope::getCorrectScopeTrace()
{
    if(lisa_settings::getVerbose() == 1)std::cout<<"lisa_scope::getCorrectScopeTrace()"<<std::endl;
    if(getScopeTraceV().size() == 0){
        if(lisa_settings::getVerbose() == 3)std::cout << "***Error_scope_cc_002: getScopeTraceV().size() == 0"<<std::endl;
        if(lisa_settings::getVerbose() == 3)std::cout << "***Please check if you have loaded raw traces."<<std::endl;
        return;
    }
    if(getScopeTraceV_corr().size() != 0){
        if(lisa_settings::getVerbose() == 3)std::cout<<"--->Trace is already corrected.***"<<std::endl;
        if(lisa_settings::getVerbose() == 3)std::cout<<"--->Skip this step."<<std::endl;
        return;
    }
    std::vector<Double_t> fxx = getScopeTraceI();
    std::vector<Double_t> fyy = getScopeTraceV();
    Int_t fshift = 0;
    for(int ii=20;ii<30;ii++){
        fshift += fyy[ii];
    }
    fshift = fshift/10;
    for(int ii=0;ii<getScopeTraceLength();ii++){
        fyy[ii] = fyy[ii]-fshift;
        //***debug***//
        fxx[ii] = fxx[ii];

    }
    setScopeTraceV_corr(fyy);
    setScopeTraceI_corr(fxx);
}

void lisa_scope::getMWDScopeTrace()
{
    if(lisa_settings::getVerbose() == 1)std::cout<<"lisa_scope::getMWDScopeTrace()"<<std::endl;
    if(getScopeTraceV_corr().size() == 0){
        if(lisa_settings::getVerbose() == 3)std::cout << "***Error_scope_cc_003: getScopeTraceV_corr().size() == 0"<<std::endl;
        if(lisa_settings::getVerbose() == 3)std::cout << "***Please check if you have loaded corrected traces."<<std::endl;
        return;
    }
    std::vector<Double_t> fxx = getScopeTraceI_corr();
    std::vector<Double_t> fyy = getScopeTraceV_corr();

    std::vector<Double_t> MWD;
    std::vector<Double_t> MWDx;
    MWD.clear();
    MWDx.clear();

    //debug//
    if(lisa_settings::getVerbose() == 1){
        std::cout<<"decaytime = "<<getDecayTime()<<std::endl;
        std::cout<<"risingtime = "<<getRisingTime()<<std::endl;
        std::cout<<"sample rate = "<<getSampleRate()<<std::endl;
        std::cout<<"trapez moving window length = "<<getTrapezMovingWindowLength()<<std::endl;
    }

    Int_t k0,kend,MM,LL;
    Double_t sum0=0;
    Double_t tau = getDecayTime()*getSampleRate()/MHZ2NS;//[sample points]
    Double_t DM=0;
    float mwd=0;
    float mwdx=0;
    //********************//
    //---            -----//
    //  a-          -d    //
    //    -        -      //
    //     -      -       //
    //     b------c       //
    //********************//
    //
    MM=(Int_t)getTrapezMovingWindowLength()*getSampleRate()/MHZ2NS;//length from b to d; [sample point]
    LL=(Int_t)getRisingTime()*getSampleRate()/MHZ2NS;//length from a to b; [sample point]

    //flat on top/bottom: MM-LL; [sample point]
    k0=getTrapezSampleWindow()[0]*getSampleRate()/MHZ2NS;//[sample point]
    kend=getTrapezSampleWindow()[1]*getSampleRate()/MHZ2NS;//[sample point]

    //***debug***//
    if(lisa_settings::getVerbose() == 1){
        std::cout<<"tau = "<<tau<<std::endl;
        std::cout<<"MM = "<<MM<<std::endl;
        std::cout<<"LL = "<<LL<<std::endl;
        std::cout<<"k0 = "<<k0<<std::endl;
        std::cout<<"kend = "<<kend<<std::endl;
    }
    int cnt=0;//for debug

    for(int kk = k0;kk < kend;kk=kk+1){
        DM=0;
        for(int j=kk-LL;j<=kk-1;j=j+1){
            if(j<1){
                if(lisa_settings::getVerbose() == 3)std::cout<<"***Error_febex_cc_005: Please decrease your rising time OR shift the start point of sample window to the right."<<std::endl;
                return;
            }
            sum0=0;
            for(int i=kk-MM;i<=kk-1;i++){
                if(i<0){
                    if(lisa_settings::getVerbose() == 3)std::cout<<"*kk-MM = "<<i<<std::endl;
                    if(lisa_settings::getVerbose() == 3)std::cout<<"***Error_febex_cc_006: Please decrease your Trapezoidal moving window length OR shift the start point of sample window to the right."<<std::endl;
                    return;
                }
                sum0 += fyy[i];
                //***debug***//
                //if(cnt<50){
                //    std::cout<<"fyy[i] = "<<fyy[i]<<std::endl;
                //    std::cout<<"sum0 = "<<sum0<<std::endl;
                //    cnt++;
                //}
            }//i=kk-MM
            DM += (fyy[kk] - fyy[kk-MM] + 1.0*sum0/tau);
        }//j=kk-LL
        mwd = DM/LL;
        mwdx = fxx[kk];//convert from int to double

        MWD.push_back(mwd);
        MWDx.push_back(mwdx);//

    }//kk=k0

    Int_t MWDsize = MWD.size();

    //****debug***//
    if(lisa_settings::getVerbose() == 1){
        for(int ii = 0;ii < 5;ii++){
            std::cout<<"MWD = "<<MWD[ii]<<std::endl;
            std::cout<<"MWDx = "<<MWDx[ii]<<std::endl;
        }
        std::cout<<"***MWD.size() = "<<MWDsize<<std::endl;
    }

    setMWDLength(MWDsize);
    setScopeTraceV_mwd(MWD);
    setScopeTraceI_mwd(MWDx);
}

void lisa_scope::calcEnergy(){
    if(getScopeTraceV_mwd().size() == 0){
        if(lisa_settings::getVerbose() == 3)std::cout << "***Error_scope_cc_004: getScopeTraceV_mwd().size() == 0"<<std::endl;
        return;
    }
    if(lisa_settings::getVerbose() == 1)std::cout<<"***calcEnergy()***"<<std::endl;

    std::vector<Double_t> fxx = getScopeTraceI_mwd();
    std::vector<Double_t> fyy = getScopeTraceV_mwd();
    Int_t length = getMWDLength();
    if(lisa_settings::getVerbose() == 3){
        std::cout<<"***length = "<<length<<std::endl;
        std::cout<<"size of fxx = "<<fxx.size()<<std::endl;
        std::cout<<"fxx[0] = "<<fxx[0]<<std::endl;
        std::cout<<"fxx[1] = "<<fxx[1]<<std::endl;
    }
    Int_t *fRange = getTrapezAmplitudeCalcWindow();//fRange[0],[1]
    std::cout<<"***fRange = "<<fRange[0]<<","<<fRange[1]<<std::endl;

    double ytem=0;
    int cnt=0;
    double fsum=0;
    for(int i=0;i<length;i++){
        if( fRange == NULL || fRange[0] > fRange[1]){
            if(lisa_settings::getVerbose() == 3)std::cout<<"Error_scope_cc_005. Please check trapez amp calc window."<<std::endl;
            return;
        }
        if( fxx[i]>fRange[0] && fxx[i]<fRange[1] ){//ns
            fsum+=fyy[i];
            cnt++;
        }
    }
    if(lisa_settings::getVerbose() == 3 && cnt == 0){
        std::cout<<"***Error_scope_cc_006. No data in the trapez amp calc window."<<std::endl;
        return;
    }
    if(lisa_settings::getVerbose() == 3)std::cout<<"***average amplitude = "<<fsum/cnt<<std::endl;
    Double_t fenergy_tem = fsum/cnt;
    if(fenergy_tem<0)fenergy_tem = fenergy_tem*(-1);
    setScopeEnergy_mwd(fenergy_tem);
}

void lisa_scope::getCFDScopeTrace(){

    if(lisa_settings::getVerbose() == 1)std::cout<<"lisa_scope::getCFDScopeTrace()"<<std::endl;
    if(getScopeTraceV_corr().size() == 0){
        if(lisa_settings::getVerbose() == 3)std::cout << "***Error_scope_cc_007: getScopeTraceV_corr().size() == 0"<<std::endl;
        if(lisa_settings::getVerbose() == 3)std::cout << "***Please check if you have loaded corrected traces."<<std::endl;
        return;
    }
    int length = getScopeTraceLength();
    if(length == 0){
        if(lisa_settings::getVerbose() == 3)std::cout << "***Error_scope_cc_008: getScopeTraceLength() == 0"<<std::endl;
        return;
    }
    std::vector<Double_t> fxx = getScopeTraceI_corr();
    std::vector<Double_t> fyy = getScopeTraceV_corr();
    std::vector<double>xx;
    std::vector<double>yy;
    std::vector<double>yyf;//with fraction
    std::vector<Double_t>xxd;//with delay; for CFD graph
    std::vector<Double_t>yyCFD;//after CFD; for CFD graph
    int cnt=0;
    xx.clear();
    yy.clear();
    yyf.clear();
    xxd.clear();
    yyCFD.clear();
    for(int i=0;i<length;i++){
        double x,y;
        xx.push_back(fxx[i]);
        yy.push_back(fyy[i]*(-1.0));//inverted
        yyf.push_back(fyy[i]*getCFDfraction());//fraction
        xxd.push_back(fxx[i]+getCFDdelay());//delay[ns]
    }
    TGraph *ftem1 = new TGraph(xx.size(),&xx[0],&yyf[0]);
    for(int i=0;i<length;i++){
        double ytem=0;
        ytem = ftem1->Eval(xxd[i]);
        yyCFD.push_back(ytem+yy[i]);
    }
    //***debug***//
    //ftem1->Draw("AP*");
    //calculate zero
    double ymax_y,ymax_x,ymin_y,ymin_x;
    ymax_y = ymin_y = 0;
    ymax_x = ymin_x = -9999;
    double fx1,fx2;
    fx1 = fx2 = -9999;
    for(int i=0;i<length;i++){
        if(xxd[i]>getCFDWindow()[0] && xxd[i]<getCFDWindow()[1]){//CFD window[ns]
            if(yyCFD[i]>ymax_y){
                ymax_y = yyCFD[i];
                ymax_x = xxd[i];
            }
            if(yyCFD[i]<ymin_y){
                ymin_y = yyCFD[i];
                ymin_x = xxd[i];
            }
        }
    }
    fx1 = ymax_x;
    fx2 = ymin_x;
    //swap
    if(fx2<fx1){
        double tem = fx1;
        fx1 = fx2;
        fx2 = tem;
    }
    std::vector<float>xxz;//to calculate zero
    std::vector<float>yyz;//to calculate zero
    xxz.clear();
    yyz.clear();
    if(lisa_settings::getVerbose() == 1)std::cout<<"fx1 = "<<fx1<<" fx2 = "<<fx2<<std::endl;
    for(int i=0;i<length;i++){
        if(xxd[i]>fx1 && xxd[i]<fx2){
            xxz.push_back(yyCFD[i]);
            yyz.push_back(xxd[i]);//int time related to the sample rate;
        }
    }
    TGraph *ftem3 = new TGraph(xxz.size(),&xxz[0],&yyz[0]);
    Double_t ftiming = ftem3->Eval(0,0)+gRandom->Uniform(-5,5);//use spline interpolation to get the "0" point;float time

    if(lisa_settings::getVerbose() == 1)std::cout<<"xxd.size() = "<<xxd.size()<<std::endl;
    if(xxd.size() == 0){
        if(lisa_settings::getVerbose() == 3)std::cout<<"Error_febex_cc_009. xxd.size() == 0."<<std::endl;
        return;
    }

    //***debug***//
    if(lisa_settings::getVerbose() == 1){
        for(int ii=0;ii<1;ii++){
            std::cout<<"xxd[ii]"<<xxd[ii]<<std::endl;
            std::cout<<"yyCFD[ii]"<<yyCFD[ii]<<std::endl;
        }
    }

    setScopeTime_cfd(ftiming);
    setScopeTraceV_cfd(yyCFD);
    setScopeTraceI_cfd(xxd);

}

void lisa_scope::getScopeTraces(){

    if(lisa_settings::getVerbose() == 3)std::cout<<"lisa_scope::getScopeTraces()"<<std::endl;

    TStopwatch timer;
    TStopwatch timer2;//start before the loop; to calculate total running time
    std::vector<float>v_averageSpeed;
    v_averageSpeed.clear();

    //save data to febex_data
    scope_data fscope_data_temp;
    std::vector<scope_data> v_fscope_data_temp;
    v_fscope_data_temp.clear();

    if( lisa_settings::getIsSaveAsRoot() )initOptTree();

    //int cnt = 0;//for debug
    //***set entry reading***//
    ULong64_t entry_beg = 0;//beginning
    ULong64_t entry_end = 0;//end
    entry_beg = lisa_settings::getEntryScope()[0];
    entry_end = lisa_settings::getEntryScope()[1];
    //*** loop from event_i to event_j ***//
    for(ULong64_t jentry = entry_beg;jentry < entry_end;jentry++){

        //stopwatch
        if(jentry%100==0){
            timer.Reset();
            timer.Start();
        }

        lisa_settings::setJentryScope(jentry);
        if(lisa_settings::getVerbose() == 2)std::cout<<"current entry = "<<lisa_settings::getJentryScope()<<""<<std::endl;

        //*** clear variables ***//
        resetVariables();//reset variables
        fscope_data_temp.clear();//set variables to initial value
        if( lisa_settings::getIsSaveAsRoot() )clearOptTree();

        //std::cout<<"cc = "<<cc<<", febexCh = "<<lisa_settings::getFebexCh()<<std::endl;

        getSingleScopeTrace();
        getCorrectScopeTrace();
        getMWDScopeTrace();
        getCFDScopeTrace();
        calcEnergy();

        //***debug***//
        //std::cout<<"--->before get values"<<std::endl;
        //febex_data_temp.print();

        //save data to febex_data
        fscope_data_temp.fenergy_raw = getScopeEnergy_mwd();
        fscope_data_temp.ftime_cfd = getScopeTime_cfd();
        fscope_data_temp.flength = getScopeTraceLength();

        fscope_data_temp.fCorrTrace_x = getScopeTraceI_corr();//
        fscope_data_temp.fCorrTrace_y = getScopeTraceV_corr();//

        fscope_data_temp.fMWDTrace_x = getScopeTraceI_mwd();//
        fscope_data_temp.fMWDTrace_y = getScopeTraceV_mwd();

        if(fscope_data_temp.flength == 0)fscope_data_temp.clear();//if empty
        setScopeData(fscope_data_temp);//set febex_data

        v_fscope_data_temp.push_back(fscope_data_temp);//add to febex_data vector
        if( lisa_settings::getIsSaveAsRoot() )fillOptTree(fscope_data_temp);//

        //***debug***//
        //std::cout<<"size of v_febex_data_temp = "<<v_febex_data_temp.size()<<std::endl;
        //std::cout<<"--->after get values"<<std::endl;
        //v_febex_data_temp.back().print();

        //***debug***//
        //std::cout<<"cnt = "<<cnt<<std::endl;
        //if(v_febex_data_temp.back().flength!=0){
        //    for(int jj=0;jj<10;jj++){
        //        std::cout<<"febex_data_temp.fCorrTrace_x[jj] = "<<v_febex_data_temp.back().fCorrTrace_x[jj]<<std::endl;
        //        std::cout<<"febex_data_temp.fCorrTrace_y[jj] = "<<v_febex_data_temp.back().fCorrTrace_y[jj]<<std::endl;
        //    }
        //}
        //cnt++;//for debug
        //***debug***//
        /*
           if(cnt==3){
           for(int jentry = 0;jentry<v_febex_data_temp.size();jentry++){
           std::cout<<"jentry = "<<jentry<<std::endl;
           if(v_febex_data_temp[jentry].flength == 0 || v_febex_data_temp[jentry].fCorrTrace_y.size() == 0)continue;
           std::cout<<"--->flength = "<<v_febex_data_temp[jentry].flength<<""<<std::endl;
           std::cout<<"--->fCorrTrace_y address = "<<&v_febex_data_temp[jentry].fCorrTrace_y<<""<<std::endl;
           std::cout<<"--->fCorrTrace_y[0] = "<<v_febex_data_temp[jentry].fCorrTrace_y[0]<<""<<std::endl;
           std::cout<<"--->fMWDTrace_y address = "<<&v_febex_data_temp[jentry].fMWDTrace_y<<""<<std::endl;
           std::cout<<"--->fMWDTrace_y[0] = "<<v_febex_data_temp[jentry].fMWDTrace_y[0]<<""<<std::endl;
           }
           }*/

        //*** fill tree ***//
        if( lisa_settings::getIsSaveAsRoot() )getOptTree()->Fill();
        //*** calculate running time ***//
        double fspeed;
        double fduration;
        if(jentry%100==99){
            fduration = timer.RealTime();//
            fspeed = 100.0/fduration;// [evt/sec]
            v_averageSpeed.push_back(fspeed);
        }
        double ftimeToGo = 0;
        if(jentry%100==99)ftimeToGo = (getEntry()[1]-jentry)/fspeed;

        if(jentry%100==99)std::cout<<"*Current speed: "<<fspeed<<"[evt/s]; Duration for 100 evts: "<<fduration<<", Num:"<<jentry<<"/"<<getEntry()[1]<<"  "<<ftimeToGo<<"s to go.";
        fflush(stdout);
        printf("\r");
    }//end of loop

    //save data to febex_data vector
    setScopeDataV(v_fscope_data_temp);

    //***export data to root file***//
    if( lisa_settings::getIsSaveAsRoot() )closeOptRoot();

    //***debug***//
    //for(int jentry = 0;jentry<v_febex_data_temp.size();jentry++){
    //    std::cout<<"jentry = "<<jentry<<std::endl;
    //    if(v_febex_data_temp[jentry].flength!=0){
    //        for(int jj=0;jj<10;jj++){
    //            std::cout<<"febex_data_temp.fCorrTrace_x[jj] = "<<v_febex_data_temp[jentry].fCorrTrace_x[jj]<<std::endl;
    //            std::cout<<"febex_data_temp.fCorrTrace_y[jj] = "<<v_febex_data_temp[jentry].fCorrTrace_y[jj]<<std::endl;
    //        }
    //    }
    //}

    float gAverageSpeed = std::accumulate(v_averageSpeed.begin(),v_averageSpeed.end(),0.0)/v_averageSpeed.size();
    float gTotalRunningTime = timer2.RealTime();
    std::cout<<std::endl;
    std::cout<<"--->Total running time: "<<gTotalRunningTime<<" s."<<std::endl;
    std::cout<<"--->Average speed     : "<<gAverageSpeed<<" [evt/s]."<<std::endl;

    std::cout<<"***getTraces() end***"<<std::endl;
    std::cout<<"...oooOO0OOooo......oooOO0OOooo......oooOO0OOooo......oooOO0OOooo..."<<std::endl;
    //***debug***//


}

//...oooOO0OOooo......oooOO0OOooo....oooOO0OOooo......oooOO0OOooo...//
//               output tree              //
//...oooOO0OOooo......oooOO0OOooo....oooOO0OOooo......oooOO0OOooo...//


void lisa_scope::initOptTree(){

    std::cout<<"***initOptTree***"<<std::endl;
    TFile *optfile = new TFile(lisa_settings::getOptRootFileName(),"RECREATE");
    TTree *optTree = new TTree("tree","tree");

    optTree->Branch("entry",&entry,"entry/I");
    optTree->Branch("Eraw",&Eraw,"Eraw/D");
    optTree->Branch("Ecal",&Ecal,"Ecal/D");
    optTree->Branch("T_cfd",&T_cfd,"T_cfd/D");
    optTree->Branch("traceLength",&traceLength,"traceLength/i");
    optTree->Branch("tracesX",tracesX,"tracesX[40000]/D");//this has to be a specific value, MAX_TRACE_LENGTH is not allowed to use here.
    optTree->Branch("tracesY",tracesY,"tracesY[40000]/D");

    std::cout<<"--->init output root file."<<std::endl;
    setOptTree(optTree);
    setOptFile(optfile);

}

void lisa_scope::fillOptTree(scope_data &fopt){

    if( lisa_settings::getVerbose() ==3 )std::cout<<"***fillOptTree***"<<std::endl;
    if(fopt.flength==0)return;
    entry = fopt.fentry;
    Eraw = fopt.fenergy_raw;
    Ecal = fopt.fenergy_cal;
    T_cfd = fopt.ftime_cfd;
    traceLength = fopt.flength;
    if(lisa_settings::getVerbose() == 3 && traceLength>40000){
        std::cout<<"***traceLength > 40000***"<<std::endl;
        return;
    }
    if(lisa_settings::getIsSaveTraces()){
        for(int i=0;i<traceLength;i++){
            Int_t x,y;//for corrected traces
            x = fopt.fCorrTrace_x[i];
            y = fopt.fCorrTrace_y[i];
            tracesX[i] = x;
            tracesY[i] = y;
            if(lisa_settings::getVerbose() == 2)std::cout<<"in saveasroot: traceX = "<<tracesX[i]<<" traceY = "<<tracesY[i]<<std::endl;
        }
    }

}

void lisa_scope::clearOptTree(){

    if( lisa_settings::getVerbose() == 3 )std::cout<<"***clearOptTree***"<<std::endl;
    entry = 0;
    Eraw = -1;
    Ecal = -1;
    T_cfd = -9999;
    traceLength = 0;
    for(int ii =0; ii<40000;ii++){
        tracesX[ii] = -1;
        tracesY[ii] = -1;
    }

}

void lisa_scope::closeOptRoot(){
    std::cout<<"***closeOptRoot***"<<std::endl;
    getOptTree()->Write("", TObject::kOverwrite);
    getOptFile()->Close();
    std::cout<<"******************************************"<<std::endl;
    std::cout<<"Data has been saved to "<<lisa_settings::getOptRootFileName()<<"."<<std::endl;
    std::cout<<"Root file has been closed."<<std::endl;

    std::cout<<"******************************************"<<std::endl;
}


