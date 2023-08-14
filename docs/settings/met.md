## [makeMetAnalysisConfig](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/PhysicsAnalysis/Algorithms/MetAnalysisAlgorithms/python/MetAnalysisConfig.py)

`seq`
:   the config sequence.

`containerName`
:   the name of the output container after calibration.

`postfix`
:   a postfix to apply to decorations and algorithm names. Typically not needed here.

`useFJVT`
:   use the forward JVT decision in the calculation. The default is `False`.

`treatPUJets`
: whether to treat pile-up jets in the MET significance calculation. The default is `False`.

`jets`
: the input jet container.

`electrons`
: the input electron container.

`muons`
: the input muon container.

`photons`
: the input photon container.

`taus`
: the input tau container.

!!! note
    Defining a jet container is mandatory, but all other input containers are optional.

!!! success "Registers the following variables:"
    - `met`: the transverse missing energy $E_\mathrm{T}$
    - `phi`: the transverse missing energy $\phi$
    - `sumet`: the sum of all visible transverse missing momentum

!!! abstract "MET definitions"
    - `mpx`: $p_{x,\mathrm{miss}} = - \sum p_x$
    - `mpy`: $p_{y,\mathrm{miss}} = - \sum p_y$
    - `met`: $p_{\mathrm{T},\mathrm{miss}} = \sqrt{p_{x,\mathrm{miss}}^2+p_{y,\mathrm{miss}}^2}$
    - `sumet`: $\Sigma E_{\mathrm{T}} = \sum p_{\mathrm{T}}$
