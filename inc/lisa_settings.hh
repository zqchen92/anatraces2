//
//last updated@12 Apr,2024
//Z.Chen
//
//


#ifndef _LISA_SETTINGS_HH_
#define _LISA_SETTINGS_HH_

#include "lisa_Env.hh"
#include <TEnv.h>


class lisa_settings{
    public:
        lisa_settings();
        lisa_settings(TString name);
        virtual ~lisa_settings();
        virtual void loadSettings(TString name);
        virtual void setSettings(TString name="lisa_settings.set"){fSettingFile = name;}
        virtual void printSettings();//print settings

        //*** setter ***//
        virtual void setVerbose(Int_t verbose=1){fVerbose = verbose;}
        virtual void setInputFileName(TString path){fFebexDataFile = path;}//only for febex
        virtual void setInputFilePathScope(TString path){fScopeDataPath = path;}//only for scope data
        virtual void setNewSettingFile(TString name){fNewSettingFile = name;}
        virtual void setOptRootFileName(TString name){fOptRootFileName = name;}

        virtual void setIsAllEntry(bool flag){fIsAllEntryRead = flag;}
        virtual void setIsSingleChannelMode(bool flag){fIsSingleChMode = flag;}
        virtual void setIsMultiChannelMode(bool flag){fIsMultiChMode = flag;}
        virtual void setIsSubNoise(bool flag){fIsSubNoise = flag;}
        virtual void setIsIntegral(bool flag){fIsIntegral = flag;}
        virtual void setIsMWD(bool flag){fIsMWD = flag;}
        virtual void setIsBaselineCorr(bool flag){fIsBaselineCorr = flag;}
        virtual void setIsTimeCorr(bool flag){fIsTimeCorr = flag;}
        virtual void setIsSaveTraces(bool flag){fIsSaveTraces = flag;}
        virtual void setIsSaveAsRoot(bool flag){fIsSaveAsRoot = flag;}

        virtual void setIsGo4Unpacker(bool flag){fIsGo4Unpacker = flag;}
        virtual void setIsUcesbUnpacker(bool flag){fIsUcesbUnpacker = flag;}

        virtual void setSampleRate(Double_t rate){fSampleRate = rate;}
        virtual void setFebexTraceL(Int_t length){fFebexTraceL = length;}
        virtual void setRisingTime(Double_t time){fRisingTime = time;}
        virtual void setDecayTime(Double_t time){fDecaytime = time;}

        virtual void setEntries(Int_t entry1, Int_t entry2){fEntry[0] = entry1; fEntry[1] = entry2;}
        virtual void setJentry(Long64_t jentry){fJentry = jentry;}
        virtual void setJentryScope(Long64_t jentry){fJentryScope = jentry;}
        virtual void setFebexCh(UInt_t ch){fFebexCh = ch;}

        virtual void setIntergralWindow(Double_t win1, Double_t win2){fIntergralWindow[0] = win1; fIntergralWindow[1] = win2;}
        virtual void setTrapezSampleWindow(Int_t win1, Int_t win2){fTrapezSampleWindow[0] = win1; fTrapezSampleWindow[1] = win2;}
        virtual void setTrapezAmplitudeCalcWindow(Int_t win1, Int_t win2){fTrapezAmpCalcWindow[0] = win1; fTrapezAmpCalcWindow[1] = win2;}
        virtual void setTrapezMovingWindowLength(Int_t len){fTrapezMovingWindowLength = len;}

