//
//last updated@09 Apr,2024
//Z.Chen
//***  for visualization  ***//
//
#ifndef _LISAVIS_HH_
#define _LISAVIS_HH_

#include "lisa_febex.hh"
#include "lisa_scope.hh"
//#include "lisa_Env.hh"

#include <iostream>
#include <vector>
#include <TCanvas.h>
#include <TGraph.h>


class lisa_vis : public lisa_febex{
    public :
        lisa_vis(lisa_febex *ffebex);
        lisa_vis();
        virtual ~lisa_vis();
        virtual TCanvas*     createCanvas(Int_t xx=1, Int_t yy=1);//create a x by y canvas
                                                                  //
        virtual void         showSingleRawTrace(lisa_febex *ffebex=0);//show raw trace
        virtual void         showSingleRawTrace(std::vector<Double_t> &tr_xx, std::vector<Double_t> &tr_yy);

        virtual void         showSingleCorrectTrace(lisa_febex *ffebex=0);//show CFD
        virtual void         showSingleCorrectTrace(std::vector<Double_t> &tr_xx, std::vector<Double_t> &tr_yy);

        virtual void         showMWDTrace(lisa_febex *ffebex=0);//show MWD trace
        virtual void         showMWDTrace2(lisa_febex *ffebex=0);//show MWD trace overlap with corrected trace
        virtual void         showMWDTrace(std::vector<Double_t> &tr_xx, std::vector<Double_t> &tr_yy);
        //virtual void         showMWDTrace2(std::vector<Double_t> &tr_xx, std::vector<Double_t> &tr_yy);

        virtual void         showCFDTrace(lisa_febex *ffebex=0);//show CFD trace
        virtual void         showCFDTrace2(lisa_febex *ffebex=0);//CFD trace overlap with corrected trace
        virtual void         showCFDTrace(std::vector<Double_t> &tr_xx, std::vector<Double_t> &tr_yy);
        //virtual void         showCFDTrace2(std::vector<Double_t> &tr_xx, std::vector<Double_t> &tr_yy);

        virtual void         anaFebex4_checkSingleTrace(lisa_febex *ffebex=0);//display corrected trace and CFD trace
        virtual void         anaFebex4_checkTraces(lisa_febex *ffebex=0);//analyze traces
        virtual void         checkMWD(lisa_febex *ffebex=0);//check MWD

        virtual void         anaScope_checkSingleTrace(lisa_scope *fscope);//display corrected trace and CFD trace
        virtual void         anaScope_checkTraces(lisa_scope *fscope);//analyze traces
        virtual void         checkMWD_Scope(lisa_scope *fscope);//check MWD
                                                            
        virtual void         setEnv();

        virtual void         setVisVerbose(Int_t vv=0){fverbose = vv;}
        virtual Int_t        getVisVerbose(){return fverbose;}
        virtual void         setVisJentry(ULong64_t jentry){fjentry = jentry;}
        virtual ULong64_t    getVisJentry(){return fjentry;}
        virtual void         setVisScope(lisa_scope *scope){this->fvisScope = scope;}
        virtual lisa_scope*  getVisScope(){return fvisScope;}

        virtual TGraph*      getGraph(std::vector<float> &fgr_x, std::vector<float> &fgr_y);//
        virtual TGraph*      getGraph(std::vector<Int_t> &fgr_x, std::vector<Int_t> &fgr_y);//
        virtual TGraph*      getGraph(std::vector<Double_t> &fgr_x, std::vector<Double_t> &fgr_y);//
                                                                                  

    private :
        Int_t fverbose;//vis verbose
        ULong64_t fjentry;//jentry
        lisa_scope *fvisScope = NULL;//vis scope

        ClassDef(lisa_vis,5)
};

#endif
