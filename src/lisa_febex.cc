//
//last updated@26 May,2024
//Z.Chen
//
//Error_febex_cc_xxx.
//
//
//

#include "../inc/lisa_febex.hh"

#include <vector>
#include <iostream>
#include "TGraph.h"
#include "TTree.h"
#include "TFile.h"
#include "TStopwatch.h"
#include "TRandom3.h"
#include <functional>
#include <numeric>

lisa_febex::lisa_febex()
{
	std::cout << "lisa_febex::lisa_febex()" << std::endl;
}

lisa_febex::lisa_febex(TTree *tree)
{
	if(tree == NULL){
		if(lisa_settings::getVerbose() == 3)std::cout << "***Error_febex_cc_000:lisa_febex::lisa_febex(tree==0)" << std::endl;
		return;
	}

	//fucesb->Init(tree);
	//loadSettings(settings);

    Init(tree);//from lisa_ucesb
	setTree(tree);//deliver tree to ftree

}

lisa_febex::~lisa_febex()
{
	std::cout << "lisa_febex::~lisa_febex()" << std::endl;
}

/*
   void lisa_febex::loadSettings(lisa_settings *settings){
   if(settings == NULL){
   std::cout << "***Error_febex_cc_001:lisa_febex::loadSettings(settings==0)" << std::endl;
   return;
   }
   lisa_settings::setVerbose(settings->getVerbose());
   setFebexCh(settings->getFebexCh());
   setJentry(settings->getJentry());
   setLength(settings->getFebexTraceL());
   setMWDEnergyCalcWindow( settings->getTrapezAmplitudeCalcWindow() );

   std::cout<<"***lisa_febex::loadSettings()***"<<std::endl;
   }
   */

