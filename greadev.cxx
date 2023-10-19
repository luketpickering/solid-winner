#include "Framework/EventGen/EventRecord.h"
#include "Framework/GHEP/GHepParticle.h"
#include "Framework/GHEP/GHepRecord.h"
#include "Framework/GHEP/GHepUtils.h"
#include "Framework/Ntuple/NtpMCEventRecord.h"

#include "TFile.h"
#include "TTree.h"

#include <iostream>

int main(int argc, char const *argv[]) {

  TFile *fin = TFile::Open(argv[1]);
  if (!fin) {
    std::cout << "[ERROR]: Couldn't read file: " << argv[1] << std::endl;
    return 1;
  }
  TTree *gtree = fin->Get<TTree>("gtree");
  if (!gtree) {
    std::cout << "[ERROR]: Couldn't read gtree from file: " << argv[1]
              << std::endl;
    return 1;
  }

  genie::NtpMCEventRecord *gntpl = nullptr;
  gtree->SetBranchAddress("gmcrec", &gntpl);

  Long64_t ents = gtree->GetEntries();

  // loop through the events
  for (Long64_t e_it = 0; e_it < ents; ++e_it) {
    gtree->GetEntry(e_it);
    genie::GHepRecord *ghep = static_cast<genie::GHepRecord *>(gntpl->event);

    std::cout << "Ent: " << e_it << std::endl;
    TObjArrayIter part_iter(ghep);
    // loop through the particle stack
    size_t p_it = 0;
    genie::GHepParticle *part = nullptr;
    while ((part = static_cast<genie::GHepParticle *>((part_iter).Next()))) {

      switch (part->Status()) {
      case genie::kIStInitialState: {
        std::cout << "\tP[" << p_it << "] Initial State, pid = " << part->Pdg()
                  << ", p = (" << part->Px() << ", " << part->Py() << ", "
                  << part->Pz() << ", " << part->E() << ") GeV" << std::endl;
      }
      case genie::kIStStableFinalState: {
        std::cout << "\tP[" << p_it << "] Final State, pid = " << part->Pdg()
                  << ", p = (" << part->Px() << ", " << part->Py() << ", "
                  << part->Pz() << ", " << part->E() << ") GeV" << std::endl;
      }
      default: {
        // some internal state
      }
      }

      p_it++;
    }
  }
}