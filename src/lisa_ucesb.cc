//
//last updated@26 May,2024
//Z.Chen
//
//Error_ucesb_cc_xxx.
//
//
//


#include "../inc/lisa_ucesb.hh"
#include <iostream>

lisa_ucesb::~lisa_ucesb()
{

    std::cout << "lisa_ucesb::~lisa_ucesb()" << std::endl;
}

lisa_ucesb::lisa_ucesb()
{
    std::cout << "lisa_ucesb::lisa_ucesb()" << std::endl;
}

lisa_ucesb::lisa_ucesb(TTree *tree)
{
    Init(tree);
}

void lisa_ucesb::Init(TTree *tree)
{
    if (tree == NULL) {
        std::cout << "***Error_ucesb_cc_001:lisa_ucesb::Init(tree==0)" << std::endl;
        return;
    }

    tree->SetBranchAddress("TRIGGER", &TRIGGER, &b_TRIGGER);
    tree->SetBranchAddress("EVENTNO", &EVENTNO, &b_EVENTNO);
    tree->SetBranchAddress("lisa_ts_subsystem_id", &lisa_ts_subsystem_id, &b_lisa_ts_subsystem_id);
    tree->SetBranchAddress("lisa_ts_t1", &lisa_ts_t1, &b_lisa_ts_t1);
    tree->SetBranchAddress("lisa_ts_t2", &lisa_ts_t2, &b_lisa_ts_t2);
    tree->SetBranchAddress("lisa_ts_t3", &lisa_ts_t3, &b_lisa_ts_t3);
    tree->SetBranchAddress("lisa_ts_t4", &lisa_ts_t4, &b_lisa_ts_t4);
    tree->SetBranchAddress("lisa_data1event_trigger_time_hi", &lisa_data1event_trigger_time_hi, &b_lisa_data1event_trigger_time_hi);
    tree->SetBranchAddress("lisa_data1event_trigger_time_lo", &lisa_data1event_trigger_time_lo, &b_lisa_data1event_trigger_time_lo);
    tree->SetBranchAddress("lisa_data1hit_pattern", &lisa_data1hit_pattern, &b_lisa_data1hit_pattern);
    tree->SetBranchAddress("lisa_data1num_channels_fired", &lisa_data1num_channels_fired, &b_lisa_data1num_channels_fired);
    tree->SetBranchAddress("lisa_data1channel_id", &lisa_data1channel_id, &b_lisa_data1channel_id);
    tree->SetBranchAddress("lisa_data1channel_idI", lisa_data1channel_idI, &b_lisa_data1channel_idI);
    tree->SetBranchAddress("lisa_data1channel_idv", lisa_data1channel_idv, &b_lisa_data1channel_idv);
    tree->SetBranchAddress("lisa_data1channel_trigger_time_hi", &lisa_data1channel_trigger_time_hi, &b_lisa_data1channel_trigger_time_hi);
    tree->SetBranchAddress("lisa_data1channel_trigger_time_hiI", lisa_data1channel_trigger_time_hiI, &b_lisa_data1channel_trigger_time_hiI);
    tree->SetBranchAddress("lisa_data1channel_trigger_time_hiv", lisa_data1channel_trigger_time_hiv, &b_lisa_data1channel_trigger_time_hiv);
    tree->SetBranchAddress("lisa_data1channel_trigger_time_lo", &lisa_data1channel_trigger_time_lo, &b_lisa_data1channel_trigger_time_lo);
    tree->SetBranchAddress("lisa_data1channel_trigger_time_loI", lisa_data1channel_trigger_time_loI, &b_lisa_data1channel_trigger_time_loI);
    tree->SetBranchAddress("lisa_data1channel_trigger_time_lov", lisa_data1channel_trigger_time_lov, &b_lisa_data1channel_trigger_time_lov);
    tree->SetBranchAddress("lisa_data1pileup1", &lisa_data1pileup1, &b_lisa_data1pileup1);
    tree->SetBranchAddress("lisa_data1pileup2", &lisa_data1pileup2, &b_lisa_data1pileup2);
    tree->SetBranchAddress("lisa_data1pileup3", &lisa_data1pileup3, &b_lisa_data1pileup3);
    tree->SetBranchAddress("lisa_data1pileup4", &lisa_data1pileup4, &b_lisa_data1pileup4);
    tree->SetBranchAddress("lisa_data1pileup5", &lisa_data1pileup5, &b_lisa_data1pileup5);
    tree->SetBranchAddress("lisa_data1pileup6", &lisa_data1pileup6, &b_lisa_data1pileup6);
    tree->SetBranchAddress("lisa_data1pileup7", &lisa_data1pileup7, &b_lisa_data1pileup7);
    tree->SetBranchAddress("lisa_data1pileup8", &lisa_data1pileup8, &b_lisa_data1pileup8);
    tree->SetBranchAddress("lisa_data1pileup9", &lisa_data1pileup9, &b_lisa_data1pileup9);
    tree->SetBranchAddress("lisa_data1pileup10", &lisa_data1pileup10, &b_lisa_data1pileup10);
    tree->SetBranchAddress("lisa_data1pileup11", &lisa_data1pileup11, &b_lisa_data1pileup11);
    tree->SetBranchAddress("lisa_data1pileup12", &lisa_data1pileup12, &b_lisa_data1pileup12);
    tree->SetBranchAddress("lisa_data1pileup13", &lisa_data1pileup13, &b_lisa_data1pileup13);
    tree->SetBranchAddress("lisa_data1pileup14", &lisa_data1pileup14, &b_lisa_data1pileup14);
    tree->SetBranchAddress("lisa_data1pileup15", &lisa_data1pileup15, &b_lisa_data1pileup15);
    tree->SetBranchAddress("lisa_data1pileup16", &lisa_data1pileup16, &b_lisa_data1pileup16);
    tree->SetBranchAddress("lisa_data1overflow1", &lisa_data1overflow1, &b_lisa_data1overflow1);
    tree->SetBranchAddress("lisa_data1overflow2", &lisa_data1overflow2, &b_lisa_data1overflow2);
    tree->SetBranchAddress("lisa_data1overflow3", &lisa_data1overflow3, &b_lisa_data1overflow3);
    tree->SetBranchAddress("lisa_data1overflow4", &lisa_data1overflow4, &b_lisa_data1overflow4);
    tree->SetBranchAddress("lisa_data1overflow5", &lisa_data1overflow5, &b_lisa_data1overflow5);
    tree->SetBranchAddress("lisa_data1overflow6", &lisa_data1overflow6, &b_lisa_data1overflow6);
    tree->SetBranchAddress("lisa_data1overflow7", &lisa_data1overflow7, &b_lisa_data1overflow7);
    tree->SetBranchAddress("lisa_data1overflow8", &lisa_data1overflow8, &b_lisa_data1overflow8);
    tree->SetBranchAddress("lisa_data1overflow9", &lisa_data1overflow9, &b_lisa_data1overflow9);
    tree->SetBranchAddress("lisa_data1overflow10", &lisa_data1overflow10, &b_lisa_data1overflow10);
    tree->SetBranchAddress("lisa_data1overflow11", &lisa_data1overflow11, &b_lisa_data1overflow11);
    tree->SetBranchAddress("lisa_data1overflow12", &lisa_data1overflow12, &b_lisa_data1overflow12);
    tree->SetBranchAddress("lisa_data1overflow13", &lisa_data1overflow13, &b_lisa_data1overflow13);
    tree->SetBranchAddress("lisa_data1overflow14", &lisa_data1overflow14, &b_lisa_data1overflow14);
    tree->SetBranchAddress("lisa_data1overflow15", &lisa_data1overflow15, &b_lisa_data1overflow15);
    tree->SetBranchAddress("lisa_data1overflow16", &lisa_data1overflow16, &b_lisa_data1overflow16);
    tree->SetBranchAddress("lisa_data1channel_cfd", &lisa_data1channel_cfd, &b_lisa_data1channel_cfd);
    tree->SetBranchAddress("lisa_data1channel_cfdI", lisa_data1channel_cfdI, &b_lisa_data1channel_cfdI);
    tree->SetBranchAddress("lisa_data1channel_cfdv", lisa_data1channel_cfdv, &b_lisa_data1channel_cfdv);
    tree->SetBranchAddress("lisa_data1channel_energy", &lisa_data1channel_energy, &b_lisa_data1channel_energy);
    tree->SetBranchAddress("lisa_data1channel_energyI", lisa_data1channel_energyI, &b_lisa_data1channel_energyI);
    tree->SetBranchAddress("lisa_data1channel_energyv", lisa_data1channel_energyv, &b_lisa_data1channel_energyv);

    tree->SetBranchAddress("lisa_data1traces1", &lisa_data1traces1, &b_lisa_data1traces1);
    tree->SetBranchAddress("lisa_data1traces1I", lisa_data1traces1I, &b_lisa_data1traces1I);
    tree->SetBranchAddress("lisa_data1traces1v", lisa_data1traces1v, &b_lisa_data1traces1v);
    tree->SetBranchAddress("lisa_data1traces2", &lisa_data1traces2, &b_lisa_data1traces2);
    tree->SetBranchAddress("lisa_data1traces2I", lisa_data1traces2I, &b_lisa_data1traces2I);
    tree->SetBranchAddress("lisa_data1traces2v", lisa_data1traces2v, &b_lisa_data1traces2v);
    tree->SetBranchAddress("lisa_data1traces3", &lisa_data1traces3, &b_lisa_data1traces3);
    tree->SetBranchAddress("lisa_data1traces3I", lisa_data1traces3I, &b_lisa_data1traces3I);
    tree->SetBranchAddress("lisa_data1traces3v", lisa_data1traces3v, &b_lisa_data1traces3v);
    tree->SetBranchAddress("lisa_data1traces4", &lisa_data1traces4, &b_lisa_data1traces4);
    tree->SetBranchAddress("lisa_data1traces4I", lisa_data1traces4I, &b_lisa_data1traces4I);
    tree->SetBranchAddress("lisa_data1traces4v", lisa_data1traces4v, &b_lisa_data1traces4v);
    tree->SetBranchAddress("lisa_data1traces5", &lisa_data1traces5, &b_lisa_data1traces5);
    tree->SetBranchAddress("lisa_data1traces5I", lisa_data1traces5I, &b_lisa_data1traces5I);
    tree->SetBranchAddress("lisa_data1traces5v", lisa_data1traces5v, &b_lisa_data1traces5v);
    tree->SetBranchAddress("lisa_data1traces6", &lisa_data1traces6, &b_lisa_data1traces6);
    tree->SetBranchAddress("lisa_data1traces6I", lisa_data1traces6I, &b_lisa_data1traces6I);
    tree->SetBranchAddress("lisa_data1traces6v", lisa_data1traces6v, &b_lisa_data1traces6v);
    tree->SetBranchAddress("lisa_data1traces7", &lisa_data1traces7, &b_lisa_data1traces7);
    tree->SetBranchAddress("lisa_data1traces7I", lisa_data1traces7I, &b_lisa_data1traces7I);
    tree->SetBranchAddress("lisa_data1traces7v", lisa_data1traces7v, &b_lisa_data1traces7v);
    tree->SetBranchAddress("lisa_data1traces8", &lisa_data1traces8, &b_lisa_data1traces8);
    tree->SetBranchAddress("lisa_data1traces8I", lisa_data1traces8I, &b_lisa_data1traces8I);
    tree->SetBranchAddress("lisa_data1traces8v", lisa_data1traces8v, &b_lisa_data1traces8v);
    tree->SetBranchAddress("lisa_data1traces9", &lisa_data1traces9, &b_lisa_data1traces9);
    tree->SetBranchAddress("lisa_data1traces9I", lisa_data1traces9I, &b_lisa_data1traces9I);
    tree->SetBranchAddress("lisa_data1traces9v", lisa_data1traces9v, &b_lisa_data1traces9v);
    tree->SetBranchAddress("lisa_data1traces10", &lisa_data1traces10, &b_lisa_data1traces10);
    tree->SetBranchAddress("lisa_data1traces10I", lisa_data1traces10I, &b_lisa_data1traces10I);
    tree->SetBranchAddress("lisa_data1traces10v", lisa_data1traces10v, &b_lisa_data1traces10v);
    tree->SetBranchAddress("lisa_data1traces11", &lisa_data1traces11, &b_lisa_data1traces11);
    tree->SetBranchAddress("lisa_data1traces11I", lisa_data1traces11I, &b_lisa_data1traces11I);
    tree->SetBranchAddress("lisa_data1traces11v", lisa_data1traces11v, &b_lisa_data1traces11v);
    tree->SetBranchAddress("lisa_data1traces12", &lisa_data1traces12, &b_lisa_data1traces12);
    tree->SetBranchAddress("lisa_data1traces12I", lisa_data1traces12I, &b_lisa_data1traces12I);
    tree->SetBranchAddress("lisa_data1traces12v", lisa_data1traces12v, &b_lisa_data1traces12v);
    tree->SetBranchAddress("lisa_data1traces13", &lisa_data1traces13, &b_lisa_data1traces13);
    tree->SetBranchAddress("lisa_data1traces13I", lisa_data1traces13I, &b_lisa_data1traces13I);
    tree->SetBranchAddress("lisa_data1traces13v", lisa_data1traces13v, &b_lisa_data1traces13v);
    tree->SetBranchAddress("lisa_data1traces14", &lisa_data1traces14, &b_lisa_data1traces14);
    tree->SetBranchAddress("lisa_data1traces14I", lisa_data1traces14I, &b_lisa_data1traces14I);
    tree->SetBranchAddress("lisa_data1traces14v", lisa_data1traces14v, &b_lisa_data1traces14v);
    tree->SetBranchAddress("lisa_data1traces15", &lisa_data1traces15, &b_lisa_data1traces15);
    tree->SetBranchAddress("lisa_data1traces15I", lisa_data1traces15I, &b_lisa_data1traces15I);
    tree->SetBranchAddress("lisa_data1traces15v", lisa_data1traces15v, &b_lisa_data1traces15v);
    tree->SetBranchAddress("lisa_data1traces16", &lisa_data1traces16, &b_lisa_data1traces16);
    tree->SetBranchAddress("lisa_data1traces16I", lisa_data1traces16I, &b_lisa_data1traces16I);
    tree->SetBranchAddress("lisa_data1traces16v", lisa_data1traces16v, &b_lisa_data1traces16v);

    tree->SetBranchStatus("*",0);  // disable all branches
    tree->SetBranchStatus("TRIGGER",1);  // activate branchname
    tree->SetBranchStatus("EVENTNO",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces1",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces1I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces1v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces2",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces2I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces2v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces3",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces3I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces3v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces4",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces4I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces4v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces5",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces5I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces5v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces6",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces6I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces6v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces7",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces7I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces7v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces8",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces8I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces8v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces9",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces9I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces9v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces10",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces10I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces10v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces11",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces11I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces11v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces12",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces12I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces12v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces13",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces13I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces13v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces14",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces14I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces14v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces15",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces15I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces15v",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces16",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces16I",1);  // activate branchname
    tree->SetBranchStatus("lisa_data1traces16v",1);  // activate branchname

}

