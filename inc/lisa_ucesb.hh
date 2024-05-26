//
//last updated@12 Apr,2024
//Z.Chen
//
//
//


#ifndef _LISAUCESB_HH_
#define _LISAUCESB_HH_

#include <TFile.h>
#include <TChain.h>
#include <TROOT.h>


class lisa_ucesb {
    public :

        lisa_ucesb();
        lisa_ucesb(TTree *tree);
        virtual ~lisa_ucesb();
        virtual void     Init(TTree *tree);
        virtual void setVerbose(Int_t verbose=0){fVerbose = verbose;};
        //virtual Int_t   getVerbose(){return fVerbose;}

        //***the following info should be in consistent with the unpacked data***//

        TTree          *fChain;   //!pointer to the analyzed TTree or TChain
        Int_t           fCurrent; //!current Tree number in a TChain

        // Declaration of leaf types
        UInt_t          TRIGGER;
        UInt_t          EVENTNO;
        UInt_t          lisa_ts_subsystem_id;
        UInt_t          lisa_ts_t1;
        UInt_t          lisa_ts_t2;
        UInt_t          lisa_ts_t3;
        UInt_t          lisa_ts_t4;
        UInt_t          lisa_data1event_trigger_time_hi;
        UInt_t          lisa_data1event_trigger_time_lo;
        UInt_t          lisa_data1hit_pattern;
        UInt_t          lisa_data1num_channels_fired;
        UInt_t          lisa_data1channel_id;
        UInt_t          lisa_data1channel_idI[4];   //[lisa_data1channel_id]
        UInt_t          lisa_data1channel_idv[4];   //[lisa_data1channel_id]
        UInt_t          lisa_data1channel_trigger_time_hi;
        UInt_t          lisa_data1channel_trigger_time_hiI[4];   //[lisa_data1channel_trigger_time_hi]
        UInt_t          lisa_data1channel_trigger_time_hiv[4];   //[lisa_data1channel_trigger_time_hi]
        UInt_t          lisa_data1channel_trigger_time_lo;
        UInt_t          lisa_data1channel_trigger_time_loI[4];   //[lisa_data1channel_trigger_time_lo]
        UInt_t          lisa_data1channel_trigger_time_lov[4];   //[lisa_data1channel_trigger_time_lo]
        UInt_t          lisa_data1pileup1;
        UInt_t          lisa_data1pileup2;
        UInt_t          lisa_data1pileup3;
        UInt_t          lisa_data1pileup4;
        UInt_t          lisa_data1pileup5;
        UInt_t          lisa_data1pileup6;
        UInt_t          lisa_data1pileup7;
        UInt_t          lisa_data1pileup8;
        UInt_t          lisa_data1pileup9;
        UInt_t          lisa_data1pileup10;
        UInt_t          lisa_data1pileup11;
        UInt_t          lisa_data1pileup12;
        UInt_t          lisa_data1pileup13;
        UInt_t          lisa_data1pileup14;
        UInt_t          lisa_data1pileup15;
        UInt_t          lisa_data1pileup16;
        UInt_t          lisa_data1overflow1;
        UInt_t          lisa_data1overflow2;
        UInt_t          lisa_data1overflow3;
        UInt_t          lisa_data1overflow4;
        UInt_t          lisa_data1overflow5;
        UInt_t          lisa_data1overflow6;
        UInt_t          lisa_data1overflow7;
        UInt_t          lisa_data1overflow8;
        UInt_t          lisa_data1overflow9;
        UInt_t          lisa_data1overflow10;
        UInt_t          lisa_data1overflow11;
        UInt_t          lisa_data1overflow12;
        UInt_t          lisa_data1overflow13;
        UInt_t          lisa_data1overflow14;
        UInt_t          lisa_data1overflow15;
        UInt_t          lisa_data1overflow16;
        UInt_t          lisa_data1channel_cfd;
        UInt_t          lisa_data1channel_cfdI[4];   //[lisa_data1channel_cfd]
        UInt_t          lisa_data1channel_cfdv[4];   //[lisa_data1channel_cfd]
        UInt_t          lisa_data1channel_energy;
        UInt_t          lisa_data1channel_energyI[4];   //[lisa_data1channel_energy]
        UInt_t          lisa_data1channel_energyv[4];   //[lisa_data1channel_energy]
                                                        //*** traces ***//												
        UInt_t          lisa_data1traces1;
        UInt_t          lisa_data1traces1I[8000];   //[lisa_data1traces1]
        UInt_t          lisa_data1traces1v[8000];   //[lisa_data1traces1]
        UInt_t          lisa_data1traces2;
        UInt_t          lisa_data1traces2I[8000];   //[lisa_data1traces2]
        UInt_t          lisa_data1traces2v[8000];   //[lisa_data1traces2]
        UInt_t          lisa_data1traces3;
        UInt_t          lisa_data1traces3I[8000];   //[lisa_data1traces3]
        UInt_t          lisa_data1traces3v[8000];   //[lisa_data1traces3]
        UInt_t          lisa_data1traces4;
        UInt_t          lisa_data1traces4I[8000];   //[lisa_data1traces4]
        UInt_t          lisa_data1traces4v[8000];   //[lisa_data1traces4]
        UInt_t          lisa_data1traces5;
        UInt_t          lisa_data1traces5I[8000];   //[lisa_data1traces5]
        UInt_t          lisa_data1traces5v[8000];   //[lisa_data1traces5]
        UInt_t          lisa_data1traces6;
        UInt_t          lisa_data1traces6I[8000];   //[lisa_data1traces6]
        UInt_t          lisa_data1traces6v[8000];   //[lisa_data1traces6]
        UInt_t          lisa_data1traces7;
        UInt_t          lisa_data1traces7I[8000];   //[lisa_data1traces7]
        UInt_t          lisa_data1traces7v[8000];   //[lisa_data1traces7]
        UInt_t          lisa_data1traces8;
        UInt_t          lisa_data1traces8I[8000];   //[lisa_data1traces8]
        UInt_t          lisa_data1traces8v[8000];   //[lisa_data1traces8]
        UInt_t          lisa_data1traces9;
        UInt_t          lisa_data1traces9I[8000];   //[lisa_data1traces9]
        UInt_t          lisa_data1traces9v[8000];   //[lisa_data1traces9]
        UInt_t          lisa_data1traces10;
        UInt_t          lisa_data1traces10I[8000];   //[lisa_data1traces10]
        UInt_t          lisa_data1traces10v[8000];   //[lisa_data1traces10]
        UInt_t          lisa_data1traces11;
        UInt_t          lisa_data1traces11I[8000];   //[lisa_data1traces11]
        UInt_t          lisa_data1traces11v[8000];   //[lisa_data1traces11]
        UInt_t          lisa_data1traces12;
        UInt_t          lisa_data1traces12I[8000];   //[lisa_data1traces12]
        UInt_t          lisa_data1traces12v[8000];   //[lisa_data1traces12]
        UInt_t          lisa_data1traces13;
        UInt_t          lisa_data1traces13I[8000];   //[lisa_data1traces13]
        UInt_t          lisa_data1traces13v[8000];   //[lisa_data1traces13]
        UInt_t          lisa_data1traces14;
        UInt_t          lisa_data1traces14I[8000];   //[lisa_data1traces14]
        UInt_t          lisa_data1traces14v[8000];   //[lisa_data1traces14]
        UInt_t          lisa_data1traces15;
        UInt_t          lisa_data1traces15I[8000];   //[lisa_data1traces15]
        UInt_t          lisa_data1traces15v[8000];   //[lisa_data1traces15]
        UInt_t          lisa_data1traces16;
        UInt_t          lisa_data1traces16I[8000];   //[lisa_data1traces16]
        UInt_t          lisa_data1traces16v[8000];   //[lisa_data1traces16]