        virtual void setHistoNBins(Int_t nbins){fHistoNbins = nbins;}
        virtual void setEnergyHistRange(Int_t range1, Int_t range2){fEHisto[0] = range1; fEHisto[1] = range2;}
        virtual void setTimeHistRange(Int_t range1, Int_t range2){fTHisto[0] = range1; fTHisto[1] = range2;}
        virtual void setEnergySpecRange(Int_t range1, Int_t range2){fEnergySpecRange[0] = range1; fEnergySpecRange[1] = range2;}
        virtual void setTimeSpecRange(Int_t range1, Int_t range2){fTimeSpecRange[0] = range1; fTimeSpecRange[1] = range2;}
        virtual void setTraceAmpRange(Int_t range1, Int_t range2){fTraceAmpRange[0] = range1; fTraceAmpRange[1] = range2;}
        virtual void setCFDref(Double_t cfd){fCFDref = cfd;}
        virtual void setCFDfraction(Double_t cfd){fCFDFra = cfd;}
        virtual void setCFDdelay(Double_t cfd){fCFDdelay = cfd;}
        virtual void setCFDWindow(Int_t win1, Int_t win2){fCFDWindow[0] = win1; fCFDWindow[1] = win2;}

        virtual void setFitParLimit(double fval){fParLimit = fval;}

        //*** getter ***//
        virtual Int_t getVerbose(){return fVerbose;}
        virtual TString getInputFileName(){return fFebexDataFile;}
        virtual TString getNewSettingFile(){return fNewSettingFile;}
        virtual TString getOptRootFileName(){return fOptRootFileName;}
        virtual TString getInputFilePathScope(){return fScopeDataPath;}

        virtual bool getIsAllEntry(){return fIsAllEntryRead;}
        virtual bool getIsSingleChannelMode(){return fIsSingleChMode;}
        virtual bool getIsMultiChannelMode(){return fIsMultiChMode;}
        virtual bool getIsSubNoise(){return fIsSubNoise;}
        virtual bool getIsIntegral(){return fIsIntegral;}
        virtual bool getIsMWD(){return fIsMWD;}
        virtual bool getIsBaselineCorr(){return fIsBaselineCorr;}
        virtual bool getIsTimeCorr(){return fIsTimeCorr;}
        virtual bool getIsSaveTraces(){return fIsSaveTraces;}
        virtual bool getIsSaveAsRoot(){return fIsSaveAsRoot;}

        virtual bool getIsGo4Unpacker(){return fIsGo4Unpacker;}
        virtual bool getIsUcesbUnpacker(){return fIsUcesbUnpacker;}

        virtual Double_t getSampleRate(){return fSampleRate;}
        virtual Int_t getFebexTraceL(){return fFebexTraceL;}
        virtual Double_t getRisingTime(){return fRisingTime;}
        virtual Double_t getDecayTime(){return fDecaytime;}

        virtual Int_t *getEntry(){return fEntry;}
        virtual Int_t *getEntryScope(){return fEntryScope;}
        virtual Long64_t getJentry(){return fJentry;}
        virtual Int_t getJentryScope(){return fJentryScope;}
        virtual UInt_t getFebexCh(){return fFebexCh;}
        virtual bool getIsFebexCh(Int_t fch){return fMultiCh[fch];}

        virtual Double_t *getIntergralWindow(){return fIntergralWindow;}
        virtual Int_t *getTrapezSampleWindow(){return fTrapezSampleWindow;}
        virtual Int_t *getTrapezAmplitudeCalcWindow(){return fTrapezAmpCalcWindow;}
        virtual Int_t getTrapezMovingWindowLength(){return fTrapezMovingWindowLength;}

        virtual Int_t getHistoNBins(){return fHistoNbins;}
        virtual Int_t *getEnergyHistRange(){return fEHisto;}
        virtual Int_t *getTimeHistRange(){return fTHisto;}
        virtual Int_t *getEnergySpecRange(){return fEnergySpecRange;}
        virtual Int_t *getTimeSpecRange(){return fTimeSpecRange;}
        virtual Int_t *getTraceAmpRange(){return fTraceAmpRange;}
        virtual Double_t getCFDref(){return fCFDref;}
        virtual Double_t getCFDfraction(){return fCFDFra;}
        virtual Double_t getCFDdelay(){return fCFDdelay;}
        virtual Int_t *getCFDWindow(){return fCFDWindow;}

        virtual double getFitParLimit(){return fParLimit;}
        virtual Int_t *getThresholdEnergy(){return fThreshold;} 
        virtual Double_t *getEnergyCalib_Bias(){return fCalibPar_b;} 
        virtual Double_t *getEnergyCalib_Grad(){return fCalibPar_s;} 


