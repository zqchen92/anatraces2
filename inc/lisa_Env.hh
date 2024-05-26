//
//last updated @ 26 May,2024
//Z.Chen
//


#ifndef _LISAENV_HH_
#define _LISAENV_HH_


#include <vector>
#include <iostream>
#include "stdio.h"
#include <stdlib.h>
#include <Rtypes.h>
#include "TCanvas.h"

#define MHZ2NS 1e3//MHz to 1ns
#define MAX_SIZE 16 //maximum number of febex channel
#define MAX_TRACE_LENGTH 600 //maximum number of trace length

//UInt_t gVerbose = 1;
extern std::vector<TCanvas*> gVisCanvas;
extern UInt_t gVisCanvasCNT;

struct febex_data {
    //***declare***//
    UInt_t trigger;
    UInt_t evtno;
    int fch;
    int fentry;
    int fentry_empty;
    Long64_t fts;
    Double_t fenergy_raw;
    Double_t fenergy_cal;
    Double_t ftime_cfd;
    UInt_t foverflow;
    UInt_t flength;

    //meet some issues when using pointer: the address of pointer is not changed when filling a vector on an event-by-event base. Finally, only the last valid event could be saved in the vector.
    //Int_t* fCorrTrace_x;//corrected trace
    //Int_t* fCorrTrace_y;//corrected trace
    std::vector<float> fCorrTrace_x;//corrected trace
    std::vector<float> fCorrTrace_y;//corrected trace
    std::vector<float> fMWDTrace_x;//MWD trace
    std::vector<float> fMWDTrace_y;//MWD trace

    //vector<Double_t>fCFDtime;
    //vector<Double_t>fMWDenergy;

    //***init***//
    febex_data():trigger(0),evtno(0),fch(-1),fentry(-1),fentry_empty(-1),fts(-1),fenergy_raw(-1),fenergy_cal(-1),ftime_cfd(-9999),foverflow(0),flength(0){}

    //***clear***//
    void clear(){
        trigger = 0;
        evtno = 0;
        fch = -1;
        fentry = -1;
        fentry_empty = -1;
        fts = -1;
        fenergy_raw = -1;
        fenergy_cal = -1;
        ftime_cfd = -9999;
        foverflow = 0;
        flength = 0;
        fCorrTrace_x.clear();
        fCorrTrace_y.clear();
        fMWDTrace_x.clear();
        fMWDTrace_y.clear();
        //fCFDtime.clear();
        //fMWDenergy.clear();
    }

    //***print info***//
    void print(){
        std::cout<<"trigger = "<<trigger<<std::endl;
        std::cout<<"evtno = "<<evtno<<std::endl;
        std::cout<<"fch = "<<fch<<std::endl;
        std::cout<<"fentry = "<<fentry<<std::endl;
        std::cout<<"fentry_empty = "<<fentry_empty<<std::endl;
        std::cout<<"fts = "<<fts<<std::endl;
        std::cout<<"fenergy_raw = "<<fenergy_raw<<std::endl;
        std::cout<<"fenergy_cal = "<<fenergy_cal<<std::endl;
        std::cout<<"ftime_cfd = "<<ftime_cfd<<std::endl;
        std::cout<<"foverflow = "<<foverflow<<std::endl;
        std::cout<<"flength = "<<flength<<std::endl;
        std::cout<<"fCorrTrace_x.size() = "<<fCorrTrace_x.size()<<std::endl;
        std::cout<<"fCorrTrace_y.size() = "<<fCorrTrace_y.size()<<std::endl;
        std::cout<<"fMWDTrace_x.size() = "<<fMWDTrace_x.size()<<std::endl;
        std::cout<<"fMWDTrace_y.size() = "<<fMWDTrace_y.size()<<std::endl;
        //std::cout<<"fCFDtime.size() = "<<fCFDtime.size()<<std::endl;
        //std::cout<<"fMWDenergy.size() = "<<fMWDenergy.size()<<std::endl;
    }
};


struct scope_data {

    ULong64_t fentry;
    Double_t fenergy_raw;
    Double_t fenergy_cal;
    Double_t ftime_cfd;
    Int_t flength;
    //ULong64_t ftimestamp;

    std::vector<Double_t> fCorrTrace_x;//corrected trace
    std::vector<Double_t> fCorrTrace_y;//corrected trace
    std::vector<Double_t> fMWDTrace_x;//MWD trace
    std::vector<Double_t> fMWDTrace_y;//MWD trace

    //init
    scope_data():fentry(0),fenergy_raw(-1),fenergy_cal(-1),ftime_cfd(-9999),flength(0){}

    //clear
    void clear(){
        fentry = 0;
        fenergy_raw = -1;
        fenergy_cal = -1;
        ftime_cfd = -1;
        flength = 0;
        //ftimestamp = 0;
        fCorrTrace_x.clear();
        fCorrTrace_y.clear();
        fMWDTrace_x.clear();
        fMWDTrace_y.clear();
    }

    void print(){
        std::cout<<"fentry = "<<fentry<<std::endl;
        std::cout<<"fenergy_raw = "<<fenergy_raw<<std::endl;
        std::cout<<"fenergy_cal = "<<fenergy_cal<<std::endl;
        std::cout<<"ftime_cfd = "<<ftime_cfd<<std::endl;
        std::cout<<"flength = "<<flength<<std::endl;
        //std::cout<<"ftimestamp = "<<ftimestamp<<std::endl;
        std::cout<<"fCorrTrace_x.size() = "<<fCorrTrace_x.size()<<std::endl;
        std::cout<<"fCorrTrace_y.size() = "<<fCorrTrace_y.size()<<std::endl;
        std::cout<<"fMWDTrace_x.size() = "<<fMWDTrace_x.size()<<std::endl;
        std::cout<<"fMWDTrace_y.size() = "<<fMWDTrace_y.size()<<std::endl;
    }

};

#endif