        // List of branches
        TBranch        *b_TRIGGER;   //!
        TBranch        *b_EVENTNO;   //!
        TBranch        *b_lisa_ts_subsystem_id;   //!
        TBranch        *b_lisa_ts_t1;   //!
        TBranch        *b_lisa_ts_t2;   //!
        TBranch        *b_lisa_ts_t3;   //!
        TBranch        *b_lisa_ts_t4;   //!
        TBranch        *b_lisa_data1event_trigger_time_hi;   //!
        TBranch        *b_lisa_data1event_trigger_time_lo;   //!
        TBranch        *b_lisa_data1hit_pattern;   //!
        TBranch        *b_lisa_data1num_channels_fired;   //!
        TBranch        *b_lisa_data1channel_id;   //!
        TBranch        *b_lisa_data1channel_idI;   //!
        TBranch        *b_lisa_data1channel_idv;   //!
        TBranch        *b_lisa_data1channel_trigger_time_hi;   //!
        TBranch        *b_lisa_data1channel_trigger_time_hiI;   //!
        TBranch        *b_lisa_data1channel_trigger_time_hiv;   //!
        TBranch        *b_lisa_data1channel_trigger_time_lo;   //!
        TBranch        *b_lisa_data1channel_trigger_time_loI;   //!
        TBranch        *b_lisa_data1channel_trigger_time_lov;   //!
        TBranch        *b_lisa_data1pileup1;   //!
        TBranch        *b_lisa_data1pileup2;   //!
        TBranch        *b_lisa_data1pileup3;   //!
        TBranch        *b_lisa_data1pileup4;   //!
        TBranch        *b_lisa_data1pileup5;   //!
        TBranch        *b_lisa_data1pileup6;   //!
        TBranch        *b_lisa_data1pileup7;   //!
        TBranch        *b_lisa_data1pileup8;   //!
        TBranch        *b_lisa_data1pileup9;   //!
        TBranch        *b_lisa_data1pileup10;   //!
        TBranch        *b_lisa_data1pileup11;   //!
        TBranch        *b_lisa_data1pileup12;   //!
        TBranch        *b_lisa_data1pileup13;   //!
        TBranch        *b_lisa_data1pileup14;   //!
        TBranch        *b_lisa_data1pileup15;   //!
        TBranch        *b_lisa_data1pileup16;   //!
        TBranch        *b_lisa_data1overflow1;   //!
        TBranch        *b_lisa_data1overflow2;   //!
        TBranch        *b_lisa_data1overflow3;   //!
        TBranch        *b_lisa_data1overflow4;   //!
        TBranch        *b_lisa_data1overflow5;   //!
        TBranch        *b_lisa_data1overflow6;   //!
        TBranch        *b_lisa_data1overflow7;   //!
        TBranch        *b_lisa_data1overflow8;   //!
        TBranch        *b_lisa_data1overflow9;   //!
        TBranch        *b_lisa_data1overflow10;   //!
        TBranch        *b_lisa_data1overflow11;   //!
        TBranch        *b_lisa_data1overflow12;   //!
        TBranch        *b_lisa_data1overflow13;   //!
        TBranch        *b_lisa_data1overflow14;   //!
        TBranch        *b_lisa_data1overflow15;   //!
        TBranch        *b_lisa_data1overflow16;   //!
        TBranch        *b_lisa_data1channel_cfd;   //!
        TBranch        *b_lisa_data1channel_cfdI;   //!
        TBranch        *b_lisa_data1channel_cfdv;   //!
        TBranch        *b_lisa_data1channel_energy;   //!
        TBranch        *b_lisa_data1channel_energyI;   //!
        TBranch        *b_lisa_data1channel_energyv;   //!

