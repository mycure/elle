//
// ---------- header ----------------------------------------------------------
//
// project       8user
//
// license       infinit
//
// file          /home/mycure/infinit/applications/8user/User.hh
//
// created       julien quintard   [sat mar 27 08:37:14 2010]
// updated       julien quintard   [wed may  5 21:46:08 2010]
//

#ifndef USER_USER_HH
#define USER_USER_HH

//
// ---------- includes --------------------------------------------------------
//

#include <Infinit.hh>
#include <elle/Elle.hh>
#include <lune/Lune.hh>
#include <etoile/Etoile.hh>

#include <elle/idiom/Close.hh>
# include <sys/stat.h>
#include <elle/idiom/Open.hh>

namespace application
{

//
// ---------- classes ---------------------------------------------------------
//

  ///
  /// this class implements the 8user application.
  ///
  class User
  {
  public:
    //
    // enumerations
    //
    enum Operation
      {
	OperationUnknown = 0,

	OperationCreate,
	OperationDestroy,
	OperationInformation
      };

    //
    // static methods
    //
    static elle::Status		Create(const elle::String&);
    static elle::Status		Destroy(const elle::String&);
    static elle::Status		Information(const elle::String&);
  };

}

#endif
