*The FAQ will be filled progressively as user questions come in!*

??? question "Where can I ask questions about the code?"
    Check out the relevant [contact points](/#get-in-touch).

??? question "Who came up with the name 'TopCPToolkit'?"
    Our good friend ChatGPT :upside_down:. And DALL-E is responsible for the avatar of the project on GitLab.

??? question "How do I enable debugging printouts?"
    All algorithms and tools inherit the `OutputLevel` property, which you can set to 0 (info), 1 (verbose) or 2 (debug). See also [`MsgLevel`](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/Control/AthToolSupport/AsgMessaging/Root/MsgLevel.cxx).

    For an algorithm config in python, you can do something like
    ```python
    myAlgo = config.createAlgorithm( 'CP::SomethingAlg', 'someName' )
    myAlgo.OutputLevel = 2 # sets to DEBUG
    ```
    and `myAlgo` will printout messages wrapped with `ATH_MSG_DEBUG`. Any tool declared by `CP::SomethingAlg` can inherit the current message level (and therefore be driven entirely in python), by setting the corresponding property (in the C++ code):
    ```cpp
        ATH_CHECK( tool->setProperty("OutputLevel", msg().level()) );
    ```
    (or equivalently for our purposes, `ANA_CHECK`).