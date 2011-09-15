//
// ---------- header ----------------------------------------------------------
//
// project       nucleus
//
// license       infinit
//
// author        julien quintard   [sun apr  4 14:38:46 2010]
//

#ifndef NUCLEUS_NEUTRON_ROLE_HH
#define NUCLEUS_NEUTRON_ROLE_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

namespace nucleus
{
  namespace neutron
  {

//
// ---------- types -----------------------------------------------------------
//

    ///
    /// this defines the type that is used to represent which role
    /// a user can play on an object.
    ///
    typedef elle::Natural8		Role;

//
// ---------- constants -------------------------------------------------------
//

    ///
    /// these are the role constants.
    ///
    const Role				RoleUnknown = 0x0;
    const Role				RoleOwner = 0x1;
    const Role				RoleLord = 0x2;
    const Role				RoleVassal = 0x4;

  }
}

#endif