    protected:
        //*** verbose ***//
        Int_t fVerbose = 0;//verbose

        //*** path and name ***//
        TString fFebexDataFile = "default";//febex data file
        TString fSettingFile = "default.set";//setting file
        TString fNewSettingFile = "default";//new setting file
        TString fOptRootFileName = "default.root";//output root file name
        TString fScopeDataPath = "default";//only for scope

        //*** functional switch ***//
        //*** enable and disable ***//
        bool fIsAllEntryRead = false;//all entry
        bool fIsSingleChMode = false;//single channel mode
        bool fIsMultiChMode = false;//multi channel mode
        bool fIsSubNoise = false;//substract noise
        bool fIsIntegral = false;//integral
        bool fIsMWD = false;//mwd
        bool fIsBaselineCorr = false;//baseline correction
        bool fIsTimeCorr = false;//time correction
        bool fIsSaveTraces = false;//save trace
        bool fIsSaveAsRoot = false;//save as root

        //*** unpacker ***//
        bool fIsGo4Unpacker = false;//go4 unpacker
        bool fIsUcesbUnpacker = false;//ucesb unpacker

        //*** details ***//
        Double_t fSampleRate = 100;//sample rate,[MHz]
        Int_t fFebexTraceL = 0;//febex trace length,[pts]
        Int_t fRisingTime = 100;//rising time,[ns]
        Double_t fDecaytime = 100;//decay time,[ns]

        Int_t fEntry[2] = {1,2};//entry number for Febex data
        Int_t fEntryScope[2] = {0,0};//entry number for scope
        Int_t fScopeSampleWindow[2] = {0,0};//scope sample window
        Long64_t fJentry = -1;//jentry under single mode
        Int_t fJentryScope = -1;//jentry under multi mode
        UInt_t fFebexCh = 0;//febex channel in single mode
        bool fMultiCh[16] = {0};//febex channel in multi mode
        Int_t fThreshold[16] = {0};//threshold in multi mode

        //*** MWD and CFD ***//
        Double_t fIntergralWindow[2] = {0.1,0.2};//energy integral window
        Int_t fTrapezSampleWindow[2] = {0,1};//trapezoid sample window
        Int_t fTrapezAmpCalcWindow[2] = {0,1};//trapezoid amplitude calculation window
        Int_t fTrapezMovingWindowLength = 0;//trapezoid moving window length
        Int_t fCFDWindow[2] = {0,1};//CFD zero point window

        //*** histogram and display ***//
        Int_t fHistoNbins = 1000;//histogram bins
        Int_t fEHisto[2] = {0,1};//range of histogram for energy spectrum; only for declaration
        Int_t fTHisto[2] = {0,1};//range of histogram for time spectrum; only for declaration
        Int_t fEnergySpecRange[2] = {0,1};//range of histogram for energy spectrum; only for display
        Int_t fTimeSpecRange[2] = {0,1};//range of histogram for time spectrum; only for display
        Int_t fTraceAmpRange[2] = {0,1};//range of TGraph for trace;
        Double_t fCFDwin[2] = {0.1,0.2};//CFD window
        Double_t fCFDref = 0;//CFD reference
        Double_t fCFDFra = 0;//fraction
        Double_t fCFDdelay = 0;//delay

        //*** calibration and fit ***//
        Double_t fParLimit = 1.0;//par limit for fitting
        Double_t fCalibPar_b[MAX_SIZE] = {0.};//calibration parameter; bias
        Double_t fCalibPar_s[MAX_SIZE] = {0.};//calibration parameters; gradient
        Double_t fmean[MAX_SIZE] = {0.};//mean
        Double_t fsigma[MAX_SIZE] = {0.};//sigma
        Double_t famp[MAX_SIZE] = {0.};//amplitude
        Double_t fEref[MAX_SIZE] = {0.};//reference energy
        Double_t fEres[MAX_SIZE] = {0.};//energy resolution

        ClassDef(lisa_settings,3)
};

#endif
