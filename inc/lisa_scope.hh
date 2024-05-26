//
//last updated@12 May,2024
//Z.Chen
//
//
//
//

#ifndef _LISA_SCOPE_HH_
#define _LISA_SCOPE_HH_

//#include "lisa_Env.hh"  //global variable
#include "lisa_settings.hh"

#include <TFile.h>
#include <TChain.h>
#include <TROOT.h>
#include <TTree.h>
#include <vector>
#include <iostream>

class lisa_scope: public lisa_settings {

    public :

        lisa_scope();
        virtual ~lisa_scope();

        virtual void    getSingleScopeTrace();
        virtual void    getCorrectScopeTrace();
        virtual void    getMWDScopeTrace();
        virtual void    getCFDScopeTrace();
        virtual void    calcEnergy();

        virtual void    getScopeTraces();

        //virtual void    resetScopeTraces();

        //***setter***//
        virtual void     setScopeTraceV(std::vector<Double_t> &tr_v){this->scopeTrace_v = tr_v;};
        virtual void     setScopeTraceI(std::vector<Double_t> &tr_I){this->scopeTrace_I = tr_I;};

        virtual void     setScopeTraceLength(Int_t len){this->fScopeTraceLength = len;}
        virtual void     setMWDLength(Int_t len){this->fMWDLength = len;}
        virtual void     setScopeTraceV_corr(std::vector<Double_t> &tr_v){this->scopeTrace_v_corr = tr_v;};
        virtual void     setScopeTraceI_corr(std::vector<Double_t> &tr_I){this->scopeTrace_I_corr = tr_I;};

        virtual void     setScopeTraceV_mwd(std::vector<Double_t> &tr_v){this->scopeTrace_v_mwd = tr_v;};
        virtual void     setScopeTraceI_mwd(std::vector<Double_t> &tr_I){this->scopeTrace_I_mwd = tr_I;};

        virtual void     setScopeTraceV_cfd(std::vector<Double_t> &tr_v){this->scopeTrace_v_cfd = tr_v;};
        virtual void     setScopeTraceI_cfd(std::vector<Double_t> &tr_I){this->scopeTrace_I_cfd = tr_I;};
        virtual void     setScopeEnergy_mwd(Double_t e){scopeEnergy_mwd = e;};
        virtual void     setScopeTime_cfd(Double_t t){scopeTime_cfd = t;}

        //***getter***//
        virtual std::vector<Double_t>   getScopeTraceV(){return scopeTrace_v;};
        virtual std::vector<Double_t>   getScopeTraceI(){return scopeTrace_I;}

        virtual std::vector<Double_t>   getScopeTraceV_corr(){return scopeTrace_v_corr;};
        virtual std::vector<Double_t>   getScopeTraceI_corr(){return scopeTrace_I_corr;}

        virtual std::vector<Double_t>   getScopeTraceV_mwd(){return scopeTrace_v_mwd;};
        virtual std::vector<Double_t>   getScopeTraceI_mwd(){return scopeTrace_I_mwd;}

        virtual std::vector<Double_t>   getScopeTraceV_cfd(){return scopeTrace_v_cfd;};
        virtual std::vector<Double_t>   getScopeTraceI_cfd(){return scopeTrace_I_cfd;};
        virtual Double_t          getScopeEnergy_mwd(){return scopeEnergy_mwd;};
        virtual Double_t          getScopeTime_cfd(){return scopeTime_cfd;}

        virtual Int_t             getScopeTraceLength(){return fScopeTraceLength;}
        virtual Int_t             getMWDLength(){return fMWDLength;}

        // scope data //
        virtual void setScopeData(scope_data &data){fScopeData = data;}

        virtual scope_data getScopeData(){return fScopeData;}
        virtual void setScopeDataV( std::vector<scope_data> &data_v  ) { fScopeData_v = data_v; }
        virtual std::vector<scope_data> getScopeDataV() { return fScopeData_v; }

        virtual void resetVariables(){scopeTrace_v.clear();scopeTrace_I.clear();scopeTrace_v_corr.clear();scopeTrace_I_corr.clear();scopeTrace_v_mwd.clear();scopeTrace_I_mwd.clear();scopeTrace_v_cfd.clear();scopeTrace_I_cfd.clear();scopeEnergy_mwd = -1;scopeTime_cfd = -1;fScopeTraceLength = 0;fMWDLength = 0;};

        //...oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...//
        //***                        Output                       ***//
        //...oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...oooOO0OOooo...//

        //export data to tree//
        virtual void   initOptTree();
        virtual void   fillOptTree(scope_data &fdata);
        virtual void   clearOptTree();
        virtual void   closeOptRoot();


        virtual void setOptTree(TTree *ftree=0){fOptTree = ftree;}
        virtual TTree* getOptTree(){return fOptTree;}
        virtual void setOptFile(TFile *ffile=0){fOptFile = ffile;}
        virtual TFile* getOptFile(){return fOptFile;}

        //output branches//
        Int_t entry;
        Double_t Eraw;
        Double_t Ecal;
        Double_t T_cfd; //time determined by CFD
        UInt_t traceLength;
        Double_t tracesX[40000];//
        Double_t tracesY[40000];

    protected :


        std::vector<Double_t> scopeTrace_v;
        std::vector<Double_t> scopeTrace_I;

        std::vector<Double_t> scopeTrace_v_corr;
        std::vector<Double_t> scopeTrace_I_corr;

        std::vector<Double_t> scopeTrace_v_mwd;
        std::vector<Double_t> scopeTrace_I_mwd;

        std::vector<Double_t> scopeTrace_v_cfd;
        std::vector<Double_t> scopeTrace_I_cfd;

        Int_t fScopeTraceLength = 0;
        Int_t fMWDLength = 0;
        Double_t scopeEnergy_mwd = -1;
        Double_t scopeTime_cfd = -1;

        //scope data
        scope_data fScopeData;
        std::vector<scope_data> fScopeData_v;

        //***output***//
        //export data to tree//
        TTree *fOptTree=NULL;//output tree
        TFile *fOptFile=NULL;//output file

        ClassDef(lisa_scope,2)

};



#endif