void lisa_febex::getSingleTrace(TTree *tree)
{
	if(lisa_settings::getVerbose() == 3)std::cout << "lisa_febex::getSingleTrace()" << std::endl;

	if (tree == NULL) {
		if(lisa_settings::getVerbose() == 3)std::cout << "***Error_febex_cc_002:lisa_febex::getSingleTrace(tree==0)" << std::endl;
		return;
	}
	if(lisa_settings::getVerbose() == 1){
		std::cout<<"*** jentry = "<<getJentry()<<std::endl;
		std::cout<<"*** febex channel = "<<getFebexCh()<<std::endl;
	}
	//debug
	//tree->Draw("lisa_data1traces1v:lisa_data1traces1I");
	//return;

	std::vector<double>yy;//amplitude
	std::vector<double>xx;//sample
	yy.clear();
	xx.clear();

	tree->GetEntry(getJentry());

	std::vector<UInt_t>len;//vector for trace length;directly read from unpacked data
	std::vector<UInt_t*>lisa_data_v;//vector for pointers
	std::vector<UInt_t*>lisa_data_I;
	len.clear();//length
	lisa_data_v.clear();
	lisa_data_I.clear();
	//*** for ucesb ***//
	len.push_back(lisa_data1traces1);
	len.push_back(lisa_data1traces2);
	len.push_back(lisa_data1traces3);
	len.push_back(lisa_data1traces4);
	len.push_back(lisa_data1traces5);
	len.push_back(lisa_data1traces6);
	len.push_back(lisa_data1traces7);
	len.push_back(lisa_data1traces8);
	len.push_back(lisa_data1traces9);
	len.push_back(lisa_data1traces10);
	len.push_back(lisa_data1traces11);
	len.push_back(lisa_data1traces12);
	len.push_back(lisa_data1traces13);
	len.push_back(lisa_data1traces14);
	len.push_back(lisa_data1traces15);
	len.push_back(lisa_data1traces16);

	lisa_data_v.push_back(lisa_data1traces1v);
	lisa_data_v.push_back(lisa_data1traces2v);
	lisa_data_v.push_back(lisa_data1traces3v);
	lisa_data_v.push_back(lisa_data1traces4v);
	lisa_data_v.push_back(lisa_data1traces5v);
	lisa_data_v.push_back(lisa_data1traces6v);
	lisa_data_v.push_back(lisa_data1traces7v);
	lisa_data_v.push_back(lisa_data1traces8v);
	lisa_data_v.push_back(lisa_data1traces9v);
	lisa_data_v.push_back(lisa_data1traces10v);
	lisa_data_v.push_back(lisa_data1traces11v);
	lisa_data_v.push_back(lisa_data1traces12v);
	lisa_data_v.push_back(lisa_data1traces13v);
	lisa_data_v.push_back(lisa_data1traces14v);
	lisa_data_v.push_back(lisa_data1traces15v);
	lisa_data_v.push_back(lisa_data1traces16v);

	lisa_data_I.push_back(lisa_data1traces1I);
	lisa_data_I.push_back(lisa_data1traces2I);
	lisa_data_I.push_back(lisa_data1traces3I);
	lisa_data_I.push_back(lisa_data1traces4I);
	lisa_data_I.push_back(lisa_data1traces5I);
	lisa_data_I.push_back(lisa_data1traces6I);
	lisa_data_I.push_back(lisa_data1traces7I);
	lisa_data_I.push_back(lisa_data1traces8I);
	lisa_data_I.push_back(lisa_data1traces9I);
	lisa_data_I.push_back(lisa_data1traces10I);
	lisa_data_I.push_back(lisa_data1traces11I);
	lisa_data_I.push_back(lisa_data1traces12I);
	lisa_data_I.push_back(lisa_data1traces13I);
	lisa_data_I.push_back(lisa_data1traces14I);
	lisa_data_I.push_back(lisa_data1traces15I);
	lisa_data_I.push_back(lisa_data1traces16I);

	setTrigger(TRIGGER);
	setEvtNo(EVENTNO);
	setFebexTraceL(len[getFebexCh()]);

	//debug//
	if(lisa_settings::getVerbose() == 1){
		for(int ii=0;ii<16;ii++)std::cout<<"***febex channel = "<<ii<<"   length(lisa_febex) = "<<len[ii]<<std::endl;
	}

	if(getFebexTraceL() == 0){
		if( lisa_settings::getVerbose() == 3  )std::cout<<"***Error_febex_cc_010: getFebexTraceL() == 0 in getSingleTrace(); febex channel = "<<getFebexCh()<<" "<<std::endl;
		return;
	}
	UInt_t *p_v = lisa_data_v[getFebexCh()];//y axis
	UInt_t *p_I = lisa_data_I[getFebexCh()];//x axis
	std::vector<Int_t> fraw_v;
	std::vector<Int_t> fraw_I;
	fraw_v.clear();
	fraw_I.clear();
	for(int ii=0;ii<getFebexTraceL();ii++){
		fraw_v.push_back(p_v[ii]);
		fraw_I.push_back(p_I[ii]);
	}
	setRawTraceV(fraw_v);
	setRawTraceI(fraw_I);
	//setRawTraceV(p_v);
	//setRawTraceI(p_I);

	//p_v=NULL;
	//p_I=NULL;
}
//***baseline correction and time correction***//
void lisa_febex::getCorrectTrace()
{
	if(getFebexTraceL() == 0){
		if(lisa_settings::getVerbose() == 3)std::cout << "***Error_febex_cc_003: getRawTraceV() == NULL in getCorrectTrace()"<<std::endl;
		if(lisa_settings::getVerbose() == 3)std::cout << "***Please check if you have loaded raw traces."<<std::endl;
		return;
	}
	if(getCorrectTraceV().size() != 0){
		if(lisa_settings::getVerbose() == 3)std::cout<<"--->Trace is already corrected.***"<<std::endl;
		if(lisa_settings::getVerbose() == 3)std::cout<<"--->Skip this step."<<std::endl;
		return;
	}
	if(lisa_settings::getVerbose() == 1)std::cout<<"***lisa_febex::getCorrectTrace()***"<<std::endl;
	std::vector<Int_t>fxx = getRawTraceI();
	std::vector<Int_t>fyy = getRawTraceV();
	std::vector<float> fxx_w;
	std::vector<float> fyy_w;
	fxx_w.clear();
	fyy_w.clear();
	float fshift = 0;
	for(int ii=20;ii<100;ii++){
		fshift += fyy[ii];
		//***debug***//
		//std::cout<<"fyy[ii]"<<fyy[ii]<<std::endl;
		//std::cout<<"fshift"<<fshift<<std::endl;
	}
	fshift = fshift/80.0;
	//***debug***//
	//std::cout<<"***fshift***"<<fshift<<std::endl;
	for(int ii=0;ii<getFebexTraceL();ii++){
		//fyy_w[ii] = fyy[ii]-fshift;
		float fyytem = fyy[ii]-fshift;
		fyytem = fyytem*1000.0/8000.0;//8000 from Febex corresponds to 1000mV;attention, fyy is Int_t
		fyy_w.push_back(fyytem);
		//fyy[ii] = fyy[ii]*1000/8000;//8000 from Febex corresponds to 1000mV;attention, fyy is Int_t
		//***debug***//
		//fxx_w[ii] = fxx[ii]*MHZ2NS/getSampleRate();//[ns]
		float fxxtem = fxx[ii];
		fxxtem = fxxtem*MHZ2NS/getSampleRate();//[ns]
		fxx_w.push_back(fxxtem);
		//fxx[ii] = fxx[ii]*MHZ2NS/getSampleRate();//[ns]

		//***debug***//
		//if(ii<20){
		//	std::cout<<"in getCorrectTrace(): ii = "<<ii<<" "<<"fyy_w[ii]"<<fyy_w[ii]<<std::endl;
		//	std::cout<<"in getCorrectTrace(): ii = "<<ii<<" "<<"fxx_w[ii]"<<fxx_w[ii]<<std::endl;
		//}
	}
	setCorrectTraceV(fyy_w);
	setCorrectTraceI(fxx_w);

	//setCorrectTraceV(fyy);
	//setCorrectTraceI(fxx);
}

