//
//last updated@26 May,2024
//Z.Chen
//
//
//
#ifndef _LISAFEBEX_HH_
#define _LISAFEBEX_HH_

#include "lisa_ucesb.hh"
#include "lisa_settings.hh" //including lisa_Env.hh

#include <TFile.h>
#include <TChain.h>
#include <TROOT.h>
#include <TTree.h>
#include <vector>
#include <iostream>

class lisa_febex : public lisa_ucesb, public lisa_settings{

    public :

        //lisa_settings *fsettings;
        //lisa_ucesb *fucesb;
        lisa_febex();
        lisa_febex(TTree *tree);
        //lisa_febex(TTree *tree, lisa_settings *settings);
        virtual ~lisa_febex();

        //virtual void     loadSettings(lisa_settings *settings);//load settings
        virtual void     getSingleTrace(TTree *tree);//fill data to rawTrace_v and rawTrace_I
        virtual void     getCorrectTrace();//fill data to corrTrace_v and corrTrace_I
        virtual void     getMWDTrace();//fill data to MWDTrace_v and MWDTrace_I
        virtual void     getCFDTrace();//fill data to CFDTrace_v and CFDTrace_I and calculate CFD time
        virtual void     getTraces(TTree *tree);//analyze N traces
        virtual void     calcEnergy();//calculate MWD energy

        virtual void     resetTraces();//reset all traces

        virtual void     setTree(TTree *tree=0){febex_tree = tree;}
        virtual TTree*   getTree(){return febex_tree;}
        virtual void     setEvtNo(UInt_t evtno=0){febex_evtno = evtno;};
        virtual UInt_t   getEvtNo(){return febex_evtno;};
        virtual void     setTrigger(UInt_t trigger=0){febex_trigger = trigger;};
        virtual UInt_t   getTrigger(){return febex_trigger;};

        virtual void     setRawTraceV(std::vector<Int_t> &tr_v){this->rawTrace_v = tr_v;};
        virtual std::vector<Int_t>   getRawTraceV(){return rawTrace_v;};
        virtual void     resetRawTraceV(){rawTrace_v.clear();};
        virtual void     setRawTraceI(std::vector<Int_t> &tr_I){this->rawTrace_I = tr_I;};
        virtual std::vector<Int_t>   getRawTraceI(){return rawTrace_I;}
        virtual void     resetRawTraceI(){rawTrace_I.clear();};

        virtual void     setCorrectTraceV(std::vector<float> &tr_v){this->corrTrace_v = tr_v;};
        virtual std::vector<float>   getCorrectTraceV(){return corrTrace_v;};
        virtual void     resetCorrectTraceV(){corrTrace_v.clear();};
        virtual void     setCorrectTraceI(std::vector<float> &tr_I){this->corrTrace_I = tr_I;};
        virtual std::vector<float>   getCorrectTraceI(){return corrTrace_I;};
        virtual void     resetCorrectTraceI(){corrTrace_I.clear();}

        //***MWD trace***//
        virtual void     setMWDTraceV(std::vector<float> &tr_v){this->MWDTrace_v = tr_v;};
        virtual std::vector<float>   getMWDTraceV(){return MWDTrace_v;};
        virtual void     resetMWDTraceV(){MWDTrace_v.clear();}
        virtual void     setMWDTraceI(std::vector<float> &tr_I){this->MWDTrace_I = tr_I;};
        virtual std::vector<float>   getMWDTraceI(){return MWDTrace_I;}
        virtual void     resetMWDTraceI(){MWDTrace_I.clear();}
        virtual void     setMWDTraceLength(Int_t length=0){MWDLength = length;};
        virtual Int_t   getMWDTraceLength(){return MWDLength;}

        //***CFD trace***//
        virtual void     setCFDtime(Double_t time=0.0){CFDtime = time;};
        virtual Double_t getCFDtime(){return CFDtime;};
        virtual void     setCFDTraceV(std::vector<float> &tr_v){this->CFDTrace_v = tr_v;};
        virtual std::vector<float>   getCFDTraceV(){return CFDTrace_v;};
        virtual void     resetCFDTraceV(){CFDTrace_v.clear();}
        virtual void     setCFDTraceI(std::vector<float> &tr_I){this->CFDTrace_I = tr_I;};
        virtual std::vector<float>   getCFDTraceI(){return CFDTrace_I;}
        virtual void     resetCFDTraceI(){CFDTrace_I.clear();}
        virtual void     setCFDTraceLength(Int_t length=0){fCFDLength = length;};
        virtual Int_t   getCFDTraceLength(){return fCFDLength;}

