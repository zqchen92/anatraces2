//
//last updated@01 May,2024
//Z.Chen
//


#include <TFile.h>
#include <TChain.h>
#include <TROOT.h>
#include <TApplication.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
//#include "./src/users/zchen.cc"
//#include "./src/lisa_OutputManager.cc"
//#include "./src/lisa_vis.cc"
//#include "./src/lisa_settings.cc"

#include "./inc/lisa_OutputManager.hh"
//#include "./inc/lisa_vis.hh"
//#include "./inc/lisa_settings.hh"



int main(int argc, char**argv){
//int anaTraces2(TString file1 = "./input/preLISA_1pF1M_241Am_Eris.root", TString file2 = "test3.root", TString file3 = "settings_Febex_export.set", TString func = "anaFebex4_traces"){


    TString file1 = "./input/preLISA_1pF1M_241Am_Eris.root";
    TString file2 = "test3.root";
    TString file3 = "settings_Febex_export.set";
    TString func = "anaFebex4_traces";
	Int_t func_convert = -1;

    if(argc<2){
        std::cout<<"argc = "<<argc<<std::endl;
        std::cout<<"argv = "<<argv[0]<<std::endl;
        std::cout<<"Usage: ./anaTraces2 -FLAG CONTENT -FLAG CONTENT ..."<<std::endl;
        return -1;
    }

    for(int i = 0;i<argc;i++){
        if(strcmp(argv[i],"-h")==0){
            std::cout<<"Usage: ./anaTraces2 -FLAG CONTENT -FLAG CONTENT ..."<<std::endl;
            return -1;
        }
        //input
        if(strcmp(argv[i],"-i")==0){
            file1 = argv[i+1];
        }
        //output
        if(strcmp(argv[i],"-o")==0){
            file2 = argv[i+1];
        }
        //setting
        if(strcmp(argv[i],"-s")==0){
            file3 = argv[i+1];
        }
        //command
        if(strcmp(argv[i],"-anaFebex4_checkSingleTrace")==0){
            func_convert = 0;
            func = argv[i];
        }
        if(strcmp(argv[i],"-anaFebex4_checkMWD")==0){
            func_convert = 1;
            func = argv[i];
        }
        if(strcmp(argv[i],"-anaFebex4_checkTraces")==0){
            func_convert = 2;
            func = argv[i];
        }
        if(strcmp(argv[i],"-anaFebex4_traces")==0){
            func_convert = 3;
            func = argv[i];
        }
        if(strcmp(argv[i],"-anaScope_checkSingleTrace")==0){
            func_convert = 4;
            func = argv[i];
        }
        if(strcmp(argv[i],"-anaScope_checkMWD")==0){
            func_convert = 5;
            func = argv[i];
        }
        if(strcmp(argv[i],"-anaScope_checkTraces")==0){
            func_convert = 6;
            func = argv[i];
        }
        if(strcmp(argv[i],"-anaScope_traces")==0){
            func_convert = 7;
            func = argv[i];
        }
    }

	std::cout<<"...oooOO0OOooo......oooOO0OOooo...... anaTraces ......oooOO0OOooo......oooOO0OOooo"<<std::endl;
	std::cout<<"---> input file = "<<file1<<std::endl;
	std::cout<<"---> output file = "<<file2<<std::endl;
	std::cout<<"---> setting file = "<<file3<<std::endl;
    std::cout<<"---> function = "<<func<<std::endl;
	std::cout<<"---> function convert = "<<func_convert<<std::endl;

	//***  set input/output here ******//
	TString iptFileName = file1;
	//TString iptFileName = "./input/tokyo_11dec_0089.root";
	TString optFileName = file2;

	TFile *iptfile;
	TTree *ipttree;
	lisa_optManager *ipt;
	//lisa_scope *iptscope;


	if(func_convert<4 && func_convert>=0){

		//...oooOO0OOooo...//
		iptfile = new TFile(iptFileName);
		ipttree = (TTree*)iptfile->Get("h101");

		ipt = new lisa_optManager(ipttree);
		std::cout<<"declared a new object of class zchen_ana"<<std::endl;


		ipt->Init(ipttree);
		std::cout<<"Init done"<<std::endl;

	}else{

		ipt = new lisa_optManager();
		//iptscope = new lisa_scope();
		//iptscope->setInputFilePathScope(iptFileName);
		//iptscope->loadSettings(file3);

	}

	ipt->loadSettings(file3);//from class lisa_settings
	std::cout<<"load settings done"<<std::endl;


	switch(func_convert){
		case 0:
			ipt->anaFebex4_checkSingleTrace(ipt);
			break;
		case 1:
			ipt->anaFebex4_checkMWD(ipt);
			break;
		case 2:
			ipt->anaFebex4_checkTraces(ipt);
			break;
		case 3:
			ipt->setOptRootFileName(optFileName);
			ipt->anaFebex4_traces(ipt);
			break;
		case 4:
			ipt->anaScope_checkSingleTrace(iptFileName,file3,optFileName);
			break;
		case 5:
			ipt->anaScope_checkMWD(iptFileName,file3,optFileName);
			break;
		case 6:
			ipt->anaScope_checkTraces(iptFileName,file3,optFileName);
			break;
		case 7:
			ipt->anaScope_traces(iptFileName,file3,optFileName);
			break;
		default:
			std::cout<<"--->Wrong function name"<<std::endl;
			break;
	}
	//...oooOO0OOooo...//
	return 0;
}