//https://doi.org/10.1016/j.apradiso.2020.109171
//B.J.Kim
void lisa_febex::getMWDTrace()
{
	if(lisa_settings::getVerbose() == 1)std::cout<<"***lisa_febex::getMWDTrace()***"<<std::endl;

	if(getCorrectTraceV().size() == 0){
		if(lisa_settings::getVerbose() == 3)std::cout << "***Error_febex_cc_004: getRawTraceV() == NULL in getMWDTrace()"<<std::endl;
		return;
	}

	std::vector<float> fxx_mwd = getCorrectTraceI();
	std::vector<float> fyy_mwd = getCorrectTraceV();

	std::vector<float> MWD;
	std::vector<float> MWDx;
	MWD.clear();
	MWDx.clear();

	//Double_t MWD[8000];
	//Double_t MWDx[8000];
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
				sum0 += fyy_mwd[i];
				//***debug***//
				//if(cnt<50){
				//    std::cout<<"fyy[i] = "<<fyy[i]<<std::endl;
				//    std::cout<<"sum0 = "<<sum0<<std::endl;
				//    cnt++;
				//}
			}//i=kk-MM
			DM += (fyy_mwd[kk] - fyy_mwd[kk-MM] + 1.0*sum0/tau);
		}//j=kk-LL
		mwd = DM/LL;
		mwdx = (float)fxx_mwd[kk];//convert from int to double

		//***debug***//
		//if(kk<350)std::cout<<"mwd = "<<mwd<<std::endl;
		//if(cnt==0)std::cout<<"mwdx = "<<mwdx<<std::endl;

		MWD.push_back(mwd);
		MWDx.push_back(mwdx);//

		//***debug***//
		//if(cnt<10){
		//    std::cout<<"MWD.back() = "<<MWD.back()<<std::endl;
		//    std::cout<<"MWDx.back() = "<<MWDx.back()<<std::endl;
		//    cnt++;
		//}
	}//kk=k0

	//***debug***//
	//std::cout<<"MWD.size() = "<<MWD.size()<<std::endl;

	std::vector<float> p_v = MWD;//y axis
	std::vector<float> p_I = MWDx;//x axis
	Int_t MWDsize = MWD.size();

	//****debug***//
	if(lisa_settings::getVerbose() == 1){
		for(int ii = 0;ii < 5;ii++){
			std::cout<<"p_I = "<<p_I[ii]<<std::endl;
			std::cout<<"p_v = "<<p_v[ii]<<std::endl;
		}
		std::cout<<"***MWD.size() = "<<MWDsize<<std::endl;
	}

	setMWDTraceLength(MWDsize);
	setMWDTraceV(p_v);//
	setMWDTraceI(p_I);//

	//*** debug ***//
	//to check if we have e-310
	//6.xxe-310, initialization issue
	//this could come up when converting from int to double
	//float *p_I2 = (float*)getMWDTraceI();
	//float *p_v2 = (float*)getMWDTraceV();
	//for(int ii = 0;ii < 5;ii++){
	//    std::cout<<"p_I2 = "<<p_I2[ii]<<std::endl;
	//    std::cout<<"p_v2 = "<<p_v2[ii]<<std::endl;
	//}

}//end of getMWDTrace

