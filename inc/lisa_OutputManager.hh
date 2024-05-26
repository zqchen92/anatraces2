//
//last updated@08 May,2024
//Z.Chen
//



#ifndef _LISA_OPTMANAGER_HH_
#define _LISA_OPTMANAGER_HH_

#include "lisa_febex.hh"

class lisa_optManager: public lisa_febex{
    public :
        lisa_optManager(TTree *tree);
        lisa_optManager();
        //lisa_optManager(TTree *tree=0, lisa_settings *settings=0);
        virtual ~lisa_optManager();
        virtual void     Show(lisa_febex *ipt);//for debug
        virtual void     Test(TTree *tree);//for debug
        virtual void     anaFebex4_checkSingleTrace(lisa_febex *ipt);//with visualization
        virtual void     anaFebex4_checkMWD(lisa_febex *ipt);//
        virtual void     anaFebex4_checkTraces(lisa_febex *ipt);//
        virtual void     anaFebex4_traces(lisa_febex *ipt);//without visualization

        virtual void     anaScope_checkSingleTrace(TString iptfilename, TString fname, TString optfile);//with visualization
        virtual void     anaScope_checkMWD(TString iptfilename, TString fname,TString optfile);//
        virtual void     anaScope_checkTraces(TString iptfilename, TString fname, TString optfile);//
        virtual void     anaScope_traces(TString iptfilename, TString fname, TString optfile);//without visualization

        ClassDef(lisa_optManager,1)
};



#endif