        TBranch        *b_lisa_data1traces1;   //!
        TBranch        *b_lisa_data1traces1I;   //!
        TBranch        *b_lisa_data1traces1v;   //!
        TBranch        *b_lisa_data1traces2;   //!
        TBranch        *b_lisa_data1traces2I;   //!
        TBranch        *b_lisa_data1traces2v;   //!
        TBranch        *b_lisa_data1traces3;   //!
        TBranch        *b_lisa_data1traces3I;   //!
        TBranch        *b_lisa_data1traces3v;   //!
        TBranch        *b_lisa_data1traces4;   //!
        TBranch        *b_lisa_data1traces4I;   //!
        TBranch        *b_lisa_data1traces4v;   //!
        TBranch        *b_lisa_data1traces5;   //!
        TBranch        *b_lisa_data1traces5I;   //!
        TBranch        *b_lisa_data1traces5v;   //!
        TBranch        *b_lisa_data1traces6;   //!
        TBranch        *b_lisa_data1traces6I;   //!
        TBranch        *b_lisa_data1traces6v;   //!
        TBranch        *b_lisa_data1traces7;   //!
        TBranch        *b_lisa_data1traces7I;   //!
        TBranch        *b_lisa_data1traces7v;   //!
        TBranch        *b_lisa_data1traces8;   //!
        TBranch        *b_lisa_data1traces8I;   //!
        TBranch        *b_lisa_data1traces8v;   //!
        TBranch        *b_lisa_data1traces9;   //!
        TBranch        *b_lisa_data1traces9I;   //!
        TBranch        *b_lisa_data1traces9v;   //!
        TBranch        *b_lisa_data1traces10;   //!
        TBranch        *b_lisa_data1traces10I;   //!
        TBranch        *b_lisa_data1traces10v;   //!
        TBranch        *b_lisa_data1traces11;   //!
        TBranch        *b_lisa_data1traces11I;   //!
        TBranch        *b_lisa_data1traces11v;   //!
        TBranch        *b_lisa_data1traces12;   //!
        TBranch        *b_lisa_data1traces12I;   //!
        TBranch        *b_lisa_data1traces12v;   //!
        TBranch        *b_lisa_data1traces13;   //!
        TBranch        *b_lisa_data1traces13I;   //!
        TBranch        *b_lisa_data1traces13v;   //!
        TBranch        *b_lisa_data1traces14;   //!
        TBranch        *b_lisa_data1traces14I;   //!
        TBranch        *b_lisa_data1traces14v;   //!
        TBranch        *b_lisa_data1traces15;   //!
        TBranch        *b_lisa_data1traces15I;   //!
        TBranch        *b_lisa_data1traces15v;   //!
        TBranch        *b_lisa_data1traces16;   //!
        TBranch        *b_lisa_data1traces16I;   //!
        TBranch        *b_lisa_data1traces16v;   //!

        protected:
        Int_t fVerbose = 0;

        ClassDef(lisa_ucesb,4)
};
#endif