//using CFD to determine time;
//NIMA 58(2):253(1968)
//delay ~ 1/4 * total trace width
//fraction ~ 0.9
void lisa_febex::getCFDTrace(){
	if(getCorrectTraceV().size() == 0){
		if(lisa_settings::getVerbose() == 3)std::cout << "***Error_febex_cc_007: getCorrectTraceV() == NULL in getCFDTrace()"<<std::endl;
		return;
	}
	if(lisa_settings::getVerbose() == 1)std::cout<<"***getCFDTrace()***"<<std::endl;
	Int_t length = getFebexTraceL();
	if( length == 0 ){
		if(lisa_settings::getVerbose() == 3)std::cout<<"Error_febex_cc_008. trace length = 0."<<std::endl;
		return;
	}
	//std::cout<<"length = "<<length<<std::endl;
	//***debug***//
	if(lisa_settings::getVerbose() == 1){
		std::cout<<"delay = "<<getCFDdelay()<<std::endl;
		std::cout<<"fraction = "<<getCFDfraction()<<std::endl;
		std::cout<<"CFDWindow = "<<getCFDWindow()[0]<<"  "<<getCFDWindow()[1]<<std::endl;
	}
	std::vector<float> fxx_cfd = getCorrectTraceI();
	std::vector<float> fyy_cfd = getCorrectTraceV();
	if(lisa_settings::getVerbose() == 1){
		for(int jj=0;jj<length;jj++)std::cout<<"**fxx_cfd[jj] = "<<fxx_cfd[jj]<<"  fyy_cfd[jj]"<<fyy_cfd[jj]<<std::endl;
	}
	std::vector<double>xx;
	std::vector<double>yy;
	std::vector<double>yyf;//with fraction
	std::vector<float>xxd;//with delay; for CFD graph
	std::vector<float>yyCFD;//after CFD; for CFD graph
	int cnt=0;
	xx.clear();
	yy.clear();
	yyf.clear();
	xxd.clear();
	yyCFD.clear();
	for(int i=0;i<length;i++){
		double x,y;
		xx.push_back(fxx_cfd[i]);
		yy.push_back(fyy_cfd[i]*(-1.0));//inverted
		yyf.push_back(fyy_cfd[i]*getCFDfraction());//fraction
		xxd.push_back(fxx_cfd[i]+getCFDdelay());//delay[ns]
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
		for(int ii=0;ii<xxd.size();ii++){
			std::cout<<"xxd[ii]="<<xxd[ii]<<"   yyCFD[ii]="<<yyCFD[ii]<<std::endl;
		}
	}
	setCFDtime(ftiming);
	setCFDTraceV(yyCFD);
	setCFDTraceI(xxd);
	setCFDTraceLength(xxd.size());
	if(lisa_settings::getVerbose() == 2)std::cout<<"zero point @ "<<ftiming<<" ns."<<std::endl;
}

