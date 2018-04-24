#include "CATTools/CatAnalyzer/interface/TopTriggerSF.h"
#include "CATTools/DataFormats/interface/Electron.h"
#include "CATTools/CommonTools/interface/TTbarModeDefs.h"
#include <cmath>

// Scale factors from AN2015/309 (OLD)
// Scale factors from AN2016/392_v3 (Update)
double computeTrigSF(const cat::Lepton& lep1, const cat::Lepton& lep2, int direction)
{
  const int sumId = std::abs(lep1.pdgId()) + std::abs(lep2.pdgId());
  const int channel = sumId == 11+11 ? cat::CH_ELEL : sumId == 13+13 ? cat::CH_MUMU : cat::CH_MUEL;

  auto getEta = [](const cat::Lepton& lep)->double {
    if ( std::abs(lep.pdgId()) == 11 ) return dynamic_cast<const cat::Electron&>(lep).scEta();
    return lep.eta();
  };
  const double aeta1 = std::abs(getEta(lep1));
  const double aeta2 = std::abs(getEta(lep2));

  if ( channel == cat::CH_ELEL ) {
    if ( aeta1 < 1.2 ) {
      if      ( aeta2 < 1.2 ) return 0.990 + direction*0.002;
      else if ( aeta2 < 2.4 ) return 0.990 + 0.5*direction*0.003;
    }
    else if ( aeta1 < 2.4 ) {
      if      ( aeta2 < 1.2 ) return 0.995 + 0.5*direction*0.003;
      else if ( aeta2 < 2.4 ) return 0.979 - direction*0.007;
    }
  }
  else if ( channel == cat::CH_MUMU ) {
    if ( aeta1 < 1.2 ) {
      if      ( aeta2 < 1.2 ) return 0.991 + direction*0.001;
      else if ( aeta2 < 2.4 ) return 0.990 + 0.5*direction*0.003;
    }
    else if ( aeta1 < 2.4 ) {
      if      ( aeta2 < 1.2 ) return 0.995 + 0.5*direction*0.003;
      else if ( aeta2 < 2.4 ) return 0.987 - direction*0.003;
    }
  }
  else if ( channel == cat::CH_MUEL ) {
    if ( aeta1 < 1.2 ) {
      if      ( aeta2 < 1.2 ) return 0.996 + direction*0.001;
      else if ( aeta2 < 2.4 ) return 0.999 + 0.5*direction*0.003;
    }
    else if ( aeta1 < 2.4 ) {
      if      ( aeta2 < 1.2 ) return 0.995 + 0.5*direction*0.003;
      else if ( aeta2 < 2.4 ) return 0.990 - direction*0.006;
    }
  }

  return 1;
};

// Scale factors are from AN16-025 (v4) http://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2016_025_v4.pdf
// Scale factors are from AN2016/392_v3 (Update) page No.5
double computeTrigSFInclusive(const cat::Lepton& lep1, const cat::Lepton& lep2, int direction)
{
  const int sumId = std::abs(lep1.pdgId()) + std::abs(lep2.pdgId());
  const int channel = sumId == 11+11 ? cat::CH_ELEL : sumId == 13+13 ? cat::CH_MUMU : cat::CH_MUEL;

  if      ( channel == cat::CH_ELEL ) return 0.996 + direction*0.001;
  else if ( channel == cat::CH_MUMU ) return 0.990 + direction*0.001;
  else if ( channel == cat::CH_MUEL ) return 0.996 + direction*0.001;

  return 1;
}


