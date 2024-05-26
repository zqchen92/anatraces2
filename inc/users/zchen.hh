//
//last updated@06 Apr,2024
//Z.Chen
//



#ifndef _ZCHEN_HH_
#define _ZCHEN_HH_

#include "../lisa_febex.hh"
#include "../lisa_settings.hh"

class zchen_ana: public lisa_febex{
    public :
        zchen_ana(TTree *tree);
        //zchen_ana(TTree *tree=0, lisa_settings *settings=0);
        virtual ~zchen_ana();
        virtual void     Show(lisa_febex *ipt);//for debug
        virtual void     Test(TTree *tree);//for debug
        virtual void     TestSingleTrace(lisa_febex *ipt);//for debug
        virtual void     TestCheckMWD(lisa_febex *ipt);//for debug
        virtual void     TestTraces(lisa_febex *ipt);//for debug
        virtual void     TestanaFebex4_checkTraces(lisa_febex *ipt);//for debug

};



#endif