void lisa_febex::calcEnergy(){
	if(getMWDTraceV().size() == 0){
		if(lisa_settings::getVerbose() == 3)std::cout << "***Error_febex_cc_008: getMWDTraceV().size() == 0 in calcEnergy()"<<std::endl;
		return;
	}
	if(lisa_settings::getVerbose() == 1)std::cout<<"***calcEnergy()***"<<std::endl;

	std::vector<float> fxx_energy = getMWDTraceI();
	std::vector<float> fyy_energy = getMWDTraceV();
	Int_t length = getMWDTraceLength();
	Int_t *fRange = getTrapezAmplitudeCalcWindow();//fRange[0],[1]

	double ytem=0;
	int cnt=0;
	double fsum=0;
	for(int i=0;i<length;i++){
		if( fRange == NULL || fRange[0] > fRange[1]){
			if(lisa_settings::getVerbose() == 3)std::cout<<"Error_febex_cc_009. Please check trapez amp calc window."<<std::endl;
			return;
		}
		if( fxx_energy[i]>fRange[0] && fxx_energy[i]<fRange[1] ){//ns
			fsum+=fyy_energy[i];
			cnt++;
		}
	}
	if(lisa_settings::getVerbose() == 2)std::cout<<"***average amplitude = "<<fsum/cnt<<std::endl;
	Double_t fenergy_tem = fsum/cnt;
	if(fenergy_tem<0)fenergy_tem = (-1)*fenergy_tem;
	setMWDenergy(fenergy_tem);
}

