#ifndef TOPNUFlLOWS_DILEPTON
#define TOPNUFlLOWS_DILEPTON

// Standard includes
#include <TLorentzVector.h>
#include <math.h>

#include <iostream>
#include <vector>
#include <numeric>

// Framework includes
#include <xAODEgamma/ElectronContainer.h>
#include <xAODJet/JetContainer.h>
#include <xAODMuon/MuonContainer.h>

// Parent class
#include "TopCPToolkit/ONNXWrapper.h"

namespace top {
class TopNuFlowsDilepton : public ONNXWrapper {
    using ONNXWrapper::ONNXWrapper;

   public:
    TopNuFlowsDilepton(const std::string &name, std::string model_even,
                       std::string model_odd);

    // Placeholder, simpler to use custon Sample method
    virtual StatusCode execute() { return StatusCode::SUCCESS; };

    // Does not return, sets the internal state
    virtual void Sample(ConstDataVector<xAOD::ElectronContainer> &electrons,
                        ConstDataVector<xAOD::MuonContainer> &muons,
                        ConstDataVector<xAOD::JetContainer> &jets, float met_mpx,
                        float met_mpy, float met_sumet, unsigned long long eventNumber);

    // The methods to set/return the values from the internal state
    virtual std::vector<float> GetSample();
    void setBtagger(std::string algorithm) { m_btagger = algorithm; };

    // Variable to work out which model to use
    unsigned m_model_idx;

    // Values to set during inference
    float m_nu_px;
    float m_nu_py;
    float m_nu_pz;
    float m_anti_nu_px;
    float m_anti_nu_py;
    float m_anti_nu_pz;
    float m_loglik;

    // Simple inline function for calculating the product of a vector
    template <typename T>
    T product(const std::vector<T> &v) {
        return std::accumulate(v.begin(), v.end(), 1, std::multiplies<T>());
    }


   protected:
    std::string m_btagger;
};

}  // namespace top

#endif
