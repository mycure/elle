//
// ---------- header ----------------------------------------------------------
//
// project       nucleus
//
// license       infinit
//
// author        julien quintard   [thu mar  5 16:04:08 2009]
//

#ifndef NUCLEUS_NEUTRON_OBJECT_HH
#define NUCLEUS_NEUTRON_OBJECT_HH

//
// ---------- includes --------------------------------------------------------
//

#include <elle/Elle.hh>

#include <nucleus/proton/Address.hh>
#include <nucleus/proton/ImprintBlock.hh>
#include <nucleus/proton/Version.hh>

#include <nucleus/neutron/Genre.hh>
#include <nucleus/neutron/Author.hh>
#include <nucleus/neutron/Size.hh>
#include <nucleus/neutron/Permissions.hh>
#include <nucleus/neutron/Token.hh>
#include <nucleus/neutron/Attributes.hh>
#include <nucleus/neutron/Access.hh>
#include <nucleus/neutron/Role.hh>

namespace nucleus
{
  namespace neutron
  {

//
// ---------- classes ---------------------------------------------------------
//

    ///
    /// this class is the most important of the whole Infinit project
    /// as it describes file system objects being files, directories and
    /// references.
    ///
    /// an object can rely on several physical constructors such as an
    /// ImprintBlock, an OwnerKeyBlock or else.
    ///
    /// basically, an object contains the author i.e the user having performed
    /// the latest modification along with the address of the Access block
    /// which contains the set of authorised users and groups. note however
    /// than most objects do not reference an access block in which cases
    /// the object is considered private i.e only its owner has access.
    ///
    /// in addition, several meta information are contained such as the
    /// owner permissions, some stamps, the attributes etc.
    ///
    /// finally, the data section contains the address of the object's
    /// contents though the nature of the contents depends upon the
    /// object's nature: file, directory or reference.
    ///
    /// noteworthy is tha meta.owner._record is generated in order to
    /// make it as easy to manipulate the owner entry as for other access
    /// records. thus, this attribute is never serialized.
    ///
    class Object:
      public proton::ImprintBlock
    {
    public:
      //
      // constructors & destructors
      //
      Object();

      //
      // methods
      //
      elle::Status	Create(const Genre,
			       const elle::PublicKey&);

      elle::Status	Update(const Author&,
			       const proton::Address&,
			       const Size&);
      elle::Status	Administrate(const Attributes&,
				     const proton::Address&,
				     const Permissions&,
				     const Token&);

      elle::Status	Seal(const elle::PrivateKey&,
			     const Access* = NULL);

      elle::Status	Validate(const proton::Address&,
				 const Access* = NULL) const;

      //
      // interfaces
      //

      // object
      declare(Object);

      // dumpable
      elle::Status	Dump(const elle::Natural32 = 0) const;

      // archivable
      elle::Status	Serialize(elle::Archive&) const;
      elle::Status	Extract(elle::Archive&);

      //
      // attributes
      //
      Author			author;

      struct
      {
	// XXX to implement: proton::Base		base;

	struct
	{
	  Permissions		permissions;
	  Token			token;

	  Record		_record;
	}			owner;

	Genre			genre;
	elle::Time		stamp;

	Attributes		attributes;

	proton::Address		access;

	proton::Version		version;
	elle::Signature		signature;

	proton::State		_state;
      }				meta;

      struct
      {
	// XXX to implement: proton::Base		base;

	proton::Address		contents;

	Size			size;
	elle::Time		stamp;

	proton::Version		version;
	elle::Signature		signature;

	proton::State		_state;
      }				data;
    };

  }
}

#endif