void lisa_febex::getTraces(TTree *tree){
	if(tree == NULL){
		if(lisa_settings::getVerbose() == 3)std::cout << "***Error_febex_cc_010: tree == NULL in getTraces()"<<std::endl;
		return;
	}
	ULong64_t fnentries = tree->GetEntriesFast();

	TStopwatch timer;
	TStopwatch timer2;//start before the loop; to calculate total running time
	std::vector<float>v_averageSpeed;
	v_averageSpeed.clear();

	//save data to febex_data
	febex_data febex_data_temp;
	std::vector<febex_data> v_febex_data_temp;
	v_febex_data_temp.clear();

	if( lisa_settings::getIsSaveAsRoot() )initOptTree();

	int cnt = 0;//for debug
				//***set entry reading***//
	ULong64_t entry_beg = 0;//beginning
	ULong64_t entry_end = 0;//end
	if( lisa_settings::getIsAllEntry() ){
		entry_beg = 0;
		entry_end = fnentries;
	}
	else{
		entry_beg = lisa_settings::getEntry()[0];
		entry_end = lisa_settings::getEntry()[1];
	}
	//*** loop from event_i to event_j ***//
	for(ULong64_t jentry = entry_beg;jentry < entry_end;jentry++){

		//stopwatch
		if(jentry%1000==0){
			timer.Reset();
			timer.Start();
		}

		lisa_settings::setJentry(jentry);
		if(lisa_settings::getVerbose() == 2)std::cout<<"current entry = "<<lisa_settings::getJentry()<<"/"<<fnentries<<std::endl;

		//*** clear variables ***//
		resetVariables();//reset variables
		febex_data_temp.clear();//set variables to initial value
		if( lisa_settings::getIsSaveAsRoot() )clearOptTree();

		bool f_is_single_mode = 0;
		for(int cc = 0;cc<16;cc++){
			if( f_is_single_mode == 1 ) continue;//if single mode, only do once without changing febexCh
			if( lisa_settings::getIsMultiChannelMode() && lisa_settings::getIsFebexCh(cc) )lisa_settings::setFebexCh(cc);//if multimode, set enabled febexCh
			if( ! lisa_settings::getIsFebexCh(cc) ) continue;//if multimode, skip disabled febexCh
															 //debug
															 //std::cout<<"cc = "<<cc<<", febexCh = "<<lisa_settings::getFebexCh()<<std::endl;

			resetTraces();
			getSingleTrace(tree);
			getCorrectTrace();
			getMWDTrace();
			getCFDTrace();
			calcEnergy();

			//***debug***//
			//std::cout<<"--->before get values"<<std::endl;
			//febex_data_temp.print();

			//save data to febex_data
			febex_data_temp.fentry = jentry;
			febex_data_temp.fenergy_raw = getMWDenergy();
			febex_data_temp.ftime_cfd = getCFDtime();
			febex_data_temp.flength = getFebexTraceL();
			febex_data_temp.fch = lisa_settings::getFebexCh();
			Double_t f_bias = 0;
			Double_t f_grad = 1;
			f_bias = lisa_settings::getEnergyCalib_Bias()[febex_data_temp.fch];
			f_grad = lisa_settings::getEnergyCalib_Grad()[febex_data_temp.fch];
			febex_data_temp.fenergy_cal = febex_data_temp.fenergy_raw*f_grad + f_bias;
			//Int_t *fCorr_x =(Int_t*) getRawTraceI();//return a pointer
			//Int_t *fCorr_y =(Int_t*) getRawTraceV();
			std::vector<float>fCorr_x =getCorrectTraceI();//return a pointer
			std::vector<float>fCorr_y =getCorrectTraceV();
			for(int ii=0;ii<febex_data_temp.flength;ii++){
				febex_data_temp.fCorrTrace_x.push_back(fCorr_x[ii]);//fCorr_x[ii];
				febex_data_temp.fCorrTrace_y.push_back(fCorr_y[ii]);//fCorr_y[ii];
			}
			//febex_data_temp.fCorrTrace_x = getCorrectTraceI();//return a pointer
			//febex_data_temp.fCorrTrace_y = getCorrectTraceV();
			febex_data_temp.fMWDTrace_x = getMWDTraceI();//return a vector
			febex_data_temp.fMWDTrace_y = getMWDTraceV();

			if(febex_data_temp.flength == 0)febex_data_temp.clear();//if empty
			setFebexData(febex_data_temp);//set febex_data

			v_febex_data_temp.push_back(febex_data_temp);//add to febex_data vector
			if( lisa_settings::getIsSaveAsRoot() )fillOptTree(febex_data_temp);//hit ++
			if( lisa_settings::getIsSingleChannelMode() )f_is_single_mode = 1;

		}//end of loop for 16 channels

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
		cnt++;//for debug
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
		if(jentry%1000==999){
			fduration = timer.RealTime();//
			fspeed = 1000.0/fduration;// [evt/sec]
			v_averageSpeed.push_back(fspeed);
		}
		double ftimeToGo = 0;
		if(getIsAllEntry()){
			if(jentry%1000==999)ftimeToGo = (fnentries-jentry)/fspeed;
		}else{
			if(jentry%1000==999)ftimeToGo = (getEntry()[1]-jentry)/fspeed;
		}

		if(jentry%1000==999)std::cout<<"*Current speed: "<<fspeed<<"[evt/s]; Duration for 1000 evts: "<<fduration<<", Num:"<<jentry<<"/"<<fnentries<<"  "<<ftimeToGo<<"s to go.";
		fflush(stdout);
		printf("\r");
	}//end of loop

	//save data to febex_data vector
	setFebexDataV(v_febex_data_temp);

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
	/*
	   std::cout<<"***  test output  ***"<<std::endl;
	   for(int ii=0;ii<v_febex_data_temp.size();ii++){
	   std::cout<<"***febex_data: Index = "<<ii<<" ***"<<std::endl;
	   std::cout<<"***febex_data.fenergy_raw***"<<v_febex_data_temp[ii].fenergy_raw<<std::endl;
	   std::cout<<"***febex_data.ftime_cfd***"<<v_febex_data_temp[ii].ftime_cfd<<std::endl;
	   }
	   */
}

void lisa_febex::resetTraces(){
	resetRawTraceV();
	resetRawTraceI();
	resetCorrectTraceV();
	resetCorrectTraceI();
	resetMWDTraceV();
	resetMWDTraceI();
	resetCFDTraceV();
	resetCFDTraceI();
}

