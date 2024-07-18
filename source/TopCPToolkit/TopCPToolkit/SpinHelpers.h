namespace SpinHelpers
{

  float cos_theta_helicity(int sign, TLorentzVector top, TLorentzVector parent, const TLorentzVector &ttbar, TLorentzVector analyser)
  {

    TVector3 boost_to_ttbar = ttbar.BoostVector();
    boost_to_ttbar *= -1.;

    parent.Boost(boost_to_ttbar);
    top.Boost(boost_to_ttbar);
    analyser.Boost(boost_to_ttbar);

    TVector3 boost_to_parent = parent.BoostVector();
    boost_to_parent *= -1.;

    analyser.Boost(boost_to_parent);

    TVector3 k_vector = top.Vect().Unit();
    k_vector *= sign;
    float theta = analyser.Vect().Unit().Dot(k_vector);

    return theta;
  }

  float cos_theta_helicity_plus(TLorentzVector &top, TLorentzVector &tbar, const TLorentzVector &ttbar, TLorentzVector &top_analyser, TLorentzVector &tbar_analyser)
  {
    (void)tbar; // Marking tbar as unused
    (void)tbar_analyser; // Marking tbar_analyser as unused
    return cos_theta_helicity(1, top, top, ttbar, top_analyser);
  }

  float cos_theta_helicity_minus(TLorentzVector &top, TLorentzVector &tbar, const TLorentzVector &ttbar, TLorentzVector &top_analyser, TLorentzVector &tbar_analyser)
  {
    (void)top_analyser; // Marking top_analyser as unused
    return cos_theta_helicity(-1, top, tbar, ttbar, tbar_analyser);
  }

  float cos_theta_raxis(int sign, TLorentzVector top, TLorentzVector parent, const TLorentzVector &ttbar, TLorentzVector analyser)
  {

    TVector3 boost_to_ttbar = ttbar.BoostVector();
    boost_to_ttbar *= -1.;

    parent.Boost(boost_to_ttbar);
    top.Boost(boost_to_ttbar);
    analyser.Boost(boost_to_ttbar);

    TVector3 boost_to_parent = parent.BoostVector();
    boost_to_parent *= -1.;

    analyser.Boost(boost_to_parent);

    TVector3 k_vector = top.Vect().Unit();
    TVector3 p_vector(0., 0., 1.);

    float y = p_vector.Dot(k_vector);
    float r = pow((1. - y * y), 0.5);

    TVector3 r_vector = (1. / r) * (p_vector - y * k_vector);
    if (sign > 0)
    {
      // a axis
      if (y > 0)
        r_vector *= 1.;
      if (y < 0)
        r_vector *= -1.;
    }
    else if (sign < 0)
    {
      // b axis
      if (y > 0)
        r_vector *= -1.;
      if (y < 0)
        r_vector *= 1.;
    }

    float theta = analyser.Vect().Unit().Dot(r_vector.Unit()); // explicitly take a unit r_vector to make sure .Mag()==1

    return theta;
  }

  float cos_theta_raxis_plus(TLorentzVector &top, TLorentzVector &tbar, const TLorentzVector &ttbar, TLorentzVector &top_analyser, TLorentzVector &tbar_analyser)
  {
    (void)tbar; // Marking tbar as unused
    (void)tbar_analyser; // Marking tbar_analyser as unused
    return cos_theta_raxis(1, top, top, ttbar, top_analyser);
  }

  float cos_theta_raxis_minus(TLorentzVector &top, TLorentzVector &tbar, const TLorentzVector &ttbar, TLorentzVector &top_analyser, TLorentzVector &tbar_analyser)
  {
    (void)top_analyser; // Marking top_analyser as unused
    return cos_theta_raxis(-1, top, tbar, ttbar, tbar_analyser);
  }

  float cos_theta_transverse(int sign, TLorentzVector top, TLorentzVector parent, const TLorentzVector &ttbar, TLorentzVector analyser)
  {

    TVector3 boost_to_ttbar = ttbar.BoostVector();
    boost_to_ttbar *= -1.;

    parent.Boost(boost_to_ttbar);
    top.Boost(boost_to_ttbar);
    analyser.Boost(boost_to_ttbar);

    TVector3 boost_to_parent = parent.BoostVector();
    boost_to_parent *= -1.;

    analyser.Boost(boost_to_parent);

    TVector3 k_vector = top.Vect().Unit();
    TVector3 p_vector(0., 0., 1.);

    float y = p_vector.Dot(k_vector);
    float r = pow((1. - y * y), 0.5);

    TVector3 n_vector = (1. / r) * (p_vector.Cross(k_vector));
    if (sign > 0)
    {
      // a axis
      if (y > 0)
        n_vector *= 1.;
      if (y < 0)
        n_vector *= -1.;
    }
    else if (sign < 0)
    {
      // b axis
      if (y > 0)
        n_vector *= -1.;
      if (y < 0)
        n_vector *= 1.;
    }

    float theta = analyser.Vect().Unit().Dot(n_vector.Unit()); // explicitly take a unit n_vector to make sure .Mag()==1

    return theta;
  }

  float cos_theta_transverse_plus(TLorentzVector &top, TLorentzVector &tbar, const TLorentzVector &ttbar, TLorentzVector &top_analyser, TLorentzVector &tbar_analyser)
  {
    (void)tbar; // Marking tbar as unused
    (void)tbar_analyser; // Marking tbar_analyser as unused
    return cos_theta_transverse(1, top, top, ttbar, top_analyser);
  }

  float cos_theta_transverse_minus(TLorentzVector &top, TLorentzVector &tbar, const TLorentzVector &ttbar, TLorentzVector &top_analyser, TLorentzVector &tbar_analyser)
  {
    (void)top_analyser; // Marking top_analyser as unused
    return cos_theta_transverse(-1, top, tbar, ttbar, tbar_analyser);
  }

  float cos_phi(TLorentzVector top, TLorentzVector tbar, const TLorentzVector &ttbar, TLorentzVector top_analyser, TLorentzVector tbar_analyser)
  {

    TVector3 boost_to_ttbar = ttbar.BoostVector();
    boost_to_ttbar *= -1;

    top.Boost(boost_to_ttbar);
    tbar.Boost(boost_to_ttbar);
    top_analyser.Boost(boost_to_ttbar);
    tbar_analyser.Boost(boost_to_ttbar);

    TVector3 boost_to_top = top.BoostVector();
    boost_to_top *= -1;

    top_analyser.Boost(boost_to_top);

    TVector3 boost_to_tbar = tbar.BoostVector();
    boost_to_tbar *= -1;

    tbar_analyser.Boost(boost_to_tbar);

    float theta = top_analyser.Vect().Unit().Dot(tbar_analyser.Vect().Unit());

    return theta;
  }

} // namespace SpinHelpers