        //***MWD energy***//
        virtual void     setMWDenergy(Double_t energy=0.0){fMWDenergy = energy;};
        virtual Double_t getMWDenergy(){return fMWDenergy;};

        //***febex data***//
        virtual void     setFebexData(febex_data &data){fdata = data;};
        virtual febex_data getFebexData(){return fdata;}
        virtual void     setFebexDataV(std::vector<febex_data> &data_v){fdata_v = data_v;};
        virtual std::vector<febex_data> getFebexDataV(){return fdata_v;}

        virtual void     resetVariables(){febex_evtno=0;febex_trigger=0;febex_tree=NULL;rawTrace_v.clear();rawTrace_I.clear();corrTrace_v.clear();corrTrace_I.clear(),MWDLength=0;MWDTrace_v.clear();MWDTrace_I.clear();fCFDLength=0;CFDtime = 0.0;CFDTrace_v.clear();CFDTrace_I.clear();fMWDenergy = 0.0;};//reset all variables

        //...oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...//
        //***                        Output                       ***//
        //...oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...//

        //export data to tree//
        virtual void   initOptTree();
        virtual void   fillOptTree(febex_data &fdata);
        virtual void   clearOptTree();
        virtual void   closeOptRoot();


        virtual void setOptTree(TTree *ftree=0){fOptTree = ftree;}
        virtual TTree* getOptTree(){return fOptTree;}
        virtual void setOptFile(TFile *ffile=0){fOptFile = ffile;}
        virtual TFile* getOptFile(){return fOptFile;}

        //output branches//
        UInt_t TRIGGER_c4; //copy from unpacked data
        UInt_t EVENTNO_c4; //copy of EVENTNO from unpacked data
        UInt_t hit;//max is 16
        Int_t febCh[16]; //0-15 
        Int_t entry;
        Int_t entry_empty[16];
        Long64_t runts[16];
        Long64_t runts_S[16];
        Double_t Eraw[16];
        Double_t Ecal[16];
        Double_t T_cfd[16]; //time determined by CFD
        UInt_t if_overflow[16]; //overflow; 0, no; 1 yes
        UInt_t traceLength[16];
        Double_t tracesX[16][MAX_TRACE_LENGTH];//MAX_TRACE_LENGTH, defined in lisa_Env.hh
        Double_t tracesY[16][MAX_TRACE_LENGTH];

    protected :

        //lisa_settings *fsettings;//settings
        UInt_t febex_evtno=0;//event number
        UInt_t febex_trigger=0;//trigger mode
        TTree *febex_tree=NULL;//tree

        //*** traces ***//
        std::vector<Int_t> rawTrace_v;//lisa_data_v;amplitude
        std::vector<Int_t> rawTrace_I;//lisa_data_I;time
        std::vector<float> corrTrace_v;//after baseline correction
        std::vector<float> corrTrace_I;//after baseline correction
        //Int_t *corrTrace_v=NULL;//after baseline correction
        //Int_t *corrTrace_I=NULL;//after baseline correction

        Int_t MWDLength=0;//size of array; used for TGraph

        //better to use vector instead of pointer to avoid e-310 issue.
        std::vector<float> MWDTrace_v;//y;trace after MWD
        std::vector<float> MWDTrace_I;//x;trace after MWD

        //***CFD time***//
        Int_t fCFDLength=0;//size of array; used for TGraph
        Double_t CFDtime = 0.0;
        std::vector<float> CFDTrace_v;//after CFD
        std::vector<float> CFDTrace_I;//after CFD

        //***MWD energy***//
        Double_t fMWDenergy = 0.0;

        //***febex_data***//
        febex_data fdata;//for single event
        std::vector<febex_data> fdata_v;//vector, for events

        //***output***//
        //export data to tree//
        TTree *fOptTree=NULL;//output tree
        TFile *fOptFile=NULL;//output file

        ClassDef(lisa_febex,0)
};
#endif