void lisa_febex::initOptTree(){
	std::cout<<"***initOptTree***"<<std::endl;
	TFile *optfile = new TFile(lisa_settings::getOptRootFileName(),"RECREATE");
	TTree *optTree = new TTree("tree","tree");

	optTree->Branch("TRIGGER_c4",&TRIGGER_c4,"TRIGGER_c4/I");
	optTree->Branch("EVENTNO_c4",&EVENTNO_c4,"EVENTNO_c4/I");
	optTree->Branch("hit",&hit,"hit/i");
	optTree->Branch("febCh",febCh,"febCh[hit]/I");
	optTree->Branch("entry",&entry,"entry/I");
	optTree->Branch("entry_empty",entry_empty,"entry_empty[hit]/I");
	optTree->Branch("ts",runts,"runts[hit]/L");
	optTree->Branch("tsS",runts_S,"runts_S[hit]/L");
	optTree->Branch("Eraw",Eraw,"Eraw[hit]/D");
	optTree->Branch("Ecal",Ecal,"Ecal[hit]/D");
	optTree->Branch("T_cfd",T_cfd,"T_cfd[hit]/D");
	optTree->Branch("if_overflow",if_overflow,"if_overflow[hit]/i");
	optTree->Branch("traceLength",traceLength,"traceLength[hit]/i");
	optTree->Branch("tracesX",tracesX,"tracesX[hit][600]/D");//this has to be a specific value, MAX_TRACE_LENGTH is not allowed to use here.
	optTree->Branch("tracesY",tracesY,"tracesY[hit][600]/D");

	std::cout<<"--->init output root file."<<std::endl;
	setOptTree(optTree);
	setOptFile(optfile);
}

void lisa_febex::fillOptTree(febex_data &fopt){
	if( lisa_settings::getVerbose() ==3 )std::cout<<"***fillOptTree***"<<std::endl;

	TRIGGER_c4 = fopt.trigger;
	EVENTNO_c4 = fopt.evtno;

	if(fopt.flength==0)return;
	if(fopt.fenergy_raw < lisa_settings::getThresholdEnergy()[fopt.fch])return;
	febCh[hit] = fopt.fch;//0-15
	entry = fopt.fentry;
	entry_empty[hit] = fopt.fentry_empty;
	runts[hit] = fopt.fts;
	runts_S[hit] = fopt.fts%1000000000;
	Eraw[hit] = fopt.fenergy_raw;
	Ecal[hit] = fopt.fenergy_cal;
	T_cfd[hit] = fopt.ftime_cfd;
	if_overflow[hit] = fopt.foverflow;
	traceLength[hit] = fopt.flength;//
	if(lisa_settings::getVerbose() == 1)std::cout<<"test in saveasroot: "<<Eraw[hit]<<" "<<Ecal[hit]<<std::endl;
	if(lisa_settings::getIsSaveTraces()){
		for(int i=0;i<fopt.flength;i++){
			Int_t x,y;//for corrected traces
			x = fopt.fCorrTrace_x[i];
			y = fopt.fCorrTrace_y[i];
			tracesX[hit][i] = x;
			tracesY[hit][i] = y;
			if(lisa_settings::getVerbose() == 2)std::cout<<"in saveasroot: traceX = "<<tracesX[hit][i]<<" traceY = "<<tracesY[hit][i]<<std::endl;
		}
	}
	hit++;

}

void lisa_febex::clearOptTree(){
	if( lisa_settings::getVerbose() == 3 )std::cout<<"***clearOptTree***"<<std::endl;
	TRIGGER_c4 = 0; //UInt_t
	EVENTNO_c4 = 0; //UInt_t
	hit = 0;
	entry = -1;
	for(int ii=0;ii<16;ii++){
		febCh[ii] = -1;
		entry_empty[ii] = -1;
		runts[ii] = -1;
		runts_S[ii] = -1;
		Eraw[ii] = -1;
		Ecal[ii] = -1;
		T_cfd[ii] = -9999;
		if_overflow[ii] = 0; //0, no; 1, yes
		traceLength[ii] = 0;//UInt_t
		for(int jj=0;jj<MAX_TRACE_LENGTH;jj++){
			tracesX[ii][jj] = -1;
			tracesY[ii][jj] = -1;
		}
	}
}

void lisa_febex::closeOptRoot(){
	std::cout<<"***closeOptRoot***"<<std::endl;
	getOptTree()->Write("", TObject::kOverwrite);
	getOptFile()->Close();
	std::cout<<"******************************************"<<std::endl;
	std::cout<<"Data has been saved to "<<lisa_settings::getOptRootFileName()<<"."<<std::endl;
	std::cout<<"Root file has been closed."<<std::endl;

	std::cout<<"******************************************"<<std::endl;
}

